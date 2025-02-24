/**
 * \file Statistics.hpp
 * \brief the C++ file with declaration of class for storing statistics for graph
 */

#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "boost/variant.hpp"

#include "SequencesLengthsHistogram.hpp"

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to store statistics for graph.
     */
    class Statistics {
    public:

        enum class Key {       // remember to add initialize value in initializeStatisticsMap()function
            AVG_SEQUENCE_SIZE,    //float
            MEDIAN_SEQUENCE_SIZE,    //float
            MAX_SEQUENCE_SIZE,    //unsigned long
            N50_SEQUENCE_SIZE,    //unsigned long
            SUM_SEQUENCES_SIZE,    //unsigned long
            NUM_OF_SEQUENCES,    //unsigned long
            NUM_OF_READS_GRAPH_VERTICES,    //unsigned long
            NUM_OF_READS_GRAPH_EDGES,    //unsigned long
            NUM_OF_CORRECTIONS,    //unsigned long
            NUM_OF_COMPONENTS    //unsigned long
        };

        typedef boost::variant<unsigned long, float> ValueType;

        typedef std::map<Key, ValueType> StatisticsMap;

        typedef Histogram<unsigned short>::HistogramContainer ReadsLengthsHistogramContainer;

        typedef Histogram<unsigned int>::HistogramContainer SequencesLengthsHistogramContainer;

        /**
         * \brief Statistics constructor.
         */
        CALC_DLL(Statistics();)

        /**
         * \brief Sets specified statistic value.
         *
         * \param key type of statistic
         * \param value value of specified statistic
         * \return returns void
         */
        CALC_DLL(void set(Key key, ValueType value);)

        /**
         * \brief Gets specified statistic value.
         *
         * \param key type of statistic
         * \return returns value of specified statistic
         */
        CALC_DLL(ValueType get(Key key);)

        /**
         * \brief Builds statistics dictionary.
         *
         * \return returns void
         */
        CALC_DLL(void initializeStatisticsMap();)

        /**
         * \brief Adds sequence length statistic.
         *
         * \param sequenceLength length of sequence
         * \return returns void
         */
        CALC_DLL(void addSequenceLengthStat(const unsigned int sequenceLength);)

        /**
         * \brief Gets sum of specified number of maximium sequences.
         *
         * \param numOfMaxSequences number of maximum sequences
         * \return returns size of specified number of maximium sequences
         */
        CALC_DLL(unsigned long long getSumOfMaxSequences(const unsigned int numOfMaxsequences);)

        /**
         * \brief Gets sum of sequences longer or equal to leastSequenceSize.
         *
         * \param leastSequenceSize sequences, which are longer or equal to this value, should be considered and added to result
         * \return returns sum of sequences longer or equal to leastSequenceSize
         */
        CALC_DLL(unsigned long long getSumOfSequencesLongerOrEqualTo(const unsigned int leastSequenceSize);)

        /**
         * \brief Gets histogram for unfiltered reads length.
         *
         * \return returns histogram for unfiltered reads length
         */
        CALC_DLL(const SequencesLengthsHistogramContainer& getSequencesLengthsHistogramContainer();)

        /**
         * \brief Collects basic statistics from set of sequences (from sequences lengths histogram).
         *
         * \return returns void
         */
        CALC_DLL(void collectStatisticsFromSequences();)

        /**
         * \brief Adds unfiltered read length statistic.
         *
         * \param readLength length of unfiltered read
         * \return returns void
         */
        CALC_DLL(void addUnfilteredReadStat(const unsigned short readLength);)

        /**
         * \brief Gets histogram for unfiltered reads length.
         *
         * \return returns histogram for unfiltered reads length
         */
        CALC_DLL(const ReadsLengthsHistogramContainer& getUnfilteredReadsHistogramContainer();)

        /**
         * \brief Gets minimum value of unfiltered reads length histogram.
         *
         * \return returns minimum value of unfiltered reads length histogram
         */
        CALC_DLL(unsigned short getUnfilteredReadsMin();)

        /**
         * \brief Gets maximum value of unfiltered reads length histogram.
         *
         * \return returns maximum value of unfiltered reads length histogram
         */
        CALC_DLL(unsigned short getUnfilteredReadsMax();)

        /**
         * \brief Gets median value of unfiltered reads length histogram.
         *
         * \return returns median value of unfiltered reads length histogram
         */
        CALC_DLL(float getUnfilteredReadsMedian();)

        /**
         * \brief Gets average value of unfiltered reads length histogram.
         *
         * \return returns average value of unfiltered reads length histogram
         */
        CALC_DLL(float getUnfilteredReadsAverage();)

        /**
         * \brief Adds filtered read length statistic.
         *
         * \param readLength length of filtered read
         * \return returns void
         */
        CALC_DLL(void addFilteredReadStat(const unsigned short readLength);)

        /**
         * \brief Gets histogram for filtered reads length.
         *
         * \return returns histogram for filtered reads length
         */
        CALC_DLL(const ReadsLengthsHistogramContainer& getFilteredReadsHistogramContainer();)

        /**
         * \brief Gets minimum value of filtered reads length histogram.
         *
         * \return returns minimum value of filtered reads length histogram
         */
        CALC_DLL(unsigned short getFilteredReadsMin();)

        /**
         * \brief Gets maximum value of filtered reads length histogram.
         *
         * \return returns maximum value of filtered reads length histogram
         */
        CALC_DLL(unsigned short getFilteredReadsMax();)

        /**
         * \brief Gets median value of filtered reads length histogram.
         *
         * \return returns median value of filtered reads length histogram
         */
        CALC_DLL(float getFilteredReadsMedian();)

        /**
         * \brief Gets average value of filtered reads length histogram.
         *
         * \return returns average value of filtered reads length histogram
         */
        CALC_DLL(float getFilteredReadsAverage();)

        /**
         * \brief Gets size of filtered reads histogram - num of reads.
         *
         * \return returns size of filtered reads histogram - num of reads
         */
        CALC_DLL(unsigned long getFilteredReadsHistogramNumOfElements();)

        /**
         * \brief Gets size of unfiltered reads histogram - num of reads.
         *
         * \return returns size of unfiltered reads histogram - num of reads
         */
        CALC_DLL(unsigned long getUnfilteredReadsHistogramNumOfElements();)

        /**
         * \brief Gets sum of filtered reads histogram - num of signs in all filtered reads.
         * \return returns sum of filtered reads histogram - num of signs in all filtered reads
         */
        CALC_DLL(unsigned long long getFilteredReadsHistogramSum();)

        /**
         * \brief Gets sum of unfiltered reads histogram - num of signs in all unfiltered reads.
         *
         * \return returns sum of unfiltered reads histogram - num of signs in all unfiltered reads
         */
        CALC_DLL(unsigned long long getUnfilteredReadsHistogramSum();)


    private:
	SequencesLengthsHistogram<unsigned int> sequencesLengthsHistogram_;
        Histogram<unsigned short> unfilteredReadsHistogram_;
        Histogram<unsigned short> filteredReadsHistogram_;
        StatisticsMap statisticsMap_;
        Statistics& operator=(const Statistics&)= delete;

    };
}}

#endif    // STATISTICS_HPP
