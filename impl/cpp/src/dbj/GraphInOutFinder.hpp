/**
 * \file GraphInOutFinder.hpp
 * \brief the C++ file with implementation of template class for finding in and out vertices of the specified graph
 */

#ifndef GRAPH_IN_OUT_FINDER_HPP
#define GRAPH_IN_OUT_FINDER_HPP

#include "globals.hpp"

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to find in and out vertices of the specified graph
    */
    template<class Graph> class GraphInOutFinder {
    public:

        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;

        /**
         * \brief GraphInOutFinder constructor.
         *
         * \param graph reference to Graph object
         */
        GraphInOutFinder(const Graph& graph): graph_(graph) {}

        /**
         * \brief Finds in vertices of the graph.
         *
         * \param inVertices in vertices of the graph will be stored in this vector
         * \return returns void
         */
        void findInVertices(std::vector<Vertex>& inVertices) {
            std::vector<unsigned short> in_degree(num_vertices(graph_), 0U);
            std::vector<unsigned short> out_degree(num_vertices(graph_), 0U);
            countDegrees(in_degree, out_degree);
            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end)= vertices(graph_); vi != vi_end; ++vi) {
                if (in_degree[*vi] == 0 && out_degree[*vi] > 0) {
                    inVertices.push_back(*vi);
                }
            }
        }

        /**
         * \brief Finds out vertices of the graph.
         *
         * \param outVertices out vertices of the graph will be stored in this vector
         * \return returns void
         */
        void findOutVertices(std::vector<Vertex>& outVertices) {
            std::vector<unsigned short> in_degree(num_vertices(graph_), 0U);
            std::vector<unsigned short> out_degree(num_vertices(graph_), 0U);
            countDegrees(in_degree, out_degree);
            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end)= vertices(graph_); vi != vi_end; ++vi) {
                if (in_degree[*vi] > 0 && out_degree[*vi] == 0) {
                    outVertices.push_back(*vi);
                }
            }
        }

    private:
        GraphInOutFinder& operator=(const GraphInOutFinder&)= delete;
        const Graph& graph_;

        /**
         * \brief Counts degrees (in and out) of each vertex of graph.
         *
         * \param in_degree vector of information about number of in-edges for each vertex
         * \param out_degree vector of information about number of out-edges for each vertex
         * \return returns void
         */
        void countDegrees(std::vector<unsigned short>& in_degree, std::vector<unsigned short>& out_degree) {
            /*typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end)= edges(graph_); ei != ei_end; ++ei) {
                ++in_degree[target(*ei, graph_)];
                ++out_degree[source(*ei, graph_)];
            }*/

            for (const auto &e : boost::make_iterator_range(edges(graph_))) {
                ++in_degree[target(e, graph_)];
                ++out_degree[source(e, graph_)];
            }
        }

    };
}}

#endif  // GRAPH_IN_OUT_FINDER_HPP
