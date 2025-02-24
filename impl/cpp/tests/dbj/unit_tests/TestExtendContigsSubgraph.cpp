/**
 * \file TestEulerPath.cpp
 * \brief the C++ file with implementation of tests for ExtendContigsSubgraph class
 *
 */

#include <boost/test/unit_test.hpp>

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
//unknown pragma
#pragma warning(disable:4068)
#pragma warning(disable:4512)
#endif

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#include "../../../src/dbj/ExtendContigsSubgraph.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

#include "../../../src/dbj/UnitigsToContigsExtension.hpp"

using namespace dnaasm::dbj;
using namespace std;

typedef std::vector<UnitigsToContigsExtension::UnitigsGraphVertex> Contig;

BOOST_AUTO_TEST_SUITE(TestExtendContigsSubgraph)

/*

BOOST_AUTO_TEST_CASE(extendTest_2In_2Out_loop)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(graph);
    add_edge(v0, v1, graph);
    add_edge(v1, v2, graph);
    add_edge(v2, v3, graph);
    add_edge(v3, v4, graph);
    add_edge(v4, v5, graph);
    add_edge(v6, v7, graph);
    add_edge(v7, v8, graph);
    add_edge(v8, v9, graph);
    add_edge(v3, v7, graph);
    add_edge(v8, v2, graph);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 10);
    BOOST_CHECK_EQUAL(resultantContig.size(), 3);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(resultantContigs[1].size(), 2);
    iv = contigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv, 3);
    BOOST_CHECK_EQUAL(resultantContigs[2].size(), 2);
    iv = contigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv, 5);
    BOOST_CHECK_EQUAL(resultantContigs[3].size(), 1);
    iv = contigs[3].begin();
    BOOST_CHECK_EQUAL(*iv, 7);
    BOOST_CHECK_EQUAL(resultantContigs[4].size(), 2);
    iv = contigs[4].begin();
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv, 7);
    BOOST_CHECK_EQUAL(resultantContigs[5].size(), 2);
    iv = contigs[5].begin();
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv, 8);
    BOOST_CHECK_EQUAL(resultantContigs[6].size(), 1);
    iv = contigs[6].begin();
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(resultantContigs[7].size(), 1);
    iv = contigs[7].begin();
    BOOST_CHECK_EQUAL(*iv, 9);
}

BOOST_AUTO_TEST_CASE(extendTest_4_vertices_loop)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    add_edge(v0, v1, graph);
    add_edge(v1, v2, graph);
    add_edge(v2, v3, graph);
    add_edge(v3, v0, graph);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 4);
    BOOST_CHECK_EQUAL(resultantContig.size(), 5);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 0);
}

BOOST_AUTO_TEST_CASE(extendTest_self_loop_with_in)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v1, v1, graph).first;
    graph[e0].counter_ = 2;
    add_edge(v0, v1, graph);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 2);
    BOOST_CHECK_EQUAL(resultantContig.size(), 4);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 1);
}

BOOST_AUTO_TEST_CASE(extendTest_self_loop_with_out)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v0, graph).first;
    graph[e0].counter_ = 2;
    add_edge(v0, v1, graph);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 2);
    BOOST_CHECK_EQUAL(resultantContig.size(), 4);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv, 1);
}

BOOST_AUTO_TEST_CASE(extendTest_self_loop_with_in_and_out)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v1, v1, graph).first;
    graph[e0].counter_ = 2;
    add_edge(v0, v1, graph);
    add_edge(v1, v2, graph);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 3);
    BOOST_CHECK_EQUAL(resultantContig.size(), 5);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
}

BOOST_AUTO_TEST_CASE(extendTest_self_loop)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v0, graph).first;
    graph[e0].counter_ = 2;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 1);
    BOOST_CHECK_EQUAL(resultantContig.size(), 3);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv, 0);
}

BOOST_AUTO_TEST_CASE(extendTest_1In_1Out_loop_fork)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v5, v8, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = add_edge(v8, v9, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e8 = add_edge(v9, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e9 = add_edge(v2, v7, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e10 = add_edge(v7, v4, graph).first;
    graph[e0].counter_ = 1;
    graph[e1].counter_ = 1;
    graph[e2].counter_ = 1;
    graph[e3].counter_ = 1;
    graph[e4].counter_ = 2;
    graph[e5].counter_ = 1;
    graph[e6].counter_ = 1;
    graph[e7].counter_ = 1;
    graph[e8].counter_ = 1;
    graph[e9].counter_ = 1;
    graph[e10].counter_ = 1;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 10);
    BOOST_CHECK_EQUAL(resultantContig.size(), 2);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv, 1);
    BOOST_CHECK_EQUAL(resultantContigs[1].size(), 2);
    iv = contigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(resultantContigs[2].size(), 2);
    iv = contigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(resultantContigs[3].size(), 2);
    iv = contigs[3].begin();
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(resultantContigs[4].size(), 2);
    iv = contigs[4].begin();
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv, 5);
    BOOST_CHECK_EQUAL(resultantContigs[5].size(), 1);
    iv = contigs[5].begin();
    BOOST_CHECK_EQUAL(*iv, 6);
    BOOST_CHECK_EQUAL(resultantContigs[6].size(), 3);
    iv = contigs[6].begin();
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv++, 9);
    BOOST_CHECK_EQUAL(*iv, 1);
}

BOOST_AUTO_TEST_CASE(extendTest_2_loops)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v7, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = add_edge(v7, v8, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e8 = add_edge(v8, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e9 = add_edge(v7, v9, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e10 = add_edge(v9, v4, graph).first;
    graph[e0].counter_ = 1;
    graph[e1].counter_ = 1;
    graph[e2].counter_ = 2;
    graph[e3].counter_ = 2;
    graph[e4].counter_ = 3;
    graph[e5].counter_ = 3;
    graph[e6].counter_ = 3;
    graph[e7].counter_ = 1;
    graph[e8].counter_ = 1;
    graph[e9].counter_ = 1;
    graph[e10].counter_ = 1;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 10);
    BOOST_CHECK_EQUAL(resultantContig.size(), 3);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(resultantContigs[1].size(), 3);
    iv = contigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(resultantContigs[2].size(), 4);
    iv = contigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv, 7);
    BOOST_CHECK_EQUAL(resultantContigs[3].size(), 2);
    iv = contigs[3].begin();
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(resultantContigs[4].size(), 2);
    iv = contigs[4].begin();
    BOOST_CHECK_EQUAL(*iv++, 9);
    BOOST_CHECK_EQUAL(*iv, 4);
}

BOOST_AUTO_TEST_CASE(extendTest_largeLoopCheckIn)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = add_edge(v2, v7, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e8 = add_edge(v8, v7, graph).first;
    graph[e0].counter_ = 1;
    graph[e1].counter_ = 2;
    graph[e2].counter_ = 1;
    graph[e3].counter_ = 1;
    graph[e4].counter_ = 1;
    graph[e5].counter_ = 1;
    graph[e6].counter_ = 1;
    graph[e7].counter_ = 1;
    graph[e8].counter_ = 1;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 9);
    BOOST_CHECK_EQUAL(resultantContig.size(), 10);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv, 7);
    BOOST_CHECK_EQUAL(resultantContigs[1].size(), 2);
    iv = contigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv, 7);
}

BOOST_AUTO_TEST_CASE(extendTest_largeLoopCheckOut)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = add_edge(v2, v7, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e8 = add_edge(v7, v8, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e9 = add_edge(v7, v9, graph).first;
    graph[e0].counter_ = 1;
    graph[e1].counter_ = 2;
    graph[e2].counter_ = 1;
    graph[e3].counter_ = 1;
    graph[e4].counter_ = 1;
    graph[e5].counter_ = 1;
    graph[e6].counter_ = 1;
    graph[e7].counter_ = 1;
    graph[e8].counter_ = 1;
    graph[e9].counter_ = 1;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 10);
    BOOST_CHECK_EQUAL(resultantContig.size(), 10);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv, 7);
    BOOST_CHECK_EQUAL(resultantContigs[1].size(), 1);
    iv = contigs[1].begin();
    BOOST_CHECK_EQUAL(*iv, 8);
    BOOST_CHECK_EQUAL(resultantContigs[2].size(), 1);
    iv = contigs[2].begin();
    BOOST_CHECK_EQUAL(*iv, 9);
}*/

