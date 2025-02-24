/**
 * \file TestUnitigsGenerator.cpp
 * \brief the C++ file with implementation of tests for UnitigsGenerator class
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

#include "../../../src/dbj/globals.hpp"
#include "../../../src/dbj/UnitigsGenerator.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

using namespace dnaasm::dbj;
using namespace std;

typedef boost::graph_traits<CompressedDeBruijnGraph>::edge_descriptor Edge;
typedef boost::graph_traits<CompressedDeBruijnGraph>::vertex_descriptor Vertex;
typedef std::vector<Vertex> Unitig;
typedef std::vector<Unitig> Unitigs;

BOOST_AUTO_TEST_SUITE(TestUnitigsGenerator)

BOOST_AUTO_TEST_CASE(emptyGraph)
{
    CompressedDeBruijnGraph compGraph;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 0U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 0);
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<0>().size(), 0);
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<1>().size(), 0);
}

BOOST_AUTO_TEST_CASE(singlePath)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 2);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 2);
    BOOST_CHECK_EQUAL(unitigs[0].front(), 0);
    BOOST_CHECK_EQUAL(unitigs[0].back(), 1);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(singleLongerPath)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 4);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 4);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv, 3);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(disconnectedGraphWithSinglePaths)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v2, v3, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 2U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 4);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs[0].size(), 2);
    BOOST_CHECK_EQUAL(unitigs[0].front(), 0);
    BOOST_CHECK_EQUAL(unitigs[0].back(), 1);
    BOOST_CHECK_EQUAL(unitigs[1].size(), 2);
    BOOST_CHECK_EQUAL(unitigs[1].front(), 2);
    BOOST_CHECK_EQUAL(unitigs[1].back(), 3);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
    BOOST_CHECK_EQUAL(isOriginal[1], true);
}
/*
BOOST_AUTO_TEST_CASE(singleLongerPathWithLoop_allCountersEqualTo1)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Vertex v6 = add_vertex(compGraph);
    Vertex v7 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v3, v4, compGraph);
    add_edge(v4, v5, compGraph);
    add_edge(v5, v6, compGraph);
    add_edge(v4, v7, compGraph);
    add_edge(v7, v2, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 8);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 3);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 5);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(unitigs[1].size(), 3);
    iv = unitigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv, 6);
    BOOST_CHECK_EQUAL(unitigs[2].size(), 3);
    iv = unitigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
    BOOST_CHECK_EQUAL(isOriginal[1], true);
    BOOST_CHECK_EQUAL(isOriginal[2], true);
}
*/

/////////* tests for correcting counters of edges in valid loop */////////

