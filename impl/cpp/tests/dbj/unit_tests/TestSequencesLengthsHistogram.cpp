/**
 * \file SequencesLengthsHistogram.cpp
 * \brief the C++ file with implementation of tests for SequencesLengthsHistogram class
 *
 */


#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/SequencesLengthsHistogram.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestSequencesLengthsHistogram)

BOOST_AUTO_TEST_CASE(SequencesLengthsHistogramTest1)
{
    SequencesLengthsHistogram<unsigned int> sequencesLengthsHistogram;
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getHistogramContainer().size(), 0);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMedian(), 0);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMin(), 0U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMax(), 0U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getAverage(), 0);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getNumOfElements(), 0U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSum(), 0U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getN50(), 0U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(0U), 0ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(0U), 0ULL);
}

BOOST_AUTO_TEST_CASE(SequencesLengthsHistogramTest2)
{
    SequencesLengthsHistogram<unsigned int> sequencesLengthsHistogram;
    sequencesLengthsHistogram.addSingleData(3);
    vector<pair<unsigned int, unsigned int>> sequencesLengthsHistogramContainer = sequencesLengthsHistogram.getHistogramContainer();
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer.size(), 1);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[0].first, 3U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[0].second, 1U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMedian(), 3);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMin(), 3U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMax(), 3U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getAverage(), 3);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getNumOfElements(), 1U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSum(), 3U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getN50(), 3U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(0U), 0ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(1U), 3ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(2U), 3ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(0U), 3ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(1U), 3ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(2U), 3ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(3U), 3ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(4U), 0ULL);
}

BOOST_AUTO_TEST_CASE(SequencesLengthsHistogramTest3)
{
    SequencesLengthsHistogram<unsigned int> sequencesLengthsHistogram;
    sequencesLengthsHistogram.addSingleData(3);
    sequencesLengthsHistogram.addSingleData(4);
    sequencesLengthsHistogram.addSingleData(2);
    sequencesLengthsHistogram.addSingleData(2);
    vector<pair<unsigned int, unsigned int>> sequencesLengthsHistogramContainer = sequencesLengthsHistogram.getHistogramContainer();
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer.size(), 3);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[0].first, 2U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[0].second, 2U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[1].first, 3U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[1].second, 1U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[2].first, 4U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[2].second, 1U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMedian(), 2.5);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMin(), 2U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMax(), 4U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getAverage(), 2.75);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getNumOfElements(), 4U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSum(), 11U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getN50(), 3U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(0U), 0ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(1U), 4ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(2U), 7ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(3U), 9ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(4U), 11ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(5U), 11ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(0U), 11ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(1U), 11ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(2U), 11ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(3U), 7ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(4U), 4ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(5U), 0ULL);
}

BOOST_AUTO_TEST_CASE(SequencesLengthsHistogramTest4)
{
    SequencesLengthsHistogram<unsigned int> sequencesLengthsHistogram;
    sequencesLengthsHistogram.addSingleData(3);
    sequencesLengthsHistogram.addSingleData(4);
    sequencesLengthsHistogram.addSingleData(2);
    sequencesLengthsHistogram.addSingleData(2);
    sequencesLengthsHistogram.addSingleData(4);
    vector<pair<unsigned int, unsigned int>> sequencesLengthsHistogramContainer = sequencesLengthsHistogram.getHistogramContainer();
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer.size(), 3);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[0].first, 2U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[0].second, 2U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[1].first, 3U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[1].second, 1U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[2].first, 4U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogramContainer[2].second, 2U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMedian(), 3);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMin(), 2U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getMax(), 4U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getAverage(), 3.0);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getNumOfElements(), 5U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSum(), 15U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getN50(), 4U);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(0U), 0ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(1U), 4ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(2U), 8ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(3U), 11ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(4U), 13ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(5U), 15ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfMaxSequences(6U), 15ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(0U), 15ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(1U), 15ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(2U), 15ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(3U), 11ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(4U), 8ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(5U), 0ULL);
    BOOST_CHECK_EQUAL(sequencesLengthsHistogram.getSumOfSequencesLongerOrEqualTo(6U), 0ULL);
}

BOOST_AUTO_TEST_SUITE_END()
