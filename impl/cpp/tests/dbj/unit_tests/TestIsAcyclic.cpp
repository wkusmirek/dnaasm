/**
 * \file TestIsAcyclic.cpp
 * \brief the C++ file with implementation of tests for isAcyclic.hpp file
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/globals.hpp"
#include "../../../src/dbj/isAcyclic.hpp"

using namespace dnaasm::dbj;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

BOOST_AUTO_TEST_SUITE(TestIsAcyclic)

BOOST_AUTO_TEST_CASE(isAcyclic_empty_graph)
{
    DeBruijnGraph deBruijnGraph;
    BOOST_CHECK_EQUAL(isAcyclic(deBruijnGraph), true);
}

BOOST_AUTO_TEST_CASE(isAcyclic_single_vertex)
{
    std::vector<DeBruijnGraphVertex> sources = {};
    std::vector<DeBruijnGraphVertex> targets = {};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 1);
    BOOST_CHECK_EQUAL(isAcyclic(deBruijnGraph), true);
}

BOOST_AUTO_TEST_CASE(isAcyclic_acyclic_larger_graph)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    std::vector<DeBruijnGraphVertex> sources = {v0, v2, v2, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v3, v4, v4};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 5);
    BOOST_CHECK_EQUAL(isAcyclic(deBruijnGraph), true);
}

BOOST_AUTO_TEST_CASE(isAcyclic_self_loop)
{
    DeBruijnGraphVertex v0 = 0;
    std::vector<DeBruijnGraphVertex> sources = {v0};
    std::vector<DeBruijnGraphVertex> targets = {v0};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 1);
    BOOST_CHECK_EQUAL(isAcyclic(deBruijnGraph), false);
}

BOOST_AUTO_TEST_CASE(isAcyclic_cyclic_larger_graph)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v2, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v1, v1};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 5);
    BOOST_CHECK_EQUAL(isAcyclic(deBruijnGraph), false);
}

BOOST_AUTO_TEST_SUITE_END()