BOOST_AUTO_TEST_CASE(singleLongerPathWithLoop_allCountersEqualTo1_allSizesEqualTo1)
{
    Unitig unitig1(1, 0U);
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    compGraph[v0].uncompressedVertices_ = unitig1;
    compGraph[v1].uncompressedVertices_ = unitig1;
    compGraph[v2].uncompressedVertices_ = unitig1;
    compGraph[v3].uncompressedVertices_ = unitig1;
    compGraph[v4].uncompressedVertices_ = unitig1;
    compGraph[v5].uncompressedVertices_ = unitig1;
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v3, v4, compGraph);
    add_edge(v3, v5, compGraph);
    add_edge(v5, v1, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 6);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 9);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(singleLongerPathWithLoop_allCountersEqualTo1_sizesInBaseOfLoopEqualTo5)
{
    Unitig unitig1(1, 0U);
    Unitig unitig5(5, 0U);
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    compGraph[v0].uncompressedVertices_ = unitig1;
    compGraph[v1].uncompressedVertices_ = unitig1;
    compGraph[v2].uncompressedVertices_ = unitig5;
    compGraph[v3].uncompressedVertices_ = unitig1;
    compGraph[v4].uncompressedVertices_ = unitig1;
    compGraph[v5].uncompressedVertices_ = unitig1;
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v3, v4, compGraph);
    add_edge(v3, v5, compGraph);
    add_edge(v5, v1, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 6);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 9);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(singleLongerPathWithLoop_countersInBaseOfLoopEqualTo2_sizesInBaseOfLoopEqualTo5)
{
    Unitig unitig1(1, 0U);
    Unitig unitig5(5, 0U);
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    compGraph[v0].uncompressedVertices_ = unitig1;
    compGraph[v1].uncompressedVertices_ = unitig1;
    compGraph[v2].uncompressedVertices_ = unitig5;
    compGraph[v3].uncompressedVertices_ = unitig1;
    compGraph[v4].uncompressedVertices_ = unitig1;
    compGraph[v5].uncompressedVertices_ = unitig1;
    add_edge(v0, v1, compGraph);
    Edge e0 = add_edge(v1, v2, compGraph).first;
    Edge e1 = add_edge(v2, v3, compGraph).first;
    add_edge(v3, v4, compGraph);
    add_edge(v3, v5, compGraph);
    add_edge(v5, v1, compGraph);
    compGraph[e0].counter_ = 2U;
    compGraph[e1].counter_ = 2U;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 6);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 9);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(singleLongerPathWithLoop_countersInBaseOfLoopEqualTo3_sizesInBaseOfLoopEqualTo5)
{
    Unitig unitig1(1, 0U);
    Unitig unitig5(5, 0U);
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    compGraph[v0].uncompressedVertices_ = unitig1;
    compGraph[v1].uncompressedVertices_ = unitig1;
    compGraph[v2].uncompressedVertices_ = unitig5;
    compGraph[v3].uncompressedVertices_ = unitig1;
    compGraph[v4].uncompressedVertices_ = unitig1;
    compGraph[v5].uncompressedVertices_ = unitig1;
    add_edge(v0, v1, compGraph);
    Edge e0 = add_edge(v1, v2, compGraph).first;
    Edge e1 = add_edge(v2, v3, compGraph).first;
    add_edge(v3, v4, compGraph);
    add_edge(v3, v5, compGraph);
    add_edge(v5, v1, compGraph);
    compGraph[e0].counter_ = 3U;
    compGraph[e1].counter_ = 3U;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 6);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 13);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}















BOOST_AUTO_TEST_CASE(singleLongerPathWithLoop)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    Edge e0 = add_edge(v2, v3, compGraph).first;
    add_edge(v3, v4, compGraph);
    add_edge(v4, v2, compGraph);
    add_edge(v3, v5, compGraph);
    compGraph[e0].counter_ = 2;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 6);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 8);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 5);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(singleLongerPathWithLoop_anotherOrderOfEdges)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    Edge e0 = add_edge(v2, v3, compGraph).first;
    add_edge(v3, v5, compGraph);
    add_edge(v3, v4, compGraph);
    add_edge(v4, v2, compGraph);
    compGraph[e0].counter_ = 2;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 6);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 8);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 5);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(singleLongerPathWithLoopGreaterCountersInLoop)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Edge e0 = add_edge(v0, v1, compGraph).first;
    Edge e1 = add_edge(v1, v2, compGraph).first;
    Edge e2 = add_edge(v2, v3, compGraph).first;
    Edge e3 = add_edge(v3, v4, compGraph).first;
    Edge e4 = add_edge(v4, v2, compGraph).first;
    Edge e5 = add_edge(v3, v5, compGraph).first;
    compGraph[e0].counter_ = 1;
    compGraph[e1].counter_ = 1;
    compGraph[e2].counter_ = 3;
    compGraph[e3].counter_ = 2;
    compGraph[e4].counter_ = 2;
    compGraph[e5].counter_ = 1;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 6);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 11);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 5);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(singleLongerPathWithLoopGreaterCountersInAllGraph)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Edge e0 = add_edge(v0, v1, compGraph).first;
    Edge e1 = add_edge(v1, v2, compGraph).first;
    Edge e2 = add_edge(v2, v3, compGraph).first;
    Edge e3 = add_edge(v3, v4, compGraph).first;
    Edge e4 = add_edge(v4, v2, compGraph).first;
    Edge e5 = add_edge(v3, v5, compGraph).first;
    compGraph[e0].counter_ = 2;
    compGraph[e1].counter_ = 2;
    compGraph[e2].counter_ = 4;
    compGraph[e3].counter_ = 2;
    compGraph[e4].counter_ = 2;
    compGraph[e5].counter_ = 2;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 6);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 11);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 5);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], false);
}

