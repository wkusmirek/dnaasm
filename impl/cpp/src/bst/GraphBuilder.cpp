#include "GraphBuilder.hpp"

namespace dnaasm { namespace bst {

    GraphBuilder::GraphBuilder() {}

    void GraphBuilder::addEdgeToGraph(unsigned i, unsigned j, std::vector<S>& ov)
    {
        if(ov.size() < minimalAssociation_   ||
           boost::edge(i, j, *graph_).second ||
           boost::edge(j, i, *graph_).second)
        {
            ov.clear();
            return;
        }

        std::vector<S>& res = chainer_->genericChaining(ov);

        if(res.size() < minimalAssociation_)
        {
            ov.clear();
            return;
        }

        //std::cout << j << " (" <<  res.size() << ") ";

        unsigned s0 = res[res.size()-1].x,
                 s1 = res[res.size()-1].y,
                 e0 = res[0].x + wordLength_ - 1,
                 e1 = res[0].y + wordLength_ - 1;

        if(s0 < s1)
        {
            std::swap(s0, s1);
            std::swap(e0, e1);
            std::swap(i, j);
        }

        unsigned tScore = wordLength_;
        for(int i = res.size() - 2; i >= 0; i--)
        {
            tScore += (res[i+1].x + 1 == res[i].x) ? 1 : wordLength_;
        }

        float score = 2.0f * (float)tScore / (float)(e1 - s1 + e0 - s0 + 2);

        Association as(s0, s1, e0, e1, score);

        boost::add_edge(i, j, EP(as), *graph_);
        ov.clear();
    }

    void GraphBuilder::buildOverlapGraph(
                    unsigned minimalAssociation,
                    unsigned wordLength,
                    unsigned readsCount,
                    std::unique_ptr<std::vector<WordAssoc> []> associationTable)
    {
        minimalAssociation_ = minimalAssociation;
        wordLength_ = wordLength;
        readsCount_ = readsCount;
        associationTable_ = std::move(associationTable);
        chainer_ = std::make_unique<Chainer>();
        graph_ = std::make_unique<OverlapGraph>(readsCount);

        for(unsigned i = 0; i < readsCount_; i++)
        {
            std::vector<S> overlap;
            int seq = associationTable_[i][0].sequence();

            //std::cout << "Connection: " << i << std::endl;

            for(unsigned j = 0; j < associationTable_[i].size(); j++)
            {
                WordAssoc word = associationTable_[i][j];

                if(word.sequence() != seq)
                {
                    addEdgeToGraph(i, seq, overlap);
                    seq = word.sequence();
                }

                overlap.push_back(S(word.selfIndex(), word.index()));
            }

            addEdgeToGraph(i, seq, overlap);

            //std::cout << std::endl;
            if(i % 1000 == 0)
            {
                std::cout << "Building graph: " << i << std::endl;
            }
         }
    }

    void GraphBuilder::removeCycles()
    {
        using sizeType =  boost::graph_traits<OverlapGraph>::vertices_size_type;
        std::vector<sizeType> d(num_vertices(*graph_));
        std::vector<sizeType> f(num_vertices(*graph_));
        std::vector<OGEdge> edges;

        int t = 0;
        boost::depth_first_search(*graph_, boost::visitor(
            categorizeEdges(
                std::make_pair(
                    boost::stamp_times(&d[0], t, boost::on_discover_vertex()),
                    boost::stamp_times(&f[0], t, boost::on_finish_vertex())
                ),
                edges
            )
        ));

        unsigned i;
        for(i = 0; i < edges.size(); i++)
        {
            boost::remove_edge(edges[i], *graph_);
        }
        std::cout << "Removed edges: " << i << std::endl;
    }

