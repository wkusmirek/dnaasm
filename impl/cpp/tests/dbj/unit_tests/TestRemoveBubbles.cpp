/**
 * \file TestRemoveBubbles.cpp
 * \brief the C++ file with implementation of tests for RemoveBubbles class
 *
 */

#include <boost/test/unit_test.hpp>

//#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
//#pragma warning(disable:4068)
//#pragma warning(disable:4389)
//#endif

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#include "../../../src/dbj/RemoveBubbles.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

using namespace dnaasm::dbj;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

BOOST_AUTO_TEST_SUITE(TestRemoveBubbles)

BOOST_AUTO_TEST_CASE(removeBubblesTest_deBruijnGraph_empty_graph)
{
    DeBruijnGraph deBruijnGraph;
    unsigned short k = 4U;
    float normalizationRate = 1.0F;
    RemoveBubbles<DeBruijnGraph> removeBubbles(deBruijnGraph, k, normalizationRate);
    unsigned int numOfRemovedBubbles = removeBubbles();
    BOOST_CHECK_EQUAL(numOfRemovedBubbles, 0U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(removeBubbles.getBubbles().size(), 0);
}

BOOST_AUTO_TEST_CASE(removeBubblesTest_deBruijnGraph_1_bubble_2_branches_with_the_same_lenght_equal_to_1_bubble_size_not_greater_than_size_limit)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v1, v2, v3, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v4, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 1U;
    unsigned short k = 2U;
    float normalizationRate = 1.0F;
    RemoveBubbles<DeBruijnGraph> removeBubbles(deBruijnGraph, k, normalizationRate);
    unsigned int numOfRemovedBubbles = removeBubbles();
    BOOST_CHECK_EQUAL(numOfRemovedBubbles, 1U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 5U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_, 5U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(removeBubbles.getBubbles().size(), 2);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0]).size(), 3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0])[0], v1);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0])[1], v2);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0])[2], v4);
    BOOST_CHECK_EQUAL(get<1>(removeBubbles.getBubbles()[0]), 0U);
    BOOST_CHECK_EQUAL(get<2>(removeBubbles.getBubbles()[0]), 3U);
    BOOST_CHECK_EQUAL(get<3>(removeBubbles.getBubbles()[0]), 60.0000038F);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1]).size(), 3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1])[0], v1);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1])[1], v3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1])[2], v4);
    BOOST_CHECK_EQUAL(get<1>(removeBubbles.getBubbles()[1]), 0U);
    BOOST_CHECK_EQUAL(get<2>(removeBubbles.getBubbles()[1]), 2U);
    BOOST_CHECK_EQUAL(get<3>(removeBubbles.getBubbles()[1]), 40.00F);
}

BOOST_AUTO_TEST_CASE(removeBubblesTest_deBruijnGraph_1_bubble_2_branches_with_the_same_lenght_equal_to_1_bubble_size_greater_than_size_limit)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v1, v2, v3, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v4, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 1U;
    unsigned short k = 0U;
    float normalizationRate = 1.0F;
    RemoveBubbles<DeBruijnGraph> removeBubbles(deBruijnGraph, k, normalizationRate);
    unsigned int numOfRemovedBubbles = removeBubbles();
    BOOST_CHECK_EQUAL(numOfRemovedBubbles, 0U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(removeBubbles.getBubbles().size(), 0);
}

BOOST_AUTO_TEST_CASE(removeBubblesTest_deBruijnGraph_1_bubble_3_branches_with_the_same_lenght_equal_to_1_bubble_size_not_greater_than_size_limit)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v1, v1, v2, v3, v4, v5};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v5, v5, v6};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 7);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v1, v4, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v2, v5, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v3, v5, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 1U;
    unsigned short k = 2U;
    float normalizationRate = 1.0F;
    RemoveBubbles<DeBruijnGraph> removeBubbles(deBruijnGraph, k, normalizationRate);
    unsigned int numOfRemovedBubbles = removeBubbles();
    BOOST_CHECK_EQUAL(numOfRemovedBubbles, 1U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 8);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v6, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 5U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v4, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v5, deBruijnGraph).first].counter_, 5U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v5, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(removeBubbles.getBubbles().size(), 3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0]).size(), 3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0])[0], v1);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0])[1], v2);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0])[2], v5);
    BOOST_CHECK_EQUAL(get<1>(removeBubbles.getBubbles()[0]), 0U);
    BOOST_CHECK_EQUAL(get<2>(removeBubbles.getBubbles()[0]), 2U);
    BOOST_CHECK_EQUAL(get<3>(removeBubbles.getBubbles()[0]), 40.00F);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1]).size(), 3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1])[0], v1);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1])[1], v3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1])[2], v5);
    BOOST_CHECK_EQUAL(get<1>(removeBubbles.getBubbles()[1]), 0U);
    BOOST_CHECK_EQUAL(get<2>(removeBubbles.getBubbles()[1]), 2U);
    BOOST_CHECK_EQUAL(get<3>(removeBubbles.getBubbles()[1]), 40.00F);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[2]).size(), 3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[2])[0], v1);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[2])[1], v4);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[2])[2], v5);
    BOOST_CHECK_EQUAL(get<1>(removeBubbles.getBubbles()[2]), 0U);
    BOOST_CHECK_EQUAL(get<2>(removeBubbles.getBubbles()[2]), 1U);
    BOOST_CHECK_EQUAL(get<3>(removeBubbles.getBubbles()[2]), 20.00F);
}

