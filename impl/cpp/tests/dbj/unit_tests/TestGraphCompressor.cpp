/**
 * \file TestGraphCompressor.cpp
 * \brief the C++ file with implementation of tests for GraphCompressor class
 *
 */

#include <boost/test/unit_test.hpp>

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
//#pragma warning(disable:4068)
//#pragma warning(disable:4512)
#endif

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#include "../../../src/dbj/globals.hpp"
#include "../../../src/dbj/GraphCompressor.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

using namespace dnaasm::dbj;
using namespace std;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

BOOST_AUTO_TEST_SUITE(TestGraphCompressor)

BOOST_AUTO_TEST_CASE(compressGraphTest_empty_graph)
{
    DeBruijnGraph deBruijnGraph;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 0);
}
/*
BOOST_AUTO_TEST_CASE(compressGraphTest_1_vertex)
{
    std::vector<DeBruijnGraphVertex> sources;
    std::vector<DeBruijnGraphVertex> targets;
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 1);
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 1);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 0);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_2_disconnected_vertices)
{
    std::vector<DeBruijnGraphVertex> sources;
    std::vector<DeBruijnGraphVertex> targets;
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 12;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 2);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 0);
}
*/
BOOST_AUTO_TEST_CASE(compressGraphTest_2_connected_vertices)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    std::vector<DeBruijnGraphVertex> sources = {v0};
    std::vector<DeBruijnGraphVertex> targets = {v1};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 2);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 2);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 1);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_long_path)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 5);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[1], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[2], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[3], v4);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_2_disconnected_long_paths)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v5, v6};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v6, v7};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 8);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 8);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[1], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[2], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[3], v4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v6);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[1], v7);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(2, 3, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_fork_2_out_long_paths_all_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    DeBruijnGraphVertex v8 = 8;
    DeBruijnGraphVertex v9 = 9;
    DeBruijnGraphVertex v10 = 10;
    DeBruijnGraphVertex v11 = 11;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6, v4, v8, v9, v10};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 12);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v4, v8, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v8, v9, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v9, v10, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v10, v11, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 12);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 11);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[1], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[2], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[3], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[1], v6);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[2], v7);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v8);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[1], v9);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[2], v10);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[3], v11);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 3, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 3, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 3, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_fork_2_in_long_paths_all_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    DeBruijnGraphVertex v8 = 8;
    DeBruijnGraphVertex v9 = 9;
    DeBruijnGraphVertex v10 = 10;
    DeBruijnGraphVertex v11 = 11;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6, v8, v9, v10, v11};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v9, v10, v11, v4};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 12);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v8, v9, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v9, v10, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v10, v11, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v11, v4, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 12);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 11);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[1], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[2], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[3], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[1], v6);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[2], v7);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v8);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[1], v9);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[2], v10);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[3], v11);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(3, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_fork_2_out_long_paths_some_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    DeBruijnGraphVertex v8 = 8;
    DeBruijnGraphVertex v9 = 9;
    DeBruijnGraphVertex v10 = 10;
    DeBruijnGraphVertex v11 = 11;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6, v4, v8, v9, v10};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 12);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v4, v8, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v8, v9, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v9, v10, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v10, v11, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 12);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 11);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[1], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[2], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[3], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[1], v6);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[2], v7);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v8);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[1], v9);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[2], v10);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[3], v11);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 3, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 3, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 3, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_fork_2_in_long_paths_some_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    DeBruijnGraphVertex v8 = 8;
    DeBruijnGraphVertex v9 = 9;
    DeBruijnGraphVertex v10 = 10;
    DeBruijnGraphVertex v11 = 11;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6, v8, v9, v10, v11};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v9, v10, v11, v4};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 12);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v8, v9, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v9, v10, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v10, v11, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v11, v4, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 12);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 11);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[1], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[2], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[3], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[1], v6);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[2], v7);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v8);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[1], v9);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[2], v10);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[3], v11);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(3, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_fork_2_out_short_paths_all_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v1};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 4);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 3);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v3);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 3, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 3, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 3, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_fork_2_in_short_paths_all_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v1};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 4);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v1, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 3);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v3);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(3, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_fork_2_out_short_paths_some_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v1};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 4);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 3);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v3);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 3, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 3, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 3, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_fork_2_in_short_paths_some_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v1};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 4);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v3, v1, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 3);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v3);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(3, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_in_1_out_with_loop_long_paths_all_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    DeBruijnGraphVertex v8 = 8;
    DeBruijnGraphVertex v9 = 9;
    DeBruijnGraphVertex v10 = 10;
    DeBruijnGraphVertex v11 = 11;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v6, v10};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v3, v10, v11};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 12);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v8, v9, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v9, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v6, v10, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v10, v11, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 12);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 12);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 6);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[1], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[2], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[1], v5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v6);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_.size(), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_[0], v7);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_[1], v8);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_[2], v9);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[5].uncompressedVertices_.size(), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[5].uncompressedVertices_[0], v10);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[5].uncompressedVertices_[1], v11);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 6);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(2, 3, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(3, 4, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(4, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(3, 5, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 4, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(4, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 5, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 4, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(4, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 5, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_in_1_out_with_loop_long_paths_some_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    DeBruijnGraphVertex v8 = 8;
    DeBruijnGraphVertex v9 = 9;
    DeBruijnGraphVertex v10 = 10;
    DeBruijnGraphVertex v11 = 11;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v6, v10};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v3, v10, v11};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 12);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v8, v9, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v9, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v6, v10, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v10, v11, deBruijnGraph).first].counter_ = 3U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 12);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 12);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 6);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[1], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[2], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[1], v5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v6);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_.size(), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_[0], v7);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_[1], v8);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_[2], v9);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[5].uncompressedVertices_.size(), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[5].uncompressedVertices_[0], v10);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[5].uncompressedVertices_[1], v11);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 6);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(2, 3, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(3, 4, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(4, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(3, 5, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 4, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(4, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 5, graphCompressor.getCompressedGraph()).first].counter_, 3U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 4, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(4, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 5, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_in_1_out_with_loop_short_paths_all_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v2};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v1, v4};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 5);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_[0], v4);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 5);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(2, 3, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(3, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(2, 4, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 4, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 4, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_in_1_out_with_loop_short_paths_some_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v2};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v1, v4};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 5);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v3, v1, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 5U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[4].uncompressedVertices_[0], v4);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 5);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(2, 3, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(3, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(2, 4, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 2U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].counter_, 3U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].counter_, 4U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 4, graphCompressor.getCompressedGraph()).first].counter_, 5U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(3, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 4, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_long_loop_without_in_out_all_counters_equal_to_1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v0};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 5);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v4, v0, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[1], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[2], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[3], v4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[4], v0);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 0, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 0, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 0, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_long_loop_without_in_out_all_counters_equal_to_3)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v0};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 5);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v4, v0, deBruijnGraph).first].counter_ = 3U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[1], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[2], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[3], v4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[4], v0);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 0, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 0, graphCompressor.getCompressedGraph()).first].counter_, 3U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 0, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_long_path_with_self_loop)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 7);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v3, deBruijnGraph).first].counter_ = 5U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 7);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[1], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[2], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[1], v5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[2], v6);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(1, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 1, graphCompressor.getCompressedGraph()).first].counter_, 5U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 2, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(1, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_long_path_with_tips_with_counters_equal_to_0)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v5, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v1, v6};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 7);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v5, v1, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v3, v6, deBruijnGraph).first].counter_ = 0U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[1], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[2], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[3], v4);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_long_path_with_tips_with_counters_equal_to_0_another_order_of_edges)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    std::vector<DeBruijnGraphVertex> sources = {v3, v5, v3, v2, v1, v0};
    std::vector<DeBruijnGraphVertex> targets = {v6, v1, v4, v3, v2, v1};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 7);
    deBruijnGraph[edge(v3, v6, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v5, v1, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[1], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[2], v3);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[3], v4);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_CASE(compressGraphTest_1_long_path_with_edges_with_counters_equal_to_0_in_the_middle_of_path)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 8);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 3U;
    GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
    graphCompressor.compressGraph();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 8);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 7);
    BOOST_CHECK_EQUAL(num_vertices(graphCompressor.getCompressedGraph()), 4);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[0].uncompressedVertices_[0], v0);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_.size(), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[0], v1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[1].uncompressedVertices_[1], v2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_.size(), 1);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[2].uncompressedVertices_[0], v5);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_.size(), 2);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[0], v6);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[3].uncompressedVertices_[1], v7);
    BOOST_CHECK_EQUAL(num_edges(graphCompressor.getCompressedGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(edge(2, 3, graphCompressor.getCompressedGraph()).second, true);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].counter_, 1U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].counter_, 3U);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(0, 1, graphCompressor.getCompressedGraph()).first].bridge_, false);
    BOOST_CHECK_EQUAL(graphCompressor.getCompressedGraph()[edge(2, 3, graphCompressor.getCompressedGraph()).first].bridge_, false);
}

BOOST_AUTO_TEST_SUITE_END()

