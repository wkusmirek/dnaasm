#ifndef OVERLAPINFO_HPP
#define OVERLAPINFO_HPP

#include <cstdint>

namespace dnaasm {
    namespace olc {
        namespace mhap {
            struct OverlapInfo {
                OverlapInfo(double score_, double rawScore_, int32_t a1_, int32_t a2_, int32_t b1_, int32_t b2_)
                        : score(score_), rawScore(rawScore_), a1(a1_), a2(a2_), b1(b1_), b2(b2_) {}

                OverlapInfo() : OverlapInfo(0.0, 0.0, 0, 0, 0, 0) {}

                double score;
                double rawScore;
                int32_t a1;
                int32_t a2;
                int32_t b1;
                int32_t b2;
            };
        }
    }
}
#endif //OVERLAPINFO_HPP