BOOST_AUTO_TEST_CASE(one_in_two_out)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Vertex v6 = add_vertex(compGraph);
    Vertex v7 = add_vertex(compGraph);
    Vertex v8 = add_vertex(compGraph);
    Vertex v9 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v3, v4, compGraph);
    add_edge(v4, v5, compGraph);
    add_edge(v5, v6, compGraph);
    add_edge(v3, v7, compGraph);
    add_edge(v7, v8, compGraph);
    add_edge(v8, v9, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 10);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 3);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 4);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv, 3);
    BOOST_CHECK_EQUAL(unitigs[1].size(), 4);
    iv = unitigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv, 6);
    BOOST_CHECK_EQUAL(unitigs[2].size(), 4);
    iv = unitigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv, 9);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
    BOOST_CHECK_EQUAL(isOriginal[1], true);
    BOOST_CHECK_EQUAL(isOriginal[2], true);
}

BOOST_AUTO_TEST_CASE(two_in_one_out)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Vertex v6 = add_vertex(compGraph);
    Vertex v7 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v3, v7, compGraph);
    add_edge(v4, v5, compGraph);
    add_edge(v5, v6, compGraph);
    add_edge(v6, v3, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 8);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 3);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 4);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv, 3);
    BOOST_CHECK_EQUAL(unitigs[1].size(), 2);
    iv = unitigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 7);
    BOOST_CHECK_EQUAL(unitigs[2].size(), 4);
    iv = unitigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv, 3);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
    BOOST_CHECK_EQUAL(isOriginal[1], true);
    BOOST_CHECK_EQUAL(isOriginal[2], true);
}

BOOST_AUTO_TEST_CASE(two_in_two_out_loop)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Vertex v6 = add_vertex(compGraph);
    Vertex v7 = add_vertex(compGraph);
    Vertex v8 = add_vertex(compGraph);
    Vertex v9 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v3, v4, compGraph);
    add_edge(v4, v5, compGraph);
    add_edge(v6, v7, compGraph);
    add_edge(v7, v8, compGraph);
    add_edge(v8, v9, compGraph);
    add_edge(v3, v7, compGraph);
    add_edge(v8, v2, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 10);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 8);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 3);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(unitigs[1].size(), 2);
    iv = unitigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv, 3);
    BOOST_CHECK_EQUAL(unitigs[2].size(), 3);
    iv = unitigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv, 5);
    BOOST_CHECK_EQUAL(unitigs[3].size(), 2);
    iv = unitigs[3].begin();
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv, 7);
    BOOST_CHECK_EQUAL(unitigs[4].size(), 2);
    iv = unitigs[4].begin();
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv, 8);
    BOOST_CHECK_EQUAL(unitigs[5].size(), 2);
    iv = unitigs[5].begin();
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv, 9);
    BOOST_CHECK_EQUAL(unitigs[6].size(), 2);
    iv = unitigs[6].begin();
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 7);
    BOOST_CHECK_EQUAL(unitigs[7].size(), 2);
    iv = unitigs[7].begin();
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(isOriginal.size(), 8);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
    BOOST_CHECK_EQUAL(isOriginal[1], true);
    BOOST_CHECK_EQUAL(isOriginal[2], true);
    BOOST_CHECK_EQUAL(isOriginal[3], true);
    BOOST_CHECK_EQUAL(isOriginal[4], true);
    BOOST_CHECK_EQUAL(isOriginal[5], true);
    BOOST_CHECK_EQUAL(isOriginal[6], true);
    BOOST_CHECK_EQUAL(isOriginal[7], true);
}

BOOST_AUTO_TEST_CASE(four_vertices_loop)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v3, v0, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 4);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 5);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 0);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(self_loop_without_in_and_without_out)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Edge e0 = add_edge(v0, v0, compGraph).first;
    compGraph[e0].counter_ = 2;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 1);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 3);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv, v0);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(self_loop_with_in_and_out)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Edge e0 = add_edge(v1, v1, compGraph).first;
    compGraph[e0].counter_ = 2;
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 3);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 5);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(self_loop)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Edge e0 = add_edge(v0, v0, compGraph).first;
    compGraph[e0].counter_ = 2;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 1);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 1);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 3);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv, 0);
    BOOST_CHECK_EQUAL(isOriginal.size(), 1);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
}

