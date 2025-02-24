/**
 * \file CorrectEdgeCounter.hpp
 * \brief the C++ file with implementation of template class for correcting weights of connected (like in contig) edges in graph
 */


#ifndef CORRECT_EDGE_COUNTER_HPP
#define CORRECT_EDGE_COUNTER_HPP
#include <iostream>
#include <fstream>
#include "Histogram.hpp"
#include "globals.hpp"
#include "../common/log.hpp"

//#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
//#pragma warning(disable:4512)
//#endif

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to correct weights of simple connected (like in contig) edges in graph
    */
    template<class Graph> class CorrectEdgeCounter {
    public:
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;

        /**
         * \brief CorrectEdgeCounter constructor.
         *
         * \param g reference to Graph object
         */
        explicit CorrectEdgeCounter(Graph& g): g_(g) {}

        /**
         * \brief Corrects weights of simple connected (like in contig) edges in graph.
         *
         * \return returns void
         */
        void operator()() {
            logInfo("correcting weights of connected edges...");
            std::vector<unsigned short> inDegree(num_vertices(g_), 0U);
            std::vector<unsigned short> outDegree(num_vertices(g_), 0U);
            std::vector<bool> ambiguousVertices(num_vertices(g_), false);
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ != 0U) {
                    ++inDegree[target(*ei, g_)];
                    ++outDegree[source(*ei, g_)];
                }
            }
            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                if (inDegree[*vi] != 1U || outDegree[*vi] != 1U) {
                    ambiguousVertices[*vi] = true;
                }
            }
            for (std::vector<bool>::iterator it = ambiguousVertices.begin(); it != ambiguousVertices.end(); ++it) {
                if (*it == true) {
                    correctPath((Vertex)(it-ambiguousVertices.begin()), ambiguousVertices);
                }
            }
        }


    private:
        CorrectEdgeCounter& operator=(const CorrectEdgeCounter&)= delete;
        Graph& g_;

        void correctPath(Vertex startVertex, std::vector<bool>& ambiguousVertices) {
            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = out_edges(startVertex, g_); ei != ei_end; ++ei) {
                std::vector<Vertex> consideredVertices;
                consideredVertices.push_back(startVertex);
                if (g_[*ei].counter_ == 0U) {
                    continue;
                }
                unsigned int sumOfCounters = 0U;
                unsigned int numOfEdges = 0U;
                Vertex current = startVertex;
                const Edge& ee = *ei;
                ++numOfEdges;
                sumOfCounters += g_[ee].counter_;
                current = target(ee, g_);
                while (true) {
                    consideredVertices.push_back(current);
                    if (ambiguousVertices[current] == true) {
                        break;
                    }
                    Vertex nextVertex = getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(current);
                    if (nextVertex == (Vertex)(-1)) {
                        break;
                    }
                    ++numOfEdges;
                    sumOfCounters += g_[edge(current, nextVertex, g_).first].counter_;
                    current = nextVertex;
                }
                unsigned short newCounter = static_cast<unsigned short>(round(static_cast<float>(sumOfCounters) / static_cast<float>(numOfEdges)));
                unsigned int size = static_cast<unsigned int>(consideredVertices.size());
                for (unsigned int i = 0; i < size - 1; ++i) {
                    if (!edge(consideredVertices[i], consideredVertices[i+1], g_).second) {
                        continue;
                    }
                    g_[edge(consideredVertices[i], consideredVertices[i+1], g_).first].counter_ = newCounter;
                }
            }
        }

        Vertex getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(Vertex& vertex) {
            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = out_edges(vertex, g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ != 0U) {
                    return target(*ei, g_);
                }
            }
            return (Vertex)(-1);
        }

    };

}}

#endif    //CORRECT_EDGE_COUNTER_HPP
