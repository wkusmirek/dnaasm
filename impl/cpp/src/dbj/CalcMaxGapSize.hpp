/**
 * \file CalcMaxGapSize.hpp
 * \brief the C++ file with declaration of class for calculating maximum value of distance between disconnected sequences (gap size)
 *
 */

#ifndef CALC_MAX_GAP_SIZE_HPP
#define CALC_MAX_GAP_SIZE_HPP

#include <boost/math/distributions/normal.hpp>
#include "globals.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to calculate maximum value of distance between disconnected sequences (gap size).
     */
    class CalcMaxGapSize {
    public:

        /**
        * \brief CalcMaxGapSize constructor.
        */
        CALC_DLL(CalcMaxGapSize(float mean, float stdDev);)

        /**
         * \brief Calculates maximum value of distance between disconnected sequences (gap size).
         *
         * \return returns maximum value of distance between disconnected sequences
         */
        CALC_DLL(unsigned short calcMaxGapSize();)

    private:
        float mean_;
        float stdDev_;
        unsigned short maxGapSize_;
        boost::math::normal_distribution<> normalDistribution_;

    };

}}

#endif    //CALC_MAX_GAP_SIZE_HPP
