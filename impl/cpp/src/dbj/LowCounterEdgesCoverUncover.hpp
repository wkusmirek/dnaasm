/**
 * \file LowCounterEdgesCoverUncover.hpp
 * \brief the C++ file with implementation of template class for covering and uncovering edges with low counter
 *
 */

#ifndef LOW_COUNTER_EDGES_COVER_UNCOVER_HPP
#define LOW_COUNTER_EDGES_COVER_UNCOVER_HPP

#include "UnitigsToContigsExtension.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to cover and uncover edges with low counter
    */
    template<class Graph> class LowCounterEdgesCoverUncover {
    public:

        /**
         * \brief LowCounterEdgesCoverUncover constructor.
         *
         * \param g reference to Graph object
         */
        LowCounterEdgesCoverUncover(Graph& g)
            : g_(g)
        {}

        /**
         * \brief Covers edges with low counter.
         *
         * \param edgeCounterThreshold edges with counters less than this value will be covered in the graph
         * \return returns void
         */
        void cover(unsigned short edgeCounterThreshold) {
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ < edgeCounterThreshold && g_[*ei].isForPairedReads_) {
                    g_[*ei].isForPairedReads_ = false;
                    g_[*ei].counter_ = std::numeric_limits<unsigned short>::max() - g_[*ei].counter_;
                }
            }
        }

        /**
         * \brief Uncovers edges covered by cover function.
         *
         * \return returns void
         */
        void uncover() {
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ > std::numeric_limits<unsigned short>::max() - 100U) {
                    g_[*ei].isForPairedReads_ = true;
                    g_[*ei].counter_ = std::numeric_limits<unsigned short>::max() - g_[*ei].counter_;
                }
            }
        }

    private:
        Graph& g_;
        LowCounterEdgesCoverUncover& operator=(const LowCounterEdgesCoverUncover&)= delete;
    };

}}

#endif    // LOW_COUNTER_EDGES_COVER_UNCOVER_HPP
