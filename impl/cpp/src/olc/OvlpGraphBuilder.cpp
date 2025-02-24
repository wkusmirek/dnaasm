/**
 * \file OvlpGraphBuilder.cpp
 * \brief the C++ file with definition of class for Overlap Graph Builder
 *
 */

#include "../common/log.hpp"

#include "OvlpGraphBuilder.hpp"

namespace dnaasm {
    namespace olc {
        OverlapGraph
        OvlpGraphBuilder::buildGraph(unsigned short kMerLength, unsigned short sketchNum,
                                     float minJaccardSim,
                                     unsigned short minEdge, mt4cpp::Progress *progress) {
            logInfo("Creating overlap graph with parameters:");
            logInfo("Number of Reads : " + std::to_string(reads_.size()));
            logInfo("K-mer length : " + std::to_string(kMerLength));
            logInfo("Sketch number : " + std::to_string(sketchNum));
            logInfo("Min Jaccard similarity : " + std::to_string(minJaccardSim));
            logInfo("Creating read sketches...");

            std::size_t numOfReads = reads_.size();
            PermutationVector permutations;
            size_t randNumGenSeed = 1U;
            MinHash::initialize(randNumGenSeed, sketchNum, permutations);
            std::vector<MinHash> hashVector(numOfReads, sketchNum);
            OverlapGraph ovlpGraph(numOfReads);

            for (size_t i = 0U; i < numOfReads; ++i) {
                loadKmersToMinHash(hashVector[i], reads_[i], kMerLength, permutations);
            }

            logInfo("Read sketches sucessfully created.");
            logInfo("Inserting vertices and edges for similar sketch pairs.");

            if (progress != nullptr) { progress->setProgress(0.34); }
            //std::size_t cnt1 = 0U, cnt2 = 0U;

            //Insert edges as v1 <-> v2 overlaps
            for (size_t v1 = 0; v1 < numOfReads; ++v1) {
                for (size_t v2 = (v1 + 1); v2 < numOfReads; ++v2) {
                    if (hashVector[v1].estJaccardSimilarity(hashVector[v2]) >= minJaccardSim) {
                        //++cnt1;
                        //stupid and unreadable -> fix this syntactic 'sugar' later
//                        auto result = aligner_->operator()(reads_[v1], reads_[v2]);
//
//                        if (result.score >= minEdge) {
//                            auto weight = EdgeProperty(result.score);
//                            ++cnt2;
//                            if (result.orient == Orientation::RL) {
//                                boost::add_edge(v2, v1, weight, ovlpGraph);
//                            } else {
//                                // EQ and LR
//                                boost::add_edge(v1, v2, weight, ovlpGraph);
//                            }
//                        }
                    }
                }

                //Deallocate unnecessary read sketches
                hashVector[v1].clear();
//
//            //Only for bad debugging practice
//            //logInfo("Finished " + std::to_string(v1));
            }

            std::cout << "From all " << numOfReads * (numOfReads - 1) / 2 << " possible edges\n";
//            std::cout << cnt1 << " have passed through a MinHash filter\n";
//            std::cout << cnt2 << " have passed through a Smith-Waterman alignment\n";
//
            logInfo("Overlap graph build process has been completed.");

            return ovlpGraph;
        }

        void OvlpGraphBuilder::loadKmersToMinHash(MinHash &minHash,
                                                  const LongRead &read,
                                                  const size_t kMerLength,
                                                  const PermutationVector &permutations) {
            auto kmerCount = read.length() - kMerLength + 1;

            for (size_t i = 0; i < kmerCount; ++i) {
                minHash.update(read.substr(i, kMerLength), i, hashObj_, permutations);
            }
        }

        OvlpGraphBuilder::~OvlpGraphBuilder() {}

    }
} //namespace dnaasm::olc
