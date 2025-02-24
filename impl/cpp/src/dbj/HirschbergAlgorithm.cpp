/**
 * \file HirschbergAlgorithm.cpp
 * \brief the C++ file with implementation of class for Hirschberg's algorithm (to align two sequences)
 *
 */

#include <limits>
#include "HirschbergAlgorithm.hpp"
#include "NeedlemanWunschAlgorithm.hpp"

using namespace std;

namespace dnaasm { namespace dbj {

    HirschbergAlgorithm::HirschbergAlgorithm(short int d,
                                             short int (&substitutionMatrix)[4][4],
                                             mt4cpp::Progress* progress,
                                             unsigned int numOfAlignedSequences,
                                             unsigned int numOfSequences)
        : d_(d)
        , substitutionMatrix_(substitutionMatrix)
        , progress_(progress)
        , numOfAlignedSequences_(numOfAlignedSequences)
        , numOfSequences_(numOfSequences)
        , sumForCounter_(0U)
        , counter_(0U)
    {}

    HirschbergAlgorithm::OutStrings HirschbergAlgorithm::align(string& xStr,
                                                               string& yStr,
                                                               bool withEndsPenalty) {
        OutStrings result;
        unsigned int xStrLength = static_cast<unsigned int>(xStr.length());
        unsigned int yStrLength = static_cast<unsigned int>(yStr.length());

        if (sumForCounter_ == 0U) {   //first time remeber the length of sequence (to estimate task's progress only)
            sumForCounter_ = (static_cast<unsigned int>(logb(xStrLength)- 3))* xStrLength;
        }

        if (xStrLength == 0U) {
            for (unsigned int i = 0U; i < yStrLength; ++i) {
                result.xStrOut += '-';
                result.yStrOut += yStr[i];
            }
        } else if (yStrLength == 0U) {
            counter_ += xStrLength;
            for (unsigned int i = 0U; i < xStrLength; ++i) {
                result.xStrOut += xStr[i];
                result.yStrOut += '-';
            }
        } else if (xStrLength < 10U || yStrLength < 10U) {
            counter_ += xStrLength;
                 NeedlemanWunschAlgorithm needlemanWunschAlgorithm(xStr, yStr, d_, substitutionMatrix_, NULL, 0U, 0U);
            needlemanWunschAlgorithm.align(withEndsPenalty);
            result.xStrOut = needlemanWunschAlgorithm.getXStrOut();
            result.yStrOut = needlemanWunschAlgorithm.getYStrOut();
        } else {
            unsigned int xStrMidLength = xStrLength / 2;
            string xStrFirstHalf = xStr.substr(0, xStrMidLength);
            vector<int> leftScore = lastAlignColumn(xStrFirstHalf, yStr, withEndsPenalty);
            string xStrSecondHalfRev = xStr.substr(xStrMidLength, xStrLength + 1);
            reverse(xStrSecondHalfRev.begin(), xStrSecondHalfRev.end());
            string yStrRev = yStr;
            reverse(yStrRev.begin(), yStrRev.end());
            vector<int> rightScore = lastAlignColumn(xStrSecondHalfRev, yStrRev, withEndsPenalty);
            unsigned int yMid = partitionY(leftScore, rightScore);
            string xStrSecondHalf = xStr.substr(xStrMidLength, xStrLength);
            string yStrFirstHalf = yStr.substr(0, yMid);
            string yStrSecondHalf = yStr.substr(yMid, yStrLength);
            OutStrings firstResult = align(xStrFirstHalf, yStrFirstHalf, withEndsPenalty);
            OutStrings secondResult = align(xStrSecondHalf, yStrSecondHalf, withEndsPenalty);
            result.xStrOut = firstResult.xStrOut + secondResult.xStrOut;
            result.yStrOut = firstResult.yStrOut + secondResult.yStrOut;
        }

        return result;
    }

    unsigned int HirschbergAlgorithm::partitionY(vector<int>& leftScore, vector<int>& rightScore) {
        unsigned int maxIndex = 0U;
        int maxSum = numeric_limits<int>::min();
        reverse(rightScore.begin(), rightScore.end());

        unsigned int limit = min(static_cast<unsigned int>(leftScore.size()),
                                 static_cast<unsigned int>(rightScore.size()));

        for (unsigned int i = 0U; i < limit; ++i) {
            if (leftScore[i] + rightScore[i] > maxSum) {
                maxSum = leftScore[i] + rightScore[i];
                maxIndex = i;
            }
        }
        return maxIndex;
    }

    vector<int> HirschbergAlgorithm::lastAlignColumn(string& x, string& y, bool withEndsPenalty) {
        unsigned int xSize = static_cast<unsigned int>(x.length());
        unsigned int ySize = static_cast<unsigned int>(y.length());
        int fU, fD, fL;
        vector<int> currentColumn (ySize + 1U, 0);
        vector<int> previousColumn (ySize + 1U, 0);
        char nuc;
        unsigned short int xSubIndex = 0U, ySubIndex = 0U;

        if (withEndsPenalty)
            for (unsigned int i = 1U; i < ySize + 1U; ++i)
                previousColumn[i] = previousColumn[i-1] + d_;
        else
            for (unsigned int i = 1U; i < ySize + 1U; ++i)
                previousColumn[i] = 0U;

        currentColumn[0] = 0;

        for (unsigned int j = 1U; j < xSize + 1U; ++j) {
            ++counter_;
            if (progress_ != NULL && numOfSequences_ != 0U)
                progress_->setProgress(static_cast<double>(numOfAlignedSequences_)
                        /static_cast<double>(numOfSequences_)
                        + static_cast<double>(counter_)
                        / static_cast<double>(sumForCounter_)
                        / static_cast<double>(numOfSequences_));

            if (withEndsPenalty)
                currentColumn[0] += d_;
            else
                currentColumn[0] = 0U;

            for (unsigned int i = 1U; i < ySize + 1U; ++i) {
                nuc = x[j-1];

                switch(nuc) {
                    case 'A': xSubIndex = 0; break;
                    case 'C': xSubIndex = 1; break;
                    case 'G': xSubIndex = 2; break;
                    case 'T': xSubIndex = 3;
                }

                nuc = y[i-1];

                switch(nuc) {
                    case 'A': ySubIndex = 0; break;
                    case 'C': ySubIndex = 1; break;
                    case 'G': ySubIndex = 2; break;
                    case 'T': ySubIndex = 3;
                }

                fU = currentColumn[i-1] + d_;
                fD = previousColumn[i-1] + substitutionMatrix_[xSubIndex][ySubIndex];
                fL = previousColumn[i] + d_;

                /*if (!withEndsPenalty) {   //no penalty for both ends
                    if (j == 1U || j == ySize) {
                        fL = previousColumn[i];
                    }
                    if (i == 1U || i == xSize) {
                        fU = currentColumn[i-1];
                    }
                }*/

                currentColumn[i] = max(max(fU,fD), fL);
            }
            previousColumn = currentColumn;
        }

        return currentColumn;
    }
}}

