/**
 * \file TestConnectedVerticesMarker.cpp
 * \brief the C++ file with implementation of tests for ConnectedVerticesMarker class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/ConnectedVerticesMarker.hpp"
#include "../../../src/dbj/UnitigsToContigsExtension.hpp"

using namespace dnaasm::dbj;
using namespace std;

typedef UnitigsToContigsExtension::UnitigsGraph UnitigsGraph;
typedef UnitigsToContigsExtension::UnitigsGraphVertex UnitigsGraphVertex;
typedef UnitigsToContigsExtension::UnitigsGraphEdge UnitigsGraphEdge;

BOOST_AUTO_TEST_SUITE(TestConnectedVerticesMarker)

BOOST_AUTO_TEST_CASE(connectedVerticesMarker_single_vertex)
{
    UnitigsGraph unitigsGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    vector<bool> isConnected(num_vertices(unitigsGraph), false);
    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph, v0, isConnected);
    connectedVerticesMarker();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 1);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(isConnected.size(), 1);
    BOOST_CHECK_EQUAL(isConnected[0], true);
}

BOOST_AUTO_TEST_CASE(connectedVerticesMarker_two_short_connected_vertices_without_paired_edges_without_originality)
{
    UnitigsGraph unitigsGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isLongNode_ = false;
    unitigsGraph[v1].isLongNode_ = false;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e0].isForPairedReads_ = false;
    vector<bool> isConnected(num_vertices(unitigsGraph), false);
    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph, v0, isConnected);
    connectedVerticesMarker();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 1);
    BOOST_CHECK_EQUAL(isConnected.size(), 2);
    BOOST_CHECK_EQUAL(isConnected[0], true);
    BOOST_CHECK_EQUAL(isConnected[1], false);
}

BOOST_AUTO_TEST_CASE(connectedVerticesMarker_two_long_connected_vertices_without_paired_edges_without_originality)
{
    UnitigsGraph unitigsGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isLongNode_ = true;
    unitigsGraph[v1].isLongNode_ = true;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e0].isForPairedReads_ = false;
    vector<bool> isConnected(num_vertices(unitigsGraph), false);
    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph, v0, isConnected);
    connectedVerticesMarker();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 1);
    BOOST_CHECK_EQUAL(isConnected.size(), 2);
    BOOST_CHECK_EQUAL(isConnected[0], true);
    BOOST_CHECK_EQUAL(isConnected[1], false);
}

BOOST_AUTO_TEST_CASE(connectedVerticesMarker_three_long_connected_vertices_without_paired_edges_without_originality)   // 0 -> 1 -> 2
{
    UnitigsGraph unitigsGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isLongNode_ = true;
    unitigsGraph[v1].isLongNode_ = true;
    unitigsGraph[v2].isLongNode_ = true;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e0].isForPairedReads_ = false;
    unitigsGraph[e1].isForPairedReads_ = false;
    vector<bool> isConnected(num_vertices(unitigsGraph), false);
    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph, v0, isConnected);
    connectedVerticesMarker();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(isConnected.size(), 3);
    BOOST_CHECK_EQUAL(isConnected[0], true);
    BOOST_CHECK_EQUAL(isConnected[1], false);
    BOOST_CHECK_EQUAL(isConnected[2], false);
}

BOOST_AUTO_TEST_CASE(connectedVerticesMarker_three_long_connected_vertices_another_order_without_paired_edges_without_originality)   // 0 -> 2 -> 1
{
    UnitigsGraph unitigsGraph;
    UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    unitigsGraph[v1].isLongNode_ = true;
    unitigsGraph[v2].isLongNode_ = true;
    unitigsGraph[v0].isLongNode_ = true;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    UnitigsGraphEdge e0 = add_edge(v0, v2, unitigsGraph).first;
    UnitigsGraphEdge e1 = add_edge(v2, v1, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e0].isForPairedReads_ = false;
    unitigsGraph[e1].isForPairedReads_ = false;
    vector<bool> isConnected(num_vertices(unitigsGraph), false);
    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph, v0, isConnected);
    connectedVerticesMarker();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(isConnected.size(), 3);
    BOOST_CHECK_EQUAL(isConnected[0], false);
    BOOST_CHECK_EQUAL(isConnected[1], false);
    BOOST_CHECK_EQUAL(isConnected[2], true);
}

BOOST_AUTO_TEST_CASE(connectedVerticesMarker_three_long_connected_vertices_another_structure_without_paired_edges_without_originality)   // 0 -> 1 and 0 -> 2
{
    UnitigsGraph unitigsGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isLongNode_ = true;
    unitigsGraph[v1].isLongNode_ = true;
    unitigsGraph[v2].isLongNode_ = true;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsGraphEdge e1 = add_edge(v0, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e0].isForPairedReads_ = false;
    unitigsGraph[e1].isForPairedReads_ = false;
    vector<bool> isConnected(num_vertices(unitigsGraph), false);
    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph, v0, isConnected);
    connectedVerticesMarker();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(isConnected.size(), 3);
    BOOST_CHECK_EQUAL(isConnected[0], true);
    BOOST_CHECK_EQUAL(isConnected[1], false);
    BOOST_CHECK_EQUAL(isConnected[2], false);
}

BOOST_AUTO_TEST_CASE(connectedVerticesMarker_three_long_connected_vertices_another_structure_with_paired_edges_without_originality)   // 0 -> 1 and 0 -> 2
{
    UnitigsGraph unitigsGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isLongNode_ = true;
    unitigsGraph[v1].isLongNode_ = true;
    unitigsGraph[v2].isLongNode_ = true;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsGraphEdge e1 = add_edge(v0, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e0].isForPairedReads_ = false;
    unitigsGraph[e1].isForPairedReads_ = true;
    vector<bool> isConnected(num_vertices(unitigsGraph), false);
    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph, v0, isConnected);
    connectedVerticesMarker();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(isConnected.size(), 3);
    BOOST_CHECK_EQUAL(isConnected[0], true);
    BOOST_CHECK_EQUAL(isConnected[1], false);
    BOOST_CHECK_EQUAL(isConnected[2], true);
}

BOOST_AUTO_TEST_CASE(connectedVerticesMarker_larger_graph_without_originality)
{
    UnitigsGraph unitigsGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v7 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v8 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isLongNode_ = true;
    unitigsGraph[v1].isLongNode_ = false;
    unitigsGraph[v2].isLongNode_ = true;
    unitigsGraph[v3].isLongNode_ = true;
    unitigsGraph[v4].isLongNode_ = true;
    unitigsGraph[v5].isLongNode_ = false;
    unitigsGraph[v6].isLongNode_ = false;
    unitigsGraph[v7].isLongNode_ = false;
    unitigsGraph[v8].isLongNode_ = false;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v4].isOriginal_ = false;
    unitigsGraph[v5].isOriginal_ = false;
    unitigsGraph[v6].isOriginal_ = false;
    unitigsGraph[v7].isOriginal_ = false;
    unitigsGraph[v8].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v3].sequenceSize_ = 5U;
    unitigsGraph[v4].sequenceSize_ = 5U;
    unitigsGraph[v5].sequenceSize_ = 5U;
    unitigsGraph[v6].sequenceSize_ = 5U;
    unitigsGraph[v7].sequenceSize_ = 5U;
    unitigsGraph[v8].sequenceSize_ = 5U;
    UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsGraphEdge e3 = add_edge(v3, v4, unitigsGraph).first;
    UnitigsGraphEdge e4 = add_edge(v3, v5, unitigsGraph).first;
    UnitigsGraphEdge e5 = add_edge(v4, v6, unitigsGraph).first;
    UnitigsGraphEdge e6 = add_edge(v4, v7, unitigsGraph).first;
    UnitigsGraphEdge e7 = add_edge(v4, v8, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    unitigsGraph[e3].isForConnectedSequences_ = true;
    unitigsGraph[e4].isForConnectedSequences_ = true;
    unitigsGraph[e5].isForConnectedSequences_ = true;
    unitigsGraph[e6].isForConnectedSequences_ = true;
    unitigsGraph[e7].isForConnectedSequences_ = true;
    unitigsGraph[e0].isForPairedReads_ = false;
    unitigsGraph[e1].isForPairedReads_ = false;
    unitigsGraph[e2].isForPairedReads_ = false;
    unitigsGraph[e3].isForPairedReads_ = false;
    unitigsGraph[e4].isForPairedReads_ = false;
    unitigsGraph[e5].isForPairedReads_ = false;
    unitigsGraph[e6].isForPairedReads_ = false;
    unitigsGraph[e7].isForPairedReads_ = false;
    UnitigsGraphEdge f0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsGraphEdge f1 = add_edge(v0, v2, unitigsGraph).first;
    UnitigsGraphEdge f2 = add_edge(v0, v3, unitigsGraph).first;
    UnitigsGraphEdge f3 = add_edge(v0, v4, unitigsGraph).first;
    UnitigsGraphEdge f4 = add_edge(v0, v7, unitigsGraph).first;
    unitigsGraph[f0].isForConnectedSequences_ = false;
    unitigsGraph[f1].isForConnectedSequences_ = false;
    unitigsGraph[f2].isForConnectedSequences_ = false;
    unitigsGraph[f3].isForConnectedSequences_ = false;
    unitigsGraph[f4].isForConnectedSequences_ = false;
    unitigsGraph[f0].isForPairedReads_ = true;
    unitigsGraph[f1].isForPairedReads_ = true;
    unitigsGraph[f2].isForPairedReads_ = true;
    unitigsGraph[f3].isForPairedReads_ = true;
    unitigsGraph[f4].isForPairedReads_ = true;
    vector<bool> isConnected(num_vertices(unitigsGraph), false);
    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph, v0, isConnected);
    connectedVerticesMarker();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 9);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 13);
    BOOST_CHECK_EQUAL(isConnected.size(), 9);
    BOOST_CHECK_EQUAL(isConnected[0], true);
    BOOST_CHECK_EQUAL(isConnected[1], true);
    BOOST_CHECK_EQUAL(isConnected[2], true);
    BOOST_CHECK_EQUAL(isConnected[3], true);
    BOOST_CHECK_EQUAL(isConnected[4], true);
    BOOST_CHECK_EQUAL(isConnected[5], false);
    BOOST_CHECK_EQUAL(isConnected[6], false);
    BOOST_CHECK_EQUAL(isConnected[7], true);
    BOOST_CHECK_EQUAL(isConnected[8], false);
}

BOOST_AUTO_TEST_CASE(connectedVerticesMarker_larger_graph_with_originality)
{
    UnitigsGraph unitigsGraph;
    UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    UnitigsGraphVertex v7 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isLongNode_ = true;
    unitigsGraph[v1].isLongNode_ = false;
    unitigsGraph[v2].isLongNode_ = true;
    unitigsGraph[v3].isLongNode_ = false;
    unitigsGraph[v4].isLongNode_ = false;
    unitigsGraph[v5].isLongNode_ = true;
    unitigsGraph[v6].isLongNode_ = false;
    unitigsGraph[v7].isLongNode_ = false;
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v3].isOriginal_ = true;
    unitigsGraph[v4].isOriginal_ = false;
    unitigsGraph[v5].isOriginal_ = true;
    unitigsGraph[v6].isOriginal_ = true;
    unitigsGraph[v7].isOriginal_ = true;
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v3].sequenceSize_ = 5U;
    unitigsGraph[v4].sequenceSize_ = 5U;
    unitigsGraph[v5].sequenceSize_ = 5U;
    unitigsGraph[v6].sequenceSize_ = 5U;
    unitigsGraph[v7].sequenceSize_ = 5U;
    UnitigsGraphEdge e0 = add_edge(v0, v2, unitigsGraph).first;
    UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsGraphEdge e3 = add_edge(v3, v4, unitigsGraph).first;
    UnitigsGraphEdge e4 = add_edge(v4, v5, unitigsGraph).first;
    UnitigsGraphEdge e5 = add_edge(v5, v6, unitigsGraph).first;
    UnitigsGraphEdge e6 = add_edge(v4, v7, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    unitigsGraph[e3].isForConnectedSequences_ = true;
    unitigsGraph[e4].isForConnectedSequences_ = true;
    unitigsGraph[e5].isForConnectedSequences_ = true;
    unitigsGraph[e6].isForConnectedSequences_ = true;
    unitigsGraph[e0].isForPairedReads_ = false;
    unitigsGraph[e1].isForPairedReads_ = false;
    unitigsGraph[e2].isForPairedReads_ = false;
    unitigsGraph[e3].isForPairedReads_ = false;
    unitigsGraph[e4].isForPairedReads_ = false;
    unitigsGraph[e5].isForPairedReads_ = false;
    unitigsGraph[e6].isForPairedReads_ = false;
    UnitigsGraphEdge f0 = add_edge(v0, v2, unitigsGraph).first;
    UnitigsGraphEdge f1 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsGraphEdge f2 = add_edge(v2, v4, unitigsGraph).first;
    UnitigsGraphEdge f3 = add_edge(v3, v5, unitigsGraph).first;
    UnitigsGraphEdge f4 = add_edge(v5, v6, unitigsGraph).first;
    UnitigsGraphEdge f5 = add_edge(v4, v7, unitigsGraph).first;
    unitigsGraph[f0].isForConnectedSequences_ = false;
    unitigsGraph[f1].isForConnectedSequences_ = false;
    unitigsGraph[f2].isForConnectedSequences_ = false;
    unitigsGraph[f3].isForConnectedSequences_ = false;
    unitigsGraph[f4].isForConnectedSequences_ = false;
    unitigsGraph[f5].isForConnectedSequences_ = false;
    unitigsGraph[f0].isForPairedReads_ = true;
    unitigsGraph[f1].isForPairedReads_ = true;
    unitigsGraph[f2].isForPairedReads_ = true;
    unitigsGraph[f3].isForPairedReads_ = true;
    unitigsGraph[f4].isForPairedReads_ = true;
    unitigsGraph[f5].isForPairedReads_ = true;
    vector<bool> isConnected(num_vertices(unitigsGraph), false);
    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph, v2, isConnected);
    connectedVerticesMarker();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 8);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 13);
    BOOST_CHECK_EQUAL(isConnected.size(), 8);
    BOOST_CHECK_EQUAL(isConnected[0], false);
    BOOST_CHECK_EQUAL(isConnected[1], false);
    BOOST_CHECK_EQUAL(isConnected[2], true);
    BOOST_CHECK_EQUAL(isConnected[3], true);
    BOOST_CHECK_EQUAL(isConnected[4], true);
    BOOST_CHECK_EQUAL(isConnected[5], true);
    BOOST_CHECK_EQUAL(isConnected[6], false);
    BOOST_CHECK_EQUAL(isConnected[7], false);
}

BOOST_AUTO_TEST_SUITE_END()

