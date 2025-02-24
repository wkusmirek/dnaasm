#include "MinHashSearch.hpp"

namespace dnaasm {
    namespace olc {
        namespace mhap {
            MinHashSearch::MinHashSearch(SequenceSketchStreamer &data, int32_t numHashes,
                                         int32_t numMinMatches, int32_t numThreads, bool storeResults,
                                         int32_t minStoreLength, double maxShift, double acceptScore,
                                         bool doReverseCompliment)
                    :  numMinMatches_(numMinMatches), minStoreLength_(minStoreLength), acceptScore_(acceptScore), hashes_(numHashes),
                      sequenceVectorsHash_(data.getNumberProcessed()) {

                data.enqueueFullFile(false);
                //seems to be unnecessary init
//                for (int iter = 0; iter < numHashes; ++iter) {
//                    hashes_[iter] = Int2ObjectOpenHashMap
//                }
                addData(data, doReverseCompliment);
            }

            bool MinHashSearch::addSequence(SequenceSketch &currHash) {
                auto &currMinHashes = currHash.getMinHashes().getMinHashArray();

                if (currMinHashes.size() != hashes_.size()) {
                    throw std::runtime_error("Number of MinHashes of the sequence does not match current settings.");
                }

                sequenceVectorsHash_.emplace(currHash.getSequenceId(), currHash);
                //TODO: maybe check return iterator?

                int32_t count = 0;

                const auto &id = currHash.getSequenceId();

                for (auto &hash : hashes_) {
                    //std::vector<SequenceId> currList;
                    int32_t hashVal = currMinHashes[count];

                    if (hash.find(hashVal) == hash.end()) {
                        hash.emplace(hashVal, std::vector<SequenceId>());
                    }

                    //currList.emplace_back(id);

                    hash[hashVal].emplace_back(id);

                    ++count;
                }

                //increase counter
                return true;
            }

            std::deque<SequenceId> MinHashSearch::getStoredForwardSequenceIds() {
                std::deque<SequenceId> seqIds;

                for (auto hash : sequenceVectorsHash_) {
                    if (hash.second.getSequenceId().isForward()) {
                        seqIds.emplace_back(hash.second.getSequenceId());
                    }
                }

                return seqIds;
            }

            SequenceSketch MinHashSearch::getStoredSequenceHash(SequenceId &id) {
                return sequenceVectorsHash_.find(id)->second;
            }

            std::vector<MatchResult>
            MinHashSearch::findMatches(SequenceSketch &seqHashes, bool toSelf) {
                auto minHash = seqHashes.getMinHashes();

                std::unordered_map<SequenceId, HitCounter, SequenceIdHash> bestSequenceHit;
                auto &minHashes = minHash.getMinHashArray();

                int hashIndex = 0;
                int64_t additionalProcessed = 0L;

                for (auto &currHash : hashes_) {
                    auto currentHashMatchList = currHash.find(minHashes[hashIndex]);

                    if (currentHashMatchList != currHash.end()) {
                        additionalProcessed += currentHashMatchList->second.size();

                        for (const auto &sequenceId : currentHashMatchList->second) {
                            //bestSequenceHit.compute
                            if (bestSequenceHit.find(sequenceId) != bestSequenceHit.end()) {
                                bestSequenceHit[sequenceId].addHit();
                            } else {
                                bestSequenceHit[sequenceId] = HitCounter(1);
                            }

                        }
                        ++hashIndex;
                    }
                }

                std::vector<MatchResult> matches;

                for (auto &match : bestSequenceHit) {
                    auto &matchId = match.first;

                    if (toSelf && matchId.getHeaderId() == seqHashes.getSequenceId().getHeaderId()) {
                        continue;
                    }

                    if (match.second.count >= numMinMatches_) {
                        auto matchedHashes = sequenceVectorsHash_.find(match.first);

                        if (matchedHashes == sequenceVectorsHash_.end()) {
                            //TODO: make code exception free in order to speed up
                            throw std::runtime_error("Hashes not found for given id.");
                        }

                        if (matchedHashes->second.getSequenceLength() < minStoreLength_ &&
                            seqHashes.getSequenceLength() < minStoreLength_) {
                            continue;
                        }

                        if (toSelf
                            && matchId.getHeaderId() > seqHashes.getSequenceId().getHeaderId()
                            && matchedHashes->second.getSequenceLength() >= minStoreLength_
                            && seqHashes.getSequenceLength() >= minStoreLength_) {
                            continue;
                        }

                        if (toSelf
                            && matchedHashes->second.getSequenceLength() < minStoreLength_
                            && seqHashes.getSequenceLength() >= minStoreLength_) {
                            continue;
                        }

                        auto result = seqHashes.getOrderedHashes().getOverlapInfo(
                                matchedHashes->second.getOrderedHashes(),
                                maxShift);
                        bool accept = result.score >= acceptScore_;

                        if (accept) {
                            auto currResult = MatchResult(seqHashes.getSequenceId(), matchId, result,
                                                          seqHashes.getSequenceLength(),
                                                          matchedHashes->second.getSequenceLength());
                            matches.emplace_back(currResult);
                        }

                        //TODO:
                        //search time stuff here
                    }
                }
                return matches;
            }

        }
    }
}