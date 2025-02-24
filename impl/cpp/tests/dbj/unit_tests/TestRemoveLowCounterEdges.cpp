/**
 * \file TestRemoveLowCounterEdges.cpp
 * \brief the C++ file with implementation of tests for RemoveLowCounterEdges class
 *
 */

#include <boost/test/unit_test.hpp>

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#include "../../../src/dbj/RemoveLowCounterEdges.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

using namespace dnaasm::dbj;
using namespace std;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

BOOST_AUTO_TEST_SUITE(TestRemoveLowCounterEdges)

BOOST_AUTO_TEST_CASE(RemoveLowCounterEdges1_deBruijn_graph)
{
    DeBruijnGraph deBruijnGraph;
    RemoveLowCounterEdges<DeBruijnGraph> removeEdges(deBruijnGraph, 2);
    removeEdges();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
}

BOOST_AUTO_TEST_CASE(RemoveLowCounterEdges2_deBruijn_graph)
{
    DeBruijnGraph deBruijnGraph;
    RemoveLowCounterEdges<DeBruijnGraph> removeEdges(deBruijnGraph, 0);
    removeEdges();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
}

BOOST_AUTO_TEST_CASE(RemoveLowCounterEdges3_deBruijn_graph)
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
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6, v7};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v8};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 9);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_ = 1U;
    RemoveLowCounterEdges<DeBruijnGraph> removeEdges(deBruijnGraph, 2);
    removeEdges();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 9);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 8);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v6, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v7, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v8, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_, 0U);
}

BOOST_AUTO_TEST_CASE(RemoveLowCounterEdges1_unitigs_graph)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    RemoveLowCounterEdges<UnitigsToContigsExtension::UnitigsGraph> removeEdges(unitigsGraph, 2);
    removeEdges();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
}

BOOST_AUTO_TEST_CASE(RemoveLowCounterEdges2_unitigs_graph)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    RemoveLowCounterEdges<UnitigsToContigsExtension::UnitigsGraph> removeEdges(unitigsGraph, 0);
    removeEdges();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
}

BOOST_AUTO_TEST_CASE(RemoveLowCounterEdges3_unitigs_graph)
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
    RemoveLowCounterEdges<UnitigsToContigsExtension::UnitigsGraph> removeEdges(unitigsGraph, 2U);
    removeEdges();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 9);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, false);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v6, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v7, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v8, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v2, v3, unitigsGraph).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v4, v5, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v5, v6, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v6, v7, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v7, v8, unitigsGraph).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v2, v3, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v4, v5, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v5, v6, unitigsGraph).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v6, v7, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v7, v8, unitigsGraph).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v0, v1, unitigsGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v1, v2, unitigsGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v2, v3, unitigsGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v4, v5, unitigsGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v5, v6, unitigsGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v6, v7, unitigsGraph).first].counter_, 5U);
    BOOST_CHECK_EQUAL(unitigsGraph[edge(v7, v8, unitigsGraph).first].counter_, 1U);
}

BOOST_AUTO_TEST_SUITE_END()
