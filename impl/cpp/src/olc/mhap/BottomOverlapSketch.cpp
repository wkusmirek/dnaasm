#include "BottomOverlapSketch.hpp"
#include <algorithm>
#include <cmath>
#include <numeric>
#include "HashUtils.hpp"

namespace dnaasm {
    namespace olc {
        namespace mhap {
            BottomOverlapSketch::BottomOverlapSketch(const std::string &seq, int32_t kmerSize, int32_t sketchSize,
                                                     bool doReverseCompliment)
                    : kmerSize_(kmerSize), seqLength_(seq.size() - kmerSize + 1) {
                std::vector<int32_t> hashes(HashUtils::computeSequenceHashes(seq, kmerSize, doReverseCompliment));

                std::vector<int32_t> perm(hashes.size());
                std::iota(perm.begin(), perm.end(), 0);

                //ugly c++14 workaround for c++17 as_const
                std::sort(perm.begin(), perm.end(), [&hashes](auto lhs, auto rhs) {
                    return hashes[lhs] < hashes[rhs];
                });

                auto k = std::min(sketchSize, static_cast<int32_t>(hashes.size()));

                orderedHashes_ = std::vector<std::vector<int32_t >>(k, std::vector<int32_t>(2));

                for (size_t i = 0; i < orderedHashes_.size(); ++i) {
                    int32_t index = perm[i];
                    orderedHashes_[i][0] = hashes[index];
                    orderedHashes_[i][1] = index;
                }
            }

            double BottomOverlapSketch::jaccardToIdentity(double score, int32_t kmerSize) {
                double d = -1.0 / static_cast<double>(kmerSize) * std::log(2.0 * score / (1.0 + score));
                return std::exp(-d);
            }

            OverlapInfo BottomOverlapSketch::getOverlapInfo(BottomOverlapSketch &toSequence, double maxPercentShift) {
                if (kmerSize_ != toSequence.kmerSize_) {
                    throw std::runtime_error("Sketch k-mer size does not match between the two sequences.");
                }

                MatchData matchData(*this, toSequence, maxPercentShift);
                recordMatchingKmers(matchData, orderedHashes_, toSequence.orderedHashes_, 0);

                if (matchData.isEmpty()) {
                    return OverlapInfo(); //EMPTY
                }

                //get matches again, but now in a better region
                recordMatchingKmers(matchData, orderedHashes_, toSequence.orderedHashes_, 1);

                if (matchData.isEmpty()) {
                    return OverlapInfo(); //EMPTY
                }

                matchData.optimizeShifts();

                if (matchData.isEmpty()) {
                    return OverlapInfo(); //EMPTY
                }

                auto edgeData = matchData.computeEdges();

                //TODO: handle edgeData as null

                double score = computeKBottomSketchJaccard(orderedHashes_,
                                                           toSequence.orderedHashes_,
                                                           matchData.getMedianShift(),
                                                           matchData.getAbsMaxShift(),
                                                           edgeData.a1,
                                                           edgeData.a2,
                                                           edgeData.b1,
                                                           edgeData.b2);

                score = jaccardToIdentity(score, kmerSize_);
                double rawScore = static_cast<double>(edgeData.count);

                return OverlapInfo(score, rawScore, edgeData.a1, edgeData.a2, edgeData.b1, edgeData.b2);
            }

