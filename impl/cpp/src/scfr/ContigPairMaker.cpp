/**
 * \file ContigPairMaker.cpp
 * \brief the C++ file with definition of Contig Pair Maker class
 *
 */

#include "ContigPairMaker.hpp"

namespace dnaasm { namespace scfr {

    ContigPairMaker::ContigPairMaker(MatepairGraph &matepairGraph,
                                     const ContigSeqHashMap &contigSeqs,
                                     ContigPairGraph &contigPairGraph,
                                     unsigned int insertSize,
                                     float stdDevOfDistance)
        : matepairGraph_(matepairGraph)
        , contigSeqs_(contigSeqs)
        , contigPairGraph_(contigPairGraph)
        , insertSize_(insertSize)
        , stdDevOfDistance_(stdDevOfDistance)
    {}

    void ContigPairMaker::pairContigs()
    {
        boost::graph_traits<MatepairGraphInternal>::edge_iterator ei, ei_end;
        boost::tie(ei, ei_end) = boost::edges(matepairGraph_.graph());

        for (; ei != ei_end; ++ei) {
            auto &v1 = matepairGraph_.graph()[source(*ei, matepairGraph_.graph())];
            auto &v2 = matepairGraph_.graph()[target(*ei, matepairGraph_.graph())];

            //if both kmers are unique on contigs
            if (v1.contigId_ != MatepairGraph::CONTIG_ID_FOR_NOT_UNIQUE_KMER
                && v2.contigId_ != MatepairGraph::CONTIG_ID_FOR_NOT_UNIQUE_KMER) {
                bool A_rev, B_rev;
                unsigned int contigId_A = v1.contigId_;
                unsigned int contigId_B = v2.contigId_;

                // if both k-mers in pair assembled
                // AND paired k-mers located on different contigs
                if ((contigId_A > 0 && contigId_B > 0) && (contigId_A != contigId_B)) {
                    auto A_length = (unsigned int) contigSeqs_.find(contigId_A)->second.size();
                    auto B_length = (unsigned int) contigSeqs_.find(contigId_B)->second.size();
                    unsigned int A_start = v1.start_;
                    unsigned int B_start = v2.start_;
                    unsigned int A_end = v1.end_;
                    unsigned int B_end = v2.end_;

                    if (A_start < A_end) {
                        if (B_start < B_end) {
                            // -> -> ::: A-> B->  /  rB-> rA->
                            A_rev = B_rev = false;
                        } else {
                            // -> <- ::: A-> rB->  / B-> rA->
                            A_rev = false;
                            B_rev = true;
                        }
                    } else {
                        if (B_start < B_end) {
                            // <- -> ::: rA-> B-> / rB-> A->
                            A_rev = true;
                            B_rev = false;;
                        } else {
                            // <- <- ::: rA-> rB-> / B-> A->
                            A_rev = B_rev = true;
                        }
                    }

                    pairTwoContigs(contigId_A, contigId_B,
                                   A_length, B_length,
                                   A_start, B_end,
                                   A_rev, B_rev, *ei);
                }
            }
        }
    }

    void ContigPairMaker::pairTwoContigs(
        unsigned int id1,
        unsigned int id2,
        unsigned int length1,
        unsigned int length2,
        unsigned int start1,
        unsigned int end2,
        bool rev1,
        bool rev2,
        Edge mpEdgeDesc)
    {
        // minDiff is minimal difference allowed on distance
        // (average distance between k-mers expected
        // to be found on contig is equal to insert size)
        float minDiff = -1 * stdDevOfDistance_ * insertSize_;

        start1 = rev1 ? length1 - start1 : start1;
        end2   = rev2 ? length2 - end2   : end2;

        std::string f1, r1, f2, r2;
        f1 = "f" + std::to_string(id1);
        r1 = "r" + std::to_string(id1);
        f2 = "f" + std::to_string(id2);
        r2 = "r" + std::to_string(id2);

        // calculate gap or overlap length between contigs
        int d = calculateGapOrOverlap(length1, start1, end2);

        if (d >= minDiff) {
            int cat = getDistanceCategory(d);
            MatepairGraphEdgeProperties &mpEp = matepairGraph_.graph()[mpEdgeDesc];
            unsigned int gapSeqOffset = mpEp.offset_ + length1 - start1;

            // create two contig pairs (directed edges in graph)
            // first pair (representing positive strand): (+/-)id1 -> (+/-)id2,
            // second pair (reverse strand): (-/+)id2 -> (-/+)id1
            // Mark gap seq. as reversed when source vertex of the edge being
            // created is reversed, i.e when read overlaps with reversed source
            // contig (reversed to the one in input file)
            createOrUpdatePair(rev1 ? r1 : f1,
                               rev2 ? r2 : f2,
                               cat, d, gapSeqOffset,
                               rev1,
                               mpEdgeDesc);
            createOrUpdatePair(rev2 ? f2 : r2,
                               rev1 ? f1 : r1,
                               cat, d, gapSeqOffset,
                               rev2,
                               mpEdgeDesc);
        }
    }

    void ContigPairMaker::createOrUpdatePair(
        std::string c1,
        std::string c2,
        int distCategory,
        int gapsIncrement,
        unsigned int gapSeqOffset,
        bool gapReversed,
        Edge mpEdgeDesc)
    {
        // add vertices or get descriptors of existing vertices
        // add_vertex defined in: boost/graph/labeled_graph.hpp
        auto v1 = boost::add_vertex(c1, c1, contigPairGraph_);
        auto v2 = boost::add_vertex(c2, c2, contigPairGraph_);

        auto parallelEdges = getAllParallelEdges(v1, v2, contigPairGraph_);

        // find existing edge with the same distance category
        auto it = std::find_if(parallelEdges.begin(), parallelEdges.end(),
            [this, &distCategory](auto & e_desc) {
                return  contigPairGraph_[e_desc].distance_ == (int16_t)distCategory;
        });

        // update if such edge exists
        if (it != parallelEdges.end()) {
            auto &edge = contigPairGraph_[*it];
            GapInfo gi(mpEdgeDesc, gapSeqOffset, gapsIncrement);

            gi.reversed_ = gapReversed;
            edge.bridges_.push_back(gi);
        }
        // or create new edge otherwise
        else {
            ContigPairGraphEdgeProperties ep((uint16_t) distCategory);
            GapInfo gi(mpEdgeDesc, gapSeqOffset, gapsIncrement);
            gi.reversed_ = gapReversed;
            ep.bridges_.push_back(gi);

            boost::add_edge(v1, v2, ep, contigPairGraph_);
        }
    }

    int ContigPairMaker::calculateGapOrOverlap(unsigned int lengthR1,
                                               unsigned int startK1,
                                               unsigned int endK2) const
    {
        // R1  ------  --------- R2
        // k1    ->        ->    k2
        //       ....  ......    insertSpan
        //       ============    insertSize

        int insertSpan = lengthR1 - startK1 + endK2;
        int gapOrOverlap = insertSize_ - insertSpan;
        return gapOrOverlap;
    }

    int ContigPairMaker::getDistanceCategory(int d) const
    {
        return d < 0 ? -1 : d < 500 ? 500 : d < 1000 ? 1000 : d < 5000 ? 5000 : 10000;
    }

}} //namespace dnaasm::scfr