/******************************* empty contigs ************************************/

BOOST_AUTO_TEST_CASE(extendTest_empty_graph)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 0);
    BOOST_CHECK_EQUAL(resultantContig.size(), 0);
}

BOOST_AUTO_TEST_CASE(extendTest_1In_1Out_linear_both_ends_are_short)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    graph[v0].sequenceSize_ = 5U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v0].isLongNode_ = false;
    graph[v1].isLongNode_ = false;
    graph[v2].isLongNode_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    graph[e0].isForConnectedSequences_ = true;
    graph[e1].isForConnectedSequences_ = true;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 1U;
    distanceArray[0][2] = 5U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 2);
    BOOST_CHECK_EQUAL(num_vertices(graph), 3);
    BOOST_CHECK_EQUAL(resultantContig.size(), 0);
}

/******************************* linear structures ************************************/

BOOST_AUTO_TEST_CASE(extendTest_1In_1Out_linear_the_same_contigs_size_ideal_distance_array)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    graph[v0].sequenceSize_ = 5U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    graph[v0].isLongNode_ = true;
    graph[v1].isLongNode_ = false;
    graph[v2].isLongNode_ = false;
    graph[v3].isLongNode_ = false;
    graph[v4].isLongNode_ = false;
    graph[v5].isLongNode_ = false;
    graph[v6].isLongNode_ = true;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, graph).first;
    graph[e0].isForConnectedSequences_ = true;
    graph[e1].isForConnectedSequences_ = true;
    graph[e2].isForConnectedSequences_ = true;
    graph[e3].isForConnectedSequences_ = true;
    graph[e4].isForConnectedSequences_ = true;
    graph[e5].isForConnectedSequences_ = true;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 15U;
    distanceArray[0][5] = 20U;
    distanceArray[0][6] = 25U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 6);
    BOOST_CHECK_EQUAL(num_vertices(graph), 7);
    BOOST_CHECK_EQUAL(resultantContig.size(), 7);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv, 6);
}

