/**
 * \file FilterGraph.hpp
 * \brief the C++ file with implementation of class for filtering subgraph from original graph (much faster for filtering small graph from large graph than BGL implementation)
 */

#ifndef FILTER_GRAPH_HPP
#define FILTER_GRAPH_HPP

#include "globals.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to filter subgraph from original graph.
    */
    template<class Graph> class FilterGraph {
    public:

        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;

        /**
         * \brief FilterGraph constructor.
         *
         * \param originalGraph reference to graph object, which will be filtered
         */
        FilterGraph(Graph& originalGraph): originalGraph_(originalGraph) {}

        /**
         * \brief Filters subgraph from original graph using information from isConnected vector.
         *
         * \param filteredSubgraph resultant, filtered graph
         * \param isConnected vector with information, if specified vertex of original graph is connected
         * \return returns vector with information about maping id of vertices: filtered subgraph vertices id -> original graph vertices id
         */
        std::vector<Vertex> operator()(Graph& filteredSubgraph, std::vector<bool>& isConnected) {
            std::vector<Vertex> connectedVerticesId;
            if (num_vertices(originalGraph_) == isConnected.size()) {
                for (std::vector<bool>::iterator it = isConnected.begin(); it != isConnected.end(); ++it) {
                    if (*it) {
                        Vertex v = add_vertex(filteredSubgraph);
                        filteredSubgraph[v] = originalGraph_[it-isConnected.begin()];
                        connectedVerticesId.push_back((Vertex)(it-isConnected.begin()));
                    }
                }

                typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

                for (typename std::vector<Vertex>::iterator it = connectedVerticesId.begin(); it != connectedVerticesId.end(); ++it) {
                    for (boost::tie(ei, ei_end) = out_edges(*it, originalGraph_); ei != ei_end; ++ei) {
                        if (originalGraph_[*ei].isForConnectedSequences_ && isConnected[target(*ei, originalGraph_)]) {
                            Vertex sourceVertex = it-connectedVerticesId.begin();
                            Vertex targetVertex = find(connectedVerticesId.begin(), connectedVerticesId.end(), target(*ei, originalGraph_))-connectedVerticesId.begin();
                            Edge e = add_edge(sourceVertex, targetVertex, filteredSubgraph).first;
                            filteredSubgraph[e] = originalGraph_[*ei];
                        }
                    }
                }
            }
            return connectedVerticesId;
        }

    private:
        FilterGraph& operator=(const FilterGraph&)= delete;
        Graph& originalGraph_;

    };

}}

#endif  // FILTER_GRAPH_HPP
