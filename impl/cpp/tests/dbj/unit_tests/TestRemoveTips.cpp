/**
 * \file TestRemoveTips.cpp
 * \brief the C++ file with implementation of tests for RemoveTips class
 *
 */

#include <boost/test/unit_test.hpp>

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
#pragma warning(disable:4068)
#pragma warning(disable:4389)
#endif

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#include "../../../src/dbj/RemoveTips.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

using namespace dnaasm::dbj;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

BOOST_AUTO_TEST_SUITE(TestRemoveTips)

BOOST_AUTO_TEST_CASE(removeTipsTest_empty_graph)
{
    DeBruijnGraph deBruijnGraph;
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 4);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_1_short_path)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    std::vector<DeBruijnGraphVertex> sources = {v0};
    std::vector<DeBruijnGraphVertex> targets = {v1};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 2);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 2);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 1U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 2);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 1);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 0U);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_1_tip_error)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v6};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 7);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 1);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 1U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v3, deBruijnGraph).first].counter_, 0U);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_without_errors)
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
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v6, v7, v8};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v3, v6, v7};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 9);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 1);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 9);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 8);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v8, v7, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v6, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v8, v7, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v6, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v3, deBruijnGraph).first].counter_, 1U);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_loop)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v2, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 2);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 3U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v5, deBruijnGraph).first].counter_, 0U);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_2_tip_start_errors)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v6, v7};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v3, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 8);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 1);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 2U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 8);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 7);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v3, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v3, deBruijnGraph).first].counter_, 0U);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_2_tip_start_errors_1_longer_path)
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
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v6, v7, v8, v9, v10};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v3, v3, v3, v8, v9};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 11);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 1);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 2U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 11);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 10);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v8, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v9, v8, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v10, v9, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v3, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v3, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v8, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v9, v8, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v10, v9, deBruijnGraph).first].counter_, 1U);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_2_tip_start_errors_on_the_same_path)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v2, v1, v3, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v1, v3, v4, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 2);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 2U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v1, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_2_tip_end_errors_on_the_same_path)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 2);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 2U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v5, deBruijnGraph).first].counter_, 0U);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_2_tip_end_errors_1_longer_path)
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
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v3, v3, v3, v8, v9};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 11);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 1);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 2U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 11);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 10);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v6, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v7, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v8, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v8, v9, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v9, v10, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v6, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v7, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v8, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v8, v9, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v9, v10, deBruijnGraph).first].counter_, 1U);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_2_tip_end_errors)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v3, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 8);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 1);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 2U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 8);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 7);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v6, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v7, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v6, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v7, deBruijnGraph).first].counter_, 0U);
}

BOOST_AUTO_TEST_CASE(removeTipsTest_long_path_without_errors)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    boost::graph_traits<DeBruijnGraph>::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(deBruijnGraph); ei != ei_end; ++ei) {
        deBruijnGraph[*ei].counter_ = 1U;
    }
    RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, 2);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
}


/************************* remove tips from unitigs graph - remove only 1-length tips built from short unitigs *****************************/


BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_empty_graph)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_short_path_unitigs_shorter_than_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 0U;
    unitigsGraph[v1].sequenceSize_ = 0U;
    add_edge(v0, v1, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 1);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_short_path_unitigs_longer_than_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 3U;
    unitigsGraph[v1].sequenceSize_ = 3U;
    add_edge(v0, v1, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 1);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_short_path_unitigs_length_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    add_edge(v0, v1, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 1);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_in_tip_length_not_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 3U;
    unitigsGraph[v1].sequenceSize_ = 3U;
    unitigsGraph[v2].sequenceSize_ = 3U;
    unitigsGraph[v3].sequenceSize_ = 3U;
    unitigsGraph[v4].sequenceSize_ = 3U;
    unitigsGraph[v5].sequenceSize_ = 3U;
    unitigsGraph[v6].sequenceSize_ = 3U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v6, v3, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v3, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_in_tip_length_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    unitigsGraph[v4].sequenceSize_ = 2U;
    unitigsGraph[v5].sequenceSize_ = 2U;
    unitigsGraph[v6].sequenceSize_ = 2U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v6, v3, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 1U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 5);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_out_tip_length_not_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 3U;
    unitigsGraph[v1].sequenceSize_ = 3U;
    unitigsGraph[v2].sequenceSize_ = 3U;
    unitigsGraph[v3].sequenceSize_ = 3U;
    unitigsGraph[v4].sequenceSize_ = 3U;
    unitigsGraph[v5].sequenceSize_ = 3U;
    unitigsGraph[v6].sequenceSize_ = 3U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v3, v6, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v6, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_out_tip_length_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    unitigsGraph[v4].sequenceSize_ = 2U;
    unitigsGraph[v5].sequenceSize_ = 2U;
    unitigsGraph[v6].sequenceSize_ = 2U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v3, v6, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 1U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 5);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_start_in_tip_length_not_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 3U;
    unitigsGraph[v1].sequenceSize_ = 3U;
    unitigsGraph[v2].sequenceSize_ = 3U;
    unitigsGraph[v3].sequenceSize_ = 3U;
    unitigsGraph[v4].sequenceSize_ = 3U;
    unitigsGraph[v5].sequenceSize_ = 3U;
    unitigsGraph[v6].sequenceSize_ = 3U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v6, v1, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v1, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_start_in_tip_length_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    unitigsGraph[v4].sequenceSize_ = 2U;
    unitigsGraph[v5].sequenceSize_ = 2U;
    unitigsGraph[v6].sequenceSize_ = 2U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v6, v1, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 2U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_start_in_tip_length_equal_and_not_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 3U;
    unitigsGraph[v1].sequenceSize_ = 3U;
    unitigsGraph[v2].sequenceSize_ = 3U;
    unitigsGraph[v3].sequenceSize_ = 3U;
    unitigsGraph[v4].sequenceSize_ = 3U;
    unitigsGraph[v5].sequenceSize_ = 3U;
    unitigsGraph[v6].sequenceSize_ = 2U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v6, v1, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 1U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 5);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_end_out_tip_length_not_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 3U;
    unitigsGraph[v1].sequenceSize_ = 3U;
    unitigsGraph[v2].sequenceSize_ = 3U;
    unitigsGraph[v3].sequenceSize_ = 3U;
    unitigsGraph[v4].sequenceSize_ = 3U;
    unitigsGraph[v5].sequenceSize_ = 3U;
    unitigsGraph[v6].sequenceSize_ = 3U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v4, v6, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v6, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_end_out_tip_length_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    unitigsGraph[v4].sequenceSize_ = 2U;
    unitigsGraph[v5].sequenceSize_ = 2U;
    unitigsGraph[v6].sequenceSize_ = 2U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v4, v6, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 2U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_end_out_tip_length_equal_and_not_equal_to_2)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 3U;
    unitigsGraph[v1].sequenceSize_ = 3U;
    unitigsGraph[v2].sequenceSize_ = 3U;
    unitigsGraph[v3].sequenceSize_ = 3U;
    unitigsGraph[v4].sequenceSize_ = 3U;
    unitigsGraph[v5].sequenceSize_ = 3U;
    unitigsGraph[v6].sequenceSize_ = 2U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v4, v6, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 1U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 5);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_long_out_tip_length_equal_to_2)
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
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    unitigsGraph[v4].sequenceSize_ = 2U;
    unitigsGraph[v5].sequenceSize_ = 2U;
    unitigsGraph[v6].sequenceSize_ = 2U;
    unitigsGraph[v7].sequenceSize_ = 2U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v2, v6, unitigsGraph);
    add_edge(v6, v7, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 8);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v6, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v7, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_1_long_in_tip_length_equal_to_2)
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
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    unitigsGraph[v4].sequenceSize_ = 2U;
    unitigsGraph[v5].sequenceSize_ = 2U;
    unitigsGraph[v6].sequenceSize_ = 2U;
    unitigsGraph[v7].sequenceSize_ = 2U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v6, v2, unitigsGraph);
    add_edge(v7, v6, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 8);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v6, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_CASE(removeTipsUnitigsGraphTest_NOT_remove_single_bubble)
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
    UnitigsToContigsExtension::UnitigsGraphVertex v9 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v10 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v11 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v12 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v13 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v14 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v15 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    unitigsGraph[v4].sequenceSize_ = 2U;
    unitigsGraph[v5].sequenceSize_ = 2U;
    unitigsGraph[v6].sequenceSize_ = 2U;
    unitigsGraph[v7].sequenceSize_ = 2U;
    unitigsGraph[v8].sequenceSize_ = 2U;
    unitigsGraph[v9].sequenceSize_ = 2U;
    unitigsGraph[v10].sequenceSize_ = 2U;
    unitigsGraph[v11].sequenceSize_ = 2U;
    unitigsGraph[v12].sequenceSize_ = 2U;
    unitigsGraph[v13].sequenceSize_ = 2U;
    unitigsGraph[v14].sequenceSize_ = 2U;
    unitigsGraph[v15].sequenceSize_ = 2U;
    add_edge(v0, v1, unitigsGraph);
    add_edge(v1, v2, unitigsGraph);
    add_edge(v2, v3, unitigsGraph);
    add_edge(v3, v4, unitigsGraph);
    add_edge(v4, v5, unitigsGraph);
    add_edge(v5, v6, unitigsGraph);
    add_edge(v6, v7, unitigsGraph);
    add_edge(v7, v8, unitigsGraph);
    add_edge(v8, v9, unitigsGraph);
    add_edge(v9, v10, unitigsGraph);
    add_edge(v10, v11, unitigsGraph);
    add_edge(v11, v12, unitigsGraph);
    add_edge(v12, v13, unitigsGraph);
    add_edge(v5, v14, unitigsGraph);
    add_edge(v14, v15, unitigsGraph);
    add_edge(v15, v8, unitigsGraph);
    RemoveTips<UnitigsToContigsExtension::UnitigsGraph> removeTips(unitigsGraph);
    unsigned int numOfRemovedTips = removeTips();
    BOOST_CHECK_EQUAL(numOfRemovedTips, 0U);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 16);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 16);
    BOOST_CHECK_EQUAL(edge(v0, v1, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v6, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v7, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v8, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v8, v9, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v9, v10, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v10, v11, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v11, v12, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v12, v13, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v14, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v14, v15, unitigsGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v15, v8, unitigsGraph).second, true);
}

BOOST_AUTO_TEST_SUITE_END()
