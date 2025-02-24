/**
 * \file TestDistanceArrayBuilder.cpp
 * \brief the C++ file with implementation of tests for DistanceArrayBuilder class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/DistanceArrayBuilder.hpp"
#include "../../../src/dbj/UnitigsToContigsExtension.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestDistanceArrayBuilder)

BOOST_AUTO_TEST_CASE(buildDistanceArray_subgraph_equal_to_graph_without_edges_all_vertices_not_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    UnitigsToContigsExtension::UnitigsGraph unitigsSubgraph;
    UnitigsToContigsExtension::UnitigsGraphVertex sv0 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv1 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv2 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv3 = add_vertex(unitigsSubgraph);
    unitigsSubgraph[sv0].isOriginal_ = false;
    unitigsSubgraph[sv1].isOriginal_ = false;
    unitigsSubgraph[sv2].isOriginal_ = false;
    unitigsSubgraph[sv3].isOriginal_ = false;
    unitigsSubgraph[sv0].sequenceSize_ = 2U;
    unitigsSubgraph[sv1].sequenceSize_ = 2U;
    unitigsSubgraph[sv2].sequenceSize_ = 2U;
    unitigsSubgraph[sv3].sequenceSize_ = 2U;
    vector<UnitigsToContigsExtension::UnitigsGraphVertex> verticesId;
    verticesId.push_back(v0);
    verticesId.push_back(v1);
    verticesId.push_back(v2);
    verticesId.push_back(v3);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph> distanceArrayBuilder(unitigsGraph);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray = distanceArrayBuilder.buildDistanceArray(unitigsSubgraph, verticesId);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsSubgraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsSubgraph), 0);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv3], numeric_limits<unsigned short>::max());
}

BOOST_AUTO_TEST_CASE(buildDistanceArray_subgraph_not_equal_to_graph_without_edges_all_vertices_not_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    UnitigsToContigsExtension::UnitigsGraph unitigsSubgraph;
    UnitigsToContigsExtension::UnitigsGraphVertex sv0 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv1 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv2 = add_vertex(unitigsSubgraph);
    unitigsSubgraph[sv0].isOriginal_ = false;
    unitigsSubgraph[sv1].isOriginal_ = false;
    unitigsSubgraph[sv2].isOriginal_ = false;
    unitigsSubgraph[sv0].sequenceSize_ = 2U;
    unitigsSubgraph[sv1].sequenceSize_ = 2U;
    unitigsSubgraph[sv2].sequenceSize_ = 2U;
    vector<UnitigsToContigsExtension::UnitigsGraphVertex> verticesId;
    verticesId.push_back(v0);
    verticesId.push_back(v3);
    verticesId.push_back(v2);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph> distanceArrayBuilder(unitigsGraph);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray = distanceArrayBuilder.buildDistanceArray(unitigsSubgraph, verticesId);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsSubgraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsSubgraph), 0);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv2], numeric_limits<unsigned short>::max());
}

BOOST_AUTO_TEST_CASE(buildDistanceArray_subgraph_equal_to_graph_with_some_edges_all_vertices_not_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v3, v1, unitigsGraph).first;
    unitigsGraph[e0].estimatedDistance_ = 10U;
    unitigsGraph[e1].estimatedDistance_ = 5U;
    UnitigsToContigsExtension::UnitigsGraph unitigsSubgraph;
    UnitigsToContigsExtension::UnitigsGraphVertex sv0 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv1 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv2 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv3 = add_vertex(unitigsSubgraph);
    unitigsSubgraph[sv0].isOriginal_ = false;
    unitigsSubgraph[sv1].isOriginal_ = false;
    unitigsSubgraph[sv2].isOriginal_ = false;
    unitigsSubgraph[sv3].isOriginal_ = false;
    unitigsSubgraph[sv0].sequenceSize_ = 2U;
    unitigsSubgraph[sv1].sequenceSize_ = 2U;
    unitigsSubgraph[sv2].sequenceSize_ = 2U;
    unitigsSubgraph[sv3].sequenceSize_ = 2U;
    vector<UnitigsToContigsExtension::UnitigsGraphVertex> verticesId;
    verticesId.push_back(v0);
    verticesId.push_back(v1);
    verticesId.push_back(v2);
    verticesId.push_back(v3);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph> distanceArrayBuilder(unitigsGraph);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray = distanceArrayBuilder.buildDistanceArray(unitigsSubgraph, verticesId);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(num_vertices(unitigsSubgraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsSubgraph), 0);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv1], 10U);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv1], 5U);
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv3], numeric_limits<unsigned short>::max());
}

BOOST_AUTO_TEST_CASE(buildDistanceArray_subgraph_not_equal_to_graph_with_some_edges_all_vertices_not_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v3, v1, unitigsGraph).first;
    unitigsGraph[e0].estimatedDistance_ = 10U;
    unitigsGraph[e1].estimatedDistance_ = 5U;
    UnitigsToContigsExtension::UnitigsGraph unitigsSubgraph;
    UnitigsToContigsExtension::UnitigsGraphVertex sv0 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv1 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv2 = add_vertex(unitigsSubgraph);
    unitigsSubgraph[sv0].isOriginal_ = false;
    unitigsSubgraph[sv1].isOriginal_ = false;
    unitigsSubgraph[sv2].isOriginal_ = false;
    unitigsSubgraph[sv0].sequenceSize_ = 2U;
    unitigsSubgraph[sv1].sequenceSize_ = 2U;
    unitigsSubgraph[sv2].sequenceSize_ = 2U;
    vector<UnitigsToContigsExtension::UnitigsGraphVertex> verticesId;
    verticesId.push_back(v0);
    verticesId.push_back(v3);
    verticesId.push_back(v1);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph> distanceArrayBuilder(unitigsGraph);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray = distanceArrayBuilder.buildDistanceArray(unitigsSubgraph, verticesId);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(num_vertices(unitigsSubgraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsSubgraph), 0);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv2], 10U);
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv2], 5U);
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv2], numeric_limits<unsigned short>::max());
}

/******************* tests for correcting distance array *******************************/

