#include "MatchData.hpp"
#include "BottomOverlapSketch.hpp"

#include <algorithm>
#include <limits>
#include <cmath>

namespace dnaasm {
    namespace olc {
        namespace mhap {
            MatchData::MatchData(const BottomOverlapSketch &o1, const BottomOverlapSketch &o2, double maxShiftPercent)
                    : maxShiftPercent_(maxShiftPercent)
                    , posShift(std::max(o1.size(), o2.size())/4 + 1)
                    , pos1Index(posShift.size())
                    , pos2Index(posShift.size())
                    , seqLength1(o1.getSequenceLength())
                    , seqLength2(o2.getSequenceLength()) {
                reset();
            }

            EdgeData MatchData::computeEdges() {
                // storage for edge computation
                int32_t leftEdge1 = std::numeric_limits<int32_t>::max();
                int32_t leftEdge2 = std::numeric_limits<int32_t>::max();
                int32_t rightEdge1 = std::numeric_limits<int32_t>::max();
                int32_t rightEdge2 = std::numeric_limits<int32_t>::max();

                // count only the shifts in the correct place
                int32_t validCount = 0;
                int32_t medianShift = getMedianShift();
                int32_t absMaxShiftInOverlap = getAbsMaxShift();
                int32_t count = size();

                for (int32_t iter = 0; iter < count; ++iter) {
                    int32_t pos1 = pos1Index[iter];
                    int32_t pos2 = pos2Index[iter];

                    // take only valid values
                    if (std::abs(posShift[iter] - medianShift) > absMaxShiftInOverlap)
                        continue;

                    // get the edges
                    if (pos1 < leftEdge1)
                        leftEdge1 = pos1;
                    if (pos2 < leftEdge2)
                        leftEdge2 = pos2;
                    if (pos1 > rightEdge1)
                        rightEdge1 = pos1;
                    if (pos2 > rightEdge2)
                        rightEdge2 = pos2;

                    ++validCount;
                }

                //TODO: handle this case
//                if (validCount < 3)
//                    return null;

                // get edge info uniformly minimum variance unbiased (UMVU) estimators
                // a = (n*a-b)/(n-1)
                // b = (n*b-a)/(n-1)
                int32_t a1 = std::max(0, static_cast<int32_t>(std::round(
                        static_cast<double>(validCount * leftEdge1 - rightEdge1) /
                        static_cast<double> (validCount - 1))));
                int32_t a2 = std::min(seqLength1, static_cast<int32_t>(std::round(
                        static_cast<double> (validCount * rightEdge1 - leftEdge1) /
                        static_cast<double> (validCount - 1))));
                int32_t b1 = std::max(0, static_cast<int32_t>(std::round(
                        static_cast<double> (validCount * leftEdge2 - rightEdge2) /
                        static_cast<double> (validCount - 1))));
                int32_t b2 = std::min(seqLength2, static_cast<int32_t>(std::round(
                        static_cast<double> (validCount * rightEdge2 - leftEdge2) /
                        static_cast<double> (validCount - 1))));

                return EdgeData(a1, a2, b1, b2, validCount);
            }

            void MatchData::optimizeShifts() {
                if (isEmpty())
                    return;

                int32_t reducedCount = -1;

                // copy over only the best values
                int32_t medianShift = getMedianShift();
                for (int32_t iter = 0; iter < count; ++iter) {
                    if (reducedCount >= 0 && pos1Index[reducedCount] == pos1Index[iter]) {
                        // if better, record it
                        if (std::abs(posShift[reducedCount] - medianShift) >
                            std::abs(posShift[iter] - medianShift)) {
                            pos1Index[reducedCount] = pos1Index[iter];
                            pos2Index[reducedCount] = pos2Index[iter];
                            posShift[reducedCount] = posShift[iter];
                        }
                    } else {
                        // add the new data
                        reducedCount++;
                        pos1Index[reducedCount] = pos1Index[iter];
                        pos2Index[reducedCount] = pos2Index[iter];
                        posShift[reducedCount] = posShift[iter];
                    }
                }

                count = reducedCount + 1;
                needRecompute = true;
            }

            void MatchData::performUpdate() {
                if (needRecompute) {
                    if (count > 0) {
                        auto copyPosShift(posShift);

                        std::nth_element(copyPosShift.begin(), copyPosShift.begin() + copyPosShift.size() / 2,
                                         copyPosShift.end());
                        medianShift = copyPosShift[copyPosShift.size() / 2];
                        //copy not needed anymore
                        copyPosShift.clear();

                        // get the actual overlap size
                        int32_t leftPosition = std::max(0, -medianShift);
                        int32_t rightPosition = std::min(seqLength1, seqLength2 - medianShift);
                        int32_t overlapSize = std::max(10, rightPosition - leftPosition);

                        // compute the max possible allowed shift in kmers
                        absMaxShiftInOverlap_ = std::min(std::max(seqLength1, seqLength2),
                                                        static_cast<int32_t>(static_cast<double>(overlapSize *
                                                                                             maxShiftPercent_)));
                    } else {
                        medianShift = 0;
                        absMaxShiftInOverlap_ = std::max(seqLength1, seqLength2) + 1;
                    }
                }

                needRecompute = false;
            }

            void MatchData::recordMatch(int32_t pos1, int32_t pos2, int32_t shift) {
                // adjust array size if needed
                if (static_cast<int32_t>(posShift.size()) <= count) {
                    //reserve twice much memory
//                    posShift = Arrays.copyOf(this.posShift, this.posShift.length * 2);
//                    pos1Index = Arrays.copyOf(this.pos1Index, this.pos1Index.length * 2);
//                    pos2Index = Arrays.copyOf(this.pos2Index, this.pos2Index.length * 2);
                }

                posShift[count] = shift;
                pos1Index[count] = pos1;
                pos2Index[count] = pos2;

                ++count;
                needRecompute = true;
            }

            void MatchData::reset() {
                count = 0;
                needRecompute = true;
            }

            int32_t MatchData::size() {
                return count;
            }
        }
    }
}