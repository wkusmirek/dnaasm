/**
 * \file RemoveBubbles.hpp
 * \brief the C++ file with implementation of template class for removing bubbles from the graph
 */

#ifndef REMOVE_BUBBLES_HPP
#define REMOVE_BUBBLES_HPP

#include "../common/log.hpp"
#include "../common/DnaSequenceRepresentationConverter.hpp"
#include "globals.hpp"
#include <fstream>
#include <iomanip>

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
#pragma warning(disable:4512)
#endif

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to remove bubbles from the graph
    */
    template<class Graph> class RemoveBubbles {
    public:
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
        typedef boost::tuple<std::vector<Vertex>, unsigned short, unsigned short, float> Bubble;
        typedef std::vector<Bubble> Bubbles;

        /**
         * \brief RemoveBubbles constructor.
         *
         * \param g reference to Graph object
         * \param k graph dimension
         * \param bubbles bubbles collection
         * \param normalizationRate value of normalization rate
         */
        RemoveBubbles(Graph& g, unsigned short k, float normalizationRate)
            : g_(g)
            , bubbles_(0)
            , K1_(k-1)
            , normalizationRate_(normalizationRate)
            , numOfRemovedBubbles_(0U)
            , maxBubbleLength_(2*k)
            , actualBubbleId_(0U)
            , bubblesFile_(CALC_TMP_DIR+std::string("bubbles.fa"))
        {}

        /**
         * \brief Removes bubbles from the graph.
         *
         * \return returns number of removed bubbles in all iterations
         */
        unsigned int operator()() {
            if (num_vertices(g_) == 0)
                return 0U;
            while (removeBubbles() != 0U) {
                ;
            }
            return numOfRemovedBubbles_;
        }

        void logBubbles(std::vector<char>& firstChars,
                        std::vector<std::bitset<2*MAX_KMER_LENGTH>>& sequences) {
            DnaSequenceRepresentationConverter dnaSequenceRepresentationConverter(K1_);

            for (auto it = bubbles_.begin(); it != bubbles_.end(); ++it) {
                std::string branchInStringRepresentation = "";

                for (auto it2 = std::begin(get<0>(*it)); it2 != std::end(get<0>(*it)); ++it2) {
                    if (*it2 == std::numeric_limits<unsigned long>::max()) {  // vertex equal to std::numeric_limits<unsigned long>::max() depicts chain of 'N' signs
                        ++it2;
                        for (unsigned long i = 0UL; i < *it2; ++i) {
                            branchInStringRepresentation += 'N';
                        }
                    } else {
                        branchInStringRepresentation += firstChars[*it2];
                    }
                }

                branchInStringRepresentation += std::string(dnaSequenceRepresentationConverter.convertToString(sequences[get<0>(*it).back()]), 1, K1_);
                bubblesFile_ << "> id: " << get<1>(*it)
                             << "  counter: " << get<2>(*it)
                             << "  percent in bubble: "
                             << std::fixed << std::setprecision(2) << get<3>(*it) << "%" << std::endl;
                bubblesFile_ << branchInStringRepresentation << std::endl;
            }
        }

        Bubbles& getBubbles() {
            return bubbles_;
        }

    private:
        Graph& g_;
        Bubbles bubbles_;
        unsigned short K1_;
        float normalizationRate_;
        unsigned int numOfRemovedBubbles_;
        unsigned short maxBubbleLength_;
        unsigned short actualBubbleId_;
        std::ofstream bubblesFile_;
        RemoveBubbles& operator=(const RemoveBubbles&)= delete;

        /**
         * \brief Removes bubbles from the graph - represents single iteration.
         *
         * \return returns number of removed bubbles is single iteration
         */
        unsigned int removeBubbles() {
            logInfo("removing bubbles...");
            unsigned int numOfRemovedBubblesInActualIteration = 0U;
            std::vector<unsigned short> in_degree(num_vertices(g_), 0U);
            std::vector<unsigned short> in_counters_sum(num_vertices(g_), 0U);
            countInDegreeAndInCountersSum(in_degree, in_counters_sum);
            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                Vertex actualVertex = *vi;

                if (in_degree[actualVertex] == 1U && countOutDegreeFromEdgesWithCounterGreaterThanZero(actualVertex) > 1) {
                    if (isStartOfBubble(actualVertex, in_degree, in_counters_sum)) {
                        serveIdentifiedBubble(actualVertex, in_degree);
                        ++numOfRemovedBubblesInActualIteration;
                        ++actualBubbleId_;
                    }
                }
            }

            numOfRemovedBubbles_ += numOfRemovedBubblesInActualIteration;
            logInfo("Removed " + std::to_string(numOfRemovedBubblesInActualIteration)+ " bubbles.");

            return numOfRemovedBubblesInActualIteration;
        }

        /**
         * \brief Checks if specified vertex begins the valid bubble.
         *
         * \param startVertex first vertex, which can be the beginning of valid bubble
         * \param in_degree number of all in edges for each vertex
         * \param in_counters_sum sum of counters of all in edges for each vertex
         * \return returns true if vertex begins the valid bubble, false otherwise
         */
        bool isStartOfBubble(Vertex& startVertex,
                             std::vector<unsigned short>& in_degree,
                             std::vector<unsigned short>& in_counters_sum) {
            std::vector<Vertex> nearestEndsOfBubbleCollection;
            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = out_edges(startVertex, g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ != 0U) {
                    Vertex actualVertex = target(*ei, g_);
                    bool existsEndOfBubble = findNearestEndOfBubble(actualVertex, nearestEndsOfBubbleCollection, in_degree, maxBubbleLength_);

                    if (existsEndOfBubble == false) {   // at least one branch has no end => bubble is invalid
                        return false;
                    }
                }
            }
            if (nearestEndsOfBubbleCollection.size() > 1) { // checks if neighbourhood of bubble is valid - counters after normalization should be equal to 1
                if (round(in_counters_sum[startVertex] * normalizationRate_) > 1U) {
                    return false;
                }

                typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

                for (boost::tie(ei, ei_end) = out_edges(nearestEndsOfBubbleCollection.back(), g_); ei != ei_end; ++ei) {
                    if (round(g_[*ei].counter_ * normalizationRate_) > 1U) {
                        return false;
                    }
                }
            }

            return (nearestEndsOfBubbleCollection.size() > 1 &&
                    equal(nearestEndsOfBubbleCollection.begin() + 1,
                          nearestEndsOfBubbleCollection.end(),
                          nearestEndsOfBubbleCollection.begin()));
        }

        /**
         * \brief Finds nearest end of bubble for specified vertex.
         *
         * \param actualVertex current vertex in searching end of branch process
         * \param nearestEndsOfBubbleCollection collection of vertices, each of them represents bubble end
         * \param in_degree number of all in edges for each vertex
         * \param bubbleLengthLimit remainig length of the branch in bubble
         * \return returns true if valid end of bubble exists, false otherwise
         */
        bool findNearestEndOfBubble(Vertex& actualVertex,
                                    std::vector<Vertex>& nearestEndsOfBubbleCollection,
                                    std::vector<unsigned short>& in_degree,
                                    unsigned short bubbleLengthLimit) {

            if (in_degree[actualVertex] != 1U || countOutDegreeFromEdgesWithCounterGreaterThanZero(actualVertex) != 1U) {
                nearestEndsOfBubbleCollection.push_back(actualVertex);
                return true;
            }

            if (bubbleLengthLimit == 0U) {
                return false;
            }

            Vertex nextVertex = getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(actualVertex);

            return findNearestEndOfBubble(nextVertex, nearestEndsOfBubbleCollection, in_degree, --bubbleLengthLimit);
        }

        /**
         * \brief Collects, logs and removes some of the branches of the bubble.
         *
         * \param startVertex first vertex, which represents the beginning of valid bubble
         * \param in_degree number of all in edges for each vertex
         * \return returns void
         */
        void serveIdentifiedBubble(Vertex& startVertex, std::vector<unsigned short>& in_degree) {

            std::vector<std::vector<Vertex>> branchesCollection;
            collectBranches(startVertex, branchesCollection, in_degree);
            unsigned short sumOfCountersInBubble = sumCountersInBubble(branchesCollection);
            unsigned int indexOfTheBestBranch = findIndexOfTheBestBranch(branchesCollection);
            logBranches(branchesCollection, sumOfCountersInBubble);
            removeSurplusBranches(branchesCollection, indexOfTheBestBranch);
            setCountersInBranch(branchesCollection[indexOfTheBestBranch], sumOfCountersInBubble);
        }

        /**
         * \brief Collects branches of the bubble.
         *
         * \param startVertex first vertex, which represents the beginning of valid bubble
         * \param branchesCollection vector of all branches in the bubble
         * \param in_degree number of all in edges for each vertex
         * \return returns void
         */
        void collectBranches(Vertex& startVertex,
                             std::vector<std::vector<Vertex>>& branchesCollection,
                             std::vector<unsigned short>& in_degree) {

            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = out_edges(startVertex, g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ != 0U) {
                    branchesCollection.push_back(std::vector<Vertex>());
                    branchesCollection.back().push_back(startVertex);
                    Vertex actualVertex = target(*ei, g_);
                    collectBranch(actualVertex, branchesCollection, in_degree);
                }
            }
        }

        /**
         * \brief Collects vertices of the branch.
         *
         * \param actualVertex current vertex in collecting branch process
         * \param branchesCollection vector of all branches in the bubble
         * \param in_degree number of all in edges for each vertex
         * \return returns void
         */
        void collectBranch(Vertex& actualVertex,
                           std::vector<std::vector<Vertex>>& branchesCollection,
                           std::vector<unsigned short>& in_degree) {
            branchesCollection.back().push_back(actualVertex);

            if (in_degree[actualVertex] != 1U || countOutDegreeFromEdgesWithCounterGreaterThanZero(actualVertex) != 1U) {
                return;
            }

            Vertex nextVertex = getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(actualVertex);
            collectBranch(nextVertex, branchesCollection, in_degree);
        }

        /**
         * \brief Counts sum of the branches' counters in the bubble.
         *
         * \param branchesCollection vector of all branches in the bubble
         * \return returns sum of the branches' counters in the bubble
         */
        unsigned short sumCountersInBubble(std::vector<std::vector<Vertex>>& branchesCollection) {
            unsigned short sumOfCountersInBubble = 0U;

            for (auto& branch : branchesCollection) {
                sumOfCountersInBubble += g_[edge(branch[0], branch[1], g_).first].counter_;
            }

            return sumOfCountersInBubble;
        }

        /**
         * \brief Finds branch with the greates counter in the specified bubble.
         *
         * \param branchesCollection vector of all branches in the bubble
         * \return returns index of the branch with greatest counter
         */
        unsigned int findIndexOfTheBestBranch(std::vector<std::vector<Vertex>>& branchesCollection) {
            unsigned int indexOfTheBestBranch = std::numeric_limits<unsigned int>::max();
            unsigned short theBestBranchEdgeCounter = std::numeric_limits<unsigned short>::min();

            for (auto& branch : branchesCollection) {
                if (branch.size() > 1 && g_[edge(branch[0], branch[1], g_).first].counter_ > theBestBranchEdgeCounter) {
                    theBestBranchEdgeCounter = g_[edge(branch[0], branch[1], g_).first].counter_;
                    indexOfTheBestBranch = (unsigned int)(&branch - &branchesCollection[0]);
                }
            }

            return indexOfTheBestBranch;
        }

        /**
         * \brief Logs information about branches in specified bubble.
         *
         * \param branchesCollection vector of all branches in the bubble
         * \param sumOfCountersInBubble sum of all counters in all branches in actual bubble
         * \return returns void
         */
        void logBranches(std::vector<std::vector<Vertex>>& branchesCollection, unsigned short sumOfCountersInBubble) {
            for (auto& branch : branchesCollection) {
                logBranch(branch, sumOfCountersInBubble);
            }
        }

        /**
         * \brief Logs information about specified branch in bubble.
         *
         * \param branch actual branch
         * \param sumOfCountersInBubble sum of all counters in all branches in actual bubble
         * \return returns void
         */
        void logBranch(std::vector<Vertex>& branch, unsigned short sumOfCountersInBubble) {
            unsigned short branchCounter = g_[edge(branch[0], branch[1], g_).first].counter_;
            float branchPercentInBubble = static_cast<float>(branchCounter) / static_cast<float>(sumOfCountersInBubble) * 100.0F;
            Bubble bubble(branch, actualBubbleId_, branchCounter, branchPercentInBubble);
            bubbles_.push_back(bubble);
        }

        /**
         * \brief Removes all surplus branches from the bubble (only branch with greatest counter will remain).
         *
         * \param branchesCollection vector of all branches in the bubble
         * \param indexOfTheBestBranch index of branch with the greatest counter
         * \return returns void
         */
        void removeSurplusBranches(std::vector<std::vector<Vertex>>& branchesCollection, unsigned int indexOfTheBestBranch) {
            for (auto& branch : branchesCollection) {
                if ((unsigned int)(&branch - &branchesCollection[0]) != indexOfTheBestBranch) {
                    removeEdgesFromBranch(branch);
                }
            }
        }

        /**
         * \brief Removes all of the edges of specified branch.
         *
         * \param branch actual branch
         * \return returns void
         */
        void removeEdgesFromBranch(std::vector<Vertex>& branch) {
            if (branch.size() < 2)
                return;

            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;
            for (auto it = branch.begin(); it != branch.end()-1; ++it) {
                if (edge(*it, *(it+1), g_).second) {
                    g_[edge(*it, *(it+1), g_).first].counter_ = 0U;
                }
            }
        }

        /**
         * \brief Sets specified counter for each edge of specified branch.
         *
         * \param branch actual branch
         * \param newCounter new value of the counters
         * \return returns void
         */
        void setCountersInBranch(std::vector<Vertex>& branch, unsigned short newCounter) {
            if (branch.size() < 2)
                return;

            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;
            for (auto it = branch.begin(); it != branch.end()-1; ++it) {
                if (edge(*it, *(it+1), g_).second) {
                    g_[edge(*it, *(it+1), g_).first].counter_ = newCounter;
                }
            }
        }

        /**
         * \brief Counts 'in' degree and sum of counters of 'in' edges for each vertex.
         *
         * \param in_degree number of all in edges for each vertex
         * \param in_counters_sum sum of counters of all in edges for each vertex
         * \return returns void
         */
        void countInDegreeAndInCountersSum(std::vector<unsigned short>& in_degree, std::vector<unsigned short>& in_counters_sum) {
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ != 0U) {
                    ++in_degree[target(*ei, g_)];
                    in_counters_sum[target(*ei, g_)] += g_[*ei].counter_;
                }
            }
        }

        unsigned short countOutDegreeFromEdgesWithCounterGreaterThanZero(Vertex& vertex) {
            unsigned short outDegree = 0U;
            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = out_edges(vertex, g_); ei != ei_end; ++ei) {
                if (g_[*ei].counter_ != 0U) {
                    ++outDegree;
                }
            }

            return outDegree;
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

#endif  // REMOVE_BUBBLES_HPP
