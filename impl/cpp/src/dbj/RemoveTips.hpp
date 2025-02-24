/**
 * \file RemoveTips.hpp
 * \brief the C++ file with implementation of template class for removing tips from graph
 */

#ifndef REMOVE_TIPS_HPP
#define REMOVE_TIPS_HPP

#include "globals.hpp"
#include "../common/log.hpp"
#include "UnitigsToContigsExtension.hpp"
#include <boost/graph/adjacency_iterator.hpp>

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
#pragma warning(disable:4512)
#endif

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to remove tips from the graph
    */
    template<class Graph> class RemoveTips {
    public:
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
        typedef typename boost::graph_traits<Graph>::adjacency_iterator adjacency_iterator;

        /**
         * \brief RemoveTips constructor.
         *
         * \param g reference to Graph object
         * \param k graph dimension
         */
        RemoveTips(Graph& g, unsigned short k): g_(g), numOfRemovedTips_(0U), k_(k) {}

        /**
         * \brief RemoveTips constructor.
         *
         * \param g reference to Graph object
         */
        explicit RemoveTips(Graph& g): g_(g), numOfRemovedTips_(0U), k_(0U) {}

        /**
         * \brief Romoves tips from the graph.
         *
         * \return returns number of removed tips
         */
        unsigned int operator()() {
            if (num_vertices(g_) == 0)
                return numOfRemovedTips_;

            removeTips();
            unsigned int tmpNumOfRemovedTips = numOfRemovedTips_;

            while (numOfRemovedTips_ != 0) {
                removeTips();

                if (tmpNumOfRemovedTips == numOfRemovedTips_)
                    break;
                tmpNumOfRemovedTips = numOfRemovedTips_;
            }

            while (numOfRemovedTips_ != 0) {
                removeTips();

                if (tmpNumOfRemovedTips == numOfRemovedTips_)
                    break;
                tmpNumOfRemovedTips = numOfRemovedTips_;
            }

            return numOfRemovedTips_;
        }

    private:
        Graph& g_;
        unsigned int numOfRemovedTips_;
        unsigned short k_;
        std::vector<Edge> edgesToDelete_;
        std::vector<Vertex> verticesToDelete_;
        RemoveTips& operator=(const RemoveTips&)= delete;

        /**
         * \brief Counts degrees for each vertex.
         *
         * \param inDegree number of all 'in' edges for each vertex will be stored here
         * \return returns void
         */
        void countDegree(std::vector<unsigned short>& inDegree) {
            /*typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end)= edges(g_); ei != ei_end; ++ei) {
                ++inDegree[target(*ei, g_)];
            }*/

            //v

            for (const auto &e : boost::make_iterator_range(edges(g_)))
                ++inDegree[target(e, g_)];
        }

        /**
         * \brief Removes tips from graph, specialized from another graphs (see the end of this file and RemoveTips.cpp file).
         *
         * \return returns void
         */
        void removeTips() {
            logInfo("removing tips...");
            std::vector<unsigned short> inDegree(num_vertices(g_), 0U);
            countDegree(inDegree);
            std::vector<Vertex> startVertices;
            std::vector<Vertex> endVertices;
            unsigned long numOfStartRemovedTips = 0U;
            unsigned long sumOfRemovedOutTips = 0U;
            unsigned short maxTipLength = 2 * k_;
            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end)= vertices(g_); vi != vi_end; ++vi) {
                if (inDegree[*vi] == 0 && out_degree(*vi, g_) > 0) {
                    startVertices.push_back(*vi);
                }

                if (out_degree(*vi, g_) > 1) {
                    endVertices.push_back(*vi);
                }
            }

            for (typename std::vector<Vertex>::iterator it = startVertices.begin(); it != startVertices.end(); ++it) {
                numOfStartRemovedTips += checkInTip(*it, inDegree, maxTipLength);
            }

            for (typename std::vector<Vertex>::iterator it = endVertices.begin(); it != endVertices.end(); ++it) {
                sumOfRemovedOutTips += checkOutTip(*it, maxTipLength);
            }

            logInfo("Removed " + std::to_string(numOfStartRemovedTips + sumOfRemovedOutTips)
                    + " tips: " + std::to_string(numOfStartRemovedTips)
                    + " for start vertices and "
                    + std::to_string(sumOfRemovedOutTips)
                    + " for end vertices.");
        }

        /**
         * \brief Checks if 'out' tip should be removed, specialized from another graphs (see the end of this file and RemoveTips.cpp file)
         *
         * \param startVertex first vertex in tip
         * \param maxLength mazimum length of tip
         * \return number of 'out' tips deletion
         */
        unsigned int checkOutTip(Vertex& startVertex, unsigned short maxLength) {
            unsigned int sumOfRemovedOutTips = 0U;
            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end)= out_edges(startVertex, g_); ei != ei_end; ++ei) {
                std::vector<Vertex> checkedVertices;
                checkedVertices.push_back(startVertex);
                Vertex current = target(*ei, g_);
                checkedVertices.push_back(current);
                unsigned short counter = 1U;

                while (true) {
                    if (counter >= maxLength || out_degree(current, g_) > 1)
                        break;

                    ++counter;

                    if (out_degree(current, g_) == 0) {
                        deleteEdges(checkedVertices);
                        ++sumOfRemovedOutTips;
                        break;
                    }

                    typename Graph::out_edge_iterator e = out_edges(current, g_).first;
                    current = target(*e, g_);
                    checkedVertices.push_back(current);
                }
            }
            return sumOfRemovedOutTips;
        }

        /**
         * \brief Checks if 'in' tip should be removed.
         *
         * \param startVertex first vertex in tip
         * \param inDegree vector of in degrees
         * \param maxLength maximum length of tip
         * \return number of 'in' tips deletion
         */
        unsigned int checkInTip(Vertex& startVertex, std::vector<unsigned short>& inDegree, unsigned short maxLength) {
            std::vector<Vertex> checkedVertices;
            Vertex current = startVertex;
            checkedVertices.push_back(current);
            unsigned short counter = 0U;

            while (true) {
                ++counter;

                if (counter >= maxLength)
                    return 0U;

                if (out_degree(current, g_) == 0)
                    break;

                typename Graph::out_edge_iterator e = out_edges(current, g_).first;
                current = target(*e, g_);
                checkedVertices.push_back(current);

                if (inDegree[current] > 1)
                    break;
            }

            deleteEdges(checkedVertices);
            return 1;
        }

        /**
         * \brief Deletes edges for set of vertices.
         *
         * \param checkedVertices set of vertices
         * \return returns void
         */
        void deleteEdges(std::vector<Vertex>& checkedVertices) {
            unsigned int size = static_cast<unsigned int>(checkedVertices.size());

            for (unsigned int i = 0; i < size - 1; ++i) {
                if (!edge(checkedVertices[i], checkedVertices[i+1], g_).second) {
                    continue;
                }

                remove_edge(edge(checkedVertices[i], checkedVertices[i+1], g_).first, g_);
                ++numOfRemovedTips_;
            }
        }

        unsigned short countOutDegreeFromEdgesWithCounterGreaterThanZero(Vertex& vertex) {
            unsigned short outDegree = 0U;
            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = out_edges(vertex, g_); ei != ei_end; ++ei) {
                if (g_[edge(vertex, target(*ei, g_), g_).first].counter_ != 0U) {
                    ++outDegree;
                }
            }
            return outDegree;
        }

        Vertex getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(Vertex& vertex) {
            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = out_edges(vertex, g_); ei != ei_end; ++ei) {
                if (g_[edge(vertex, target(*ei, g_), g_).first].counter_ != 0U) {
                    return target(*ei, g_);
                }
            }
            return (Vertex)(-1);
        }

    };

    template<>
    CALC_DLL(void RemoveTips<UnitigsToContigsExtension::UnitigsGraph>::removeTips();)

    template<>
    CALC_DLL(unsigned int RemoveTips<UnitigsToContigsExtension::UnitigsGraph>::checkOutTip(Vertex& startVertex, unsigned short maxLength);)

    template<>
    CALC_DLL(void RemoveTips<DeBruijnGraph>::countDegree(std::vector<unsigned short>& inDegree);)

    template<>
    CALC_DLL(void RemoveTips<DeBruijnGraph>::removeTips();)

    template<>
    CALC_DLL(unsigned int RemoveTips<DeBruijnGraph>::checkOutTip(Vertex& startVertex, unsigned short maxLength);)

    template<>
    CALC_DLL(unsigned int RemoveTips<DeBruijnGraph>::checkInTip(Vertex& startVertex, std::vector<unsigned short>& inDegree, unsigned short maxLength);)

    template<>
    CALC_DLL(void RemoveTips<DeBruijnGraph>::deleteEdges(std::vector<Vertex>& checkedVertices);)

}}

#endif    // REMOVE_TIPS_HPP
