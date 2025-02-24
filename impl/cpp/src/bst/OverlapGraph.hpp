#ifndef OVERLAPGRAPH_HPP
#define OVERLAPGRAPH_HPP

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
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
#include <boost/graph/visitors.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/transitive_reduction.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "Association.hpp"

namespace dnaasm { namespace bst {

    struct EdgeProperty {
        EdgeProperty() {}
        EdgeProperty(Association as) :assoc_(as) {}
        Association assoc_;
    };

    using EP = EdgeProperty;

    using OverlapGraph =
        boost::adjacency_list<
            boost::vecS, boost::vecS,
            boost::bidirectionalS,
            boost::no_property,
            EdgeProperty
        >;

    using edgeIter = boost::graph_traits<OverlapGraph>::out_edge_iterator;
    using OGVertex = boost::graph_traits<OverlapGraph>::vertex_descriptor;
    using OGEdge = boost::graph_traits<OverlapGraph>::edge_descriptor;
    using EP = EdgeProperty;

    template <class VisitorList>
    struct EdgeCategorizer : public boost::dfs_visitor<VisitorList>
    {
        EdgeCategorizer(std::vector<OGEdge>& edges,
                        const VisitorList& v = boost::null_visitor())
            : boost::dfs_visitor<VisitorList>(v),
              edges_(edges)
        {}

        template <class Edge, class Graph>
        void back_edge(Edge e, Graph& G)
        {
            edges_.push_back(e);
        }

    protected:
        std::vector<OGEdge>& edges_;
    };

    template <class VisitorList>
    EdgeCategorizer<VisitorList> categorizeEdges(const VisitorList& v,
                                                 std::vector<OGEdge>& edges)
    {
        return EdgeCategorizer<VisitorList>(edges, v);
    }

}} //namespace dnaasm::bst

#endif //OVERLAPGRAPH_HPP
