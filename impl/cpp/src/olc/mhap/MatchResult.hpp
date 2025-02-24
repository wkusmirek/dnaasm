#ifndef MATCHRESULT_HPP
#define MATCHRESULT_HPP

#include "OverlapInfo.hpp"
#include "SequenceId.hpp"
#include <algorithm>
#include <string>
#include <numeric>
#include <vector>

namespace dnaasm {
    namespace olc {
        namespace mhap {
            struct MatchResult {
                MatchResult(const SequenceId &fromId_, const SequenceId &toId_, OverlapInfo &overlap, int32_t fromLength_,
                            int32_t toLength_)
                        : fromId(fromId_), toId(toId_), fromLength(fromLength_), toLength(toLength_) {
                    a1 = fromId.isForward() ? overlap.a1 : fromLength - overlap.a2 - 1;
                    a2 = fromId.isForward() ? overlap.a2 : fromLength - overlap.a1 - 1;
                    b1 = toId.isForward() ? overlap.b1 : toLength - overlap.b2 - 1;
                    b2 = toId.isForward() ? overlap.b2 : toLength - overlap.b1 - 1;

                    rawScore = overlap.rawScore;

                    if (overlap.score > 1.0) {
                        score = 1.0;
                    } else {
                        score = overlap.score;
                    }
                }

                std::string toString() const {
                    auto stringList = {
                            fromId.getHeader(),
                            toId.getHeader(),
                            std::to_string(1.0 - score),
                            std::to_string(rawScore),
                            std::to_string(fromId.isForward() ? 0 : 1),
                            std::to_string(a1),
                            std::to_string(a2),
                            std::to_string(fromLength),
                            std::to_string(toId.isForward() ? 0 : 1),
                            std::to_string(b1),
                            std::to_string(b2),
                            std::to_string(toLength)
                    };

                    return std::accumulate(stringList.begin(), stringList.end(), std::string(" "));
                }

                SequenceId fromId;
                SequenceId toId;
                int32_t a1;
                int32_t a2;
                int32_t b1;
                int32_t b2;
                double score;
                double rawScore;
                int32_t fromLength;
                int32_t toLength;
            };
        }
    }
}
#endif //MATCHRESULT_HPP