BOOST_AUTO_TEST_CASE(buildDistanceArray_subgraph_equal_to_graph_without_edges_all_vertices_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = true;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v3].isOriginal_ = true;
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    UnitigsToContigsExtension::UnitigsGraph unitigsSubgraph;
    UnitigsToContigsExtension::UnitigsGraphVertex sv0 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv1 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv2 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv3 = add_vertex(unitigsSubgraph);
    unitigsSubgraph[sv0].isOriginal_ = true;
    unitigsSubgraph[sv1].isOriginal_ = true;
    unitigsSubgraph[sv2].isOriginal_ = true;
    unitigsSubgraph[sv3].isOriginal_ = true;
    unitigsSubgraph[sv0].sequenceSize_ = 2U;
    unitigsSubgraph[sv1].sequenceSize_ = 2U;
    unitigsSubgraph[sv2].sequenceSize_ = 2U;
    unitigsSubgraph[sv3].sequenceSize_ = 2U;
    vector<UnitigsToContigsExtension::UnitigsGraphVertex> verticesId;
    verticesId.push_back(v0);
    verticesId.push_back(v1);
    verticesId.push_back(v2);
    verticesId.push_back(v3);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph> distanceArrayBuilder(unitigsGraph);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray = distanceArrayBuilder.buildDistanceArray(unitigsSubgraph, verticesId);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsSubgraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsSubgraph), 0);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv3], numeric_limits<unsigned short>::max());
}

