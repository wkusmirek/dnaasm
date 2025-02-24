#include "AssemblyManager.hpp"

namespace dnaasm { namespace bst {

    AssemblyManager::AssemblyManager(std::string readsFilePath,
                                     short wordLength = 12,
                                     short minimalWordCount = 6,
                                     short maximalWordCount = 40,
                                     short minimalAssociation = 20,
                                     short similarity = 1)
        : readsPath_(readsFilePath),
          wordLength_(wordLength),
          minimalAssociation_(minimalAssociation),
          similarity_(similarity),
          blast_(std::make_unique<Blast>(wordLength,
                                         minimalWordCount,
                                         maximalWordCount)),
          graphBuilder_(std::make_unique<GraphBuilder>()),
          totalTime_(0)
    {}

    void AssemblyManager::run()
    {
        tstart("Loading reads from file");
        {
            loadFastaReads();
        }
        tstop();

        tstart("Creating hashmap of words");
        {
            blast_->findWords(reads_);
        }
        tstop();
        tstart("Removing infrequent matches");
        {
            blast_->removeInfrequentMatches();
        }
        tstop();
        blast_->debug();
        tstart("Creating association table");
        {
            blast_->createAssociationTable();
            blast_->deleteWordsMap();
        }
        tstop();
        tstart("Sorting association table");
        {
            associationTable_ = blast_->sortAssociationTable();
        }
        tstop();
        tstart("Builing overlap graph");
        {
            graphBuilder_->buildOverlapGraph(minimalAssociation_,
                                             wordLength_,
                                             reads_.size(),
                                             std::move(associationTable_));
            graphBuilder_->deleteAssociationTable();
            graphBuilder_->removeTransitiveEdges();
        }
        tstop();

        using ReadLayout = std::vector<std::string>;
        using OffsetLayout = std::vector<unsigned>;
        std::vector<std::pair<ReadLayout, OffsetLayout>> allReadLayouts;

        tstart("Create layouts");
        {
            std::vector<Layout> allLayouts = graphBuilder_->getLayouts();
            for(Layout layout : allLayouts)
            {
                ReadLayout rl;
                OffsetLayout ol;
                for(auto readAssocPair : layout)
                {
                    rl.emplace_back(reads_[readAssocPair.first]);
                    ol.emplace_back(readAssocPair.second);
                }

                allReadLayouts.emplace_back(rl, ol);
            }
        }
        tstop();

        std::cout << "Found " << allReadLayouts.size() << " layouts" << std::endl;

        tstart("Consensus");
        std::ofstream ofs("res");

        for(unsigned i = 0; i < allReadLayouts.size(); i++)
        {
            std::cout << "Nr: " << i << " reads: " << allReadLayouts[i].first.size() << std::endl;

            Consensus c(similarity_);
            c.run(allReadLayouts[i].first);
            auto contig = c.toString();

            ofs << ">tig=" << i << " reads=" << allReadLayouts[i].first.size();
            ofs << " length=" << contig->size() << std::endl;
            ofs << *contig << std::endl;
        }
        ofs.close();
        tstop();

        std::cout << "Total time: " << totalTime_ << "ms" << std::endl;
    }

    void AssemblyManager::loadFastaReads()
    {
        std::ifstream in(readsPath_);
        const unsigned maxLength = 26;
        if(!in.is_open())
        {
            std::cout << "Can't open file " + readsPath_ << std::endl;
            exit(0);
        }

        int tab[maxLength] = {0};
        std::string buffer;
        while(getline(in, buffer)) {
            if(buffer[0] == '>' || buffer.size() >= 1000 * maxLength)
                continue;

            reads_.push_back(buffer);
            tab[buffer.size() / 1000]++;
        }

        for(unsigned i=0; i < maxLength; i++)
        {
            std::cout << i * 1000 << "-" << i * 1000 + 999;
            std::cout << ": " << tab[i] << std::endl;
        }

        std::cout << "Reads count: " << reads_.size() << std::endl;
        in.close();
    }

    void AssemblyManager::tstart(std::string info)
    {
        std::cout << info << "... " << std::flush;
        start = std::chrono::system_clock::now();
    }

    void AssemblyManager::tstop()
    {
        int tstamp = std::chrono::duration_cast<std::chrono::milliseconds>
            (std::chrono::system_clock::now() - start).count();
        totalTime_ += tstamp;
        std::cout << tstamp << "ms"<< std::endl;
    }
}}