BOOST_AUTO_TEST_CASE(one_in_one_out_loop_fork)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Vertex v6 = add_vertex(compGraph);
    Vertex v7 = add_vertex(compGraph);
    Vertex v8 = add_vertex(compGraph);
    Vertex v9 = add_vertex(compGraph);
    Edge e0 = add_edge(v0, v1, compGraph).first;
    Edge e1 = add_edge(v1, v2, compGraph).first;
    Edge e2 = add_edge(v2, v3, compGraph).first;
    Edge e3 = add_edge(v3, v4, compGraph).first;
    Edge e4 = add_edge(v4, v5, compGraph).first;
    Edge e5 = add_edge(v5, v6, compGraph).first;
    Edge e6 = add_edge(v5, v8, compGraph).first;
    Edge e7 = add_edge(v8, v9, compGraph).first;
    Edge e8 = add_edge(v9, v1, compGraph).first;
    Edge e9 = add_edge(v2, v7, compGraph).first;
    Edge e10 = add_edge(v7, v4, compGraph).first;
    compGraph[e0].counter_ = 1;
    compGraph[e1].counter_ = 1;
    compGraph[e2].counter_ = 1;
    compGraph[e3].counter_ = 1;
    compGraph[e4].counter_ = 2;
    compGraph[e5].counter_ = 1;
    compGraph[e6].counter_ = 1;
    compGraph[e7].counter_ = 1;
    compGraph[e8].counter_ = 1;
    compGraph[e9].counter_ = 1;
    compGraph[e10].counter_ = 1;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 10);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 7);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 2);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv, 1);
    BOOST_CHECK_EQUAL(unitigs[1].size(), 2);
    iv = unitigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(unitigs[2].size(), 3);
    iv = unitigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(unitigs[3].size(), 2);
    iv = unitigs[3].begin();
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv, 5);
    BOOST_CHECK_EQUAL(unitigs[4].size(), 2);
    iv = unitigs[4].begin();
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv, 6);
    BOOST_CHECK_EQUAL(unitigs[5].size(), 3);
    iv = unitigs[5].begin();
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(unitigs[6].size(), 4);
    iv = unitigs[6].begin();
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv++, 9);
    BOOST_CHECK_EQUAL(*iv, 1);
    BOOST_CHECK_EQUAL(isOriginal.size(), 7);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
    BOOST_CHECK_EQUAL(isOriginal[1], true);
    BOOST_CHECK_EQUAL(isOriginal[2], true);
    BOOST_CHECK_EQUAL(isOriginal[3], false);
    BOOST_CHECK_EQUAL(isOriginal[4], true);
    BOOST_CHECK_EQUAL(isOriginal[5], true);
    BOOST_CHECK_EQUAL(isOriginal[6], true);
}
/*
BOOST_AUTO_TEST_CASE(2_loops)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Vertex v6 = add_vertex(compGraph);
    Vertex v7 = add_vertex(compGraph);
    Vertex v8 = add_vertex(compGraph);
    Vertex v9 = add_vertex(compGraph);
    Edge e0 = add_edge(v0, v1, compGraph).first;
    Edge e1 = add_edge(v1, v2, compGraph).first;
    Edge e2 = add_edge(v2, v3, compGraph).first;
    Edge e3 = add_edge(v3, v4, compGraph).first;
    Edge e4 = add_edge(v4, v5, compGraph).first;
    Edge e5 = add_edge(v5, v6, compGraph).first;
    Edge e6 = add_edge(v6, v7, compGraph).first;
    Edge e7 = add_edge(v7, v8, compGraph).first;
    Edge e8 = add_edge(v8, v2, compGraph).first;
    Edge e9 = add_edge(v7, v9, compGraph).first;
    Edge e10 = add_edge(v9, v4, compGraph).first;
    compGraph[e0].counter_ = 1;
    compGraph[e1].counter_ = 1;
    compGraph[e2].counter_ = 2;
    compGraph[e3].counter_ = 2;
    compGraph[e4].counter_ = 3;
    compGraph[e5].counter_ = 3;
    compGraph[e6].counter_ = 3;
    compGraph[e7].counter_ = 1;
    compGraph[e8].counter_ = 1;
    compGraph[e9].counter_ = 1;
    compGraph[e10].counter_ = 1;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 10);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 5);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 3);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(unitigs[1].size(), 3);
    iv = unitigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(unitigs[2].size(), 4);
    iv = unitigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv, 7);
    BOOST_CHECK_EQUAL(unitigs[3].size(), 3);
    iv = unitigs[3].begin();
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv, 2);
    BOOST_CHECK_EQUAL(unitigs[4].size(), 3);
    iv = unitigs[4].begin();
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv++, 9);
    BOOST_CHECK_EQUAL(*iv, 4);
    BOOST_CHECK_EQUAL(isOriginal.size(), 5);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
    BOOST_CHECK_EQUAL(isOriginal[1], false);
    BOOST_CHECK_EQUAL(isOriginal[2], false);
    BOOST_CHECK_EQUAL(isOriginal[3], true);
    BOOST_CHECK_EQUAL(isOriginal[4], true);
}
*/
BOOST_AUTO_TEST_CASE(largeLoopCheckIn)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Vertex v6 = add_vertex(compGraph);
    Vertex v7 = add_vertex(compGraph);
    Vertex v8 = add_vertex(compGraph);
    Edge e0 = add_edge(v0, v1, compGraph).first;
    Edge e1 = add_edge(v1, v2, compGraph).first;
    Edge e2 = add_edge(v2, v3, compGraph).first;
    Edge e3 = add_edge(v3, v4, compGraph).first;
    Edge e4 = add_edge(v4, v5, compGraph).first;
    Edge e5 = add_edge(v5, v6, compGraph).first;
    Edge e6 = add_edge(v6, v1, compGraph).first;
    Edge e7 = add_edge(v2, v7, compGraph).first;
    Edge e8 = add_edge(v8, v7, compGraph).first;
    compGraph[e0].counter_ = 1;
    compGraph[e1].counter_ = 2;
    compGraph[e2].counter_ = 1;
    compGraph[e3].counter_ = 1;
    compGraph[e4].counter_ = 1;
    compGraph[e5].counter_ = 1;
    compGraph[e6].counter_ = 1;
    compGraph[e7].counter_ = 1;
    compGraph[e8].counter_ = 1;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 9);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 2);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 10);
    Unitig::const_iterator iv = unitigs[0].begin();
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
    BOOST_CHECK_EQUAL(unitigs[1].size(), 2);
    iv = unitigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv, 7);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
    BOOST_CHECK_EQUAL(isOriginal[1], true);
}

