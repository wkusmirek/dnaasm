/**
 * \file TestLowCounterEdgesCoverUncover.cpp
 * \brief the C++ file with implementation of tests for LowCounterEdgesCoverUncover class
 *
 */

#include <boost/test/unit_test.hpp>

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#include "../../../src/dbj/LowCounterEdgesCoverUncover.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestLowCounterEdgesCoverUncover)

BOOST_AUTO_TEST_CASE(empty_unitigs_graph_cover)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    LowCounterEdgesCoverUncover<UnitigsToContigsExtension::UnitigsGraph> lowCounterEdgesCoverUncover(unitigsGraph);
    lowCounterEdgesCoverUncover.cover(5U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
}

BOOST_AUTO_TEST_CASE(empty_unitigs_graph_uncover)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    LowCounterEdgesCoverUncover<UnitigsToContigsExtension::UnitigsGraph> lowCounterEdgesCoverUncover(unitigsGraph);
    lowCounterEdgesCoverUncover.uncover();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
}

BOOST_AUTO_TEST_CASE(not_empty_unitigs_graph_cover)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = (add_edge(v0, v1, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = (add_edge(v1, v2, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = (add_edge(v2, v3, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = (add_edge(v3, v4, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = (add_edge(v4, v5, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = (add_edge(v5, v6, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = (add_edge(v6, v7, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = (add_edge(v7, v8, unitigsGraph)).first;
    unitigsGraph[e0].isForPairedReads_ = true;
    unitigsGraph[e1].isForPairedReads_ = true;
    unitigsGraph[e2].isForPairedReads_ = true;
    unitigsGraph[e3].isForPairedReads_ = true;
    unitigsGraph[e4].isForPairedReads_ = false;
    unitigsGraph[e5].isForPairedReads_ = false;
    unitigsGraph[e6].isForPairedReads_ = false;
    unitigsGraph[e7].isForPairedReads_ = false;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = false;
    unitigsGraph[e3].isForConnectedSequences_ = false;
    unitigsGraph[e4].isForConnectedSequences_ = true;
    unitigsGraph[e5].isForConnectedSequences_ = true;
    unitigsGraph[e6].isForConnectedSequences_ = false;
    unitigsGraph[e7].isForConnectedSequences_ = false;
    unitigsGraph[e0].counter_ = 4U;
    unitigsGraph[e1].counter_ = 1U;
    unitigsGraph[e2].counter_ = 2U;
    unitigsGraph[e3].counter_ = 1U;
    unitigsGraph[e4].counter_ = 3U;
    unitigsGraph[e5].counter_ = 0U;
    unitigsGraph[e6].counter_ = 5U;
    unitigsGraph[e7].counter_ = 1U;
    LowCounterEdgesCoverUncover<UnitigsToContigsExtension::UnitigsGraph> lowCounterEdgesCoverUncover(unitigsGraph);
    lowCounterEdgesCoverUncover.cover(2U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 9);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 8);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v6, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v7, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v8, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v2, v3, unitigsGraph).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v3, v4, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v4, v5, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v5, v6, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v6, v7, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v7, v8, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v2, v3, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v3, v4, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v4, v5, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v5, v6, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v6, v7, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v7, v8, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].counter_, std::numeric_limits<unsigned short>::max() - 1U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v2, v3, unitigsGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v3, v4, unitigsGraph).first].counter_, std::numeric_limits<unsigned short>::max() - 1U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v4, v5, unitigsGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v5, v6, unitigsGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v6, v7, unitigsGraph).first].counter_, 5U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v7, v8, unitigsGraph).first].counter_, 1U);
}

BOOST_AUTO_TEST_CASE(not_empty_unitigs_graph_uncover)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v8 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = (add_edge(v0, v1, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = (add_edge(v1, v2, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = (add_edge(v2, v3, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = (add_edge(v3, v4, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = (add_edge(v4, v5, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = (add_edge(v5, v6, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = (add_edge(v6, v7, unitigsGraph)).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = (add_edge(v7, v8, unitigsGraph)).first;
    unitigsGraph[e0].isForPairedReads_ = true;
    unitigsGraph[e1].isForPairedReads_ = false;
    unitigsGraph[e2].isForPairedReads_ = true;
    unitigsGraph[e3].isForPairedReads_ = false;
    unitigsGraph[e4].isForPairedReads_ = false;
    unitigsGraph[e5].isForPairedReads_ = false;
    unitigsGraph[e6].isForPairedReads_ = false;
    unitigsGraph[e7].isForPairedReads_ = false;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = false;
    unitigsGraph[e3].isForConnectedSequences_ = false;
    unitigsGraph[e4].isForConnectedSequences_ = true;
    unitigsGraph[e5].isForConnectedSequences_ = true;
    unitigsGraph[e6].isForConnectedSequences_ = false;
    unitigsGraph[e7].isForConnectedSequences_ = false;
    unitigsGraph[e0].counter_ = 4U;
    unitigsGraph[e1].counter_ = std::numeric_limits<unsigned short>::max() - 1U;
    unitigsGraph[e2].counter_ = 2U;
    unitigsGraph[e3].counter_ = std::numeric_limits<unsigned short>::max() - 1U;
    unitigsGraph[e4].counter_ = 3U;
    unitigsGraph[e5].counter_ = 0U;
    unitigsGraph[e6].counter_ = 5U;
    unitigsGraph[e7].counter_ = 1U;
    LowCounterEdgesCoverUncover<UnitigsToContigsExtension::UnitigsGraph> lowCounterEdgesCoverUncover(unitigsGraph);
    lowCounterEdgesCoverUncover.uncover();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 9);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 8);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v6, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v7, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v8, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v2, v3, unitigsGraph).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v3, v4, unitigsGraph).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v4, v5, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v5, v6, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v6, v7, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v7, v8, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v2, v3, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v3, v4, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v4, v5, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v5, v6, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v6, v7, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v7, v8, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v2, v3, unitigsGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v3, v4, unitigsGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v4, v5, unitigsGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v5, v6, unitigsGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v6, v7, unitigsGraph).first].counter_, 5U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v7, v8, unitigsGraph).first].counter_, 1U);
}

BOOST_AUTO_TEST_SUITE_END()
