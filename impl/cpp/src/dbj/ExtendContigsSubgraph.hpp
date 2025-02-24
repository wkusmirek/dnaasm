/**
 * \file ExtendContigsSubgraph.hpp
 * \brief the C++ file with implementation of template class for extending contigs from subgraph of contigs
 */


#ifndef EXTEND_CONTIGS_SUBGRAPH_HPP
#define EXTEND_CONTIGS_SUBGRAPH_HPP

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
#pragma warning(disable:4512)
#pragma warning(disable:4459)   // for boost/multi_array
#endif

#include "globals.hpp"
#include "boost/multi_array.hpp"
#include "../common/log.hpp"
#include "GraphInOutFinder.hpp"
#include <iostream>
#include "AllPathsFinder.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to extend contigs from subgraph of contigs
    */
    template<class Graph> class ExtendContigsSubgraph {
    public:
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
        typedef std::vector<Vertex> Contig;
        typedef std::vector<Contig> Contigs;
        typedef boost::multi_array<unsigned short, 2> DistanceArray;

        /**
         * \brief ExtendContigsSubgraph constructor.
         *
         * \param g reference to Graph object
         * \param distanceArray reference to DistanceArray object with distances between contigs
         */
        ExtendContigsSubgraph(Graph& g, DistanceArray& distanceArray): g_(g), distanceArray_(distanceArray) {}


        /**
         * \brief Generates contigs for actual graph.
         *
         * \return returns set of contigs
         */
        Contig extendContigsSubgraph(bool contigsShouldBeLong) {
            //std::cout << "begin" << std::endl;
            std::vector<bool> isDisconnected(num_vertices(g_), false);
            std::vector<Vertex> startV;
            std::vector<Vertex> endV;
            GraphInOutFinder<Graph> graphInOutFinder(g_);
            graphInOutFinder.findInVertices(startV);
            graphInOutFinder.findOutVertices(endV);
            typename AllPathsFinder<Graph>::Path bestPath;
            if (startV.size() == 1 && endV.size() == 1 && ((contigsShouldBeLong && g_[startV[0]].isLongNode_ &&
                g_[endV[0]].isLongNode_) || (!contigsShouldBeLong))) {
                unsigned int numInVertices = 0U, numOutVertices = 0U, numOriginalVertices = 0U;
                std::vector<unsigned short> in_degree(num_vertices(g_), 0U);
                typename boost::graph_traits<Graph>::edge_iterator ei, ei_end;

                for (boost::tie(ei, ei_end)= edges(g_); ei != ei_end; ++ei) {
                    ++in_degree[target(*ei, g_)];
                }

                typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

                for (boost::tie(vi, vi_end)= vertices(g_); vi != vi_end; ++vi) {
                    if (in_degree[*vi] == 0U && out_degree(*vi, g_) == 0U)
                        isDisconnected[*vi] = true;

                    if (in_degree[*vi] > 1)
                        numInVertices+=(in_degree[*vi]-1);
                    if (out_degree(*vi, g_) > 1)
                        numOutVertices+=static_cast<unsigned int>((out_degree(*vi, g_))-1);
                    if (g_[*vi].isOriginal_)
                        ++numOriginalVertices;
                }

                AllPathsFinder<Graph> pathsFinder(g_, startV.back(), endV.back(), 500U/*2*distanceArray_[startV[0]][endV[0]]*/);
                //2*distanceArray_[startV[0]][endV[0]] mocno pogarsza jakość wyników - błędy i długości
                typename AllPathsFinder<Graph>::Paths paths;
                unsigned short bestPathScore = std::numeric_limits<unsigned short>::max();

                if (/*paths.size() == 1*/numInVertices == 0U && numOutVertices == 0U) {   // struktura liniowa grafu, 100% poprawne dla coli8 k=55 lub k=35
                    //std::cout << "linear structure" << std::endl;
                    AllPathsFinder<Graph> pathsFinder(g_, startV.back(), endV.back());
                    paths = pathsFinder.findAllPaths();
                    if (paths.size() > 0) {
                        bestPath = paths[0];
                        bestPathScore = 0U;
                    }
                } else if (numInVertices == 1 && numOutVertices == 1) {   // struktura z jedną pętlą, 100% poprawne dla coli8 k=55 lub k=35
                    //std::cout << "structure with one loop" << std::endl;
                    //AllPathsFinder<Graph> pathsFinder(g_, startV.back(), endV.back());    // wtedy byłoby nieograniczone szukanie w pętli!!!
                    paths = pathsFinder.findAllPaths();
                    for (typename AllPathsFinder<Graph>::Paths::iterator it = paths.begin(); it != paths.end(); ++it) {
                        unsigned short pathScore = countPathScoreForOneLoop(startV[0], endV[0], *it, distanceArray_[startV[0]][endV[0]]);
                        if (pathScore < bestPathScore) {
                            bestPathScore = pathScore;
                            bestPath = *it;
                        }
                        printPathAndScore(*it, pathScore);
                    }
                } else {
                    //std::cout << "another structure" << std::endl;
                    paths = pathsFinder.findSpecifiedPaths();
                    for (typename AllPathsFinder<Graph>::Paths::iterator it = paths.begin(); it != paths.end(); ++it) {
                        unsigned short pathScore = 0U;
                        if (numOriginalVertices > 2U) {
                            pathScore = countPathScore(startV[0], endV[0], *it, isDisconnected);
                        } else {
                            pathScore = countPathScoreLittleOriginalVertices(startV[0], endV[0], *it, isDisconnected);
                        }
                        if (pathScore < bestPathScore) {
                            bestPathScore = pathScore;
                            bestPath = *it;
                        }
                        printPathAndScore(*it, pathScore);
                    }
                }

                if (bestPath.size() == 0 && startV.size() == 1 && endV.size() == 1) {
                    bestPath.push_back(startV[0]);
                    bestPath.push_back(std::numeric_limits<unsigned long>::max());
                    bestPath.push_back(distanceArray_[startV[0]][endV[0]]);
                    bestPath.push_back(endV[0]);
                    bestPathScore = 0U;
                }

                //std::cout << "Paths size: " << paths.size() << std::endl;
                //std::cout << "Num of disconnected vertices: " << std::count(isDisconnected.begin(), isDisconnected.end(), true) << std::endl;
                //std::cout << "Best path:" << std::endl;
                printPathAndScore(bestPath, bestPathScore);
            }
            return bestPath;
        }

    private:
        ExtendContigsSubgraph& operator=(const ExtendContigsSubgraph&)= delete;
        Graph& g_;
        DistanceArray& distanceArray_;

        unsigned short countPathScoreForOneLoop(Vertex& startVertex,
                                                Vertex& endVertex,
                                                typename AllPathsFinder<Graph>::Path& path,
                                                unsigned short estimatedDistance) {

            if (path.size() > 1 && path.front() == startVertex && path.back() == endVertex) {
                typename Contig::const_iterator first = path.begin();
                typename Contig::const_iterator last = path.end()- 1;
                Contig subPath(first, last);

                return static_cast<unsigned short>(abs(estimatedDistance - countOvercomedDistance(subPath)));

            } else {
                return std::numeric_limits<unsigned short>::max();
            }
        }

        unsigned short countPathScore(Vertex& startVertex,
                                     Vertex& endVertex,
                                     typename AllPathsFinder<Graph>::Path& path,
                                     std::vector<bool>& isDisconnected) {
            unsigned short pathScore = 0U;

            // odrzucanie ścieżek, które mają w sobie więcej niż jeden raz oryginalny kontig, może niepotrzebne
            for (typename AllPathsFinder<Graph>::Path::iterator it = path.begin(); it != path.end(); ++it) {
                if (g_[*it].isOriginal_ == false)
                    continue;

                typename Contig::const_iterator first = path.begin()+ (it - path.begin()+ 1);
                typename Contig::const_iterator last = path.end();

                if (std::find(first, last, *it) != path.end()) {
                    return std::numeric_limits<unsigned short>::max();
                }
            }

            // odrzucanie ścieżek, dla których sparowane kontigi (wielkość większa od 2)nie występują za rozpatrywwanem kontigiem, może niepotrzebne
            for (typename AllPathsFinder<Graph>::Path::iterator it = path.begin(); it != path.end(); ++it) {
                if (g_[*it].isOriginal_ == false)
                    continue;

                typename Contig::const_iterator first = path.begin()+ (it - path.begin()+ 1);
                typename Contig::const_iterator last = path.end();

                for (size_t toV = 0; toV < distanceArray_.shape()[1]; toV++) {
                    if (*it != toV && distanceArray_[*it][toV] != 0U &&
                        distanceArray_[*it][toV] != std::numeric_limits<unsigned short>::max() &&
                        g_[*it].sequenceSize_ > 2 && g_[toV].sequenceSize_ > 2 && std::find(first, last, toV) == path.end()) {
                        return std::numeric_limits<unsigned short>::max();
                    }
                }
            }

            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end)= vertices(g_); vi != vi_end; ++vi) {
                if (isDisconnected[*vi] == false && std::find(path.begin(), path.end(), *vi) == path.end()) {
                    return std::numeric_limits<unsigned short>::max();
                }
            }

            for (typename AllPathsFinder<Graph>::Path::iterator it = path.begin(); it != path.end(); ++it) {
                if (g_[*it].isOriginal_ == false || isDisconnected[*it] == true || distanceArray_[path[0]][*it] == 0U)
                    continue;

                typename Contig::const_iterator first = path.begin();
                typename Contig::const_iterator last = path.begin()+ (it - path.begin());
                Contig subPath(first, last);
                pathScore += static_cast<unsigned short>(abs(distanceArray_[path[0]][*it] - countOvercomedDistance(subPath)));
            }

            if (path.size()- std::count(distanceArray_[startVertex].begin(), distanceArray_[startVertex].end(), 0U) != 0)
                return pathScore /
                    static_cast<unsigned short>((path.size()
                                - std::count(distanceArray_[startVertex].begin(), distanceArray_[startVertex].end(), 0U)));
            else
                return std::numeric_limits<unsigned short>::max();
        }


        unsigned short countPathScoreLittleOriginalVertices(Vertex& startVertex,
                                                            Vertex& endVertex,
                                                            typename AllPathsFinder<Graph>::Path& path,
                                                            std::vector<bool>& isDisconnected) {
            unsigned short pathScore = 0U;

            // odrzucanie ścieżek, które mają w sobie więcej niż jeden raz oryginalny kontig, może niepotrzebne
            for (typename AllPathsFinder<Graph>::Path::iterator it = path.begin(); it != path.end(); ++it) {
                if (g_[*it].isOriginal_ == false)
                    continue;

                typename Contig::const_iterator first = path.begin()+ (it - path.begin()+ 1);
                typename Contig::const_iterator last = path.end();
                if (std::find(first, last, *it) != path.end()) {
                    return std::numeric_limits<unsigned short>::max();
                }
            }

            // odrzucanie ścieżek, dla których sparowane kontigi (wielkość większa od 2)nie występują za rozpatrywwanem kontigiem, może niepotrzebne
            for (typename AllPathsFinder<Graph>::Path::iterator it = path.begin(); it != path.end(); ++it) {
                if (g_[*it].isOriginal_ == false)
                    continue;

                typename Contig::const_iterator first = path.begin()+ (it - path.begin()+ 1);
                typename Contig::const_iterator last = path.end();
                for (size_t toV = 0; toV < distanceArray_.shape()[1]; toV++) {
                    if (*it != toV && distanceArray_[*it][toV] != 0U &&
                        distanceArray_[*it][toV] != std::numeric_limits<unsigned short>::max() &&
                        g_[*it].sequenceSize_ > 2 && g_[toV].sequenceSize_ > 2 && std::find(first, last, toV) == path.end()) {

                        return std::numeric_limits<unsigned short>::max();
                    }
                }
            }

            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end)= vertices(g_); vi != vi_end; ++vi) {
                if (isDisconnected[*vi] == false && std::find(path.begin(), path.end(), *vi) == path.end()) {
                    return std::numeric_limits<unsigned short>::max();
                }
            }

            for (typename AllPathsFinder<Graph>::Path::iterator it = path.begin(); it != path.end(); ++it) {
                if (/*g_[*it].isOriginal_ == false ||*/ isDisconnected[*it] == true || distanceArray_[path[0]][*it] == 0U)
                    continue;

                typename Contig::const_iterator first = path.begin();
                typename Contig::const_iterator last = path.begin()+ (it - path.begin());
                Contig subPath(first, last);
                pathScore += static_cast<unsigned short>(abs(distanceArray_[path[0]][*it] - countOvercomedDistance(subPath)));
            }

            if (path.size()- std::count(distanceArray_[startVertex].begin(), distanceArray_[startVertex].end(), 0U) != 0)
                return pathScore / static_cast<unsigned short>((path.size()- std::count(distanceArray_[startVertex].begin(), distanceArray_[startVertex].end(), 0U)));
            else
                return std::numeric_limits<unsigned short>::max();
        }

        unsigned short countOvercomedDistance(Contig& contig) {
            if (contig.size() == 0)
                return 0U;

            unsigned short overcomedDistance = 0U;

            for (typename Contig::iterator it = contig.begin()+ 1; it != contig.end(); ++it) {
                overcomedDistance += static_cast<unsigned short>(g_[*it].sequenceSize_);
            }

            return overcomedDistance;
        }

        void printPathAndScore(typename AllPathsFinder<Graph>::Path& path, unsigned short pathScore) {
            if (pathScore != std::numeric_limits<unsigned short>::max()) {
                for (auto it = path.begin(); it != path.end(); ++it) {
                    //std::cout << *it << " ";
                }
                //std::cout << "   " << pathScore << std::endl;
            }
        }
    };

}}

#endif    //EXTEND_CONTIGS_SUBGRAPH_HPP
