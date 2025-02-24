/**
 * \file ClearGraph.hpp
 * \brief the C++ file with implementation of template class for clearing graph from inproper edges and vertices
 */


#ifndef CLEAR_GRAPH_HPP
#define CLEAR_GRAPH_HPP

#include "globals.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to clear graph from inproper edges and vertices
    */
    template<class Graph> class ClearGraph {
    public:
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;

        ClearGraph(Graph& g) : g_(g) {}

        void removeInEdgesForStartVertex(Vertex& startVertex)
        {
            std::vector<boost::adjacency_list<>::edge_descriptor> edgesToDelete;
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end)= edges(g_); ei != ei_end; ++ei)
            {
                if (target(*ei, g_) == startVertex)
                {
                    edgesToDelete.push_back(*ei);
                }
            }
            for (std::vector<boost::adjacency_list<>::edge_descriptor>::iterator it = edgesToDelete.begin(); it != edgesToDelete.end(); ++it)
            {
                remove_edge(*it, g_);
            }
        }

        void removeOutEdgesForEndVertex(Vertex& startVertex)
        {
            std::vector<boost::adjacency_list<>::edge_descriptor> edgesToDelete;
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end)= edges(g_); ei != ei_end; ++ei)
            {
                if (source(*ei, g_) != startVertex && g_[source(*ei, g_)].isLongNode_ && g_[source(*ei, g_)].isOriginal_)
                {
                    edgesToDelete.push_back(*ei);
                }
            }
            for (std::vector<boost::adjacency_list<>::edge_descriptor>::iterator it = edgesToDelete.begin(); it != edgesToDelete.end(); ++it)
            {
                remove_edge(*it, g_);
            }
        }

    private:
        ClearGraph& operator=(const ClearGraph&)= delete;
        Graph& g_;

    };
}}

#endif    // CLEAR_GRAPH_HPP