BOOST_AUTO_TEST_CASE(extendTest_disconnected_graph_1In_1Out_linear_the_same_contigs_size_ideal_distance_array)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    graph[v0].sequenceSize_ = 5U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    graph[v7].sequenceSize_ = 5U;
    graph[v0].isLongNode_ = true;
    graph[v1].isLongNode_ = false;
    graph[v2].isLongNode_ = false;
    graph[v3].isLongNode_ = false;
    graph[v4].isLongNode_ = false;
    graph[v5].isLongNode_ = false;
    graph[v6].isLongNode_ = true;
    graph[v7].isLongNode_ = true;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, graph).first;
    graph[e0].isForConnectedSequences_ = true;
    graph[e1].isForConnectedSequences_ = true;
    graph[e2].isForConnectedSequences_ = true;
    graph[e3].isForConnectedSequences_ = true;
    graph[e4].isForConnectedSequences_ = true;
    graph[e5].isForConnectedSequences_ = true;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 15U;
    distanceArray[0][5] = 20U;
    distanceArray[0][6] = 25U;
    distanceArray[0][7] = 1U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 6);
    BOOST_CHECK_EQUAL(num_vertices(graph), 8);
    BOOST_CHECK_EQUAL(resultantContig.size(), 7);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv, 6);
}

BOOST_AUTO_TEST_CASE(extendTest_1In_1Out_linear_with_fork_the_same_contigs_size_distance_array_with_short_int_max)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    graph[v0].sequenceSize_ = 5U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v0].isLongNode_ = true;
    graph[v1].isLongNode_ = false;
    graph[v2].isLongNode_ = true;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v0, v2, graph).first;
    graph[e0].isForConnectedSequences_ = true;
    graph[e1].isForConnectedSequences_ = true;
    graph[e2].isForConnectedSequences_ = true;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 1U;
    distanceArray[0][2] = numeric_limits<unsigned short>::max();
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 3);
    BOOST_CHECK_EQUAL(num_vertices(graph), 3);
    BOOST_CHECK_EQUAL(resultantContig.size(), 3);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
}

