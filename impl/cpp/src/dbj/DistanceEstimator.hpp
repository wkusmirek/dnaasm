/**
 * \file DistanceEstimator.hpp
 * \brief the C++ file with declaration of class for estimating distance between two disconnected sequences
 *
 */

#ifndef DISTANCE_ESTIMATOR_HPP
#define DISTANCE_ESTIMATOR_HPP

#include <boost/math/distributions/normal.hpp>
#include "globals.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to estimate distance between two disconnected sequences.
     */
    class DistanceEstimator {
    public:

        /**
        * \brief DistanceEstimator constructor.
        *
        * \param mean mean value of insert size
        * \param stdDev standard deviation of insert size
        * \param maxGapSize maximum value of gap size between two disconnected sequences
        */
        CALC_DLL(DistanceEstimator(float mean, float stdDev, unsigned short maxGapSize);)

        /**
         * \brief Estimates distance between two disconnected sequences.
         *
         * \param inserSizeOffsetVector vector of values (each value is the sum of distances from start/end of disconnected sequences and start/end of paired reads), each velue means: insertSize = gapSize + insertSizeOffset
         * \return returns distance between two disconnected sequences
         */
        CALC_DLL(unsigned short estimateDistanceBetweenSequences(std::vector<unsigned short>& inserSizeOffsetVector);)

    private:
        float mean_;
        float stdDev_;
        unsigned short minGapSize_;
        unsigned short maxGapSize_;
        boost::math::normal_distribution<> normalDistribution_;

        /**
         * \brief Counts propability, that distance between two disconnected sequences is equal to specified gapSize parameter.
         *
         * \param inserSizeOffsetVector vector of values (each value is the sum of distances from start/end of disconnected sequences and start/end of paired reads), each velue means: insertSize = gapSize + insertSizeOffset
         * \param gapSize actual distance between to disconnected sequences
         * \return returns propability for specified gapSize parameter
         */
        CALC_DLL(double countPropability(std::vector<unsigned short>& inserSizeOffsetVector, unsigned short gapSize);)

    };

}}

#endif    //DISTANCE_ESTIMATOR_HPP
