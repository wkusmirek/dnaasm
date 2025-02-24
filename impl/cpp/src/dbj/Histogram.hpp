/**
 * \file Histogram.hpp
 * \brief the C++ file with implementation of template class for collecting histogram
 *
 */

#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

#include "globals.hpp"
#include <boost/bind.hpp>

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to collect histogram.
     */
    template<class DataType> class Histogram {

    public:

        typedef std::vector<std::pair<DataType, unsigned int>> HistogramContainer;

        /**
         * \brief Histogram constructor.
         *
         */
        Histogram() : isSorted(true) {}

        /**
         * \brief Adds single data to a histogram container.
         *
         * \param data data which will be added to a histogram container
         * \return returns void
         */
        void addSingleData(DataType data) {
            typename HistogramContainer::iterator histogramContainerIt;

            histogramContainerIt = find_if (histogramContainer.begin(),
                                            histogramContainer.end(),
                                            [&data] (const std::pair<DataType, unsigned int>& element) {
                                                return element.first == data;
                                            });

            if (histogramContainerIt == histogramContainer.end()) {
                std::pair<DataType, unsigned int> temp (data, 1);
                histogramContainer.push_back(temp);
                isSorted = false;
            } else {
                histogramContainerIt->second += 1;
            }
        }

        /**
         * \brief Gets median of histogram container.
         *
         * \return returns median of histogram container
         */
        const float getMedian() {
            if (!isSorted) {
                sortHistogramContainer();
            }

            unsigned int size = 0, index = 0;

            for (typename HistogramContainer::iterator it = histogramContainer.begin(); it != histogramContainer.end(); ++it) {
                size += it->second;
            }

            for (typename HistogramContainer::iterator it = histogramContainer.begin(); it != histogramContainer.end(); ++it) {
                index += it->second;
                if (index >= size/2) {
                    if (index == size/2 && size % 2 == 0) {
                        return static_cast<float>(it->first + (++it)->first)/ 2;
                    }
                    if (index == size/2 && size % 2 == 1) {
                        return static_cast<float>((++it)->first);
                    }
                    return static_cast<float>(it->first);
                }
            }
            return 0;
        }

        /**
         * \brief Gets max value of histogram container.
         *
         * \return returns max value of histogram container
         */
        const DataType getMax() {
            if (!isSorted) {
                sortHistogramContainer();
            }

            if (histogramContainer.size() != 0)
                return histogramContainer.back().first;
            else
                return 0;
        }

        /**
         * \brief Gets min value of histogram container.
         *
         * \return returns min value of histogram container
         */
        const DataType getMin() {
            if (!isSorted) {
                sortHistogramContainer();
            }

            if (histogramContainer.size() != 0)
                return histogramContainer[0].first;
            else
                return 0;
        }

        /**
         * \brief Gets average value of histogram container.
         *
         * \return returns average value of histogram container
         */
        const float getAverage() {
            if (histogramContainer.size() == 0)
                return 0;
            unsigned int size = 0U;
            unsigned long sum = 0U;

            for (typename HistogramContainer::iterator it = histogramContainer.begin(); it != histogramContainer.end(); ++it) {
                size += it->second;
                sum += static_cast<unsigned long>((it->first * (DataType)it->second));
            }

            return static_cast<float>(sum)/static_cast<float>(size);
        }

        /**
         * \brief Gets num of elements in histogram container.
         *
         * \return returns num of elements in histogram container
         */
        unsigned long getNumOfElements() {
            unsigned long size = 0;
            for (typename HistogramContainer::iterator it = histogramContainer.begin(); it != histogramContainer.end(); ++it) {
                size += it->second;
            }

            return size;
        }

        /**
         * \brief Gets size of histogram container.
         *
         * \return returns size of histogram container
         */
        unsigned long long getSum() {
            unsigned long long sum = 0;

            for (typename HistogramContainer::iterator it = histogramContainer.begin(); it != histogramContainer.end(); ++it) {
                sum += (it->first * it->second);
            }
            return sum;
        }

        /**
         * \brief Gets the reference to HistogramContainer object.
         *
         * \return returns reference to HistogramContainer object
         */
        const HistogramContainer& getHistogramContainer() {
            sortHistogramContainer();
            return histogramContainer;
        }

    protected:
        HistogramContainer histogramContainer;
        bool isSorted;

        /**
        * \brief Sorts histogram container.
        *
        * \return returns void
        */
        void sortHistogramContainer() {
            sort(histogramContainer.begin(), histogramContainer.end(),
                 boost::bind(&std::pair<DataType, unsigned int>::first, _1) <
                 boost::bind(&std::pair<DataType, unsigned int>::first, _2));
            isSorted = true;
        }

    private:
        Histogram& operator=(const Histogram&)= delete;
    };
}}

#endif    //HISTOGRAM_HPP
