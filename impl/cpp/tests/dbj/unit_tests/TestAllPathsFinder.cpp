/**
 * \file TestAllPathsFinder.cpp
 * \brief the C++ file with implementation of tests for AllPathsFinder class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/AllPathsFinder.hpp"
#include "../../../src/dbj/UnitigsToContigsExtension.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestAllPathsFinder)

BOOST_AUTO_TEST_CASE(findTest_the_same_start_and_end_vertex_limit_equal_to_0)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v1, v1, 0U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(paths.size(), 1);
    BOOST_CHECK_EQUAL(paths[0].size(), 1);
    BOOST_CHECK_EQUAL(paths[0][0], v1);
}

BOOST_AUTO_TEST_CASE(findTest_1_linear_path_below_limit_threshold)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 15U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 15U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v0, v2, 7U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(paths.size(), 1);
    BOOST_CHECK_EQUAL(paths[0].size(), 3);
    BOOST_CHECK_EQUAL(paths[0][0], v0);
    BOOST_CHECK_EQUAL(paths[0][1], v1);
    BOOST_CHECK_EQUAL(paths[0][2], v2);
}

BOOST_AUTO_TEST_CASE(findTest_1_linear_path_above_limit_threshold)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 15U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v0, v2, 10U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(paths.size(), 0);
}

BOOST_AUTO_TEST_CASE(findTest_no_linear_path_from_v1_to_v0)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 15U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 15U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v1, v0, 7U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(paths.size(), 0);
}

BOOST_AUTO_TEST_CASE(findTest_1_linear_path_with_end_tip_at_the_beginning_of_path_large_limit_threshold)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v3].sequenceSize_ = 5U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v0, v3, 100U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(paths.size(), 1);
    BOOST_CHECK_EQUAL(paths[0].size(), 3);
    BOOST_CHECK_EQUAL(paths[0][0], v0);
    BOOST_CHECK_EQUAL(paths[0][1], v2);
    BOOST_CHECK_EQUAL(paths[0][2], v3);
}

BOOST_AUTO_TEST_CASE(findTest_1_linear_path_with_end_tip_in_the_end_large_limit_threshold)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v3].sequenceSize_ = 5U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v1, v3, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v0, v2, 100U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(paths.size(), 1);
    BOOST_CHECK_EQUAL(paths[0].size(), 3);
    BOOST_CHECK_EQUAL(paths[0][0], v0);
    BOOST_CHECK_EQUAL(paths[0][1], v1);
    BOOST_CHECK_EQUAL(paths[0][2], v2);
}

BOOST_AUTO_TEST_CASE(findTest_1_linear_path_with_end_tips_in_middle_of_path_large_limit_threshold)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v3].sequenceSize_ = 5U;
    unitigsGraph[v4].sequenceSize_ = 5U;
    unitigsGraph[v5].sequenceSize_ = 5U;
    unitigsGraph[v6].sequenceSize_ = 5U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v4].isOriginal_ = false;
    unitigsGraph[v5].isOriginal_ = false;
    unitigsGraph[v6].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v5, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v2, v6, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    unitigsGraph[e3].isForConnectedSequences_ = true;
    unitigsGraph[e4].isForConnectedSequences_ = true;
    unitigsGraph[e5].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v0, v4, 100U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 6);
    BOOST_CHECK_EQUAL(paths.size(), 1);
    BOOST_CHECK_EQUAL(paths[0].size(), 5);
    BOOST_CHECK_EQUAL(paths[0][0], v0);
    BOOST_CHECK_EQUAL(paths[0][1], v1);
    BOOST_CHECK_EQUAL(paths[0][2], v2);
    BOOST_CHECK_EQUAL(paths[0][3], v3);
    BOOST_CHECK_EQUAL(paths[0][4], v4);
}

BOOST_AUTO_TEST_CASE(findTest_2_paths_linear_structure_with_fork_in_middle_of_graph_large_limit_threshold)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v3].sequenceSize_ = 5U;
    unitigsGraph[v4].sequenceSize_ = 5U;
    unitigsGraph[v5].sequenceSize_ = 5U;
    unitigsGraph[v6].sequenceSize_ = 5U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v4].isOriginal_ = false;
    unitigsGraph[v5].isOriginal_ = false;
    unitigsGraph[v6].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v1, v5, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    unitigsGraph[e3].isForConnectedSequences_ = true;
    unitigsGraph[e4].isForConnectedSequences_ = true;
    unitigsGraph[e5].isForConnectedSequences_ = true;
    unitigsGraph[e6].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v0, v4, 100U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(paths.size(), 2);
    BOOST_CHECK_EQUAL(paths[0].size(), 5);
    BOOST_CHECK_EQUAL(paths[0][0], v0);
    BOOST_CHECK_EQUAL(paths[0][1], v1);
    BOOST_CHECK_EQUAL(paths[0][2], v2);
    BOOST_CHECK_EQUAL(paths[0][3], v3);
    BOOST_CHECK_EQUAL(paths[0][4], v4);
    BOOST_CHECK_EQUAL(paths[1].size(), 7);
    BOOST_CHECK_EQUAL(paths[1][0], v0);
    BOOST_CHECK_EQUAL(paths[1][1], v1);
    BOOST_CHECK_EQUAL(paths[1][2], v5);
    BOOST_CHECK_EQUAL(paths[1][3], v6);
    BOOST_CHECK_EQUAL(paths[1][4], v2);
    BOOST_CHECK_EQUAL(paths[1][5], v3);
    BOOST_CHECK_EQUAL(paths[1][6], v4);
}

BOOST_AUTO_TEST_CASE(findTest_2_paths_linear_structure_with_fork_in_middle_of_graph_one_path_below_limit_threshold)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v3].sequenceSize_ = 5U;
    unitigsGraph[v4].sequenceSize_ = 5U;
    unitigsGraph[v5].sequenceSize_ = 5U;
    unitigsGraph[v6].sequenceSize_ = 5U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v4].isOriginal_ = false;
    unitigsGraph[v5].isOriginal_ = false;
    unitigsGraph[v6].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v1, v5, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    unitigsGraph[e3].isForConnectedSequences_ = true;
    unitigsGraph[e4].isForConnectedSequences_ = true;
    unitigsGraph[e5].isForConnectedSequences_ = true;
    unitigsGraph[e6].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v0, v4, 17U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(paths.size(), 1);
    BOOST_CHECK_EQUAL(paths[0].size(), 5);
    BOOST_CHECK_EQUAL(paths[0][0], v0);
    BOOST_CHECK_EQUAL(paths[0][1], v1);
    BOOST_CHECK_EQUAL(paths[0][2], v2);
    BOOST_CHECK_EQUAL(paths[0][3], v3);
    BOOST_CHECK_EQUAL(paths[0][4], v4);
}

BOOST_AUTO_TEST_CASE(findTest_3_paths_structure_with_one_loop)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v3].sequenceSize_ = 5U;
    unitigsGraph[v4].sequenceSize_ = 5U;
    unitigsGraph[v5].sequenceSize_ = 5U;
    unitigsGraph[v6].sequenceSize_ = 5U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v4].isOriginal_ = false;
    unitigsGraph[v5].isOriginal_ = false;
    unitigsGraph[v6].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v2, v5, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v5, v6, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v1, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    unitigsGraph[e3].isForConnectedSequences_ = true;
    unitigsGraph[e4].isForConnectedSequences_ = true;
    unitigsGraph[e5].isForConnectedSequences_ = true;
    unitigsGraph[e6].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v0, v4, 70U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 7);
    BOOST_CHECK_EQUAL(paths.size(), 3);
    BOOST_CHECK_EQUAL(paths[0].size(), 5);
    BOOST_CHECK_EQUAL(paths[0][0], v0);
    BOOST_CHECK_EQUAL(paths[0][1], v1);
    BOOST_CHECK_EQUAL(paths[0][2], v2);
    BOOST_CHECK_EQUAL(paths[0][3], v3);
    BOOST_CHECK_EQUAL(paths[0][4], v4);
    BOOST_CHECK_EQUAL(paths[1].size(), 9);
    BOOST_CHECK_EQUAL(paths[1][0], v0);
    BOOST_CHECK_EQUAL(paths[1][1], v1);
    BOOST_CHECK_EQUAL(paths[1][2], v2);
    BOOST_CHECK_EQUAL(paths[1][3], v5);
    BOOST_CHECK_EQUAL(paths[1][4], v6);
    BOOST_CHECK_EQUAL(paths[1][5], v1);
    BOOST_CHECK_EQUAL(paths[1][6], v2);
    BOOST_CHECK_EQUAL(paths[1][7], v3);
    BOOST_CHECK_EQUAL(paths[1][8], v4);
    BOOST_CHECK_EQUAL(paths[2].size(), 13);
    BOOST_CHECK_EQUAL(paths[2][0], v0);
    BOOST_CHECK_EQUAL(paths[2][1], v1);
    BOOST_CHECK_EQUAL(paths[2][2], v2);
    BOOST_CHECK_EQUAL(paths[2][3], v5);
    BOOST_CHECK_EQUAL(paths[2][4], v6);
    BOOST_CHECK_EQUAL(paths[2][5], v1);
    BOOST_CHECK_EQUAL(paths[2][6], v2);
    BOOST_CHECK_EQUAL(paths[2][7], v5);
    BOOST_CHECK_EQUAL(paths[2][8], v6);
    BOOST_CHECK_EQUAL(paths[2][9], v1);
    BOOST_CHECK_EQUAL(paths[2][10], v2);
    BOOST_CHECK_EQUAL(paths[2][11], v3);
    BOOST_CHECK_EQUAL(paths[2][12], v4);
}

BOOST_AUTO_TEST_CASE(findTest_structure_with_two_loops)
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
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v3].sequenceSize_ = 5U;
    unitigsGraph[v4].sequenceSize_ = 5U;
    unitigsGraph[v5].sequenceSize_ = 5U;
    unitigsGraph[v6].sequenceSize_ = 5U;
    unitigsGraph[v7].sequenceSize_ = 5U;
    unitigsGraph[v8].sequenceSize_ = 5U;
    unitigsGraph[v9].sequenceSize_ = 5U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v4].isOriginal_ = false;
    unitigsGraph[v5].isOriginal_ = false;
    unitigsGraph[v6].isOriginal_ = false;
    unitigsGraph[v7].isOriginal_ = false;
    unitigsGraph[v8].isOriginal_ = false;
    unitigsGraph[v9].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v3, v6, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v7, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = add_edge(v7, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e8 = add_edge(v4, v8, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e9 = add_edge(v8, v9, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e10 = add_edge(v9, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    unitigsGraph[e3].isForConnectedSequences_ = true;
    unitigsGraph[e4].isForConnectedSequences_ = true;
    unitigsGraph[e5].isForConnectedSequences_ = true;
    unitigsGraph[e6].isForConnectedSequences_ = true;
    unitigsGraph[e7].isForConnectedSequences_ = true;
    unitigsGraph[e8].isForConnectedSequences_ = true;
    unitigsGraph[e9].isForConnectedSequences_ = true;
    unitigsGraph[e10].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v0, v5, 80U);
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 10);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 11);
    BOOST_CHECK_EQUAL(paths.size(), 7);
    BOOST_CHECK_EQUAL(paths[0].size(), 6);
    BOOST_CHECK_EQUAL(paths[0][0], v0);
    BOOST_CHECK_EQUAL(paths[0][1], v1);
    BOOST_CHECK_EQUAL(paths[0][2], v2);
    BOOST_CHECK_EQUAL(paths[0][3], v3);
    BOOST_CHECK_EQUAL(paths[0][4], v4);
    BOOST_CHECK_EQUAL(paths[0][5], v5);
    BOOST_CHECK_EQUAL(paths[1].size(), 11);
    BOOST_CHECK_EQUAL(paths[1][0], v0);
    BOOST_CHECK_EQUAL(paths[1][1], v1);
    BOOST_CHECK_EQUAL(paths[1][2], v2);
    BOOST_CHECK_EQUAL(paths[1][3], v3);
    BOOST_CHECK_EQUAL(paths[1][4], v4);
    BOOST_CHECK_EQUAL(paths[1][5], v8);
    BOOST_CHECK_EQUAL(paths[1][6], v9);
    BOOST_CHECK_EQUAL(paths[1][7], v2);
    BOOST_CHECK_EQUAL(paths[1][8], v3);
    BOOST_CHECK_EQUAL(paths[1][9], v4);
    BOOST_CHECK_EQUAL(paths[1][10], v5);
    BOOST_CHECK_EQUAL(paths[2].size(), 16);
    BOOST_CHECK_EQUAL(paths[2][0], v0);
    BOOST_CHECK_EQUAL(paths[2][1], v1);
    BOOST_CHECK_EQUAL(paths[2][2], v2);
    BOOST_CHECK_EQUAL(paths[2][3], v3);
    BOOST_CHECK_EQUAL(paths[2][4], v4);
    BOOST_CHECK_EQUAL(paths[2][5], v8);
    BOOST_CHECK_EQUAL(paths[2][6], v9);
    BOOST_CHECK_EQUAL(paths[2][7], v2);
    BOOST_CHECK_EQUAL(paths[2][8], v3);
    BOOST_CHECK_EQUAL(paths[2][9], v4);
    BOOST_CHECK_EQUAL(paths[2][10], v8);
    BOOST_CHECK_EQUAL(paths[2][11], v9);
    BOOST_CHECK_EQUAL(paths[2][12], v2);
    BOOST_CHECK_EQUAL(paths[2][13], v3);
    BOOST_CHECK_EQUAL(paths[2][14], v4);
    BOOST_CHECK_EQUAL(paths[2][15], v5);
    BOOST_CHECK_EQUAL(paths[3].size(), 16);
    BOOST_CHECK_EQUAL(paths[3][0], v0);
    BOOST_CHECK_EQUAL(paths[3][1], v1);
    BOOST_CHECK_EQUAL(paths[3][2], v2);
    BOOST_CHECK_EQUAL(paths[3][3], v3);
    BOOST_CHECK_EQUAL(paths[3][4], v4);
    BOOST_CHECK_EQUAL(paths[3][5], v8);
    BOOST_CHECK_EQUAL(paths[3][6], v9);
    BOOST_CHECK_EQUAL(paths[3][7], v2);
    BOOST_CHECK_EQUAL(paths[3][8], v3);
    BOOST_CHECK_EQUAL(paths[3][9], v6);
    BOOST_CHECK_EQUAL(paths[3][10], v7);
    BOOST_CHECK_EQUAL(paths[3][11], v1);
    BOOST_CHECK_EQUAL(paths[3][12], v2);
    BOOST_CHECK_EQUAL(paths[3][13], v3);
    BOOST_CHECK_EQUAL(paths[3][14], v4);
    BOOST_CHECK_EQUAL(paths[3][15], v5);
    BOOST_CHECK_EQUAL(paths[4].size(), 11);
    BOOST_CHECK_EQUAL(paths[4][0], v0);
    BOOST_CHECK_EQUAL(paths[4][1], v1);
    BOOST_CHECK_EQUAL(paths[4][2], v2);
    BOOST_CHECK_EQUAL(paths[4][3], v3);
    BOOST_CHECK_EQUAL(paths[4][4], v6);
    BOOST_CHECK_EQUAL(paths[4][5], v7);
    BOOST_CHECK_EQUAL(paths[4][6], v1);
    BOOST_CHECK_EQUAL(paths[4][7], v2);
    BOOST_CHECK_EQUAL(paths[4][8], v3);
    BOOST_CHECK_EQUAL(paths[4][9], v4);
    BOOST_CHECK_EQUAL(paths[4][10], v5);
    BOOST_CHECK_EQUAL(paths[5].size(), 16);
    BOOST_CHECK_EQUAL(paths[5][0], v0);
    BOOST_CHECK_EQUAL(paths[5][1], v1);
    BOOST_CHECK_EQUAL(paths[5][2], v2);
    BOOST_CHECK_EQUAL(paths[5][3], v3);
    BOOST_CHECK_EQUAL(paths[5][4], v6);
    BOOST_CHECK_EQUAL(paths[5][5], v7);
    BOOST_CHECK_EQUAL(paths[5][6], v1);
    BOOST_CHECK_EQUAL(paths[5][7], v2);
    BOOST_CHECK_EQUAL(paths[5][8], v3);
    BOOST_CHECK_EQUAL(paths[5][9], v4);
    BOOST_CHECK_EQUAL(paths[5][10], v8);
    BOOST_CHECK_EQUAL(paths[5][11], v9);
    BOOST_CHECK_EQUAL(paths[5][12], v2);
    BOOST_CHECK_EQUAL(paths[5][13], v3);
    BOOST_CHECK_EQUAL(paths[5][14], v4);
    BOOST_CHECK_EQUAL(paths[5][15], v5);
    BOOST_CHECK_EQUAL(paths[6].size(), 16);
    BOOST_CHECK_EQUAL(paths[6][0], v0);
    BOOST_CHECK_EQUAL(paths[6][1], v1);
    BOOST_CHECK_EQUAL(paths[6][2], v2);
    BOOST_CHECK_EQUAL(paths[6][3], v3);
    BOOST_CHECK_EQUAL(paths[6][4], v6);
    BOOST_CHECK_EQUAL(paths[6][5], v7);
    BOOST_CHECK_EQUAL(paths[6][6], v1);
    BOOST_CHECK_EQUAL(paths[6][7], v2);
    BOOST_CHECK_EQUAL(paths[6][8], v3);
    BOOST_CHECK_EQUAL(paths[6][9], v6);
    BOOST_CHECK_EQUAL(paths[6][10], v7);
    BOOST_CHECK_EQUAL(paths[6][11], v1);
    BOOST_CHECK_EQUAL(paths[6][12], v2);
    BOOST_CHECK_EQUAL(paths[6][13], v3);
    BOOST_CHECK_EQUAL(paths[6][14], v4);
    BOOST_CHECK_EQUAL(paths[6][15], v5);
}
/*
BOOST_AUTO_TEST_CASE(findTest_structure_with_two_loops_very_large_limit)
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
    unitigsGraph[v0].sequenceSize_ = 5U;
    unitigsGraph[v1].sequenceSize_ = 5U;
    unitigsGraph[v2].sequenceSize_ = 5U;
    unitigsGraph[v3].sequenceSize_ = 5U;
    unitigsGraph[v4].sequenceSize_ = 5U;
    unitigsGraph[v5].sequenceSize_ = 5U;
    unitigsGraph[v6].sequenceSize_ = 5U;
    unitigsGraph[v7].sequenceSize_ = 5U;
    unitigsGraph[v8].sequenceSize_ = 5U;
    unitigsGraph[v9].sequenceSize_ = 5U;
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v4].isOriginal_ = false;
    unitigsGraph[v5].isOriginal_ = false;
    unitigsGraph[v6].isOriginal_ = false;
    unitigsGraph[v7].isOriginal_ = false;
    unitigsGraph[v8].isOriginal_ = false;
    unitigsGraph[v9].isOriginal_ = false;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v3, v4, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e4 = add_edge(v4, v5, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e5 = add_edge(v3, v6, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e6 = add_edge(v6, v7, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e7 = add_edge(v7, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e8 = add_edge(v4, v8, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e9 = add_edge(v8, v9, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e10 = add_edge(v9, v2, unitigsGraph).first;
    unitigsGraph[e0].isForConnectedSequences_ = true;
    unitigsGraph[e1].isForConnectedSequences_ = true;
    unitigsGraph[e2].isForConnectedSequences_ = true;
    unitigsGraph[e3].isForConnectedSequences_ = true;
    unitigsGraph[e4].isForConnectedSequences_ = true;
    unitigsGraph[e5].isForConnectedSequences_ = true;
    unitigsGraph[e6].isForConnectedSequences_ = true;
    unitigsGraph[e7].isForConnectedSequences_ = true;
    unitigsGraph[e8].isForConnectedSequences_ = true;
    unitigsGraph[e9].isForConnectedSequences_ = true;
    unitigsGraph[e10].isForConnectedSequences_ = true;
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph> pathsFinder(unitigsGraph, v0, v5, numeric_limits<unsigned short>::max());
    AllPathsFinder<UnitigsToContigsExtension::UnitigsGraph>::Paths paths = pathsFinder.findAllPaths();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 10);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 11);
    BOOST_CHECK_EQUAL(paths.size(), 0);
}
*/
BOOST_AUTO_TEST_SUITE_END()
