/**
 * \file TestFilterGraph.cpp
 * \brief the C++ file with implementation of tests for FilterGraph class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/FilterGraph.hpp"
#include "../../../src/dbj/UnitigsToContigsExtension.hpp"

using namespace dnaasm::dbj;
using namespace std;

typedef UnitigsToContigsExtension::UnitigsGraph UnitigsGraph;
typedef UnitigsToContigsExtension::UnitigsGraphVertex UnitigsGraphVertex;
typedef UnitigsToContigsExtension::UnitigsGraphEdge UnitigsGraphEdge;

BOOST_AUTO_TEST_SUITE(TestFilterGraph)

BOOST_AUTO_TEST_CASE(filterTest_empty_graph)
{
    UnitigsGraph unitigsOriginalGraph;
    vector<bool> isConnected;
    UnitigsGraph unitigsFilteredSubgraph;
    FilterGraph<UnitigsGraph> filterGraph(unitigsOriginalGraph);
    vector<UnitigsGraphVertex> connectedVerticesId = filterGraph(unitigsFilteredSubgraph, isConnected);
    BOOST_CHECK_EQUAL(num_vertices(unitigsOriginalGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsOriginalGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsFilteredSubgraph), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsFilteredSubgraph), 0);
    BOOST_CHECK_EQUAL(connectedVerticesId.size(), 0);
}

BOOST_AUTO_TEST_CASE(filterTest_another_size_of_isConnected_vector_and_num_of_vertices_in_original_graph)
{
    UnitigsGraph unitigsOriginalGraph;
    vector<bool> isConnected(3, false);
    UnitigsGraph unitigsFilteredSubgraph;
    FilterGraph<UnitigsGraph> filterGraph(unitigsOriginalGraph);
    vector<UnitigsGraphVertex> connectedVerticesId = filterGraph(unitigsFilteredSubgraph, isConnected);
    BOOST_CHECK_EQUAL(num_vertices(unitigsOriginalGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsOriginalGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsFilteredSubgraph), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsFilteredSubgraph), 0);
    BOOST_CHECK_EQUAL(connectedVerticesId.size(), 0);
}

BOOST_AUTO_TEST_CASE(filterTest_all_values_of_isConnected_set_to_false)
{
    UnitigsGraph unitigsOriginalGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsOriginalGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsOriginalGraph);
    UnitigsGraphVertex v2 = add_vertex(unitigsOriginalGraph);
    unitigsOriginalGraph[v0].sequenceSize_ = 15U;
    unitigsOriginalGraph[v1].sequenceSize_ = 5U;
    unitigsOriginalGraph[v2].sequenceSize_ = 15U;
    unitigsOriginalGraph[v0].isOriginal_ = false;
    unitigsOriginalGraph[v1].isOriginal_ = false;
    unitigsOriginalGraph[v2].isOriginal_ = false;
    UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsOriginalGraph).first;
    UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsOriginalGraph).first;
    UnitigsGraphEdge e2 = add_edge(v0, v2, unitigsOriginalGraph).first;
    unitigsOriginalGraph[e0].isForConnectedSequences_ = true;
    unitigsOriginalGraph[e1].isForConnectedSequences_ = true;
    unitigsOriginalGraph[e2].isForConnectedSequences_ = false;
    unitigsOriginalGraph[e0].isForPairedReads_ = true;
    unitigsOriginalGraph[e1].isForPairedReads_ = true;
    unitigsOriginalGraph[e2].isForPairedReads_ = true;
    vector<bool> isConnected(num_vertices(unitigsOriginalGraph), false);
    UnitigsGraph unitigsFilteredSubgraph;
    FilterGraph<UnitigsGraph> filterGraph(unitigsOriginalGraph);
    vector<UnitigsGraphVertex> connectedVerticesId = filterGraph(unitigsFilteredSubgraph, isConnected);
    BOOST_CHECK_EQUAL(num_vertices(unitigsOriginalGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsOriginalGraph), 3);
    BOOST_CHECK_EQUAL(num_vertices(unitigsFilteredSubgraph), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsFilteredSubgraph), 0);
    BOOST_CHECK_EQUAL(connectedVerticesId.size(), 0);
}

BOOST_AUTO_TEST_CASE(filterTest_all_values_of_isConnected_set_to_true)
{
    UnitigsGraph unitigsOriginalGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsOriginalGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsOriginalGraph);
    UnitigsGraphVertex v2 = add_vertex(unitigsOriginalGraph);
    unitigsOriginalGraph[v0].sequenceSize_ = 15U;
    unitigsOriginalGraph[v1].sequenceSize_ = 5U;
    unitigsOriginalGraph[v2].sequenceSize_ = 15U;
    unitigsOriginalGraph[v0].isOriginal_ = false;
    unitigsOriginalGraph[v1].isOriginal_ = false;
    unitigsOriginalGraph[v2].isOriginal_ = false;
    UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsOriginalGraph).first;
    UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsOriginalGraph).first;
    UnitigsGraphEdge e2 = add_edge(v0, v2, unitigsOriginalGraph).first;
    unitigsOriginalGraph[e0].isForConnectedSequences_ = true;
    unitigsOriginalGraph[e1].isForConnectedSequences_ = true;
    unitigsOriginalGraph[e2].isForConnectedSequences_ = false;
    unitigsOriginalGraph[e0].isForPairedReads_ = true;
    unitigsOriginalGraph[e1].isForPairedReads_ = true;
    unitigsOriginalGraph[e2].isForPairedReads_ = true;
    vector<bool> isConnected(num_vertices(unitigsOriginalGraph), true);
    UnitigsGraph unitigsFilteredSubgraph;
    FilterGraph<UnitigsGraph> filterGraph(unitigsOriginalGraph);
    vector<UnitigsGraphVertex> connectedVerticesId = filterGraph(unitigsFilteredSubgraph, isConnected);
    BOOST_CHECK_EQUAL(num_vertices(unitigsOriginalGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsOriginalGraph), 3);
    BOOST_CHECK_EQUAL(num_vertices(unitigsFilteredSubgraph), 3);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[0].isOriginal_, unitigsOriginalGraph[v0].isOriginal_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[1].isOriginal_, unitigsOriginalGraph[v1].isOriginal_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[2].isOriginal_, unitigsOriginalGraph[v2].isOriginal_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[0].sequenceSize_, unitigsOriginalGraph[v0].sequenceSize_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[1].sequenceSize_, unitigsOriginalGraph[v1].sequenceSize_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[2].sequenceSize_, unitigsOriginalGraph[v2].sequenceSize_);
    BOOST_CHECK_EQUAL(num_edges(unitigsFilteredSubgraph), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsFilteredSubgraph).second, true);
    BOOST_CHECK_EQUAL(edge(1, 2, unitigsFilteredSubgraph).second, true);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[edge(0, 1, unitigsFilteredSubgraph).first].isForConnectedSequences_, unitigsOriginalGraph[e0].isForConnectedSequences_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[edge(1, 2, unitigsFilteredSubgraph).first].isForConnectedSequences_, unitigsOriginalGraph[e1].isForConnectedSequences_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[edge(0, 1, unitigsFilteredSubgraph).first].isForPairedReads_, unitigsOriginalGraph[e0].isForPairedReads_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[edge(1, 2, unitigsFilteredSubgraph).first].isForPairedReads_, unitigsOriginalGraph[e1].isForPairedReads_);
    BOOST_CHECK_EQUAL(connectedVerticesId.size(), 3);
    BOOST_CHECK_EQUAL(connectedVerticesId[0], v0);
    BOOST_CHECK_EQUAL(connectedVerticesId[1], v1);
    BOOST_CHECK_EQUAL(connectedVerticesId[2], v2);
}

BOOST_AUTO_TEST_CASE(filterTest_some_values_of_isConnected_set_to_true_v0_set_to_false)
{
    UnitigsGraph unitigsOriginalGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsOriginalGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsOriginalGraph);
    UnitigsGraphVertex v2 = add_vertex(unitigsOriginalGraph);
    unitigsOriginalGraph[v0].sequenceSize_ = 15U;
    unitigsOriginalGraph[v1].sequenceSize_ = 5U;
    unitigsOriginalGraph[v2].sequenceSize_ = 15U;
    unitigsOriginalGraph[v0].isOriginal_ = false;
    unitigsOriginalGraph[v1].isOriginal_ = false;
    unitigsOriginalGraph[v2].isOriginal_ = false;
    UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsOriginalGraph).first;
    UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsOriginalGraph).first;
    UnitigsGraphEdge e2 = add_edge(v0, v2, unitigsOriginalGraph).first;
    unitigsOriginalGraph[e0].isForConnectedSequences_ = true;
    unitigsOriginalGraph[e1].isForConnectedSequences_ = true;
    unitigsOriginalGraph[e2].isForConnectedSequences_ = false;
    unitigsOriginalGraph[e0].isForPairedReads_ = true;
    unitigsOriginalGraph[e1].isForPairedReads_ = true;
    unitigsOriginalGraph[e2].isForPairedReads_ = true;
    vector<bool> isConnected(num_vertices(unitigsOriginalGraph), true);
    isConnected[v0] = false;
    UnitigsGraph unitigsFilteredSubgraph;
    FilterGraph<UnitigsGraph> filterGraph(unitigsOriginalGraph);
    vector<UnitigsGraphVertex> connectedVerticesId = filterGraph(unitigsFilteredSubgraph, isConnected);
    BOOST_CHECK_EQUAL(num_vertices(unitigsOriginalGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsOriginalGraph), 3);
    BOOST_CHECK_EQUAL(num_vertices(unitigsFilteredSubgraph), 2);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[0].isOriginal_, unitigsOriginalGraph[v1].isOriginal_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[1].isOriginal_, unitigsOriginalGraph[v2].isOriginal_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[0].sequenceSize_, unitigsOriginalGraph[v1].sequenceSize_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[1].sequenceSize_, unitigsOriginalGraph[v2].sequenceSize_);
    BOOST_CHECK_EQUAL(num_edges(unitigsFilteredSubgraph), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsFilteredSubgraph).second, true);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[edge(0, 1, unitigsFilteredSubgraph).first].isForConnectedSequences_, unitigsOriginalGraph[e0].isForConnectedSequences_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[edge(0, 1, unitigsFilteredSubgraph).first].isForPairedReads_, unitigsOriginalGraph[e0].isForPairedReads_);
    BOOST_CHECK_EQUAL(connectedVerticesId.size(), 2);
    BOOST_CHECK_EQUAL(connectedVerticesId[0], v1);
    BOOST_CHECK_EQUAL(connectedVerticesId[1], v2);
}

BOOST_AUTO_TEST_CASE(filterTest_some_values_of_isConnected_set_to_true_v1_set_to_false)
{
    UnitigsGraph unitigsOriginalGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsOriginalGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsOriginalGraph);
    UnitigsGraphVertex v2 = add_vertex(unitigsOriginalGraph);
    unitigsOriginalGraph[v0].sequenceSize_ = 15U;
    unitigsOriginalGraph[v1].sequenceSize_ = 5U;
    unitigsOriginalGraph[v2].sequenceSize_ = 15U;
    unitigsOriginalGraph[v0].isOriginal_ = false;
    unitigsOriginalGraph[v1].isOriginal_ = false;
    unitigsOriginalGraph[v2].isOriginal_ = false;
    UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsOriginalGraph).first;
    UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsOriginalGraph).first;
    UnitigsGraphEdge e2 = add_edge(v0, v2, unitigsOriginalGraph).first;
    unitigsOriginalGraph[e0].isForConnectedSequences_ = true;
    unitigsOriginalGraph[e1].isForConnectedSequences_ = true;
    unitigsOriginalGraph[e2].isForConnectedSequences_ = false;
    unitigsOriginalGraph[e0].isForPairedReads_ = true;
    unitigsOriginalGraph[e1].isForPairedReads_ = true;
    unitigsOriginalGraph[e2].isForPairedReads_ = true;
    vector<bool> isConnected(num_vertices(unitigsOriginalGraph), true);
    isConnected[v1] = false;
    UnitigsGraph unitigsFilteredSubgraph;
    FilterGraph<UnitigsGraph> filterGraph(unitigsOriginalGraph);
    vector<UnitigsGraphVertex> connectedVerticesId = filterGraph(unitigsFilteredSubgraph, isConnected);
    BOOST_CHECK_EQUAL(num_vertices(unitigsOriginalGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsOriginalGraph), 3);
    BOOST_CHECK_EQUAL(num_vertices(unitigsFilteredSubgraph), 2);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[0].isOriginal_, unitigsOriginalGraph[v0].isOriginal_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[1].isOriginal_, unitigsOriginalGraph[v2].isOriginal_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[0].sequenceSize_, unitigsOriginalGraph[v0].sequenceSize_);
    BOOST_CHECK_EQUAL(unitigsFilteredSubgraph[1].sequenceSize_, unitigsOriginalGraph[v2].sequenceSize_);
    BOOST_CHECK_EQUAL(num_edges(unitigsFilteredSubgraph), 0);
    BOOST_CHECK_EQUAL(connectedVerticesId.size(), 2);
    BOOST_CHECK_EQUAL(connectedVerticesId[0], v0);
    BOOST_CHECK_EQUAL(connectedVerticesId[1], v2);
}

BOOST_AUTO_TEST_SUITE_END()