/*
BOOST_AUTO_TEST_CASE(extendTest_1In_2Out_linear_the_same_contigs_size_ideal_distance_array)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    graph[v0].sequenceSize_ = 5U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    add_edge(v0, v1, graph).first;
    add_edge(v1, v2, graph).first;
    add_edge(v2, v3, graph).first;
    add_edge(v3, v4, graph).first;
    add_edge(v4, v5, graph).first;
    add_edge(v2, v6, graph).first;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 15U;
    distanceArray[0][5] = 20U;
    distanceArray[0][6] = 10U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 7);
    BOOST_CHECK_EQUAL(resultantContig.size(), 3);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(resultantContigs[1].size(), 3);
    iv = contigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv, 5);
    BOOST_CHECK_EQUAL(resultantContigs[2].size(), 1);
    iv = contigs[2].begin();
    BOOST_CHECK_EQUAL(*iv, 6);
}

BOOST_AUTO_TEST_CASE(extendTest_2In_1Out_linear_the_same_contigs_size_ideal_distance_array)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    graph[v0].sequenceSize_ = 5U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    add_edge(v0, v1, graph).first;
    add_edge(v1, v2, graph).first;
    add_edge(v2, v3, graph).first;
    add_edge(v3, v4, graph).first;
    add_edge(v4, v5, graph).first;
    add_edge(v6, v2, graph).first;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 15U;
    distanceArray[0][5] = 20U;
    distanceArray[0][6] = 0U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 7);
    BOOST_CHECK_EQUAL(resultantContig.size(), 3);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(resultantContigs[1].size(), 4);
    iv = contigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv, 5);
    BOOST_CHECK_EQUAL(resultantContigs[2].size(), 2);
    iv = contigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv, 2);
}
*/

/******************************* simple loops ************************************/

BOOST_AUTO_TEST_CASE(extendTest_1In_1Out_simple_loop_in_the_same_sequenceSize_the_same_contigs_size_ideal_distance_array)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(graph);
    graph[v0].sequenceSize_ = 25U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    graph[v7].sequenceSize_ = 5U;
    graph[v8].sequenceSize_ = 5U;
    graph[v9].sequenceSize_ = 25U;
    graph[v0].isOriginal_ = true;
    graph[v1].isOriginal_ = false;
    graph[v2].isOriginal_ = false;
    graph[v3].isOriginal_ = false;
    graph[v4].isOriginal_ = false;
    graph[v5].isOriginal_ = false;
    graph[v6].isOriginal_ = false;
    graph[v7].isOriginal_ = false;
    graph[v8].isOriginal_ = false;
    graph[v9].isOriginal_ = true;
    graph[v0].isLongNode_ = true;
    graph[v1].isLongNode_ = false;
    graph[v2].isLongNode_ = false;
    graph[v3].isLongNode_ = false;
    graph[v4].isLongNode_ = false;
    graph[v5].isLongNode_ = false;
    graph[v6].isLongNode_ = false;
    graph[v7].isLongNode_ = false;
    graph[v8].isLongNode_ = false;
    graph[v9].isLongNode_ = true;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v7, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = add_edge(v7, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e8 = add_edge(v2, v8, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e9 = add_edge(v8, v9, graph).first;
    graph[e0].isForConnectedSequences_ = true;
    graph[e1].isForConnectedSequences_ = true;
    graph[e2].isForConnectedSequences_ = true;
    graph[e3].isForConnectedSequences_ = true;
    graph[e4].isForConnectedSequences_ = true;
    graph[e5].isForConnectedSequences_ = true;
    graph[e6].isForConnectedSequences_ = true;
    graph[e7].isForConnectedSequences_ = true;
    graph[e8].isForConnectedSequences_ = true;
    graph[e9].isForConnectedSequences_ = true;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 15U;
    distanceArray[0][5] = 20U;
    distanceArray[0][6] = 25U;
    distanceArray[0][7] = 30U;
    distanceArray[0][8] = 50U;
    distanceArray[0][9] = 55U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 10);
    BOOST_CHECK_EQUAL(num_vertices(graph), 10);
    BOOST_CHECK_EQUAL(resultantContig.size(), 11);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv, 9);
}