            void BottomOverlapSketch::recordMatchingKmers(MatchData &matchData,
                                            std::vector<std::vector<int32_t >> &seq1KmerHashes,
                                            std::vector<std::vector<int32_t >> &seq2KmerHashes,
                                            int repeat) {
                // init the loop storage
                int32_t hash1;
                int32_t hash2;
                int32_t pos1;
                int32_t pos2;

                // init the borders
                int32_t medianShift = matchData.getMedianShift();
                int32_t absMaxShift = matchData.getAbsMaxShift();
                int32_t valid1Lower = matchData.valid1Lower();
                int32_t valid2Lower = matchData.valid2Lower();
                int32_t valid1Upper = matchData.valid1Upper();
                int32_t valid2Upper = matchData.valid2Upper();

                // init counters
                size_t i1 = 0;
                size_t i2 = 0;

                //reset the data, redo the shifts
                matchData.reset();
                // perform merge operation to get the shift and the kmer count
                while (true) {
                    if (i1 >= seq1KmerHashes.size())
                        break;
                    if (i2 >= seq2KmerHashes.size())
                        break;

                    // get the values in the array
                    hash1 = seq1KmerHashes[i1][0];
                    pos1 = seq1KmerHashes[i1][1];
                    hash2 = seq2KmerHashes[i2][0];
                    pos2 = seq2KmerHashes[i2][1];

                    if (hash1 < hash2 || pos1 < valid1Lower || pos1 >= valid1Upper)
                        i1++;
                    else if (hash2 < hash1 || pos2 < valid2Lower || pos2 >= valid2Upper)
                        i2++;
                    else {
                        // check if current shift makes sense positionally
                        int32_t currShift = pos2 - pos1;
                        int32_t diffFromExpected = currShift - medianShift;
                        if (diffFromExpected > absMaxShift)
                            i1++;
                        else if (diffFromExpected < -absMaxShift)
                            i2++;
                        else {
                            //record match
                            matchData.recordMatch(pos1, pos2, currShift);

                            //we need to create symmetry for reverse compliment, so we will look at first and last matches

                            //move the index to last point of same hash
                            size_t i1Last = i1;
                            size_t i1Try = i1 + 1;
                            if (i1Try < seq1KmerHashes.size()) {
                                int32_t hash1Try = seq1KmerHashes[i1Try][0];
                                int32_t pos1Try = seq1KmerHashes[i1Try][1];
                                while ((hash1Try == hash1 && pos1Try >= valid1Lower && pos1Try < valid1Upper)) {
                                    i1Last = i1Try;

                                    i1Try++;
                                    if (i1Try >= seq1KmerHashes.size())
                                        break;

                                    hash1Try = seq1KmerHashes[i1Try][0];
                                    pos1Try = seq1KmerHashes[i1Try][1];
                                }
                            }

                            //move the index to last point of same hash
                            size_t i2Last = i2;
                            size_t i2Try = i2 + 1;
                            if (i2Try < seq2KmerHashes.size()) {
                                int32_t hash2Try = seq2KmerHashes[i2Try][0];
                                int32_t pos2Try = seq2KmerHashes[i2Try][1];
                                while ((hash2Try == hash2 && pos2Try >= valid2Lower && pos2Try < valid2Upper)) {
                                    i2Last = i2Try;
                                    i2Try++;
                                    if (i2Try >= seq2KmerHashes.size())
                                        break;

                                    hash2Try = seq2KmerHashes[i2Try][0];
                                    pos2Try = seq2KmerHashes[i2Try][1];
                                }
                            }

                            //store the match and update the counters
                            if (i1 != i1Last || i2 != i2Last) {
                                int32_t pos1New = seq1KmerHashes[i1Last][1];
                                int32_t pos2New = seq2KmerHashes[i2Last][1];
                                matchData.recordMatch(pos1New, pos2New, pos2New - pos1New);
                                i1 = i1Last + 1;
                                i2 = i2Last + 1;
                            } else {
                                //simply move on if they don't match
                                i1++;
                                i2++;
                            }
                        }
                    }
                }
            }

            double BottomOverlapSketch::computeKBottomSketchJaccard(std::vector<std::vector<int32_t >> &seq1Hashes,
                                                      std::vector<std::vector<int32_t >> &seq2Hashes,
                                                      int32_t medianShift,
                                                      int32_t absMaxShiftInOverlap,
                                                      int32_t a1, int32_t a2, int32_t b1, int32_t b2) {
                //get k for first string
                int32_t s1 = 0;
                auto array1 = std::vector<std::vector<int32_t >>(seq1Hashes.size());

                for (size_t i = 0; i < seq1Hashes.size(); ++i) {
                    int32_t pos = seq1Hashes[i][1];
                    if (pos >= a1 && pos <= a2) {
                        array1[s1] = seq1Hashes[i];
                        s1++;
                    }
                }

                //get k for second string
                int32_t s2 = 0;
                auto array2 = std::vector<std::vector<int32_t >>(seq1Hashes.size());

                for (size_t j = 0; j < seq2Hashes.size(); j++) {
                    int32_t pos = seq2Hashes[j][1];
                    if (pos >= b1 && pos <= b2) {
                        array2[s2] = seq2Hashes[j];
                        s2++;
                    }
                }

                //compute k
                int32_t k = std::min(s1, s2);

                //empty has jaccard of 1
                if (k == 0)
                    return 0;

                //perform the k-bottom count
                int32_t i = 0;
                int32_t j = 0;
                int32_t intersectCount = 0;
                int32_t unionCount = 0;

                while (unionCount < k) {
                    if (array1[i][0] < array2[j][0])
                        i++;
                    else if (array1[i][0] > array2[j][0])
                        j++;
                    else {
                        intersectCount++;
                        i++;
                        j++;
                    }

                    unionCount++;
                }

                double score = (static_cast<double>(intersectCount) / static_cast<double>(k));

                return score;
            }
        }
    }
}