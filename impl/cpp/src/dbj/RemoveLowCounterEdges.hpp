/**
 * \file RemoveLowCounterEdges.hpp
 * \brief the C++ file with implementation of template class for removing edges with low counter
 *
 */

#ifndef REMOVELOWCOUNTEREDGES_HPP
#define REMOVELOWCOUNTEREDGES_HPP

#include "globals.hpp"
#include "../common/log.hpp"
#include "UnitigsToContigsExtension.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to remove edges with low counter
    */
    template<class Graph> class RemoveLowCounterEdges {
    public:

        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;

        /**
         * \brief RemoveLowCounterEdges constructor.
         *
         * \param g reference to Graph object
         * \param edgeCounterThreshold edges with counters less than this value will be removed from graph
         */
        RemoveLowCounterEdges(Graph& g, unsigned short int edgeCounterThreshold)
            : g_(g)
            , edgeCounterThreshold_(edgeCounterThreshold)
        {}

        /**
         * \brief Removes edges with low counter.
         *
         * \return returns void
         */
        void operator()() {
            logInfo("removing low counter edges...");
            if (edgeCounterThreshold_ == 0) {
                return;
            }

            typename boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ < edgeCounterThreshold_) {
                    g_[*ei].counter_ = 0U;
                }
            }
        }

    private:
        Graph& g_;
        unsigned short int edgeCounterThreshold_;
        RemoveLowCounterEdges& operator=(const RemoveLowCounterEdges&)= delete;
    };

    template<>
    CALC_DLL(void RemoveLowCounterEdges<UnitigsToContigsExtension::UnitigsGraph>::operator()();)

}}

#endif    // REMOVELOWCOUNTEREDGES_HPP