BOOST_AUTO_TEST_CASE(extendTest_1In_1Out_simple_loop_the_same_contigs_size_ideal_distance_array_single_repetition)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(graph);
    graph[v0].sequenceSize_ = 25U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    graph[v7].sequenceSize_ = 5U;
    graph[v8].sequenceSize_ = 5U;
    graph[v9].sequenceSize_ = 25U;
    graph[v0].isOriginal_ = true;
    graph[v1].isOriginal_ = false;
    graph[v2].isOriginal_ = false;
    graph[v3].isOriginal_ = false;
    graph[v4].isOriginal_ = false;
    graph[v5].isOriginal_ = false;
    graph[v6].isOriginal_ = false;
    graph[v7].isOriginal_ = false;
    graph[v8].isOriginal_ = false;
    graph[v9].isOriginal_ = true;
    graph[v0].isLongNode_ = true;
    graph[v1].isLongNode_ = false;
    graph[v2].isLongNode_ = false;
    graph[v3].isLongNode_ = false;
    graph[v4].isLongNode_ = false;
    graph[v5].isLongNode_ = false;
    graph[v6].isLongNode_ = false;
    graph[v7].isLongNode_ = false;
    graph[v8].isLongNode_ = false;
    graph[v9].isLongNode_ = true;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v7, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = add_edge(v7, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e8 = add_edge(v5, v8, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e9 = add_edge(v8, v9, graph).first;
    graph[e0].isForConnectedSequences_ = true;
    graph[e1].isForConnectedSequences_ = true;
    graph[e2].isForConnectedSequences_ = true;
    graph[e3].isForConnectedSequences_ = true;
    graph[e4].isForConnectedSequences_ = true;
    graph[e5].isForConnectedSequences_ = true;
    graph[e6].isForConnectedSequences_ = true;
    graph[e7].isForConnectedSequences_ = true;
    graph[e8].isForConnectedSequences_ = true;
    graph[e9].isForConnectedSequences_ = true;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 15U;
    distanceArray[0][5] = 20U;
    distanceArray[0][6] = 25U;
    distanceArray[0][7] = 30U;
    distanceArray[0][8] = 55U;
    distanceArray[0][9] = 60U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 10);
    BOOST_CHECK_EQUAL(num_vertices(graph), 10);
    BOOST_CHECK_EQUAL(resultantContig.size(), 14);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv, 9);
}

BOOST_AUTO_TEST_CASE(extendTest_1In_1Out_simple_loop_the_same_contigs_size_ideal_distance_array_double_repetition)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(graph);
    graph[v0].sequenceSize_ = 25U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    graph[v7].sequenceSize_ = 5U;
    graph[v8].sequenceSize_ = 5U;
    graph[v9].sequenceSize_ = 25U;
    graph[v0].isOriginal_ = true;
    graph[v1].isOriginal_ = false;
    graph[v2].isOriginal_ = false;
    graph[v3].isOriginal_ = false;
    graph[v4].isOriginal_ = false;
    graph[v5].isOriginal_ = false;
    graph[v6].isOriginal_ = false;
    graph[v7].isOriginal_ = false;
    graph[v8].isOriginal_ = false;
    graph[v9].isOriginal_ = true;
    graph[v0].isLongNode_ = true;
    graph[v1].isLongNode_ = false;
    graph[v2].isLongNode_ = false;
    graph[v3].isLongNode_ = false;
    graph[v4].isLongNode_ = false;
    graph[v5].isLongNode_ = false;
    graph[v6].isLongNode_ = false;
    graph[v7].isLongNode_ = false;
    graph[v8].isLongNode_ = false;
    graph[v9].isLongNode_ = true;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v7, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = add_edge(v7, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e8 = add_edge(v5, v8, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e9 = add_edge(v8, v9, graph).first;
    graph[e0].isForConnectedSequences_ = true;
    graph[e1].isForConnectedSequences_ = true;
    graph[e2].isForConnectedSequences_ = true;
    graph[e3].isForConnectedSequences_ = true;
    graph[e4].isForConnectedSequences_ = true;
    graph[e5].isForConnectedSequences_ = true;
    graph[e6].isForConnectedSequences_ = true;
    graph[e7].isForConnectedSequences_ = true;
    graph[e8].isForConnectedSequences_ = true;
    graph[e9].isForConnectedSequences_ = true;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 15U;
    distanceArray[0][5] = 20U;
    distanceArray[0][6] = 25U;
    distanceArray[0][7] = 30U;
    distanceArray[0][8] = 55U;
    distanceArray[0][9] = 90U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 10);
    BOOST_CHECK_EQUAL(num_vertices(graph), 10);
    BOOST_CHECK_EQUAL(resultantContig.size(), 20);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv, 9);
}