BOOST_AUTO_TEST_CASE(largeLoopCheckOut)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Vertex v6 = add_vertex(compGraph);
    Vertex v7 = add_vertex(compGraph);
    Vertex v8 = add_vertex(compGraph);
    Vertex v9 = add_vertex(compGraph);
    Edge e0 = add_edge(v0, v1, compGraph).first;
    Edge e1 = add_edge(v1, v2, compGraph).first;
    Edge e2 = add_edge(v2, v3, compGraph).first;
    Edge e3 = add_edge(v3, v4, compGraph).first;
    Edge e4 = add_edge(v4, v5, compGraph).first;
    Edge e5 = add_edge(v5, v6, compGraph).first;
    Edge e6 = add_edge(v6, v1, compGraph).first;
    Edge e7 = add_edge(v2, v7, compGraph).first;
    Edge e8 = add_edge(v7, v8, compGraph).first;
    Edge e9 = add_edge(v7, v9, compGraph).first;
    compGraph[e0].counter_ = 1;
    compGraph[e1].counter_ = 2;
    compGraph[e2].counter_ = 1;
    compGraph[e3].counter_ = 1;
    compGraph[e4].counter_ = 1;
    compGraph[e5].counter_ = 1;
    compGraph[e6].counter_ = 1;
    compGraph[e7].counter_ = 1;
    compGraph[e8].counter_ = 1;
    compGraph[e9].counter_ = 1;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 10);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 3);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 10);
    Unitig::const_iterator iv = unitigs[0].begin();
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
    BOOST_CHECK_EQUAL(unitigs[1].size(), 2);
    iv = unitigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv, 8);
    BOOST_CHECK_EQUAL(unitigs[2].size(), 2);
    iv = unitigs[2].begin();
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv, 9);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
    BOOST_CHECK_EQUAL(isOriginal[1], true);
    BOOST_CHECK_EQUAL(isOriginal[2], true);
}

