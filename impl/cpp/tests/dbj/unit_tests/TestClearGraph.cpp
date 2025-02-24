/**
 * \file TestClearGraph.cpp
 * \brief the C++ file with implementation of tests for ClearGraph class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/ClearGraph.hpp"
#include "../../../src/dbj/UnitigsToContigsExtension.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestClearGraph)

BOOST_AUTO_TEST_CASE(removeInEdgesForStartVertex)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v0].isLongNode_ = true;
    unitigsGraph[v1].isLongNode_ = false;
    unitigsGraph[v2].isLongNode_ = true;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v1, v0, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    unitigsGraph[e0].isForPairedReads_ = true;
    unitigsGraph[e1].isForPairedReads_ = true;
    unitigsGraph[e2].isForPairedReads_ = true;
    ClearGraph<UnitigsToContigsExtension::UnitigsGraph> clearGraph(unitigsGraph);
    clearGraph.removeInEdgesForStartVertex(v0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(unitigsGraph[v0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[v1].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[v2].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[v0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[v1].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[v2].isLongNode_, true);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].isForPairedReads_, true);
}

BOOST_AUTO_TEST_CASE(removeOutEdgesForEndVertex)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v0].isLongNode_ = true;
    unitigsGraph[v1].isLongNode_ = false;
    unitigsGraph[v2].isLongNode_ = true;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v1, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    unitigsGraph[e0].isForPairedReads_ = true;
    unitigsGraph[e1].isForPairedReads_ = true;
    unitigsGraph[e2].isForPairedReads_ = true;
    ClearGraph<UnitigsToContigsExtension::UnitigsGraph> clearGraph(unitigsGraph);
    clearGraph.removeOutEdgesForEndVertex(v0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(unitigsGraph[v0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[v1].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[v2].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[v0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[v1].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[v2].isLongNode_, true);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].isForPairedReads_, true);
}

BOOST_AUTO_TEST_SUITE_END()
