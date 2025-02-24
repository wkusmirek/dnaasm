#ifndef MATCHDATA_HPP
#define MATCHDATA_HPP

#include <vector>
//#include "BottomOverlapSketch.hpp"
#include "EdgeData.hpp"
#include <cstdint>

#if defined(_MSC_VER) && (_MSC_VER >= 1800)
#include <algorithm>
#endif

namespace dnaasm {
    namespace olc {
        namespace mhap {
            class BottomOverlapSketch;

            class MatchData {
            private:
                int32_t absMaxShiftInOverlap_ = 0;
                int32_t count = 0;
                double maxShiftPercent_ = 0;
                int32_t medianShift = 0;
                bool needRecompute = false;
            public:
                std::vector<int32_t> posShift;
                std::vector<int32_t> pos1Index;
                std::vector<int32_t> pos2Index;
            private:
                int32_t seqLength1 = 0;
                int32_t seqLength2 = 0;
            public:
                MatchData(const BottomOverlapSketch &o1, const BottomOverlapSketch &o2, double maxShiftPercent);

                EdgeData computeEdges();

                int getAbsMaxShift() {
                    performUpdate();
                    return absMaxShiftInOverlap_;
                }

                int getMedianShift() {
                    performUpdate();
                    return medianShift;
                }

                bool isEmpty() {
                    return count <= 0;
                }

                void optimizeShifts();

            private:
                void performUpdate();

            public:
                void recordMatch(int32_t pos1, int32_t pos2, int32_t shift);

                void reset();

                int32_t size();

                int32_t valid1Lower() {
                    performUpdate();
                    int32_t valid = std::max(0, -getMedianShift() - getAbsMaxShift());

                    return valid;
                }

                int32_t valid1Upper() {
                    performUpdate();
                    int32_t valid = std::min(seqLength1, seqLength2 - getMedianShift() + getAbsMaxShift());

                    return valid;
                }

                int32_t valid2Lower() {
                    performUpdate();
                    int32_t valid = std::max(0, getMedianShift() - getAbsMaxShift());

                    return valid;
                }

                int32_t valid2Upper() {
                    performUpdate();
                    int32_t valid = std::min(seqLength2, seqLength1 + getMedianShift() + getAbsMaxShift());

                    return valid;
                }
            };
        }
    }
}

#endif //MATCHDATA_HPP