BOOST_AUTO_TEST_CASE(circular_unitig_with_circular_loop)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    Vertex v6 = add_vertex(compGraph);
    Vertex v7 = add_vertex(compGraph);
    Vertex v8 = add_vertex(compGraph);
    Vertex v9 = add_vertex(compGraph);
    Edge e0 = add_edge(v0, v1, compGraph).first;
    Edge e1 = add_edge(v1, v2, compGraph).first;
    Edge e2 = add_edge(v2, v3, compGraph).first;
    Edge e3 = add_edge(v3, v4, compGraph).first;
    Edge e4 = add_edge(v4, v5, compGraph).first;
    Edge e5 = add_edge(v5, v6, compGraph).first;
    Edge e6 = add_edge(v6, v0, compGraph).first;
    Edge e7 = add_edge(v0, v7, compGraph).first;
    Edge e8 = add_edge(v7, v8, compGraph).first;
    Edge e9 = add_edge(v8, v9, compGraph).first;
    Edge e10 = add_edge(v9, v0, compGraph).first;
    compGraph[e0].counter_ = 1;
    compGraph[e1].counter_ = 1;
    compGraph[e2].counter_ = 1;
    compGraph[e3].counter_ = 1;
    compGraph[e4].counter_ = 1;
    compGraph[e5].counter_ = 1;
    compGraph[e6].counter_ = 1;
    compGraph[e7].counter_ = 2;
    compGraph[e8].counter_ = 2;
    compGraph[e9].counter_ = 2;
    compGraph[e10].counter_ = 2;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    boost::tuple<Unitigs, std::vector<bool>, unsigned long> unitigsGeneratorResult = generate();
    BOOST_CHECK_EQUAL(unitigsGeneratorResult.get<2>(), 1U);
    BOOST_CHECK_EQUAL(num_edges(compGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(compGraph), 10);
    Unitigs unitigs = unitigsGeneratorResult.get<0>();
    std::vector<bool> isOriginal = unitigsGeneratorResult.get<1>();
    BOOST_CHECK_EQUAL(unitigs.size(), 2);
    BOOST_CHECK_EQUAL(unitigs[0].size(), 8);
    Unitig::const_iterator iv = unitigs[0].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 1);
    BOOST_CHECK_EQUAL(*iv++, 2);
    BOOST_CHECK_EQUAL(*iv++, 3);
    BOOST_CHECK_EQUAL(*iv++, 4);
    BOOST_CHECK_EQUAL(*iv++, 5);
    BOOST_CHECK_EQUAL(*iv++, 6);
    BOOST_CHECK_EQUAL(*iv, 0);
    BOOST_CHECK_EQUAL(unitigs[1].size(), 5);
    iv = unitigs[1].begin();
    BOOST_CHECK_EQUAL(*iv++, 0);
    BOOST_CHECK_EQUAL(*iv++, 7);
    BOOST_CHECK_EQUAL(*iv++, 8);
    BOOST_CHECK_EQUAL(*iv++, 9);
    BOOST_CHECK_EQUAL(*iv, 0);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
    BOOST_CHECK_EQUAL(isOriginal[0], true);
    BOOST_CHECK_EQUAL(isOriginal[1], false);
}

/////////* find simle path between vertices in graph test */////////

BOOST_AUTO_TEST_CASE(findSimplePathBetweenVertices_singlePath_sourceEqualToDestination)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    vector<unsigned short> in_degree_all(num_vertices(compGraph), 1U);
    vector<unsigned short> out_degree_all(num_vertices(compGraph), 1U);
    vector<Vertex> path;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    generate.findSimplePathBetweenVertices(v0, v0, path, in_degree_all, out_degree_all);
    BOOST_CHECK_EQUAL(path.size(), 1);
    vector<Vertex>::const_iterator iv = path.begin();
    BOOST_CHECK_EQUAL(*iv, v0);
}

BOOST_AUTO_TEST_CASE(findSimplePathBetweenVertices_singlePath_sourceNotEqualToDestination_pathExist)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    vector<unsigned short> in_degree_all(num_vertices(compGraph), 1U);
    vector<unsigned short> out_degree_all(num_vertices(compGraph), 1U);
    vector<Vertex> path;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    generate.findSimplePathBetweenVertices(v0, v2, path, in_degree_all, out_degree_all);
    BOOST_CHECK_EQUAL(path.size(), 3);
    vector<Vertex>::const_iterator iv = path.begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv, v2);
}

BOOST_AUTO_TEST_CASE(findSimplePathBetweenVertices_singlePath_sourceNotEqualToDestination_pathNotExist)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    vector<unsigned short> in_degree_all(num_vertices(compGraph), 1U);
    vector<unsigned short> out_degree_all(num_vertices(compGraph), 1U);
    vector<Vertex> path;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    generate.findSimplePathBetweenVertices(v2, v0, path, in_degree_all, out_degree_all);
    BOOST_CHECK_EQUAL(path.size(), 0);
}

