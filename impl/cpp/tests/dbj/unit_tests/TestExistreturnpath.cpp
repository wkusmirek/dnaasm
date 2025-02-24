/**
 * \file TestExistreturnpath.cpp
 * \brief the C++ file with implementation of tests for existreturnpath.hpp file
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/globals.hpp"
#include "../../../src/dbj/existreturnpath.hpp"

using namespace dnaasm::dbj;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

BOOST_AUTO_TEST_SUITE(TestExistreturnpath)

BOOST_AUTO_TEST_CASE(BackPathVisitor1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    std::vector<DeBruijnGraphVertex> sources = {};
    std::vector<DeBruijnGraphVertex> targets = {};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 2);
    bool found = false;
    BackPathVisitor<DeBruijnGraph> backPathVisitor(v0, found);
    BOOST_CHECK_EQUAL(backPathVisitor.getFound(), false);
    backPathVisitor.discover_vertex(v1, deBruijnGraph);
    BOOST_CHECK_EQUAL(backPathVisitor.getFound(), false);
    backPathVisitor.discover_vertex(v0, deBruijnGraph);
    BOOST_CHECK_EQUAL(backPathVisitor.getFound(), true);
}

BOOST_AUTO_TEST_CASE(existReturnPath1)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    std::vector<DeBruijnGraphVertex> sources = {v0, v0};
    std::vector<DeBruijnGraphVertex> targets = {v0, v1};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 2);
    DeBruijnGraph::out_edge_iterator e = out_edges(v0, deBruijnGraph).first;
    BOOST_CHECK_EQUAL(existReturnPath(deBruijnGraph, *e), true);
    BOOST_CHECK_EQUAL(existReturnPath(deBruijnGraph, *++e), false);
}

BOOST_AUTO_TEST_SUITE_END()
