/**
 * \file SequencesLengthsHistogram.hpp
 * \brief the C++ file with implementation of template class for collecting histogram of sequences lengths
 *
 */

#ifndef SEQUENCES_LENGTHS_HISTOGRAM_HPP
#define SEQUENCES_LENGTHS_HISTOGRAM_HPP

#include "Histogram.hpp"

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to collect histogram of sequences lengths.
     */
    template<class DataType> class SequencesLengthsHistogram : public Histogram<DataType> {

    public:

        /**
         * \brief SequencesLengthsHistogram constructor.
         *
         */
        SequencesLengthsHistogram() : Histogram<DataType>() {}

        /**
         * \brief Gets N50 of histogram container.
         *
         * \return returns N50 of histogram container
         */
        const DataType getN50() {
            if (!this->isSorted) {
                this->sortHistogramContainer();
            }
            unsigned long long actualSum = 0ULL;
            unsigned long long sum = this->getSum();
            for (typename Histogram<DataType>::HistogramContainer::reverse_iterator it = this->histogramContainer.rbegin(); it != this->histogramContainer.rend(); ++it) {
                actualSum += (it->first * it->second);
                if (actualSum >= sum/2) {
                    return it->first;
                }
            }
            return static_cast<DataType>(sum);
        }

        /**
         * \brief Gets sum of specified number of maximium sequences.
         *
         * \param numOfMaxSequences number of maximum sequences
         * \return returns size of specified number of maximium sequences
         */
        unsigned long long getSumOfMaxSequences(const unsigned int numOfMaxSequences) {
            if (!this->isSorted) {
                this->sortHistogramContainer();
            }
            unsigned long long sum = 0;
            unsigned int numOfMaxSequencesContiainedInSum = 0U;
            for (typename Histogram<DataType>::HistogramContainer::reverse_iterator it = this->histogramContainer.rbegin(); it != this->histogramContainer.rend(); ++it) {
                if (numOfMaxSequences - numOfMaxSequencesContiainedInSum < it->second) {
                    sum += (it->first * (numOfMaxSequences - numOfMaxSequencesContiainedInSum));
                    break;
                }
                sum += (it->first * it->second);
                numOfMaxSequencesContiainedInSum += it->second;
            }
            return sum;
        }

        /**
         * \brief Gets sum of sequences longer or equal to leastSequenceSize.
         *
         * \param leastSequenceSize sequences, which are longer or equal to this value, should be considered and added to result
         * \return returns sum of sequences longer or equal to leastSequenceSize
         */
        unsigned long long getSumOfSequencesLongerOrEqualTo(const DataType leastSequenceSize) {
            if (!this->isSorted) {
                this->sortHistogramContainer();
            }
            unsigned long long sum = 0;
            for (typename Histogram<DataType>::HistogramContainer::reverse_iterator it = this->histogramContainer.rbegin(); it != this->histogramContainer.rend(); ++it) {
                if (leastSequenceSize > it->first) {
                    break;
                }
                sum += (it->first * it->second);
            }
            return sum;
        }

    private:
        SequencesLengthsHistogram& operator=(const SequencesLengthsHistogram&)= delete;

    };
}}

#endif    // SEQUENCES_LENGTHS_HISTOGRAM_HPP
