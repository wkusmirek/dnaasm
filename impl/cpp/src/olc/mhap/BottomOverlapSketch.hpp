#ifndef BOTTOMOVERLAPSKETCH_HPP
#define BOTTOMOVERLAPSKETCH_HPP


#include "OverlapInfo.hpp"
#include "MatchData.hpp"
#include <string>

namespace dnaasm {
    namespace olc {
        namespace mhap {

            class BottomOverlapSketch {
            public:
                BottomOverlapSketch(const std::string &seq, int32_t kmerSize, int32_t sketchSize,
                                    bool doReverseCompliment);

                size_t size() const { return orderedHashes_.size(); }

                int32_t getSequenceLength() const { return seqLength_; }

                OverlapInfo getOverlapInfo(BottomOverlapSketch &toSequence, double maxPercentShift);

                static double jaccardToIdentity(double score, int32_t kmerSize);

            private:
                int32_t kmerSize_;
                int32_t seqLength_;
                std::vector<std::vector<int32_t >> orderedHashes_;

                static void recordMatchingKmers(MatchData &matchData,
                                                std::vector<std::vector<int32_t >> &seq1KmerHashes,
                                                std::vector<std::vector<int32_t >> &seq2KmerHashes,
                                                int repeat);

                static double computeKBottomSketchJaccard(std::vector<std::vector<int32_t >> &seq1Hashes,
                                                          std::vector<std::vector<int32_t >> &seq2Hashes,
                                                          int32_t medianShift,
                                                          int32_t absMaxShiftInOverlap,
                                                          int32_t a1, int32_t a2, int32_t b1, int32_t b2);
            };
        }
    }
}
#endif /* BOTTOMOVERLAPSKETCH_HPP */
