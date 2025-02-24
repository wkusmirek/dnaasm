/**
 * \file TestStatistics.cpp
 * \brief the C++ file with implementation of tests for Statistics class
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/Statistics.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestStatistics)

BOOST_AUTO_TEST_CASE(filteredReadsHistogramStat)
{
    Statistics statistics;
    statistics.addFilteredReadStat(3);
    Statistics::ReadsLengthsHistogramContainer histogramContainer = statistics.getFilteredReadsHistogramContainer();
    BOOST_CHECK_EQUAL(histogramContainer.size(), 1);
    BOOST_CHECK_EQUAL(histogramContainer[0].first, 3U);
    BOOST_CHECK_EQUAL(histogramContainer[0].second, 1U);
    BOOST_CHECK_EQUAL(statistics.getFilteredReadsMedian(), 3);
    BOOST_CHECK_EQUAL(statistics.getFilteredReadsMin(), 3U);
    BOOST_CHECK_EQUAL(statistics.getFilteredReadsMax(), 3U);
    BOOST_CHECK_EQUAL(statistics.getFilteredReadsAverage(), 3);
    BOOST_CHECK_EQUAL(statistics.getFilteredReadsHistogramNumOfElements(), 1U);
    BOOST_CHECK_EQUAL(statistics.getFilteredReadsHistogramSum(), 3U);
}

BOOST_AUTO_TEST_CASE(unfilteredReadsHistogramStat)
{
    Statistics statistics;
    statistics.addUnfilteredReadStat(3);
    Statistics::ReadsLengthsHistogramContainer histogramContainer = statistics.getUnfilteredReadsHistogramContainer();
    BOOST_CHECK_EQUAL(histogramContainer.size(), 1);
    BOOST_CHECK_EQUAL(histogramContainer[0].first, 3U);
    BOOST_CHECK_EQUAL(histogramContainer[0].second, 1U);
    BOOST_CHECK_EQUAL(statistics.getUnfilteredReadsMedian(), 3);
    BOOST_CHECK_EQUAL(statistics.getUnfilteredReadsMin(), 3U);
    BOOST_CHECK_EQUAL(statistics.getUnfilteredReadsMax(), 3U);
    BOOST_CHECK_EQUAL(statistics.getUnfilteredReadsAverage(), 3);
    BOOST_CHECK_EQUAL(statistics.getUnfilteredReadsHistogramNumOfElements(), 1U);
    BOOST_CHECK_EQUAL(statistics.getUnfilteredReadsHistogramSum(), 3U);
}

BOOST_AUTO_TEST_CASE(sequencesLengthsHistogramStat)
{
    Statistics statistics;
    statistics.addSequenceLengthStat(3U);
    statistics.addSequenceLengthStat(2U);
    statistics.addSequenceLengthStat(3U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 2);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].first, 2U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].second, 1U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].first, 3U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].second, 2U);
    BOOST_CHECK_EQUAL(statistics.getSumOfMaxSequences(0U), 0ULL);
    BOOST_CHECK_EQUAL(statistics.getSumOfMaxSequences(1U), 3ULL);
    BOOST_CHECK_EQUAL(statistics.getSumOfMaxSequences(2U), 6ULL);
    BOOST_CHECK_EQUAL(statistics.getSumOfMaxSequences(3U), 8ULL);
    BOOST_CHECK_EQUAL(statistics.getSumOfMaxSequences(4U), 8ULL);
    BOOST_CHECK_EQUAL(statistics.getSumOfSequencesLongerOrEqualTo(0U), 8ULL);
    BOOST_CHECK_EQUAL(statistics.getSumOfSequencesLongerOrEqualTo(1U), 8ULL);
    BOOST_CHECK_EQUAL(statistics.getSumOfSequencesLongerOrEqualTo(2U), 8ULL);
    BOOST_CHECK_EQUAL(statistics.getSumOfSequencesLongerOrEqualTo(3U), 6ULL);
    BOOST_CHECK_EQUAL(statistics.getSumOfSequencesLongerOrEqualTo(4U), 0ULL);
}

BOOST_AUTO_TEST_CASE(setReadsGraphStatistics)
{
    Statistics statistics;
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::NUM_OF_READS_GRAPH_EDGES)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::NUM_OF_READS_GRAPH_VERTICES)), 0UL);
    statistics.set(Statistics::Key::NUM_OF_READS_GRAPH_EDGES, 1UL);
    statistics.set(Statistics::Key::NUM_OF_READS_GRAPH_VERTICES, 2UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::NUM_OF_READS_GRAPH_EDGES)), 1UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::NUM_OF_READS_GRAPH_VERTICES)), 2UL);
}


BOOST_AUTO_TEST_CASE(setNumOfComponents)
{
    Statistics statistics;
    unsigned long numOfComponents = 2UL;
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::NUM_OF_COMPONENTS)), 0UL);
    statistics.set(Statistics::Key::NUM_OF_COMPONENTS, numOfComponents);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::NUM_OF_COMPONENTS)), numOfComponents);
}

BOOST_AUTO_TEST_CASE(setSequencesStatistics)
{
    float avgSequenceSize = 1.0;
    float medianSequenceSize = 2.0;
    unsigned long maxSequenceSize = 3UL;
    unsigned long N50SequenceSize = 4UL;
    unsigned long sumSequencesSize = 5UL;
    unsigned long numOfSequences = 11UL;
    Statistics statistics;
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 0.0F);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 0.0F);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::NUM_OF_SEQUENCES)), 0UL);
    statistics.set(Statistics::Key::AVG_SEQUENCE_SIZE, avgSequenceSize);
    statistics.set(Statistics::Key::MEDIAN_SEQUENCE_SIZE, medianSequenceSize);
    statistics.set(Statistics::Key::MAX_SEQUENCE_SIZE, maxSequenceSize);
    statistics.set(Statistics::Key::N50_SEQUENCE_SIZE, N50SequenceSize);
    statistics.set(Statistics::Key::SUM_SEQUENCES_SIZE, sumSequencesSize);
    statistics.set(Statistics::Key::NUM_OF_SEQUENCES, numOfSequences);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), avgSequenceSize);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), medianSequenceSize);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), maxSequenceSize);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), N50SequenceSize);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), sumSequencesSize);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::NUM_OF_SEQUENCES)), numOfSequences);
}

BOOST_AUTO_TEST_CASE(collectStatisticsFromSequences)
{
    Statistics statistics;
    statistics.addSequenceLengthStat(3U);
    statistics.addSequenceLengthStat(2U);
    statistics.addSequenceLengthStat(3U);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 0.0F);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 0.0F);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::NUM_OF_SEQUENCES)), 0UL);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 2);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].first, 2U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].second, 1U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].first, 3U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].second, 2U);
    statistics.collectStatisticsFromSequences();
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 2.66666675F);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 3.0F);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 3UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 3UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 8UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::NUM_OF_SEQUENCES)), 3UL);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 2);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].first, 2U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].second, 1U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].first, 3U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].second, 2U);
}
BOOST_AUTO_TEST_SUITE_END()
