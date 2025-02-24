/**
 * \file TestHistogram.cpp
 * \brief the C++ file with implementation of tests for Histogram class
 *
 */


#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/Histogram.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestHistogram)

BOOST_AUTO_TEST_CASE(HistogramTest1)
{
    Histogram<unsigned int> histogram;
    BOOST_CHECK_EQUAL(histogram.getHistogramContainer().size(), 0);
    BOOST_CHECK_EQUAL(histogram.getMedian(), 0);
    BOOST_CHECK_EQUAL(histogram.getMin(), 0U);
    BOOST_CHECK_EQUAL(histogram.getMax(), 0U);
    BOOST_CHECK_EQUAL(histogram.getAverage(), 0);
    BOOST_CHECK_EQUAL(histogram.getNumOfElements(), 0U);
    BOOST_CHECK_EQUAL(histogram.getSum(), 0U);
}

BOOST_AUTO_TEST_CASE(HistogramTest2)
{
    Histogram<unsigned int> histogram;
    histogram.addSingleData(3);
    vector<pair<unsigned int, unsigned int>> histogramContainer = histogram.getHistogramContainer();
    BOOST_CHECK_EQUAL(histogramContainer.size(), 1);
    BOOST_CHECK_EQUAL(histogramContainer[0].first, 3U);
    BOOST_CHECK_EQUAL(histogramContainer[0].second, 1U);
    BOOST_CHECK_EQUAL(histogram.getMedian(), 3);
    BOOST_CHECK_EQUAL(histogram.getMin(), 3U);
    BOOST_CHECK_EQUAL(histogram.getMax(), 3U);
    BOOST_CHECK_EQUAL(histogram.getAverage(), 3);
    BOOST_CHECK_EQUAL(histogram.getNumOfElements(), 1U);
    BOOST_CHECK_EQUAL(histogram.getSum(), 3U);
}

BOOST_AUTO_TEST_CASE(HistogramTest3)
{
    Histogram<unsigned int> histogram;
    histogram.addSingleData(3);
    histogram.addSingleData(4);
    histogram.addSingleData(2);
    histogram.addSingleData(2);
    vector<pair<unsigned int, unsigned int>> histogramContainer = histogram.getHistogramContainer();
    BOOST_CHECK_EQUAL(histogramContainer.size(), 3);
    BOOST_CHECK_EQUAL(histogramContainer[0].first, 2U);
    BOOST_CHECK_EQUAL(histogramContainer[0].second, 2U);
    BOOST_CHECK_EQUAL(histogramContainer[1].first, 3U);
    BOOST_CHECK_EQUAL(histogramContainer[1].second, 1U);
    BOOST_CHECK_EQUAL(histogramContainer[2].first, 4U);
    BOOST_CHECK_EQUAL(histogramContainer[2].second, 1U);
    BOOST_CHECK_EQUAL(histogram.getMedian(), 2.5);
    BOOST_CHECK_EQUAL(histogram.getMin(), 2U);
    BOOST_CHECK_EQUAL(histogram.getMax(), 4U);
    BOOST_CHECK_EQUAL(histogram.getAverage(), 2.75);
    BOOST_CHECK_EQUAL(histogram.getNumOfElements(), 4U);
    BOOST_CHECK_EQUAL(histogram.getSum(), 11U);
}

BOOST_AUTO_TEST_CASE(HistogramTest4)
{
    Histogram<unsigned int> histogram;
    histogram.addSingleData(3);
    histogram.addSingleData(4);
    histogram.addSingleData(2);
    histogram.addSingleData(2);
    histogram.addSingleData(4);
    vector<pair<unsigned int, unsigned int>> histogramContainer = histogram.getHistogramContainer();
    BOOST_CHECK_EQUAL(histogramContainer.size(), 3);
    BOOST_CHECK_EQUAL(histogramContainer[0].first, 2U);
    BOOST_CHECK_EQUAL(histogramContainer[0].second, 2U);
    BOOST_CHECK_EQUAL(histogramContainer[1].first, 3U);
    BOOST_CHECK_EQUAL(histogramContainer[1].second, 1U);
    BOOST_CHECK_EQUAL(histogramContainer[2].first, 4U);
    BOOST_CHECK_EQUAL(histogramContainer[2].second, 2U);
    BOOST_CHECK_EQUAL(histogram.getMedian(), 3);
    BOOST_CHECK_EQUAL(histogram.getMin(), 2U);
    BOOST_CHECK_EQUAL(histogram.getMax(), 4U);
    BOOST_CHECK_EQUAL(histogram.getAverage(), 3.0);
    BOOST_CHECK_EQUAL(histogram.getNumOfElements(), 5U);
    BOOST_CHECK_EQUAL(histogram.getSum(), 15U);
}

BOOST_AUTO_TEST_SUITE_END()
