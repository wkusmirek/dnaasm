#include <algorithm>

#include <boost/numeric/ublas/io.hpp>
#include <boost/math/special_functions/sign.hpp>
#include "../common/common.hpp"

#include "SmithWatermanAligner.hpp"
#include <iostream>

namespace dnaasm {
    namespace olc {
        SmithWatermanAligner::SmithWatermanAligner(int32_t matchScore, int32_t mismatchScore,
                                                   int32_t gapScore)
                : MatrixSize_(15000), matchScore_(matchScore), mismatchScore_(mismatchScore),
                  gapScore_(gapScore), scoreMatrix_(MatrixSize_, ScoreRow(MatrixSize_, 0)),
                  dirMatrix_(MatrixSize_, DirRow(MatrixSize_, Directions::NONE)) {
            cache_ = {
                    {Directions::NONE, 0},
                    {Directions::LEFT, 0},
                    {Directions::LEFTUP, 0},
                    {Directions::UP, 0}
            };
        }

        inline Orientation
        SmithWatermanAligner::getOrientation(uint32_t ind1, uint32_t ind2) const {
            int32_t diff = static_cast<int32_t>(ind1) - static_cast<int32_t>(ind2);
            return static_cast<Orientation>(boost::math::sign(diff));
        }

        inline int32_t SmithWatermanAligner::similarityScore(char a, char b) const {
            return (a == b) ? matchScore_ : mismatchScore_;
        }

        LocalAlignment SmithWatermanAligner::operator()(const LongRead &lhs, const LongRead &rhs) {
            //clean up functor cache
            std::for_each(cache_.begin(), cache_.end(), [](auto &entry) { entry.second = 0; });
            scoreMatrix_[0][0] = 0;
            dirMatrix_[0][0] = Directions::NONE;

            //for (uint32_t i = 1; i <= lhs.length(); ++i) {
                //scoreMatrix_[i][0] = 0;
                //dirMatrix_[i][0] = Directions::NONE;
            //}

            //for (uint32_t j = 1; j <= rhs.length(); ++j) {
                //scoreMatrix_[0][j] = 0;
                //dirMatrix_[0][j] = Directions::NONE;
            //}

            uint32_t maxI = 0, maxJ = 0;
            int32_t maxScore = 0;
            /*
             * Fill up scoring matrix
             */
            for (uint32_t i = 1; i <= lhs.length(); ++i) {
                for (uint32_t j = 1; j <= rhs.length(); ++j) {
                    //cases:
                    //max score is negative
                    // cache_[NONE] = 0;
                    //gap in rhs
                    cache_[LEFT] = scoreMatrix_[i - 1][j] + gapScore_;
                    //gap in lhs
                    cache_[UP] = scoreMatrix_[i][j - 1] + gapScore_;
                    //match or mismatch
                    cache_[LEFTUP] =
                            scoreMatrix_[i - 1][j - 1] + similarityScore(lhs[i - 1], rhs[j - 1]);

                    //choose best option
                    auto maxElem = std::max_element(cache_.begin(), cache_.end(),
                                                    [](const auto &lhs, const auto &rhs) {
                                                        return lhs.second < rhs.second;
                                                    });

                    scoreMatrix_[i][j] = maxElem->second;
                    //direction is needed for traceback
                    dirMatrix_[i][j] = maxElem->first;

                    //for traceback
                    if (scoreMatrix_[i][j] >= maxScore) {
                        maxScore = scoreMatrix_[i][j];
                        maxI = i;
                        maxJ = j;
                    }
                }
            }

            /*
             * Traceback to determine order of reads
             */
            uint32_t i = maxI; //begin of right seq on left seq
            uint32_t j = maxJ; //begin of left seq on right seq

            while (i > 0 and j > 0) {
                switch (dirMatrix_[i][j]) {
                    case LEFT:
                        --i;
                        break;
                    case UP:
                        --j;
                        break;
                    case LEFTUP:
                    default:
                        --i;
                        --j;
                        break;
                }
            }

            return LocalAlignment(getOrientation(i, j), maxScore);
        }

    }
} //namespace dnaasm::olc
