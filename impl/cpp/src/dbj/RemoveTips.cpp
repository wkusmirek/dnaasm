/**
 * \file RemoveTips.cpp
 * \brief the C++ file with implementation of specialized template class function to remove tips from graph
 *
 */

#include "RemoveTips.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    template<>
    void RemoveTips<UnitigsToContigsExtension::UnitigsGraph>::removeTips() {
        std::vector<unsigned short> inDegree(num_vertices(g_), 0U);
        countDegree(inDegree);
        std::vector<Vertex> startVertices;
        std::vector<Vertex> endVertices;
        unsigned short maxTipLength = 2U;
        typename boost::graph_traits<UnitigsToContigsExtension::UnitigsGraph>::vertex_iterator vi, vi_end;

        for (boost::tie(vi, vi_end)= vertices(g_); vi != vi_end; ++vi) {
            if (inDegree[*vi] == 0 && out_degree(*vi, g_) > 0) {
                startVertices.push_back(*vi);
            }

            if (out_degree(*vi, g_) > 1) {
                endVertices.push_back(*vi);
            }
        }

        for (typename std::vector<Vertex>::iterator it = startVertices.begin(); it != startVertices.end(); ++it) {
            if (g_[*it].sequenceSize_ == 2) {
                checkInTip(*it, inDegree, maxTipLength);
            }
        }

        for (typename std::vector<Vertex>::iterator it = endVertices.begin(); it != endVertices.end(); ++it) {
            checkOutTip(*it, maxTipLength);
        }
    }

    template<>
    unsigned int RemoveTips<UnitigsToContigsExtension::UnitigsGraph>::checkOutTip(Vertex& startVertex, unsigned short maxLength) {
        unsigned int sumOfRemovedOutTips = 0U;
        typename boost::graph_traits<UnitigsToContigsExtension::UnitigsGraph>::out_edge_iterator ei, ei_end;

        for (boost::tie(ei, ei_end)= out_edges(startVertex, g_); ei != ei_end; ++ei) {
            std::vector<Vertex> checkedVertices;
            checkedVertices.push_back(startVertex);
            Vertex current = target(*ei, g_);
            checkedVertices.push_back(current);
            unsigned short counter = 1U;

            while (true) {
                if (counter >= maxLength || out_degree(current, g_) > 1 || g_[current].sequenceSize_ != 2)
                    break;
                ++counter;
                if (out_degree(current, g_) == 0) {
                    deleteEdges(checkedVertices);
                    ++sumOfRemovedOutTips;
                    break;
                }
                typename UnitigsToContigsExtension::UnitigsGraph::out_edge_iterator e = out_edges(current, g_).first;
                current = target(*e, g_);
                checkedVertices.push_back(current);
            }
        }
        return sumOfRemovedOutTips;
    }

    template<>
    void RemoveTips<DeBruijnGraph>::countDegree(std::vector<unsigned short>& inDegree) {
        typename boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;

        for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
            if (g_[*ei].counter_ != 0U) {
                ++inDegree[target(*ei, g_)];
            }
        }
    }

    template<>
    void RemoveTips<DeBruijnGraph>::removeTips() {
        logInfo("removing tips...");
        std::vector<unsigned short> inDegree(num_vertices(g_), 0U);
        countDegree(inDegree);
        std::vector<Vertex> startVertices;
        std::vector<Vertex> endVertices;
        unsigned long numOfStartRemovedTips = 0U;
        unsigned long sumOfRemovedOutTips = 0U;
        unsigned short maxTipLength = 2 * k_;
        typename boost::graph_traits<DeBruijnGraph>::vertex_iterator vi, vi_end;

        for (boost::tie(vi, vi_end)= vertices(g_); vi != vi_end; ++vi) {
            Vertex current = *vi;

            if (inDegree[current] == 0 && countOutDegreeFromEdgesWithCounterGreaterThanZero(current) > 0) {
                startVertices.push_back(current);
            }

            if (countOutDegreeFromEdgesWithCounterGreaterThanZero(current) > 1) {
                endVertices.push_back(current);
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

    template<>
    unsigned int RemoveTips<DeBruijnGraph>::checkOutTip(Vertex& startVertex, unsigned short maxLength) {
        unsigned int sumOfRemovedOutTips = 0U;
        typename boost::graph_traits<DeBruijnGraph>::out_edge_iterator ei, ei_end;

        for (boost::tie(ei, ei_end)= out_edges(startVertex, g_); ei != ei_end; ++ei) {
            if (g_[*ei].counter_ == 0U) {
                continue;
            }

            std::vector<Vertex> checkedVertices;
            checkedVertices.push_back(startVertex);
            Vertex current = target(*ei, g_);
            checkedVertices.push_back(current);
            unsigned short counter = 1U;

            while (true) {
                if (counter >= maxLength || countOutDegreeFromEdgesWithCounterGreaterThanZero(current) > 1)
                    break;

                ++counter;

                if (countOutDegreeFromEdgesWithCounterGreaterThanZero(current) == 0) {
                    deleteEdges(checkedVertices);
                    ++sumOfRemovedOutTips;
                    break;
                }

                current = getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(current);

                if (current == (Vertex)(-1)) {
                    break;
                }

                checkedVertices.push_back(current);
            }
        }
        return sumOfRemovedOutTips;
    }

    template<>
    unsigned int RemoveTips<DeBruijnGraph>::checkInTip(Vertex& startVertex, std::vector<unsigned short>& inDegree, unsigned short maxLength) {
        std::vector<Vertex> checkedVertices;
        Vertex current = startVertex;
        checkedVertices.push_back(current);
        unsigned short counter = 0U;
        while (true) {
            ++counter;
            if (counter >= maxLength)
                return 0U;
            if (countOutDegreeFromEdgesWithCounterGreaterThanZero(current) == 0) {
                break;
            }
            current = getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(current);
            if (current == (Vertex)(-1)) {
                break;
            }
            checkedVertices.push_back(current);
            if (inDegree[current] > 1) {
                break;
            }
        }
        deleteEdges(checkedVertices);
        return 1;
    }

    template<>
    void RemoveTips<DeBruijnGraph>::deleteEdges(std::vector<Vertex>& checkedVertices) {
        unsigned int size = static_cast<unsigned int>(checkedVertices.size());
        for (unsigned int i = 0; i < size - 1; ++i) {
            if (!edge(checkedVertices[i], checkedVertices[i+1], g_).second) {
                continue;
            }
            if (g_[edge(checkedVertices[i], checkedVertices[i+1], g_).first].counter_ != 0U) {
                g_[edge(checkedVertices[i], checkedVertices[i+1], g_).first].counter_ = 0U;
                ++numOfRemovedTips_;
            }
        }
    }
}}
