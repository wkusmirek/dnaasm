/**
 * \file Statistics.cpp
 * \brief the C++ file with implementation of class for storing statistics for graph
 */

#include "Statistics.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    Statistics::Statistics() { initializeStatisticsMap(); }

    void Statistics::set(Key key, Statistics::ValueType value) {
        Statistics::StatisticsMap::iterator it = statisticsMap_.find(key);
        if (it != statisticsMap_.end()) {
            it->second = value;
        } else {
            statisticsMap_.insert(make_pair(key, value));
        }
    }

    Statistics::ValueType Statistics::get(Key key) {
        Statistics::StatisticsMap::iterator it = statisticsMap_.find(key);
        if (it == statisticsMap_.end()) {
            return 0UL;
        } else {
            return it->second;
        }
    }

    void Statistics::initializeStatisticsMap() {
        statisticsMap_[Key::AVG_SEQUENCE_SIZE] = 0.0F;
        statisticsMap_[Key::MEDIAN_SEQUENCE_SIZE] = 0.0F;
        statisticsMap_[Key::MAX_SEQUENCE_SIZE] = 0UL;
        statisticsMap_[Key::N50_SEQUENCE_SIZE] = 0UL;
        statisticsMap_[Key::SUM_SEQUENCES_SIZE] = 0UL;
        statisticsMap_[Key::NUM_OF_SEQUENCES] = 0UL;
        statisticsMap_[Key::NUM_OF_READS_GRAPH_VERTICES] = 0UL;
        statisticsMap_[Key::NUM_OF_READS_GRAPH_EDGES] = 0UL;
        statisticsMap_[Key::NUM_OF_CORRECTIONS] = 0UL;
        statisticsMap_[Key::NUM_OF_COMPONENTS] = 0UL;
    }

    void Statistics::addSequenceLengthStat(const unsigned int sequenceLength) {
        sequencesLengthsHistogram_.addSingleData(sequenceLength);
    }

    unsigned long long Statistics::getSumOfMaxSequences(const unsigned int numOfMaxSequences) {
        return sequencesLengthsHistogram_.getSumOfMaxSequences(numOfMaxSequences);
    }

    unsigned long long Statistics::getSumOfSequencesLongerOrEqualTo(const unsigned int leastSequenceSize) {
        return sequencesLengthsHistogram_.getSumOfSequencesLongerOrEqualTo(leastSequenceSize);
    }

    const Statistics::SequencesLengthsHistogramContainer& Statistics::getSequencesLengthsHistogramContainer() {
        return sequencesLengthsHistogram_.getHistogramContainer();
    }

    void Statistics::collectStatisticsFromSequences() {
        set(Key::AVG_SEQUENCE_SIZE, static_cast<float>(sequencesLengthsHistogram_.getAverage()));
        set(Key::MEDIAN_SEQUENCE_SIZE, static_cast<float>(sequencesLengthsHistogram_.getMedian()));
        set(Key::N50_SEQUENCE_SIZE, static_cast<unsigned long>(sequencesLengthsHistogram_.getN50()));
        set(Key::MAX_SEQUENCE_SIZE, static_cast<unsigned long>(sequencesLengthsHistogram_.getMax()));
        set(Key::SUM_SEQUENCES_SIZE, static_cast<unsigned long>(sequencesLengthsHistogram_.getSum()));
        set(Key::NUM_OF_SEQUENCES, static_cast<unsigned long>(sequencesLengthsHistogram_.getNumOfElements()));
    }

    void Statistics::addUnfilteredReadStat(const unsigned short readLength) {
        unfilteredReadsHistogram_.addSingleData(readLength);
    }

    const Statistics::ReadsLengthsHistogramContainer& Statistics::getUnfilteredReadsHistogramContainer() {
        return unfilteredReadsHistogram_.getHistogramContainer();
    }

    unsigned short Statistics::getUnfilteredReadsMin() {
        return unfilteredReadsHistogram_.getMin();
    }

    unsigned short Statistics::getUnfilteredReadsMax() {
        return unfilteredReadsHistogram_.getMax();
    }

    float Statistics::getUnfilteredReadsMedian() {
        return unfilteredReadsHistogram_.getMedian();
    }

    float Statistics::getUnfilteredReadsAverage() {
        return unfilteredReadsHistogram_.getAverage();
    }

    void Statistics::addFilteredReadStat(const unsigned short readLength) {
        filteredReadsHistogram_.addSingleData(readLength);
    }

    const Statistics::ReadsLengthsHistogramContainer& Statistics::getFilteredReadsHistogramContainer() {
        return filteredReadsHistogram_.getHistogramContainer();
    }

    unsigned short Statistics::getFilteredReadsMin() {
        return filteredReadsHistogram_.getMin();
    }

    unsigned short Statistics::getFilteredReadsMax() {
        return filteredReadsHistogram_.getMax();
    }

    float Statistics::getFilteredReadsMedian() {
        return filteredReadsHistogram_.getMedian();
    }

    float Statistics::getFilteredReadsAverage() {
        return filteredReadsHistogram_.getAverage();
    }

    unsigned long Statistics::getUnfilteredReadsHistogramNumOfElements() {
        return unfilteredReadsHistogram_.getNumOfElements();
    }

    unsigned long Statistics::getFilteredReadsHistogramNumOfElements() {
        return filteredReadsHistogram_.getNumOfElements();
    }

    unsigned long long Statistics::getUnfilteredReadsHistogramSum() {
        return unfilteredReadsHistogram_.getSum();
    }

    unsigned long long Statistics::getFilteredReadsHistogramSum() {
        return filteredReadsHistogram_.getSum();
    }

}}

