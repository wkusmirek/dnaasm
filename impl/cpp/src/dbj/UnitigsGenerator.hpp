/**
 * \file UnitigsGenerator.hpp
 * \brief the C++ file with implementation of template class for generating unitigs from de Bruijn graph
 */

#ifndef UNITIGS_GENERATOR_HPP
#define UNITIGS_GENERATOR_HPP

#include <fstream>
#include <mt4cpp/Scheduler.hpp>
#include "existreturnpath.hpp"
#include "../common/log.hpp"
#include <boost/graph/strong_components.hpp>
#include <boost/tuple/tuple.hpp>

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
#pragma warning(disable:4512)
#endif

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to generate unitigs from de Bruijn graph
    */
    template<class Graph> class UnitigsGenerator {
    public:
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
        typedef std::vector<Vertex> Unitig;
        typedef std::vector<Unitig> Unitigs;
        typedef boost::tuple<Unitigs, std::vector<bool>, unsigned long> Result;

        /**
         * \brief UnitigsGenerator constructor.
         *
         * \param g reference to Graph object
         * \param progress actual task's progress
         * \param endProgressRate rate for estimation task's progress
         */
        UnitigsGenerator(Graph& g,
                  mt4cpp::Progress* progress,
                  float endProgressRate)
            : g_(g)
            , ambiguousVertices_(num_vertices(g_), false)
            , validLoops_(num_vertices(g_), false)
            , sumEdgesCounters_(0U)
            , progress_(progress)
            , endProgressRate_(endProgressRate)
            , unitigsStats(CALC_TMP_DIR+std::string("unitigsStats"))
        {}

        /**
         * \brief Generates unitigs for actual graph.
         *
         * \return returns unitigs, informaton about originality of specified unitig and number of components
         */
        Result operator()() {
            Result result;    // unitigs, informaton about originality of specified unitig and number of components

            if (num_vertices(g_) == 0)
                return result;

            markBridges();
            std::vector<unsigned long> component(num_vertices(g_), 0);    // component id of each vertex
            boost::get<2>(result) = markComponents(component);
            std::vector<unsigned short int> in_degree_bridges(num_vertices(g_), 0);    // num of in bridge edges for each vertex
            std::vector<unsigned short int> out_degree_bridges(num_vertices(g_), 0);    // num of out bridge edges for each vertex
            std::vector<unsigned short int> in_degree_all(num_vertices(g_), 0);    // num of in edges for each vertex
            std::vector<unsigned short int> out_degree_all(num_vertices(g_), 0);    // num of out edges for each vertex
            std::vector<unsigned short int> in_counters_sum(num_vertices(g_), 0);   // sum of counters of all in edges for each vertex
            std::vector<unsigned short int> out_counters_sum(num_vertices(g_), 0);   // sum of counters of all out edges for each vertex
            fillDegreeVectors(out_degree_bridges, in_degree_bridges, in_degree_all, out_degree_all, in_counters_sum, out_counters_sum);
            serveDisconnectedVertices(in_degree_all, out_degree_all, result);
            checkInVertices(in_degree_all, out_degree_all);
            markAmbiguousVertices(out_degree_bridges, in_degree_bridges, in_degree_all, out_degree_all, in_counters_sum, out_counters_sum);
            correctEdgesCountersInValidLoop(in_degree_all, out_degree_all, in_counters_sum, out_counters_sum);
            logComponentsStats(boost::get<2>(result), component, in_degree_all, in_degree_bridges, out_degree_bridges);
            logInfo("num components: " + std::to_string(boost::get<2>(result)));
            generateUnitigs(result);
            return result;
        }

        bool findSimplePathBetweenVertices(Vertex& actualVertex,
                                           Vertex& destination,
                                           std::vector<Vertex>& path,
                                           std::vector<unsigned short int>& in_degree_all,
                                           std::vector<unsigned short int>& out_degree_all) {
            path.push_back(actualVertex);

            if (actualVertex == destination) {
                return true;
            }

            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = out_edges(actualVertex, g_); ei != ei_end; ++ei) {
                Vertex targetVertex = target(*ei, g_);

                if (targetVertex != destination && (in_degree_all[targetVertex] != 1U || out_degree_all[targetVertex] != 1U)) {
                    continue;
                }

                if (findSimplePathBetweenVertices(targetVertex, destination, path, in_degree_all, out_degree_all) == false) {
                    path.clear();
                    path.push_back(actualVertex);
                } else {
                    return true;
                }
            }

            path.clear();
            return false;
        }

    private:
        UnitigsGenerator& operator=(const UnitigsGenerator&)= delete;
        Graph& g_;
        std::vector<bool> ambiguousVertices_;    // if vertex is ambiguous, it ends actual unitig and starts a new one
        std::vector<bool> validLoops_;
        unsigned int sumEdgesCounters_;    // only to estimate progress
        mt4cpp::Progress* progress_;
        float endProgressRate_;
        std::ofstream unitigsStats;

        void markAmbiguousVertices(std::vector<unsigned short int>& out_degree_bridges,
                                   std::vector<unsigned short int>& in_degree_bridges,
                                   std::vector<unsigned short int>& in_degree_all,
                                   std::vector<unsigned short int>& out_degree_all,
                                   std::vector<unsigned short int>& in_counters_sum,
                                   std::vector<unsigned short int>& out_counters_sum) {
            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                Vertex actualVertex = *vi;
                if (out_degree_bridges[actualVertex] > 1 || in_degree_bridges[actualVertex] > 1) {
                    ambiguousVertices_[actualVertex] = true;
                } else if (ambiguousVertices_[actualVertex] == false && (in_degree_all[actualVertex] > 2 || out_degree_all[actualVertex] > 2)) {
                    ambiguousVertices_[actualVertex] = true;
                } else if (ambiguousVertices_[actualVertex] == false && in_degree_all[actualVertex] == 1 && out_degree_all[actualVertex] == 2 && !checkOutVertex(actualVertex)) {
                    ambiguousVertices_[actualVertex] = true;
                } else if (ambiguousVertices_[actualVertex] == false && (in_degree_all[actualVertex] > 1 && out_degree_all[actualVertex] > 1 &&
                           !edge(actualVertex, actualVertex, g_).second)) {
                    ambiguousVertices_[actualVertex] = true;
                }
            }

            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;
            for (unsigned int i = 0U; i < 5U; ++i) {
                for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                    Vertex actualVertex = *vi;
                    if (ambiguousVertices_[actualVertex] == false && ((in_degree_all[actualVertex] == 1U &&
                        out_degree_all[actualVertex] == 2U) || (in_degree_all[actualVertex] == 2U &&
                        out_degree_all[actualVertex] == 2U && edge(actualVertex, actualVertex, g_).second))) {

                        unsigned short numOfReturnPaths = 0U;
                        unsigned short numOfLoops = 0U;
                        unsigned short counterSum = 0U;

                        for (tie(ei, ei_end) = out_edges(actualVertex, g_); ei != ei_end; ++ei) {
                            if (!g_[*ei].bridge_) {
                                Vertex startSinglePath = target(*ei, g_);
                                if (existLoopAcceptIn(startSinglePath, actualVertex, in_degree_all, out_degree_all, actualVertex==startSinglePath)) {
                                    ++numOfLoops;
                                }
                                ++numOfReturnPaths;
                            }
                            counterSum += g_[*ei].counter_;
                        }
                        if (numOfLoops == 1U && (numOfReturnPaths == 1U || counterSum == 2U)) {
                            validLoops_[actualVertex] = true;
                        } else {
                            ambiguousVertices_[actualVertex] = true;
                            validLoops_[actualVertex] = false;
                        }
                    }
                }
                for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                    Vertex actualVertex = *vi;
                    if (ambiguousVertices_[actualVertex] == false && in_degree_all[actualVertex] == 2U && out_degree_all[actualVertex] == 1U) {
                        unsigned short numOfLoops = 0U;
                        for (tie(ei, ei_end) = out_edges(actualVertex, g_); ei != ei_end; ++ei) {
                            if (!g_[*ei].bridge_) {
                                Vertex startSinglePath = target(*ei, g_);
                                if (existLoopAcceptOut(startSinglePath, actualVertex, in_degree_all, out_degree_all, actualVertex==startSinglePath)) {
                                    ++numOfLoops;
                                }
                            }
                        }
                        if (numOfLoops == 1U) {
                            validLoops_[actualVertex] = true;
                        } else {
                            ambiguousVertices_[actualVertex] = true;
                            validLoops_[actualVertex] = false;
                        }
                    }
                }
            }

            for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                Vertex actualVertex = *vi;
                if (validLoops_[actualVertex] == false && ambiguousVertices_[actualVertex] == false && (in_degree_all[actualVertex] > 1 || out_degree_all[actualVertex] > 1)) {
                    ambiguousVertices_[actualVertex] = true;
                }
            }
        }

        void correctEdgesCountersInValidLoop(std::vector<unsigned short int>& in_degree_all,
                                             std::vector<unsigned short int>& out_degree_all,
                                             std::vector<unsigned short int>& in_counters_sum,
                                             std::vector<unsigned short int>& out_counters_sum) {
            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                Vertex actualVertex = *vi;
                if (validLoops_[actualVertex] == true && ambiguousVertices_[actualVertex] == false && in_degree_all[actualVertex] == 2 && out_degree_all[actualVertex] == 1) {
                    std::vector<bool> wasUsed(num_vertices(g_), false);
                    Vertex closestOutVertex = findClosestOutVertex(actualVertex, wasUsed);

                    if (closestOutVertex == std::numeric_limits<unsigned int>::max()) {
                        continue;
                    }

                    if (in_degree_all[closestOutVertex] == 1U && out_degree_all[closestOutVertex] == 2U && in_counters_sum[actualVertex] != out_counters_sum[actualVertex]) {
                        std::vector<Vertex> baseOfLoop, headOfLoop;
                        findSimplePathBetweenVertices(actualVertex, closestOutVertex, baseOfLoop, in_degree_all, out_degree_all);
                        findSimplePathBetweenVertices(closestOutVertex, actualVertex, headOfLoop, in_degree_all, out_degree_all);
                        unsigned int baseOfLoopSize = countSumOfUncompressedVerticesInCompressedPath(baseOfLoop);
                        unsigned int headOfLoopSize = countSumOfUncompressedVerticesInCompressedPath(headOfLoop);
                        unsigned short baseOfLoopCounter = g_[edge(baseOfLoop[0], baseOfLoop[1], g_).first].counter_;
                        unsigned short headOfLoopCounter = g_[edge(headOfLoop[0], headOfLoop[1], g_).first].counter_;

                        if (baseOfLoopCounter == 1U && headOfLoopCounter == 1U) {
                            setCountersInPath(baseOfLoop, 2U, in_counters_sum, out_counters_sum);
                        } else if (baseOfLoopSize > headOfLoopSize) {
                            setCountersInPath(headOfLoop, baseOfLoopCounter-1U, in_counters_sum, out_counters_sum);
                        } else {
                            setCountersInPath(baseOfLoop, headOfLoopCounter+1U, in_counters_sum, out_counters_sum);
                        }
                    }
                }
            }
        }

        unsigned int countSumOfUncompressedVerticesInCompressedPath(std::vector<Vertex>& path) {
            unsigned int sum = 0U;
            for (auto it = path.begin(); it != path.end(); ++it) {
                sum += static_cast<unsigned int>(g_[*it].uncompressedVertices_.size());
            }
            return sum;
        }

        void setCountersInPath(std::vector<Vertex>& path,
                               unsigned short newCounter,
                               std::vector<unsigned short>& in_counters_sum,
                               std::vector<unsigned short>& out_counters_sum) {

            for (auto it = path.begin(); it != path.end()-1; ++it) {
                if (edge(*it, *(it+1), g_).second) {
                    out_counters_sum[*it] = out_counters_sum[*it] + newCounter - g_[edge(*it, *(it+1), g_).first].counter_;
                    in_counters_sum[*(it+1)] = in_counters_sum[*(it+1)] + newCounter - g_[edge(*it, *(it+1), g_).first].counter_;
                    g_[edge(*it, *(it+1), g_).first].counter_ = newCounter;
                }
            }
        }

        bool checkOutVertex(Vertex& vertex) {
            unsigned short numOfBridges = 0U;
            unsigned short numOfEdgesCountersEqualTo1 = 0U;
            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = out_edges(vertex, g_); ei != ei_end; ++ei) {
                if (g_[*ei].bridge_)
                    ++numOfBridges;
                if (g_[*ei].counter_ == 1U)
                    ++numOfEdgesCountersEqualTo1;
            }
            return numOfBridges != 0U || numOfEdgesCountersEqualTo1 != 0U;
        }

        void checkInVertices(std::vector<unsigned short int>& in_degree_all, std::vector<unsigned short int>& out_degree_all) {
            std::vector<unsigned short int> numOfBridges(num_vertices(g_), 0U);
            std::vector<unsigned short int> numOfEdgesCountersEqualTo1(num_vertices(g_), 0U);
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                if (g_[*ei].bridge_)
                    ++numOfBridges[target(*ei, g_)];
                if (g_[*ei].counter_ == 1U)
                    ++numOfEdgesCountersEqualTo1[target(*ei, g_)];
            }

            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                if (ambiguousVertices_[*vi] == false && in_degree_all[*vi] == 2 && out_degree_all[*vi] == 1 &&
                    numOfBridges[*vi] == 0U && numOfEdgesCountersEqualTo1[*vi] == 0U) {
                    ambiguousVertices_[*vi] = true;
                }
            }
        }

        Vertex findClosestOutVertex(Vertex& actualVertex, std::vector<bool>& wasUsed) {
            if (wasUsed[actualVertex]) {
                return std::numeric_limits<unsigned int>::max();
            }

            wasUsed[actualVertex] = true;

            if (out_degree(actualVertex, g_) > 1 || out_degree(actualVertex, g_) == 0) {
                return actualVertex;
            }

            typename Graph::out_edge_iterator e = out_edges(actualVertex, g_).first;
            Vertex tmpVertex = target(*e, g_);
            return findClosestOutVertex(tmpVertex, wasUsed);
        }

        /**
         * \brief Counts degrees information.
         *
         * \param out_degree_bridges number of all out edges, which are bridges, for each vertex
         * \param in_degree_bridges number of all in edges, which are bridges, for each vertex
         * \param in_degree_all number of all in edges for each vertex
         * \param out_degree_all number of all out edges for each vertex
         * \param in_counters_sum sum of counters of all in edges for each vertex
         * \param out_counters_sum sum of counters of all out edges for each vertex
         * \return returns void
         */
        void fillDegreeVectors(std::vector<unsigned short int>& out_degree_bridges,
                               std::vector<unsigned short int>& in_degree_bridges,
                               std::vector<unsigned short int>& in_degree_all,
                               std::vector<unsigned short int>& out_degree_all,
                               std::vector<unsigned short int>& in_counters_sum,
                               std::vector<unsigned short int>& out_counters_sum) {
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                sumEdgesCounters_ += static_cast<unsigned int>(g_[*ei].counter_);
                ++in_degree_all[target(*ei, g_)];
                ++out_degree_all[source(*ei, g_)];
                in_counters_sum[target(*ei, g_)] += g_[*ei].counter_;
                out_counters_sum[source(*ei, g_)] += g_[*ei].counter_;

                if (g_[*ei].bridge_) {   // if this will be commented, all UnitigsGenerator will work as standard DNA assembler
                    ++in_degree_bridges[target(*ei, g_)];
                    ++out_degree_bridges[source(*ei, g_)];
                }
            }
        }

        /**
         * \brief Generates set of resultant unitigs from graph with marked ambiguous vertices.
         *
         * \param result reference to Result object, where set of resultant unitigs will be stored
         * \return returns void
         */
        void generateUnitigs(Result& result) {
            Vertex current;
            std::vector<Vertex> startVertices;
            unsigned int progress = 0U;

            while (findStartVertices(startVertices) != -1) {
                for (typename std::vector<Vertex>::iterator it = startVertices.begin(); it != startVertices.end(); ++it) {
                    if (out_degree(*it, g_) == 0)   // sequences form single, disconnected vertices are not in resultant set of unitigs
                        continue;

                    current = *it;
                    Unitig unitig;

                    while (true) {
                        ++progress;
                        if (progress % 1000 == 0) {
                            if (progress_ != NULL)
                                progress_->setProgress(0.5+static_cast<float>(progress)/static_cast<float>(sumEdgesCounters_)/endProgressRate_);
                        }
                        unitig.push_back(current);
                        unsigned long degree = static_cast<unsigned long>(out_degree(current, g_));
                        if ((ambiguousVertices_[current] && unitig.size() != 1) || degree == 0) {    // the end of the actual unitig
                            saveUnitig(boost::get<0>(result), unitig, boost::get<1>(result), current, progress);
                            break;
                        }
                        typename Graph::out_edge_iterator e = out_edges(current, g_).first;
                        if (ambiguousVertices_[current] == false && degree > 1) {
                            typename Graph::out_edge_iterator f = e;
                            ++f;
                            if (degree == 2) {  // for e return path should exist and for f return path should not exist (edges with return path are preffered)
                                /*if (!existReturnPath(g_, *f)) {
                                    if (!existReturnPath(g_, *f)) {
                                        saveUnitig(result.get<0>(), unitig, result.get<1>(), current, progress);
                                        break;
                                    }
                                } else if (!existReturnPath(g_, *e)) {
                                    e = f;
                                } else {    // for both, e and f, return path exists
                                    saveUnitig(result.get<0>(), unitig, result.get<1>(), current, progress);
                                    break;
                                }*/
                                bool existReturnPathE = existReturnPath(g_, *e);
                                bool existReturnPathF = existReturnPath(g_, *f);

                                if ((existReturnPathE && existReturnPathF) || (!existReturnPathE && !existReturnPathF)) {
                                    saveUnitig(boost::get<0>(result), unitig, boost::get<1>(result), current, progress);
                                    break;
                                } else if (!existReturnPathE && existReturnPathF) {
                                    e = f;
                                } else if (existReturnPathE && !existReturnPathF) {
                                }
                            }
                        }
                        const Edge& ee = *e;
                        current = target(ee, g_);

                        if (g_[ee].counter_ > 1) {  // decrement edge's counter or remove actual edge
                            --(g_[ee].counter_);
                        } else {
                            remove_edge(e, g_);
                        }
                    }
                }
                startVertices.clear();
            }
        }

        /**
         * \brief Checks if exist single path - without any in or out edges except this single path.
         *
         * \param start reference to source vertex
         * \param destination reference to destination vertex
         * \param in_degree_all number of all in edges for each vertex
         * \param out_degree_all number of all out edges for each vertex
         * \return returns true - single path exists, false - path does not exist
         */
        bool checkSinglePath(Vertex& start,
                             Vertex& destination,
                             std::vector<unsigned short int>& in_degree_all,
                             std::vector<unsigned short int>& out_degree_all) {

            std::vector<bool> wasUsed(num_vertices(g_), false);
            Vertex current = start;

            if (start == destination) {
                return true;
            }

            if (out_degree(start, g_) == 0 || in_degree_all[start] != 1) {
                return false;
            }

            while (true) {
                if (ambiguousVertices_[current])
                    return false;
                typename boost::graph_traits<Graph>::out_edge_iterator ei = out_edges(current, g_).first;
                current = target(*ei, g_);
                if (ambiguousVertices_[current])
                    return false;
                if (current == destination) {
                    return true;
                }
                if (out_degree(current, g_) != 1 || in_degree_all[current] != 1 || wasUsed[current]) {
                    return false;
                }
                wasUsed[current] = true;
            }
        }

        /**
         * \brief Checks if exist return path with only one in edge (loop with one in).
         *
         * \param start reference to source vertex
         * \param destination reference to destination vertex
         * \param in_degree_all number of all in edges for each vertex
         * \param out_degree_all number of all out edges for each vertex
         * \param isSelfLoop true - source and destination of the loop are the same vertex, otherwise - false
         * \return returns true - loop which accepts one in exists, false - loop does not exist
         */
        bool existLoopAcceptIn(Vertex& start,
                               Vertex& destination,
                               std::vector<unsigned short int>& in_degree_all,
                               std::vector<unsigned short int>& out_degree_all, bool isSelfLoop) {

            std::vector<bool> wasUsed(num_vertices(g_), false);
            Vertex current = start;

            if (start == destination) {
                return true;
            }

            if (out_degree(start, g_) == 0 || (out_degree_all[current] != 1 && !isSelfLoop)) {
                return false;
            }

            while (true) {
                if (ambiguousVertices_[current])
                    return false;

                typename boost::graph_traits<Graph>::out_edge_iterator ei = out_edges(current, g_).first;
                current = target(*ei, g_);

                if (ambiguousVertices_[current])
                    return false;
                if (current == destination) {
                    return true;
                }

                if (out_degree_all[current] > 1 || out_degree(current, g_) != 1 || wasUsed[current]) {
                    return false;
                }

                if (in_degree_all[current] == 2) {
                    typename boost::graph_traits<Graph>::out_edge_iterator ei2, ei2_end;
                    for (tie(ei2, ei2_end)= out_edges(current, g_); ei2 != ei2_end; ++ei2) {
                        Vertex startVertex = target(*ei2, g_);
                        if (checkSinglePath(startVertex, destination, in_degree_all, out_degree_all)) {
                            return true;
                        }
                    }
                    return false;
                }
                wasUsed[current] = true;
            }
        }

        /**
         * \brief Checks if exist return path with only one out edge (loop with one out).
         *
         * \param start reference to source vertex
         * \param destination reference to destination vertex
         * \param in_degree_all number of all in edges for each vertex
         * \param out_degree_all number of all out edges for each vertex
         * \param isSelfLoop true - source and destination of the loop are the same vertex, otherwise - false
         * \return returns true - loop which accepts one out exists, false - loop does not exist
         */
        bool existLoopAcceptOut(Vertex& start,
                                Vertex& destination,
                                std::vector<unsigned short int>& in_degree_all,
                                std::vector<unsigned short int>& out_degree_all, bool isSelfLoop) {
            std::vector<bool> wasUsed(num_vertices(g_), false);
            Vertex current = start;

            if (start == destination) {
                return true;
            }

            if (out_degree(start, g_) == 0 || (in_degree_all[current] != 1 && !isSelfLoop)) {
                return false;
            }

            while (true) {
                if (ambiguousVertices_[current])
                    return false;

                typename boost::graph_traits<Graph>::out_edge_iterator ei = out_edges(current, g_).first;
                current = target(*ei, g_);

                if (ambiguousVertices_[current])
                    return false;
                if (current == destination) {
                    return true;
                }

                if (in_degree_all[current] != 1 || wasUsed[current]) {
                    return false;
                }

                if (out_degree_all[current] == 2) {
                    typename boost::graph_traits<Graph>::out_edge_iterator ei2, ei2_end;
                    for (tie(ei2, ei2_end)= out_edges(current, g_); ei2 != ei2_end; ++ei2) {
                        Vertex startVertex = target(*ei2, g_);
                        if (checkSinglePath(startVertex, destination, in_degree_all, out_degree_all)) {
                            return true;
                        }
                    }
                    return false;

                }
                wasUsed[current] = true;
            }
        }

        /**
         * \brief Saves actual unitig to set of resultant unitigs.
         *
         * \param unitigs set of resultan unitigs
         * \param unitig actual unitig, which should be stored in unitigs
         * \param isOriginal information about originality of each unitig
         * \param vertex actual vertex of de Bruijn graph
         * \param progress reference to value of progress of generating unitigs from de Bruijn graph process
         * \return returns void
         */
        void saveUnitig(Unitigs& unitigs,
                        Unitig& unitig,
                        std::vector<bool>& isOriginal,
                        Vertex& vertex, unsigned int& progress) {
            if (unitig.size() > 3) {
                unitigsStats << "Unitig: ";

                for (typename Unitig::iterator it = unitig.begin(); it != unitig.end(); ++it) {
                    unitigsStats << *it << " ";
                }
                unitigsStats << std::endl;
            }

            unitigs.push_back(Unitig());
            unitig.swap(unitigs.back());
            unsigned int numOfRemovedEdges = removeEdges(unitigs.back());   // for graph: A -> B -> C and all edges weights equal to 4 (greater than 1),
                                                                            // in resultant set of unitigs should be only one unitig (ABC)
            isOriginal.push_back(numOfRemovedEdges == 0U);  // if all edges in unitig had counters equal to 1, unitig is original
            progress += numOfRemovedEdges;
            unitig.push_back(vertex);
            ambiguousVertices_[vertex] = true;   // each vertex, which ends unitig, is ambiguous
        }

        /**
         * \brief Logs statistics for each components into componentsStats file.
         *
         * \param numOfComponents number of components of de Bruijn graph
         * \param component reference to vector with component id for each vertex
         * \param in_degree_all number of all in edges for each vertex
         * \param in_degree_bridges number of all in edges, which are bridges, for each vertex
         * \param out_degree_bridges number of all out edges, which are bridges, for each vertex
         * \return returns void
         */
        void logComponentsStats(unsigned long numOfComponents,
                                std::vector<unsigned long>& component,
                                std::vector<unsigned short int>& in_degree_all,
                                std::vector<unsigned short int>& in_degree_bridges,
                                std::vector<unsigned short int>& out_degree_bridges) {

            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            std::vector<bool> isPath(numOfComponents, true);
            std::vector<unsigned long> componentSize(numOfComponents, 0);
            std::vector<unsigned int> numOut (component.size(), 0U);
            std::vector<unsigned int> numIn (component.size(), 0U);
            std::vector<unsigned int> numOut1 (component.size(), 0U);
            std::vector<unsigned int> numIn1 (component.size(), 0U);
            std::vector<unsigned int> numAmb (component.size(), 0U);

            for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                Vertex v = *vi;
                ++componentSize[component[v]];
                if (out_degree_bridges[v] > 1 || in_degree_bridges[v] > 1 ||
                    in_degree_all[v] - in_degree_bridges[v] > 1 || out_degree(v, g_)- out_degree_bridges[v] > 1)
                    ++numAmb[component[v]];
                if (out_degree(v, g_) == 0 && in_degree_all[v] > 0)
                    ++numOut[component[v]];
                if (out_degree(v, g_) > 0 && in_degree_all[v] == 0)
                    ++numIn[component[v]];
                if (out_degree(v, g_) > 1)
                    ++numOut1[component[v]];
                if (in_degree_all[v] > 1)
                    ++numIn1[component[v]];
            }
            std::ofstream ifile(CALC_TMP_DIR+std::string("componentsStats"));
            unsigned long int i = 0;
            ifile << "isPath componentSize in out amb in>1 out>1" << std::endl;
            for (std::vector<bool>::iterator it = isPath.begin(); it != isPath.end(); ++it, ++i) {
                if (componentSize[i] > 1)
                    ifile << isPath[i]
                          << "   " << componentSize[i]
                          << "   " << numIn[i]
                          << "   " << numOut[i]
                          << "     " << numAmb[i]
                          << "     " << numIn1[i]
                          << "     " << numOut1[i] << std::endl;
            }
        }

        /**
         * \brief Checks for each edge if it's a bridge.
         *
         * \return returns void
         */
        void markBridges() {
            std::vector<unsigned long> c(num_vertices(g_), 0); // property - id of strongly connected group
            strong_components(g_, make_iterator_property_map(c.begin(), get(boost::vertex_index, g_), c[0]));
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                const Edge& ee = *ei;
                Vertex u = source(ee, g_);
                Vertex v = target(ee, g_);
                if (c[u] != c[v]) {
                    g_[ee].bridge_ = true;
                } else {
                    g_[ee].bridge_ = false;
                }
            }
        }

        /**
         * \brief Marks connected components for directed graph.
         *
         * \param component vector of components
         * \return returns number of components in graph
         */
        unsigned long markComponents(std::vector<unsigned long>& component) {
            //adding parallel edges for bridges (strong_components for directed graph will be like connected_components for undirected graph)
            //connected_components for directed graph doesn't work!!!
            unsigned long numComp;
            std::vector<boost::adjacency_list<>::edge_descriptor> extraEdges;
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                const Edge& ee = *ei;

                if (g_[ee].bridge_) {
                    std::pair<boost::adjacency_list<>::edge_descriptor, bool> p = add_edge(target(*ei, g_), source(*ei, g_), g_);
                    if (p.second) {
                        extraEdges.push_back(p.first);
                    }
                }
            }
            numComp = strong_components(g_, make_iterator_property_map(component.begin(), get(boost::vertex_index, g_), component[0]));
            for (std::vector<boost::adjacency_list<>::edge_descriptor>::iterator it = extraEdges.begin(); it != extraEdges.end(); ++it) {
                remove_edge(*it, g_);
            }
            return numComp;
        }

        /**
         * \brief Finds starts vertices.
         *
         * \param startVertices vector to store start vertices
         * \return returns '0' if any start vertex exists, '-1' otherwise
         */
        int findStartVertices(std::vector<Vertex>& startVertices) {
            std::vector<unsigned short int> in_degree_bridges(num_vertices(g_), 0U);
            std::vector<unsigned short int> out_degree(num_vertices(g_), 0U);
            std::vector<unsigned short int> in_degree_counter_sum(num_vertices(g_), 0U);
            std::vector<unsigned short int> out_degree_counter_sum(num_vertices(g_), 0U);
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                ++out_degree[source(*ei, g_)];
                ++in_degree_bridges[target(*ei, g_)];
                out_degree_counter_sum[source(*ei, g_)] += g_[*ei].counter_;
                in_degree_counter_sum[target(*ei, g_)] += g_[*ei].counter_;
            }

            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                if ((ambiguousVertices_[*vi] || in_degree_bridges[*vi] == 0) && out_degree[*vi] > 0) {
                    startVertices.push_back(*vi);
                }
            }

            if (startVertices.size() == 0 && countEndVertices() == 0U) {   // for Hymonolepsis diminuta mtDNA graph structure
                //for loops like a -> b -> c -> a -> d -> a
                for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                    if (in_degree_counter_sum[*vi] == 1 && out_degree_counter_sum[*vi] == 1) {
                        startVertices.push_back(*vi);
                        return 0;
                    }
                }
            }

            if (startVertices.size() == 0 && countEndVertices() != 0U) {
                //for loops like a -> b -> c -> a -> d     //ten if powinien byc chyba poprawiony
                for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi){
                    if (out_degree[*vi] > in_degree_bridges[*vi]) {
                        startVertices.push_back(*vi);
                        return 0;
                    }
                }
            }

            if (startVertices.size() == 0) {
                //for loops like a -> b -> c -> a
                for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                    if (out_degree[*vi] > 0 && in_degree_bridges[*vi] > 0) {
                        startVertices.push_back(*vi);
                        return 0;
                    }
                }
            }

            if (startVertices.size() == 0)
                return -1;
            else
                return 0;
        }

        /**
         * \brief Counts number of end vertices.
         *
         * \return returns number of end vertices
         */
        unsigned int countEndVertices() {
            unsigned int numOfEndVertices = 0U;
            std::vector<unsigned short int> in_degree(num_vertices(g_), 0U);
            std::vector<unsigned short int> out_degree(num_vertices(g_), 0U);
            typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end; ++ei) {
                ++out_degree[source(*ei, g_)];
                ++in_degree[target(*ei, g_)];
            }

            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                if (in_degree[*vi] > 0 && out_degree[*vi] == 0) {
                    ++numOfEndVertices;
                }
            }

            return numOfEndVertices;
        }

        /**
         * \brief Removes edges between vertices from specified unitig.
         *
         * \param unitig set of vertices
         * \return returns sum of deleted edges counters
         */
        unsigned int removeEdges(Unitig& unitig) {
            unsigned int sumDeletedEdges = 0U;

            if (unitig.size() < 2)
                return 0U;

            for (typename Unitig::iterator it = unitig.begin(); it != unitig.end()-1; ++it) {
                if (edge(*it, *(it+1), g_).second) {
                    sumDeletedEdges += static_cast<unsigned int>(g_[edge(*it, *(it+1), g_).first].counter_);
                    remove_edge(edge(*it, *(it+1), g_).first, g_);
                }
            }

            return sumDeletedEdges;
        }

        /**
         * \brief Serves disconnected vertices - saving one-element unitig.
         *
         * \param in_degree_all number of all in edges for each vertex
         * \param out_degree_all number of all out edges for each vertex
         * \param result set of resultant unitigs and information about originality of each unitig
         * \return returns void
         */
        void serveDisconnectedVertices(std::vector<unsigned short int>& in_degree_all,
                                       std::vector<unsigned short int>& out_degree_all,
                                       Result& result) {
            // this function in properly compressed graph will not work - properly compressed graph does not contain disconnected vertices
            unsigned int numOfDisconnectedUnitigs = 0U;    // only to count num of disconnected vertices, only for statistics
            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end) = vertices(g_); vi != vi_end; ++vi) {
                Vertex actualVertex = *vi;
                if (in_degree_all[actualVertex] == 0 && out_degree(actualVertex, g_) == 0) {
                    ++numOfDisconnectedUnitigs;    // only for statistics
                    Unitig unitig;
                    unitig.push_back(actualVertex);
                    boost::get<0>(result).push_back(unitig);
                    boost::get<1>(result).push_back(true);  // disconnected unitig is original, TODO not always, but this situation should not occurre !!!!!!!!!!!!!!!!!!!!!!
                }
            }
            logInfo("num of disconnected unitigs: " + std::to_string(numOfDisconnectedUnitigs));
        }

    };

}}

#endif    //UNITIGS_GENERATOR_HPP