BOOST_AUTO_TEST_CASE(extendTest_1In_1Out_simple_1_vertex_loop_the_same_contigs_size_ideal_distance_array_single_repetition)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    graph[v0].sequenceSize_ = 25U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 25U;
    graph[v0].isOriginal_ = true;
    graph[v1].isOriginal_ = false;
    graph[v2].isOriginal_ = false;
    graph[v3].isOriginal_ = true;
    graph[v0].isLongNode_ = true;
    graph[v1].isLongNode_ = false;
    graph[v2].isLongNode_ = false;
    graph[v3].isLongNode_ = true;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v1, graph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v1, v3, graph).first;
    graph[e0].isForConnectedSequences_ = true;
    graph[e1].isForConnectedSequences_ = true;
    graph[e2].isForConnectedSequences_ = true;
    graph[e3].isForConnectedSequences_ = true;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 7U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 15U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 4);
    BOOST_CHECK_EQUAL(num_vertices(graph), 4);
    BOOST_CHECK_EQUAL(resultantContig.size(), 5);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 3);
}

/******************************* loops with single fork ************************************/

/*
BOOST_AUTO_TEST_CASE(extendTest_1In_1Out_loop_fork_in_base_of_loop_the_same_contigs_size_ideal_distance_array)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(graph);
    graph[v0].sequenceSize_ = 5U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    graph[v7].sequenceSize_ = 5U;
    graph[v8].sequenceSize_ = 5U;
    graph[v9].sequenceSize_ = 5U;
    add_edge(v0, v1, graph).first;
    add_edge(v1, v2, graph).first;
    add_edge(v2, v3, graph).first;
    add_edge(v3, v4, graph).first;
    add_edge(v4, v5, graph).first;
    add_edge(v5, v6, graph).first;
    add_edge(v5, v8, graph).first;
    add_edge(v8, v9, graph).first;
    add_edge(v9, v1, graph).first;
    add_edge(v2, v7, graph).first;
    add_edge(v7, v4, graph).first;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 15U;
    distanceArray[0][5] = 20U;
    distanceArray[0][6] = 40U;
    distanceArray[0][7] = 35U;
    distanceArray[0][8] = 25U;
    distanceArray[0][9] = 30U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 10);
    BOOST_CHECK_EQUAL(resultantContig.size(), 14);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv++, 9);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv, 6);
}

BOOST_AUTO_TEST_CASE(extendTest_1In_1Out_loop_fork_in_head_of_loop_the_same_contigs_size_ideal_distance_array)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(graph);
    graph[v0].sequenceSize_ = 5U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    graph[v7].sequenceSize_ = 5U;
    graph[v8].sequenceSize_ = 5U;
    graph[v9].sequenceSize_ = 5U;
    add_edge(v0, v1, graph).first;
    add_edge(v1, v2, graph).first;
    add_edge(v2, v3, graph).first;
    add_edge(v3, v4, graph).first;
    add_edge(v4, v5, graph).first;
    add_edge(v5, v6, graph).first;
    add_edge(v5, v8, graph).first;
    add_edge(v8, v9, graph).first;
    add_edge(v9, v1, graph).first;
    add_edge(v8, v7, graph).first;
    add_edge(v7, v1, graph).first;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 15U;
    distanceArray[0][5] = 20U;
    distanceArray[0][6] = 95U;
    distanceArray[0][7] = 30U;
    distanceArray[0][8] = 25U;
    distanceArray[0][9] = 35U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 10);
    BOOST_CHECK_EQUAL(resultantContig.size(), 21);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv++, 9);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv, 6);
}
*/
/*
BOOST_AUTO_TEST_CASE(extendTest_1In_0Out_single_loop_the_same_contigs_size_ideal_distance_array)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    graph[v0].sequenceSize_ = 5U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    add_edge(v0, v1, graph).first;
    add_edge(v1, v2, graph).first;
    add_edge(v2, v3, graph).first;
    add_edge(v3, v4, graph).first;
    add_edge(v4, v5, graph).first;
    add_edge(v5, v6, graph).first;
    add_edge(v6, v3, graph).first;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 15U;
    distanceArray[0][5] = 20U;
    distanceArray[0][6] = 25U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 0);
    BOOST_CHECK_EQUAL(num_vertices(graph), 7);
    BOOST_CHECK_EQUAL(resultantContig.size(), 8);
    Contig::const_iterator iv = resultantContig.begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv, 3);
}

BOOST_AUTO_TEST_CASE(extendTest_1In_0Out_double_loop_the_same_contigs_size_ideal_distance_array)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    graph[v0].sequenceSize_ = 5U;
    graph[v1].sequenceSize_ = 5U;
    graph[v2].sequenceSize_ = 5U;
    graph[v3].sequenceSize_ = 5U;
    graph[v4].sequenceSize_ = 5U;
    graph[v5].sequenceSize_ = 5U;
    graph[v6].sequenceSize_ = 5U;
    add_edge(v0, v1, graph).first;
    add_edge(v1, v2, graph).first;
    add_edge(v2, v3, graph).first;
    add_edge(v3, v1, graph).first;
    add_edge(v0, v4, graph).first;
    add_edge(v4, v5, graph).first;
    add_edge(v5, v6, graph).first;
    add_edge(v6, v4, graph).first;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 0U;
    distanceArray[0][5] = 5U;
    distanceArray[0][6] = 10U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 8);
    BOOST_CHECK_EQUAL(num_vertices(graph), 7);
}*/

