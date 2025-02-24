/**
 * \file TestDistanceEstimator.cpp
 * \brief the C++ file with implementation of tests for DistanceEstimator class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/DistanceEstimator.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestDistanceEstimator)

BOOST_AUTO_TEST_CASE(estimateDistanceBetweenSequences_empty_inserSizeOffsetVector)
{
    float mean = 70.0F;
    float stdDev = 2.0F;
    unsigned short maxInsertSize = 90U;
    vector<unsigned short> inserSizeOffsetVector;
    DistanceEstimator distanceEstimator(mean, stdDev, maxInsertSize);
    BOOST_CHECK_EQUAL(distanceEstimator.estimateDistanceBetweenSequences(inserSizeOffsetVector), numeric_limits<unsigned short>::max());
}

BOOST_AUTO_TEST_CASE(estimateDistanceBetweenSequences_stdDev_equal_to_0)
{
    float mean = 70.0F;
    float stdDev = 0.0F;
    unsigned short maxInsertSize = 70U;
    vector<unsigned short> inserSizeOffsetVector;
    inserSizeOffsetVector.push_back(50);
    DistanceEstimator distanceEstimator(mean, stdDev, maxInsertSize);
    BOOST_CHECK_EQUAL(distanceEstimator.estimateDistanceBetweenSequences(inserSizeOffsetVector), 20U);
}

BOOST_AUTO_TEST_CASE(estimateDistanceBetweenSequences_stdDev_not_equal_to_0)
{
    float mean = 70.0F;
    float stdDev = 0.001F;
    unsigned short maxInsertSize = 70U;
    vector<unsigned short> inserSizeOffsetVector;
    inserSizeOffsetVector.push_back(50);
    DistanceEstimator distanceEstimator(mean, stdDev, maxInsertSize);
    BOOST_CHECK_EQUAL(distanceEstimator.estimateDistanceBetweenSequences(inserSizeOffsetVector), 20U);
}

BOOST_AUTO_TEST_CASE(estimateDistanceBetweenSequences_not_fixed_insert_size_2_connects_between_sequences)
{
    float mean = 70.0F;
    float stdDev = 5.0F;
    unsigned short maxInsertSize = 100U;
    vector<unsigned short> inserSizeOffsetVector;
    inserSizeOffsetVector.push_back(50);
    inserSizeOffsetVector.push_back(40);
    DistanceEstimator distanceEstimator(mean, stdDev, maxInsertSize);
    BOOST_CHECK_EQUAL(distanceEstimator.estimateDistanceBetweenSequences(inserSizeOffsetVector), 25U);
}

BOOST_AUTO_TEST_CASE(estimateDistanceBetweenSequences_fixed_insert_size_2_connects_between_sequences)
{
    float mean = 70.0F;
    float stdDev = 0.0F;
    unsigned short maxInsertSize = 70U;
    vector<unsigned short> inserSizeOffsetVector;
    inserSizeOffsetVector.push_back(40);
    inserSizeOffsetVector.push_back(50);
    DistanceEstimator distanceEstimator(mean, stdDev, maxInsertSize);
    BOOST_CHECK_EQUAL(distanceEstimator.estimateDistanceBetweenSequences(inserSizeOffsetVector), 20U);
}

BOOST_AUTO_TEST_CASE(estimateDistanceBetweenSequences_not_fixed_insert_size_many_connecting_between_sequences)
{
    float mean = 70.0F;
    float stdDev = 10.0F;
    unsigned short maxInsertSize = 120U;
    vector<unsigned short> inserSizeOffsetVector;
    for (unsigned int i = 0U; i < 400; ++i) {
        inserSizeOffsetVector.push_back(42);
        inserSizeOffsetVector.push_back(40);
        inserSizeOffsetVector.push_back(50);
        inserSizeOffsetVector.push_back(34);
        inserSizeOffsetVector.push_back(44);
    }
    DistanceEstimator distanceEstimator(mean, stdDev, maxInsertSize);
    BOOST_CHECK_EQUAL(distanceEstimator.estimateDistanceBetweenSequences(inserSizeOffsetVector) != 0U, true);
}

BOOST_AUTO_TEST_CASE(estimateDistanceBetweenSequences_not_fixed_insert_size_2_connects_between_sequences_large_dispersion_avg_value)
{
    float mean = 70.0F;
    float stdDev = 5.0F;
    unsigned short maxInsertSize = 100U;
    vector<unsigned short> inserSizeOffsetVector;
    inserSizeOffsetVector.push_back(150);
    inserSizeOffsetVector.push_back(20);
    DistanceEstimator distanceEstimator(mean, stdDev, maxInsertSize);
    BOOST_CHECK_EQUAL(distanceEstimator.estimateDistanceBetweenSequences(inserSizeOffsetVector), 85U);
}

BOOST_AUTO_TEST_CASE(estimateDistanceBetweenSequences_not_fixed_insert_size_2_connects_between_sequences_large_dispersion_greater_than_maxInsertSize)
{
    float mean = 70.0F;
    float stdDev = 5.0F;
    unsigned short maxInsertSize = 100U;
    vector<unsigned short> inserSizeOffsetVector;
    inserSizeOffsetVector.push_back(180);
    inserSizeOffsetVector.push_back(40);
    DistanceEstimator distanceEstimator(mean, stdDev, maxInsertSize);
    BOOST_CHECK_EQUAL(distanceEstimator.estimateDistanceBetweenSequences(inserSizeOffsetVector), numeric_limits<unsigned short>::max());
}

BOOST_AUTO_TEST_SUITE_END()

