/**
 * \file DistanceEstimator.cpp
 * \brief the C++ file with implementation of class for estimating distance between two disconnected sequences
 *
 */

#include "DistanceEstimator.hpp"
#include "../common/log.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    DistanceEstimator::DistanceEstimator(float mean,
                                         float stdDev,
                                         unsigned short maxGapSize)
        : mean_(mean)
        , stdDev_(stdDev == 0.0 ? numeric_limits<float>::epsilon() : stdDev), minGapSize_(1U)
        , maxGapSize_(maxGapSize)
        , normalDistribution_(mean_, stdDev_)
    {}

    double DistanceEstimator::countPropability(vector<unsigned short>& inserSizeOffsetVector,
                                               unsigned short gapSize) {
        double propability = 1.0;

        for (vector<unsigned short>::iterator it = inserSizeOffsetVector.begin(); it != inserSizeOffsetVector.end(); ++it) {
            double s_i = static_cast<double>((*it + gapSize));
            double tmpProp = boost::math::pdf(normalDistribution_, s_i);
            if (tmpProp > 0) {
                propability += log(tmpProp);
            }
        }
        return propability;
    }

    unsigned short DistanceEstimator::estimateDistanceBetweenSequences(
            vector<unsigned short>& inserSizeOffsetVector) {
        if (inserSizeOffsetVector.size() == 0) {
            return numeric_limits<unsigned short>::max();
        }

        unsigned short bestGapSize = 0U;
        double bestPropability = numeric_limits<double>::lowest();

        for (unsigned short actualGapSize = minGapSize_; actualGapSize < maxGapSize_; actualGapSize += 5U) {   // maybe should be changed to binary search
            double actualPropability = countPropability(inserSizeOffsetVector, actualGapSize);

            if (actualPropability > bestPropability) {
                bestPropability = actualPropability;
                bestGapSize = actualGapSize;
            } else if (actualPropability != bestPropability && bestGapSize != 0U) {
                break;
            }
        }
        if (bestPropability != 1U) {    // only when first for loop finds neigbourhood of the best gap size value,
                                        // when bestPropability is equal to 1, all values of actualPropability for all values of actualGapSize was equal to 1,
                                        // function is 'flat' and all values of possible gap size should be considered (last for loop of this function)
            unsigned short newSearchIndex = bestGapSize > 5 ? bestGapSize - 3 : 0U;
            for (unsigned short actualGapSize = newSearchIndex; actualGapSize < newSearchIndex + 5; ++actualGapSize) {
                double actualPropability = countPropability(inserSizeOffsetVector, actualGapSize);
                if (actualPropability > bestPropability) {
                    bestPropability = actualPropability;
                    bestGapSize = actualGapSize;
                }
            }
        } else {    // simple, linear search for the best gap size
            double bestPropability = numeric_limits<double>::lowest();

            for (unsigned short actualGapSize = minGapSize_; actualGapSize < maxGapSize_; ++actualGapSize)
            {
                double actualPropability = countPropability(inserSizeOffsetVector, actualGapSize);
                if (actualPropability > bestPropability)
                {
                    bestPropability = actualPropability;
                    bestGapSize = actualGapSize;
                }
            }
        }
        // if estimated distance is eual to 0 change this value to average of values from inserSizeOffsetVector
        if (bestGapSize == 0U) {
            unsigned short sumOfElements = 0U;
            for (auto& n : inserSizeOffsetVector) {
                sumOfElements += n;
            }
            bestGapSize = sumOfElements / inserSizeOffsetVector.size();
        }
        // if estimated distance is greater than value of maximum gap sth went wrong
        if (bestGapSize > maxGapSize_) {
            bestGapSize = numeric_limits<unsigned short>::max();
        }
        return bestGapSize;
    }
}}