/*
BOOST_AUTO_TEST_CASE(extendTest_coli_test)
{
    UnitigsToContigsExtension::UnitigsGraph graph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(graph);
    UnitigsToContigsExtension::UnitigsGraphVertex v10 = add_vertex(graph);
    graph[v0].sequenceSize_ = 8U;
    graph[v1].sequenceSize_ = 23U;
    graph[v2].sequenceSize_ = 6U;
    graph[v3].sequenceSize_ = 44U;
    graph[v4].sequenceSize_ = 185U;
    graph[v5].sequenceSize_ = 56U;
    graph[v6].sequenceSize_ = 30U;
    graph[v7].sequenceSize_ = 21536U;
    graph[v8].sequenceSize_ = 2U;
    graph[v9].sequenceSize_ = 23U;
    graph[v10].sequenceSize_ = 20U;
    add_edge(v0, v1, graph).first;
    add_edge(v0, v2, graph).first;
    add_edge(v1, v5, graph).first;
    add_edge(v2, v6, graph).first;
    add_edge(v3, v10, graph).first;
    add_edge(v4, v5, graph).first;
    add_edge(v5, v6, graph).first;
    add_edge(v6, v8, graph).first;
    add_edge(v7, v1, graph).first;
    add_edge(v7, v2, graph).first;
    add_edge(v8, v9, graph).first;
    add_edge(v9, v4, graph).first;
    add_edge(v10, v3, graph).first;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray(boost::extents[num_vertices(graph)][num_vertices(graph)]);
    distanceArray[0][0] = 0U;
    distanceArray[0][1] = 0U;
    distanceArray[0][2] = 5U;
    distanceArray[0][3] = 10U;
    distanceArray[0][4] = 0U;
    distanceArray[0][5] = 5U;
    distanceArray[0][6] = 10U;
    ExtendContigsSubgraph<UnitigsToContigsExtension::UnitigsGraph> extend(graph, distanceArray);
    Contig resultantContig = extend.extendContigsSubgraph(true);
    BOOST_CHECK_EQUAL(num_edges(graph), 13);
    BOOST_CHECK_EQUAL(num_vertices(graph), 11);
    BOOST_CHECK_EQUAL(resultantContig.size(), 0);
}*/

BOOST_AUTO_TEST_SUITE_END()