BOOST_AUTO_TEST_CASE(buildDistanceArray_subgraph_equal_to_graph_single_sub_connection_all_vertices_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = true;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v3].isOriginal_ = true;
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    unitigsGraph[e0].estimatedDistance_ = 10U;
    unitigsGraph[e1].estimatedDistance_ = 5U;
    UnitigsToContigsExtension::UnitigsGraph unitigsSubgraph;
    UnitigsToContigsExtension::UnitigsGraphVertex sv0 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv1 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv2 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv3 = add_vertex(unitigsSubgraph);
    unitigsSubgraph[sv0].isOriginal_ = true;
    unitigsSubgraph[sv1].isOriginal_ = true;
    unitigsSubgraph[sv2].isOriginal_ = true;
    unitigsSubgraph[sv3].isOriginal_ = true;
    unitigsSubgraph[sv0].sequenceSize_ = 2U;
    unitigsSubgraph[sv1].sequenceSize_ = 2U;
    unitigsSubgraph[sv2].sequenceSize_ = 2U;
    unitigsSubgraph[sv3].sequenceSize_ = 2U;
    vector<UnitigsToContigsExtension::UnitigsGraphVertex> verticesId;
    verticesId.push_back(v0);
    verticesId.push_back(v1);
    verticesId.push_back(v2);
    verticesId.push_back(v3);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph> distanceArrayBuilder(unitigsGraph);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray = distanceArrayBuilder.buildDistanceArray(unitigsSubgraph, verticesId);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 2);
    BOOST_CHECK_EQUAL(num_vertices(unitigsSubgraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsSubgraph), 0);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv1], 10U);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv2], 17U);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv2], 5U);
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv3], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv3], numeric_limits<unsigned short>::max());
}

BOOST_AUTO_TEST_CASE(buildDistanceArray_subgraph_equal_to_graph_double_sub_connections_all_vertices_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = true;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v3].isOriginal_ = true;
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    unitigsGraph[e0].estimatedDistance_ = 10U;
    unitigsGraph[e1].estimatedDistance_ = 5U;
    unitigsGraph[e2].estimatedDistance_ = 10U;
    UnitigsToContigsExtension::UnitigsGraph unitigsSubgraph;
    UnitigsToContigsExtension::UnitigsGraphVertex sv0 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv1 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv2 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv3 = add_vertex(unitigsSubgraph);
    unitigsSubgraph[sv0].isOriginal_ = true;
    unitigsSubgraph[sv1].isOriginal_ = true;
    unitigsSubgraph[sv2].isOriginal_ = true;
    unitigsSubgraph[sv3].isOriginal_ = true;
    unitigsSubgraph[sv0].sequenceSize_ = 2U;
    unitigsSubgraph[sv1].sequenceSize_ = 2U;
    unitigsSubgraph[sv2].sequenceSize_ = 2U;
    unitigsSubgraph[sv3].sequenceSize_ = 2U;
    vector<UnitigsToContigsExtension::UnitigsGraphVertex> verticesId;
    verticesId.push_back(v0);
    verticesId.push_back(v1);
    verticesId.push_back(v2);
    verticesId.push_back(v3);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph> distanceArrayBuilder(unitigsGraph);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray = distanceArrayBuilder.buildDistanceArray(unitigsSubgraph, verticesId);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_vertices(unitigsSubgraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsSubgraph), 0);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv1], 10U);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv2], 17U);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv3], 29U);
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv2], 5U);
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv3], 17U);
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv3], 10U);
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv3], numeric_limits<unsigned short>::max());
}

