/**
 * \file CalcMaxGapSize.hpp
 * \brief the C++ file with implementation of class for calculating maximum value of distance between disconnected sequences (gap size)
 *
 */

#include "CalcMaxGapSize.hpp"
#include "../common/log.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    CalcMaxGapSize::CalcMaxGapSize(float mean, float stdDev)
        : mean_(mean)
        , stdDev_(stdDev == 0.0 ? numeric_limits<float>::epsilon(): stdDev)
        , maxGapSize_(10U)
        , normalDistribution_(mean_, stdDev_)
    {}

    unsigned short CalcMaxGapSize::calcMaxGapSize() {
        unsigned short tmpMaxGapSize = 0U;
        while (true) {
            tmpMaxGapSize += 10U;
            if (boost::math::cdf(normalDistribution_, tmpMaxGapSize) > 0.999)
                // 0.999 maybe should be added as parameter
                break;
        }

        maxGapSize_ = tmpMaxGapSize;
        logInfo("Estimated max gap size between two contgis equal to " + to_string(maxGapSize_));
        return maxGapSize_;
    }
}}
