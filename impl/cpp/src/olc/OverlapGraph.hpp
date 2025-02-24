/**
 * \file OvlpGraph.hpp
 * \brief the C++ file with Overlap Graph type declaration
 *
 */

#ifndef OVERLAPGRAPH_HPP
#define OVERLAPGRAPH_HPP

#include <memory>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/compressed_sparse_row_graph.hpp>

#include "common.hpp"
#include "MinHash.hpp"

namespace dnaasm {
    namespace olc {
        struct EdgeProperty {
            EdgeProperty() {}

            EdgeProperty(float s) : score(s) {}

            float score;
        };

        using OverlapGraph =
        boost::adjacency_list<
                boost::vecS,
                boost::vecS,
                boost::bidirectionalS,
                boost::no_property,
                EdgeProperty>;

        using OvlpGraphVertIterator = boost::graph_traits<OverlapGraph>::vertex_iterator;
        using OvlpGraphVertSizeType = boost::graph_traits<OverlapGraph>::vertices_size_type;
        using OvlpGraphAdjIterator = boost::graph_traits<OverlapGraph>::adjacency_iterator;
        using vertex_t = boost::graph_traits<OverlapGraph>::vertex_descriptor;
        using OvlpEdge = boost::graph_traits<OverlapGraph>::edge_descriptor;

        template<class VisitorList>
        struct EdgeCategorizer : public boost::dfs_visitor<VisitorList> {
            EdgeCategorizer(std::vector<OvlpEdge> &edges,
                            const VisitorList &v = boost::null_visitor())
                    : boost::dfs_visitor<VisitorList>(v),
                      edges_(edges) {}

            template<class Edge, class Graph>
            void back_edge(Edge e, Graph &G) {
                edges_.push_back(e);
            }

        protected:
            std::vector<OvlpEdge> &edges_;
        };

        template<class VisitorList>
        EdgeCategorizer<VisitorList> categorizeEdges(const VisitorList &v,
                                                     std::vector<OvlpEdge> &edges) {
            return EdgeCategorizer<VisitorList>(edges, v);
        }

    }
} //namespace dnaasm::olc

#endif //OVERLAPGRAPH_HPP
