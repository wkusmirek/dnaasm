/**
 * \file EdgeNormalization.hpp
 * \brief the C++ file with implementation of template class for normalizing counters of edges
 */

#ifndef EDGE_NORMALIZATION_HPP
#define EDGE_NORMALIZATION_HPP

#include <cmath>
#include "globals.hpp"
#include "../common/log.hpp"

#include "Histogram.hpp"
#include <fstream>

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to normalize counters of edges
    */
    template<class Graph> class EdgeNormalization {
    public:

        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;

        /**
         * \brief EdgeNormalization constructor.
         *
         * \param g reference to Graph object
         * \param k graph dimension
         * \param originalGenomeLength original genome length
         * \param edgeCounterThreshold edges with counters less than this value will be removed from graph
         */
        EdgeNormalization(Graph& g,
                          unsigned short k,
                          unsigned long long int originalGenomeLength,
                          unsigned short int edgeCounterThreshold)
            : g_(g)
            , k_(k)
            , originalGenomeLength_(originalGenomeLength)
            , normalizationRate_(1.0F)
            , deletedEdgesCountersSumWhileNormalization_(0U)
            , edgeCounterThreshold_(edgeCounterThreshold)
            , edgesCountersSum_(0U)
        { countNormalizationRate(); }

        /**
         * \brief Normalizes counter of each edge.
         *
         * \return returns void
         */
        void normalizeEdges() {
            countNewCountersForEdges();
            deleteEdges();
        }

        /**
         * \brief Gets value of normalization rate.
         *
         * \return value of normalization rate
         */
        float getNormalizationRate() {
            return normalizationRate_;
        }

    private:
        EdgeNormalization& operator=(const EdgeNormalization&)= delete;
        Graph& g_;
        unsigned short k_;
        unsigned long long int originalGenomeLength_;
        float normalizationRate_;
        unsigned int deletedEdgesCountersSumWhileNormalization_;
        unsigned short int edgeCounterThreshold_;
        unsigned long edgesCountersSum_;

        /**
         * \brief Counts normalization rate.
         *
         * \return returns void
         */
        void countNormalizationRate() {
            if (k_ == 0U || originalGenomeLength_ == 0U || num_vertices(g_) == 0 || num_edges(g_) == 0) {
                normalizationRate_ = 1.0F;
                return;
            }
            countDeletedEdgesCountersSumWhileNormalization();
            countEdgesCountersSum();
            normalizationRate_ = ((originalGenomeLength_ - k_)
                                 / static_cast<float>(edgesCountersSum_
                                                      - static_cast<unsigned long>(deletedEdgesCountersSumWhileNormalization_))) * 2;
            logInfo("normalization rate: " + std::to_string(normalizationRate_));
        }

        /**
         * \brief Counts sum of counters of edges, which counters are less or equal to threshold.
         *
         * \return returns void
         */
        void countDeletedEdgesCountersSumWhileNormalization() {
            deletedEdgesCountersSumWhileNormalization_ = 0U;
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end)= edges(g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ <= edgeCounterThreshold_)
                    deletedEdgesCountersSumWhileNormalization_ += g_[*ei].counter_;
            }
        }

        /**
         * \brief Counts sum of counters of all edges.
         *
         * \return returns void
         */
        void countEdgesCountersSum() {
            edgesCountersSum_ = 0U;
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end)= edges(g_); ei != ei_end; ++ei) {
                edgesCountersSum_ += static_cast<unsigned long>(g_[*ei].counter_);
            }
        }

        /**
         * \brief Counts new counter for each edge and updates degree for source and target vertex.
         *
         * \return returns void
         */
        void countNewCountersForEdges() {
            Histogram<unsigned short> countersBeforeNormalizationHistogram;
            Histogram<unsigned short> countersAfterNormalizationHistogram;
            typename boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
            unsigned short deletedCountersSum = 0U;
            for (boost::tie(ei, ei_end)= edges(g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ == 0U) {
                    countersAfterNormalizationHistogram.addSingleData(0U);
                    countersBeforeNormalizationHistogram.addSingleData(0U);
                    continue;
                }

                unsigned short counterAfterNormalization = static_cast<unsigned short>(round(normalizationRate_ * g_[*ei].counter_));
                if (counterAfterNormalization == 0U)
                    deletedCountersSum += g_[*ei].counter_;
                if (counterAfterNormalization == 0U && g_[*ei].counter_ >= edgeCounterThreshold_)
                    counterAfterNormalization = 1U;
                countersAfterNormalizationHistogram.addSingleData(counterAfterNormalization);
                countersBeforeNormalizationHistogram.addSingleData(g_[*ei].counter_);
                g_[*ei].counter_ = counterAfterNormalization;
            }

            logHistograms(countersBeforeNormalizationHistogram, countersAfterNormalizationHistogram);
            logInfo("Sum of deleted edges counters while normalization: " + std::to_string(deletedCountersSum));
        }

        /**
         * \brief Logs histograms to file.
         *
         * \param countersBeforeNormalizationHistogram histogram with counters for all edges before normalization
         * \param countersAfterNormalizationHistogram histogram with counters for all edges after normalization
         * \return returns void
         */
        void logHistograms(Histogram<unsigned short> countersBeforeNormalizationHistogram, Histogram<unsigned short> countersAfterNormalizationHistogram) {
            std::ofstream ofile(CALC_TMP_DIR+std::string("edgesCountersHistogram"));
            ofile << "Before normalization:" << std::endl;
            for (std::vector<std::pair<unsigned short, unsigned int>>::const_iterator it = countersBeforeNormalizationHistogram.getHistogramContainer().begin();
                 it != countersBeforeNormalizationHistogram.getHistogramContainer().end(); ++it) {
                ofile << it->first << " " << it->second << std::endl;
            }

            ofile << "avg: " << countersBeforeNormalizationHistogram.getAverage() << std::endl;
            ofile << std::endl << "After normalization:" << std::endl;
            for (std::vector<std::pair<unsigned short, unsigned int>>::const_iterator it = countersAfterNormalizationHistogram.getHistogramContainer().begin();
                 it != countersAfterNormalizationHistogram.getHistogramContainer().end(); ++it) {
                ofile << it->first << " " << it->second << std::endl;
            }
            ofile << std::endl << "normalization rate: " << normalizationRate_ << std::endl;
        }
        /**
         * \brief Removes edges with counter = 0 and counts degrees for vertices.
         *
         * \return returns void
         */
        void deleteEdges() {
            /*std::vector<Edge> edgesToDelete;
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end)= edges(g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ == 0U) {
                    edgesToDelete.push_back(*ei);
                }
            }

            unsigned int i = 0;
            logInfo("Normalization deletes " + std::to_string(edgesToDelete.size())+ " edges");
            for (unsigned int size = static_cast<unsigned int>(edgesToDelete.size()); i != size; ++i) {
                remove_edge(edgesToDelete.back(), g_);
                edgesToDelete.pop_back();
            }*/
        }

    };

}}

#endif    // EDGE_NORMALIZATION_HPP
