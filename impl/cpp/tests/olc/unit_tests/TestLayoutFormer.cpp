/**
 * \file TestLayoutFormer.cpp
 * \brief the C++ file with implementation of tests for MinHash structure
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/olc/common.hpp"
#include "../../../src/olc/OverlapGraph.hpp"
#include "../../../src/olc/OvlpGraphBuilder.hpp"
#include "../../../src/olc/LayoutFormer.hpp"

using namespace dnaasm::olc;

BOOST_AUTO_TEST_SUITE(TestLayoutFormer)

BOOST_AUTO_TEST_CASE(removeCycle01)
{
    OverlapGraph ovlpGraph;
    auto v1 = boost::add_vertex(ovlpGraph);
    auto v2 = boost::add_vertex(ovlpGraph);
    auto v3 = boost::add_vertex(ovlpGraph);
    auto v4 = boost::add_vertex(ovlpGraph);
    boost::add_edge(v1, v2, ovlpGraph);
    boost::add_edge(v2, v3, ovlpGraph);
    boost::add_edge(v3, v4, ovlpGraph);
    boost::add_edge(v4, v1, ovlpGraph);

    LayoutFormer layoutFormer(ovlpGraph);
    layoutFormer.removeCycles();

    BOOST_CHECK_EQUAL(boost::num_edges(ovlpGraph), 3);
    BOOST_CHECK_EQUAL(boost::edge(v1, v2, ovlpGraph).second, true);
    BOOST_CHECK_EQUAL(boost::edge(v2, v3, ovlpGraph).second, true);
    BOOST_CHECK_EQUAL(boost::edge(v3, v4, ovlpGraph).second, true);
    BOOST_CHECK_EQUAL(boost::edge(v4, v1, ovlpGraph).second, false);
}

BOOST_AUTO_TEST_CASE(removeCycle02)
{
    OverlapGraph ovlpGraph;
    auto v1 = boost::add_vertex(ovlpGraph);
    auto v2 = boost::add_vertex(ovlpGraph);
    auto v3 = boost::add_vertex(ovlpGraph);
    auto v4 = boost::add_vertex(ovlpGraph);
    auto v5 = boost::add_vertex(ovlpGraph);
    auto v6 = boost::add_vertex(ovlpGraph);
    auto v7 = boost::add_vertex(ovlpGraph);
    auto v8 = boost::add_vertex(ovlpGraph);

    //first cycle
    boost::add_edge(v1, v2, ovlpGraph);
    boost::add_edge(v2, v3, ovlpGraph);
    boost::add_edge(v3, v4, ovlpGraph);
    boost::add_edge(v4, v5, ovlpGraph);
    boost::add_edge(v5, v1, ovlpGraph);
    //second cycle
    boost::add_edge(v2, v6, ovlpGraph);
    boost::add_edge(v6, v7, ovlpGraph);
    boost::add_edge(v7, v8, ovlpGraph);
    boost::add_edge(v8, v1, ovlpGraph);

    LayoutFormer layoutFormer(ovlpGraph);
    layoutFormer.removeCycles();

    BOOST_CHECK_EQUAL(boost::edge(v1, v2, ovlpGraph).second, true);
    BOOST_CHECK_EQUAL(boost::edge(v2, v3, ovlpGraph).second, true);
    BOOST_CHECK_EQUAL(boost::edge(v3, v4, ovlpGraph).second, true);
    BOOST_CHECK_EQUAL(boost::edge(v4, v5, ovlpGraph).second, true);
    BOOST_CHECK_EQUAL(boost::edge(v5, v1, ovlpGraph).second, false);

    BOOST_CHECK_EQUAL(boost::edge(v2, v6, ovlpGraph).second, true);
    BOOST_CHECK_EQUAL(boost::edge(v6, v7, ovlpGraph).second, true);
    BOOST_CHECK_EQUAL(boost::edge(v7, v8, ovlpGraph).second, true);
    BOOST_CHECK_EQUAL(boost::edge(v8, v1, ovlpGraph).second, false);
}

BOOST_AUTO_TEST_SUITE_END()
