/**
 * \file LayoutFormer.cpp
 * \brief the C++ file with definition of class responsible for forming
 * layouts (maximal simple paths)
 *
 */
#include <numeric>
#include <vector>

#if defined(_MSC_VER) && (_MSC_VER >= 1800)
/*
* Need to define that macro,
* because Visual Studio Compiler,
* does not support keyword 'not',
* when language extensions are enabled,
* which causes boost::graph::transitive_reduction
* compilation fail
*/
#define not !
#endif

#include <boost/graph/transitive_reduction.hpp>


#include "../common/log.hpp"
#include "LayoutFormer.hpp"
#include <iostream>
#include <numeric>
#include <stack>

namespace dnaasm {
    namespace olc {
        void LayoutFormer::removeCycles() {
            using SizeType =  boost::graph_traits<OverlapGraph>::vertices_size_type;

            std::vector<SizeType> d(boost::num_vertices(ovlpGraph_));
            std::vector<SizeType> f(boost::num_vertices(ovlpGraph_));
            std::vector<OvlpEdge> edgesToRemove;

            int t = 0;

            //how to even format this section?
            boost::depth_first_search(ovlpGraph_, boost::visitor(
                    categorizeEdges(
                            std::make_pair(
                                    boost::stamp_times(&d[0], t, boost::on_discover_vertex()),
                                    boost::stamp_times(&f[0], t, boost::on_finish_vertex())
                            ),
                            edgesToRemove
                    )
            ));

            for (const auto &edge : edgesToRemove) {
                boost::remove_edge(edge, ovlpGraph_);
            }
        }

        void LayoutFormer::removeTransInfEdges() {
            OverlapGraph trResult;
            std::map<vertex_t, vertex_t> vertMap;
            std::vector<size_t> id_map(boost::num_vertices(ovlpGraph_));
            std::iota(id_map.begin(), id_map.end(), 0U);

            boost::transitive_reduction(ovlpGraph_,
                                        trResult,
                                        boost::make_assoc_property_map(vertMap),
                                        id_map.data());

            OverlapGraph result(boost::num_vertices(ovlpGraph_));
            auto scores = boost::get(&EdgeProperty::score, ovlpGraph_);
            auto edges = boost::edges(ovlpGraph_);

            //before transitive reduction algorithm
            //vertex index == number of read in input file
            //after boost algorithm that information is lost
            //so there is a need to restore it
            for (auto it = edges.first; it != edges.second; ++it) {
                vertex_t source = boost::source(*it, ovlpGraph_);
                vertex_t target = boost::target(*it, ovlpGraph_);

                if (boost::edge(vertMap[source], vertMap[target], trResult).second) {
                    boost::add_edge(source, target, scores[*it], result);
                }
            }
            ovlpGraph_.clear();
            ovlpGraph_ = std::move(result);
        }

        LayoutVec LayoutFormer::findLayoutsInOvlpGraph() {
            auto takeNextVertex = [](const auto &v, auto &ovlpGraph) {
                return *boost::adjacent_vertices(static_cast<vertex_t>(v),
                                                 ovlpGraph).first;
            };

            auto isInternalPathNode = [](const auto &v, auto &ovlpGraph) {
                return (boost::out_degree(static_cast<vertex_t>(v), ovlpGraph) == 1 and
                        boost::in_degree(static_cast<vertex_t>(v), ovlpGraph) == 1);
            };

            auto isInitialPathNode = [](const auto &v, auto &ovlpGraph) {
                return (boost::in_degree(*v, ovlpGraph) != 1 and
                        boost::out_degree(*v, ovlpGraph) == 1);
            };

            auto isFork = [](auto v, auto &ovlpGraph) {
                return (boost::in_degree(static_cast<vertex_t>(v), ovlpGraph) == 1 and
                        boost::out_degree(static_cast<vertex_t>(v), ovlpGraph) != 1);
            };

            auto result = LayoutVec();
            std::vector<bool> visited(boost::num_vertices(ovlpGraph_), false);

            OvlpGraphVertIterator vi, vi_end;
            boost::tie(vi, vi_end) = boost::vertices(ovlpGraph_);

            for (; vi != vi_end; ++vi) {
                if (isInitialPathNode(vi, ovlpGraph_)) {
                    //layout beginning -> add to map
                    result.emplace_back(1, *vi);
                    visited[*vi] = true;
                }
            }

            logInfo("Found " + std::to_string(result.size()) + " layout initial vertices");

            for (auto &layout : result) {
                auto vertex = *(layout.begin());

                vertex = takeNextVertex(vertex, ovlpGraph_);

                while (isInternalPathNode(vertex, ovlpGraph_) and not visited[vertex]) {
                    visited[vertex] = true;
                    layout.emplace_back(vertex);
                    vertex = takeNextVertex(vertex, ovlpGraph_);
                }

                //path can be ended with fork
                if (isFork(vertex, ovlpGraph_)) {
                    visited[vertex] = true;
                    layout.emplace_back(vertex);
                }
            }

            //debug
//            logInfo("Layout sizes : ");
//            for (const auto &layout : result) {
//                logInfo(std::to_string(layout.size()));
//            }

            logInfo("Filling layouts complete");

            return result;
        }
    }
} //namespace dnaasm::olc