    void GraphBuilder::removeTransitiveEdges()
    {
        removeCycles();
        removeCycles();

        OverlapGraph temp;
        std::map<OGVertex, OGVertex> vertMap;
        std::vector<unsigned> ids(boost::num_vertices(*graph_));
        std::iota(ids.begin(), ids.end(), 0u);
        boost::transitive_reduction(
            *graph_, temp, boost::make_assoc_property_map(vertMap), ids.data());

        auto result = std::make_unique<OverlapGraph>(readsCount_);

        auto assocs = get(&EP::assoc_, *graph_);
        auto edges = boost::edges(*graph_);

        for (auto it = edges.first; it != edges.second; ++it)
        {
            OGVertex source = boost::source(*it, *graph_);
            OGVertex target = boost::target(*it, *graph_);
            if(boost::edge(vertMap[source], vertMap[target], temp).second)
            {
                boost::add_edge(source, target, assocs[*it], *result);
            }
        }

        graph_ = std::move(result);
    }

    void GraphBuilder::deleteAssociationTable()
    {
        associationTable_.reset(nullptr);
    }

    Layout GraphBuilder::longestPath(unsigned current, Layout l)
    {
        auto edgeProperty = boost::get(&EP::assoc_, *graph_);
        auto outDegree = boost::out_degree(current, *graph_);

        while(outDegree == 1)
        {
            auto outEdge = boost::out_edges(current, *graph_).first;
            auto assoc = edgeProperty[*outEdge];

            //position of supposed start of alignment on First read
            unsigned offset = assoc.start0_ - assoc.start1_;

            l.emplace_back(current, offset);

            current = boost::target(*outEdge, *graph_);
            outDegree = boost::out_degree(current, *graph_);
        }

        if(outDegree == 0 || enough_)
        {
            l.emplace_back(current, 0);
            return l;
        }

        auto itPair = boost::out_edges(current, *graph_);
        std::vector<Layout> layouts;
        for(auto it = itPair.first; it != itPair.second; ++it)
        {
            auto assoc = edgeProperty[*it];

            //position of supposed start of alignment on First read
            unsigned offset = assoc.start0_ - assoc.start1_;

            Layout newLayout = l;
            auto newCurrent = boost::target(*it, *graph_);
            newLayout.emplace_back(current, offset);

            layouts.push_back(longestPath(newCurrent, newLayout));
        }

        unsigned maxSize = layouts[0].size(), index = 0;

        for(unsigned i = 1; i < layouts.size(); i++)
        {
            if(layouts[i].size() > maxSize)
            {
                maxSize = layouts[i].size();
                index = i;
            }
        }

        if(maxSize > maxFound_)
        {
            std::cout << "Length: " << maxSize << std::endl;
            maxFound_ = maxSize;
            iterations_ = 0;
        }

        iterations_++;
        if(iterations_ == 1000000)
        {
            enough_ = true;
            std::cout << std::endl;
        }
        if(iterations_ % 100000 == 0)
        {
            std::cout << " " << iterations_ / 100000 << std::endl;
        }

        return layouts[index];
    }

    std::vector<Layout> GraphBuilder::getLayouts()
    {
        std::vector<Layout> layouts;
        std::vector<unsigned> layoutBeginnings;

        unsigned i;
        for(i = 0; i < readsCount_; i++)
        {
            if(boost::in_degree(i, *graph_) == 0)
            {
                layoutBeginnings.push_back(i);
            }
        }

        //every layout
        for(unsigned i = 0; i < layoutBeginnings.size(); i++)
        {
            std::cout << "Layout " << i << ": " << std::endl;
            unsigned current = layoutBeginnings[i];

            Layout init;
            iterations_ = 0;
            maxFound_ = 0;
            enough_ = false;
            Layout layout = longestPath(current, init);

            if(layout.size() != 1)
            {
                layouts.push_back(layout);

                for(unsigned k = 1; k < layout.size(); k++)
                {
                    std::cout << "(" << layout[k - 1].first << ",";
                    std::cout << layout[k].first << ")" << std::endl;
                }
            }
        }
        return layouts;
    }

}}
