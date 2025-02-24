/**
 * \file isAcyclic.hpp
 * \brief the C++ file with implementation of function for checking if graph is acyclic
 */

#ifndef IS_ACYCLIC_HPP
#define IS_ACYCLIC_HPP

#include "existreturnpath.hpp"

namespace dnaasm { namespace dbj {

    /**
     * \brief Checks if graph is acyclic.
     *
     * \param graph reference to Graph object
     * \return returns true if graph is acyclic, false otherwise.
     */
    template<typename Graph>
    bool isAcyclic(const Graph& graph) {
        typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

        for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
            if (existReturnPath(graph, *ei)) {
                return false;
            }
        }
        return true;
    }

}}

#endif    // IS_ACYCLIC_HPP
