/**
 * \file TestCalcMaxGapSize.cpp
 * \brief the C++ file with implementation of tests for CalcMaxGapSize class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/CalcMaxGapSize.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestCalcMaxGapSize)

BOOST_AUTO_TEST_CASE(calcMaxGapSize_mean_equal_to_0_std_dev_equal_to_0)
{
    float mean = 0.0;
    float stdDev = 0.0;
    CalcMaxGapSize calcMaxGapSize(mean, stdDev);
    BOOST_CHECK_EQUAL(calcMaxGapSize.calcMaxGapSize(), 10U);
}

BOOST_AUTO_TEST_CASE(calcMaxGapSize_mean_equal_to_0_std_dev_not_equal_to_0)
{
    float mean = 0.0;
    float stdDev = 5.0;
    CalcMaxGapSize calcMaxGapSize(mean, stdDev);
    BOOST_CHECK_EQUAL(calcMaxGapSize.calcMaxGapSize(), 20U);
}

BOOST_AUTO_TEST_CASE(calcMaxGapSize_mean_not_equal_to_0_std_dev_equal_to_0)
{
    float mean = 70.0;
    float stdDev = 0.0;
    CalcMaxGapSize calcMaxGapSize(mean, stdDev);
    BOOST_CHECK_EQUAL(calcMaxGapSize.calcMaxGapSize(), 80U);
}

BOOST_AUTO_TEST_CASE(calcMaxGapSize_mean_not_equal_to_0_std_dev_not_equal_to_0)
{
    float mean = 400.0;
    float stdDev = 20.0;
    CalcMaxGapSize calcMaxGapSize(mean, stdDev);
    BOOST_CHECK_EQUAL(calcMaxGapSize.calcMaxGapSize(), 470U);
}

BOOST_AUTO_TEST_SUITE_END()