BOOST_AUTO_TEST_CASE(removeBubblesTest_deBruijnGraph_2_bubbles_2_branches_in_which_bubble_all_bubbles_sizes_greater_than_size_limit_first_bubble_in_second_bubble)
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
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v3, v7, v1, v2, v5, v6, v2, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v3, v7, v8, v2, v5, v6, v7, v4, v6};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 9);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v3, v7, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v2, v5, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v4, v6, deBruijnGraph).first].counter_ = 2U;
    unsigned short k = 5U;
    float normalizationRate = 0.33F;
    RemoveBubbles<DeBruijnGraph> removeBubbles(deBruijnGraph, k, normalizationRate);
    unsigned int numOfRemovedBubbles = removeBubbles();
    BOOST_CHECK_EQUAL(numOfRemovedBubbles, 2U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 9);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 10);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v7, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v8, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v6, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v7, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v6, deBruijnGraph).second, true); 
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v7, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v5, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v6, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(removeBubbles.getBubbles().size(), 4);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0]).size(), 3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0])[0], v2);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0])[1], v5);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[0])[2], v6);
    BOOST_CHECK_EQUAL(get<1>(removeBubbles.getBubbles()[0]), 0U);
    BOOST_CHECK_EQUAL(get<2>(removeBubbles.getBubbles()[0]), 3U);
    BOOST_CHECK_EQUAL(get<3>(removeBubbles.getBubbles()[0]), 60.0000038F);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1]).size(), 3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1])[0], v2);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1])[1], v4);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[1])[2], v6);
    BOOST_CHECK_EQUAL(get<1>(removeBubbles.getBubbles()[1]), 0U);
    BOOST_CHECK_EQUAL(get<2>(removeBubbles.getBubbles()[1]), 2U);
    BOOST_CHECK_EQUAL(get<3>(removeBubbles.getBubbles()[1]), 40.00F);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[2]).size(), 3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[2])[0], v1);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[2])[1], v3);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[2])[2], v7);
    BOOST_CHECK_EQUAL(get<1>(removeBubbles.getBubbles()[2]), 1U);
    BOOST_CHECK_EQUAL(get<2>(removeBubbles.getBubbles()[2]), 1U);
    BOOST_CHECK_EQUAL(get<3>(removeBubbles.getBubbles()[2]), 25.00F);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[3]).size(), 5);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[3])[0], v1);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[3])[1], v2);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[3])[2], v5);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[3])[3], v6);
    BOOST_CHECK_EQUAL(get<0>(removeBubbles.getBubbles()[3])[4], v7);
    BOOST_CHECK_EQUAL(get<1>(removeBubbles.getBubbles()[3]), 1U);
    BOOST_CHECK_EQUAL(get<2>(removeBubbles.getBubbles()[3]), 3U);
    BOOST_CHECK_EQUAL(get<3>(removeBubbles.getBubbles()[3]), 75.00F);
}

BOOST_AUTO_TEST_CASE(removeBubblesTest_deBruijnGraph_1_bubble_2_branches_with_the_same_lenght_equal_to_1_bubble_size_not_greater_than_size_limit_counters_in_one_branch_equal_to_zero)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v1, v2, v3, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v4, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 0U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 1U;
    unsigned short k = 2U;
    float normalizationRate = 1.0F;
    RemoveBubbles<DeBruijnGraph> removeBubbles(deBruijnGraph, k, normalizationRate);
    unsigned int numOfRemovedBubbles = removeBubbles();
    BOOST_CHECK_EQUAL(numOfRemovedBubbles, 0U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(removeBubbles.getBubbles().size(), 0);
}

/**********************************************************************************************************************************************************************************/
/***************************************************************** tests of removing bubbles in repetitve regions *****************************************************************/
/**********************************************************************************************************************************************************************************/

BOOST_AUTO_TEST_CASE(removeBubblesTest_deBruijnGraph_1_bubble_2_branches_with_the_same_lenght_equal_to_1_bubble_size_not_greater_than_size_limit_bubble_in_repetitive_region_in_both_ends)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v1, v2, v3, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v4, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 2U;
    unsigned short k = 2U;
    float normalizationRate = 1.0F;
    RemoveBubbles<DeBruijnGraph> removeBubbles(deBruijnGraph, k, normalizationRate);
    unsigned int numOfRemovedBubbles = removeBubbles();
    BOOST_CHECK_EQUAL(numOfRemovedBubbles, 0U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(removeBubbles.getBubbles().size(), 0);
}

BOOST_AUTO_TEST_CASE(removeBubblesTest_deBruijnGraph_1_bubble_2_branches_with_the_same_lenght_equal_to_1_bubble_size_not_greater_than_size_limit_bubble_in_repetitive_region_in_start_of_bubble)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v1, v2, v3, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v4, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 1U;
    unsigned short k = 2U;
    float normalizationRate = 1.0F;
    RemoveBubbles<DeBruijnGraph> removeBubbles(deBruijnGraph, k, normalizationRate);
    unsigned int numOfRemovedBubbles = removeBubbles();
    BOOST_CHECK_EQUAL(numOfRemovedBubbles, 0U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(removeBubbles.getBubbles().size(), 0);
}

BOOST_AUTO_TEST_CASE(removeBubblesTest_deBruijnGraph_1_bubble_2_branches_with_the_same_lenght_equal_to_1_bubble_size_not_greater_than_size_limit_bubble_in_repetitive_region_in_end_of_bubble)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v1, v2, v3, v4};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v4, v5};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 6);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 1U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 3U;
    deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_ = 2U;
    deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_ = 2U;
    unsigned short k = 2U;
    float normalizationRate = 1.0F;
    RemoveBubbles<DeBruijnGraph> removeBubbles(deBruijnGraph, k, normalizationRate);
    unsigned int numOfRemovedBubbles = removeBubbles();
    BOOST_CHECK_EQUAL(numOfRemovedBubbles, 0U);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(removeBubbles.getBubbles().size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
