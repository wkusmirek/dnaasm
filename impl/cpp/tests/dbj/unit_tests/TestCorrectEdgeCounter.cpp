/**
 * \file TestCorrectEdgeCounter.cpp
 * \brief the C++ file with implementation of tests for TestCorrectEdgeCounter class
 *
 */


#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/globals.hpp"

#include "../../../src/dbj/CorrectEdgeCounter.hpp"

using namespace dnaasm::dbj;
using namespace std;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

BOOST_AUTO_TEST_SUITE(TestCorrectEdgeCounter)

BOOST_AUTO_TEST_CASE(CorrectEdgeCounter_emptyGraph)
{
    DeBruijnGraph deBruijnGraph;
    CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounter(deBruijnGraph);
    correctEdgeCounter();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
}

BOOST_AUTO_TEST_CASE(CorrectEdgeCounter_sigleLinearStructure)
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
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_ = 1U;
    CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounter(deBruijnGraph);
    correctEdgeCounter();
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
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_, 3U);
}

BOOST_AUTO_TEST_CASE(CorrectEdgeCounter_structureContainsThreeLinearSeq)
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
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v4, v7};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v8};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 9);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v4, v7, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_ = 1U;
    CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounter(deBruijnGraph);
    correctEdgeCounter();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 9);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 8);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v6, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v7, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v8, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v7, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_, 3U);
}

BOOST_AUTO_TEST_CASE(CorrectEdgeCounter_structureWithSelfLoop)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v2};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v2, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 4);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 5U;
    deBruijnGraph[edge(v2, v2, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 3U;
    CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounter(deBruijnGraph);
    correctEdgeCounter();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 5U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 5U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 3U);
}

BOOST_AUTO_TEST_CASE(CorrectEdgeCounter_loopAndLinearSeq)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v1, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 5U;
    deBruijnGraph[edge(v4, v1, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v5, v3, deBruijnGraph).first].counter_ = 1U;
    CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounter(deBruijnGraph);
    correctEdgeCounter();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v1, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v5, v3, deBruijnGraph).first].counter_, 1U);
}

BOOST_AUTO_TEST_CASE(CorrectEdgeCounter_sigleLinearStructure_twoTipsWithCounterEqualToZero)
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
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6, v7, v2, v10};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 11);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v9, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v10, v5, deBruijnGraph).first].counter_ = 0U;
    CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounter(deBruijnGraph);
    correctEdgeCounter();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 11);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 10);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v6, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v7, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v8, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v9, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v10, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v9, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v10, v5, deBruijnGraph).first].counter_, 0U);
}

BOOST_AUTO_TEST_CASE(CorrectEdgeCounter_sigleLinearStructure_edgeWithCounterEqualToZeroInTheMiddleOfLinearStructure)
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
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_ = 1U;
    CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounter(deBruijnGraph);
    correctEdgeCounter();
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
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_, 2U);
}

BOOST_AUTO_TEST_CASE(CorrectEdgeCounter_sigleLinearStructure_edgesWithCounterEqualToZeroInTheEndsOfLinearStructure)
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
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 4U;
    deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_ = 0U;
    CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounter(deBruijnGraph);
    correctEdgeCounter();
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
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_, 0U);
}

BOOST_AUTO_TEST_SUITE_END()