BOOST_AUTO_TEST_CASE(findSimplePathBetweenVertices_singlePathWithIn_sourceNotEqualToDestination_pathNotExist)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v4, v2, compGraph);
    vector<unsigned short> in_degree_all(num_vertices(compGraph), 1U);
    vector<unsigned short> out_degree_all(num_vertices(compGraph), 1U);
    in_degree_all[v2] = 2U;
    vector<Vertex> path;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    generate.findSimplePathBetweenVertices(v0, v3, path, in_degree_all, out_degree_all);
    BOOST_CHECK_EQUAL(path.size(), 0);
}

BOOST_AUTO_TEST_CASE(findSimplePathBetweenVertices_graphWithLoop_sourceNotEqualToDestination_pathFromLoopInToLoopOut)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v3, v4, compGraph);
    add_edge(v4, v2, compGraph);
    add_edge(v3, v5, compGraph);
    vector<unsigned short> in_degree_all(num_vertices(compGraph), 1U);
    vector<unsigned short> out_degree_all(num_vertices(compGraph), 1U);
    in_degree_all[v2] = 2U;
    out_degree_all[v3] = 2U;
    vector<Vertex> path;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    generate.findSimplePathBetweenVertices(v2, v3, path, in_degree_all, out_degree_all);
    BOOST_CHECK_EQUAL(path.size(), 2);
    vector<Vertex>::const_iterator iv = path.begin();
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv, v3);
}

BOOST_AUTO_TEST_CASE(findSimplePathBetweenVertices_graphWithLoop_sourceNotEqualToDestination_pathFromLoopOutToLoopIn)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    add_edge(v0, v1, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v3, v4, compGraph);
    add_edge(v4, v2, compGraph);
    add_edge(v3, v5, compGraph);
    vector<unsigned short> in_degree_all(num_vertices(compGraph), 1U);
    vector<unsigned short> out_degree_all(num_vertices(compGraph), 1U);
    in_degree_all[v2] = 2U;
    out_degree_all[v3] = 2U;
    vector<Vertex> path;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    generate.findSimplePathBetweenVertices(v3, v2, path, in_degree_all, out_degree_all);
    BOOST_CHECK_EQUAL(path.size(), 3);
    vector<Vertex>::const_iterator iv = path.begin();
    BOOST_CHECK_EQUAL(*iv++, v3);
    BOOST_CHECK_EQUAL(*iv++, v4);
    BOOST_CHECK_EQUAL(*iv, v2);
}

BOOST_AUTO_TEST_CASE(findSimplePathBetweenVertices_graphWithLoop_sourceNotEqualToDestination_pathFromLoopOutToLoopIn_anotherOrderOfEdges)
{
    CompressedDeBruijnGraph compGraph;
    Vertex v0 = add_vertex(compGraph);
    Vertex v1 = add_vertex(compGraph);
    Vertex v2 = add_vertex(compGraph);
    Vertex v3 = add_vertex(compGraph);
    Vertex v4 = add_vertex(compGraph);
    Vertex v5 = add_vertex(compGraph);
    add_edge(v3, v5, compGraph);
    add_edge(v4, v2, compGraph);
    add_edge(v3, v4, compGraph);
    add_edge(v2, v3, compGraph);
    add_edge(v1, v2, compGraph);
    add_edge(v0, v1, compGraph);
    vector<unsigned short> in_degree_all(num_vertices(compGraph), 1U);
    vector<unsigned short> out_degree_all(num_vertices(compGraph), 1U);
    in_degree_all[v2] = 2U;
    out_degree_all[v3] = 2U;
    vector<Vertex> path;
    UnitigsGenerator<CompressedDeBruijnGraph> generate(compGraph, NULL, 0.0);
    generate.findSimplePathBetweenVertices(v3, v2, path, in_degree_all, out_degree_all);
    BOOST_CHECK_EQUAL(path.size(), 3);
    vector<Vertex>::const_iterator iv = path.begin();
    BOOST_CHECK_EQUAL(*iv++, v3);
    BOOST_CHECK_EQUAL(*iv++, v4);
    BOOST_CHECK_EQUAL(*iv, v2);
}

BOOST_AUTO_TEST_SUITE_END()

