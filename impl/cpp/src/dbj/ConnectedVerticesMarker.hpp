/**
 * \file ConnectedVerticesMarker.hpp
 * \brief the C++ file with implementation of template class for marking connected vertices
 *
 */

#ifndef CONNECTED_VERTICES_MARKER_HPP
#define CONNECTED_VERTICES_MARKER_HPP

#include "globals.hpp"
#include "../common/log.hpp"
#include "RemoveTips.hpp"
#include "isAcyclic.hpp"
#include "GraphInOutFinder.hpp"
#include "FilterGraph.hpp"
#include <boost/graph/topological_sort.hpp>

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to mark connected (only by paired reads) vertices graph.
    */
    template<class Graph> class ConnectedVerticesMarker {
    public:

        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;

        /**
         * \brief ConnectedVerticesMarker constructor.
         *
         * \param graph reference to graph of sequences object
         * \param startVertex vertex of sequences graph for which connected vertices should be marked
         * \param isConnected vector with information, if specified vertex of sequences graph is connected
         */
        ConnectedVerticesMarker(Graph& graph, Vertex& startVertex, std::vector<bool>& isConnected)
            : graph_(graph)
            , filterGraph_(graph_)
            , startVertex_(startVertex)
            , isConnected_(isConnected)
            , wasConsidered_(num_vertices(graph_)
            , false)
        {}

        /**
         * \brief Marks connected (only by paired reads) vertices of sequences graph.
         *
         * \return returns void
         */
        void operator()() {
            markAllConnectedVerticesForVertex(startVertex_);
            wasConsidered_[startVertex_] = true;

            for (unsigned int i = 0U; i < 10U; ++i) {
                Graph filteredGraph;
                std::vector<Vertex> connectedVerticesId = filterGraph_(filteredGraph, isConnected_);
                std::vector<Vertex> inVertices;
                std::vector<Vertex> outVertices;
                RemoveTips<Graph> removeTips(filteredGraph);
                removeTips();
                GraphInOutFinder<Graph> graphInOutFinder(filteredGraph);
                graphInOutFinder.findInVertices(inVertices);
                graphInOutFinder.findOutVertices(outVertices);
                if (inVertices.size() == 1 && outVertices.size() == 1 && filteredGraph[inVertices[0]].isLongNode_ &&
                    filteredGraph[outVertices[0]].isLongNode_ && filteredGraph[inVertices[0]].isOriginal_ &&
                    filteredGraph[outVertices[0]].isOriginal_) {
                    return;
                }

                if (isAcyclic(filteredGraph)) {
                    unsigned int maxVertexSize = 0U;
                    Vertex maxVertex;

                    typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
                    for (boost::tie(vi, vi_end) = vertices(filteredGraph); vi != vi_end; ++vi) {
                        Vertex v = connectedVerticesId[*vi];
                        if (graph_[v].isLongNode_ == false && graph_[v].isOriginal_ == true &&
                            wasConsidered_[v] == false) {
                            if (graph_[v].sequenceSize_ > maxVertexSize) {
                                maxVertexSize = graph_[v].sequenceSize_;
                                maxVertex = v;
                            }
                        }
                    }
                    if (maxVertexSize != 0U) {
                        markAllConnectedVerticesForVertex(maxVertex);
                        wasConsidered_[maxVertex] = true;
                    }
                }
            }
            return;
        }

    private:
        ConnectedVerticesMarker& operator=(const ConnectedVerticesMarker&) = delete;
        Graph& graph_;
        FilterGraph<Graph> filterGraph_;
        Vertex& startVertex_;
        std::vector<bool>& isConnected_;
        std::vector<bool> wasConsidered_;

        /**
         * \brief Marks connected (only by paired reads) vertices of sequences graph (for specified vertex).
         *
         * \param vertex vertex of sequences graph for which connected vertices should be marked
         * \return returns void
         */
        void markAllConnectedVerticesForVertex(Vertex& vertex) {
            isConnected_[vertex] = true;
            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

            for (tie(ei, ei_end) = out_edges(vertex, graph_); ei != ei_end; ++ei) {
                if (graph_[*ei].isForPairedReads_ == false) {
                    continue;
                }

                Vertex tmpVertex = target(*ei, graph_);
                isConnected_[tmpVertex] = true;
            }
        }
    };

}}
#endif    // CONNECTED_VERTICES_MARKER_HPP