BOOST_AUTO_TEST_CASE(buildDistanceArray_subgraph_equal_to_graph_two_double_sub_connections_all_vertices_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = true;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v3].isOriginal_ = true;
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v1, v3, unitigsGraph).first;
    unitigsGraph[e0].estimatedDistance_ = 10U;
    unitigsGraph[e1].estimatedDistance_ = 5U;
    unitigsGraph[e2].estimatedDistance_ = 10U;
    unitigsGraph[e3].estimatedDistance_ = 30U;
    UnitigsToContigsExtension::UnitigsGraph unitigsSubgraph;
    UnitigsToContigsExtension::UnitigsGraphVertex sv0 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv1 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv2 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv3 = add_vertex(unitigsSubgraph);
    unitigsSubgraph[sv0].isOriginal_ = true;
    unitigsSubgraph[sv1].isOriginal_ = true;
    unitigsSubgraph[sv2].isOriginal_ = true;
    unitigsSubgraph[sv3].isOriginal_ = true;
    unitigsSubgraph[sv0].sequenceSize_ = 2U;
    unitigsSubgraph[sv1].sequenceSize_ = 2U;
    unitigsSubgraph[sv2].sequenceSize_ = 2U;
    unitigsSubgraph[sv3].sequenceSize_ = 2U;
    vector<UnitigsToContigsExtension::UnitigsGraphVertex> verticesId;
    verticesId.push_back(v0);
    verticesId.push_back(v1);
    verticesId.push_back(v2);
    verticesId.push_back(v3);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph> distanceArrayBuilder(unitigsGraph);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray = distanceArrayBuilder.buildDistanceArray(unitigsSubgraph, verticesId);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_vertices(unitigsSubgraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsSubgraph), 0);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv1], 10U);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv2], 17U);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv3], 35U);
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv2], 5U);
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv3], 30U);
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv3], 10U);
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv3], numeric_limits<unsigned short>::max());
}

BOOST_AUTO_TEST_CASE(buildDistanceArray_subgraph_equal_to_graph_two_double_sub_connections_not_all_vertices_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = true;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = true;
    unitigsGraph[v0].sequenceSize_ = 2U;
    unitigsGraph[v1].sequenceSize_ = 2U;
    unitigsGraph[v2].sequenceSize_ = 2U;
    unitigsGraph[v3].sequenceSize_ = 2U;
    UnitigsToContigsExtension::UnitigsGraphEdge e0 = add_edge(v0, v1, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e1 = add_edge(v1, v2, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e2 = add_edge(v2, v3, unitigsGraph).first;
    UnitigsToContigsExtension::UnitigsGraphEdge e3 = add_edge(v1, v3, unitigsGraph).first;
    unitigsGraph[e0].estimatedDistance_ = 10U;
    unitigsGraph[e1].estimatedDistance_ = 5U;
    unitigsGraph[e2].estimatedDistance_ = 10U;
    unitigsGraph[e3].estimatedDistance_ = 30U;
    UnitigsToContigsExtension::UnitigsGraph unitigsSubgraph;
    UnitigsToContigsExtension::UnitigsGraphVertex sv0 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv1 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv2 = add_vertex(unitigsSubgraph);
    UnitigsToContigsExtension::UnitigsGraphVertex sv3 = add_vertex(unitigsSubgraph);
    unitigsSubgraph[sv0].isOriginal_ = true;
    unitigsSubgraph[sv1].isOriginal_ = true;
    unitigsSubgraph[sv2].isOriginal_ = false;
    unitigsSubgraph[sv3].isOriginal_ = true;
    unitigsSubgraph[sv0].sequenceSize_ = 2U;
    unitigsSubgraph[sv1].sequenceSize_ = 2U;
    unitigsSubgraph[sv2].sequenceSize_ = 2U;
    unitigsSubgraph[sv3].sequenceSize_ = 2U;
    vector<UnitigsToContigsExtension::UnitigsGraphVertex> verticesId;
    verticesId.push_back(v0);
    verticesId.push_back(v1);
    verticesId.push_back(v2);
    verticesId.push_back(v3);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph> distanceArrayBuilder(unitigsGraph);
    DistanceArrayBuilder<UnitigsToContigsExtension::UnitigsGraph>::DistanceArray distanceArray = distanceArrayBuilder.buildDistanceArray(unitigsSubgraph, verticesId);
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_vertices(unitigsSubgraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsSubgraph), 0);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv1], 10U);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv2], 17U);
    BOOST_CHECK_EQUAL(distanceArray[sv0][sv3], 42U);
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv2], 5U);
    BOOST_CHECK_EQUAL(distanceArray[sv1][sv3], 30U);
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv2][sv3], 10U);
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv0], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv1], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv2], numeric_limits<unsigned short>::max());
    BOOST_CHECK_EQUAL(distanceArray[sv3][sv3], numeric_limits<unsigned short>::max());
}

BOOST_AUTO_TEST_SUITE_END()

