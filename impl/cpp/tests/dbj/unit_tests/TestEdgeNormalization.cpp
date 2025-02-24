/**
 * \file TestEdgeNormalization.cpp
 * \brief the C++ file with implementation of tests for EdgeNormalization class
 *
 */


#include <boost/test/unit_test.hpp>

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
#pragma warning(disable:4068)
#endif

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#include "../../../src/dbj/EdgeNormalization.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

using namespace dnaasm::dbj;
using namespace std;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

BOOST_AUTO_TEST_SUITE(TestEdgeNormalization)

BOOST_AUTO_TEST_CASE(EdgeNormalization1)
{
    DeBruijnGraph deBruijnGraph;
    EdgeNormalization<DeBruijnGraph> edgeNormalization(deBruijnGraph, 2, 2ULL, 0);
    edgeNormalization.normalizeEdges();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(edgeNormalization.getNormalizationRate(), 1.0F);
}

BOOST_AUTO_TEST_CASE(EdgeNormalization2)
{
    DeBruijnGraph deBruijnGraph;
    EdgeNormalization<DeBruijnGraph> edgeNormalization(deBruijnGraph, 0, 0ULL, 0);
    edgeNormalization.normalizeEdges();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(edgeNormalization.getNormalizationRate(), 1.0F);
}

BOOST_AUTO_TEST_CASE(EdgeNormalization3)
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
    EdgeNormalization<DeBruijnGraph> edgeNormalization(deBruijnGraph, 3, 5ULL, 2);
    edgeNormalization.normalizeEdges();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 9);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 8);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v5, v6, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v6, v7, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v7, v8, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v5, v6, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v6, v7, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v7, v8, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(edgeNormalization.getNormalizationRate(), 0.190476194F);
}

BOOST_AUTO_TEST_CASE(EdgeNormalization4)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v2};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v1, v4};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 5);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 5U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 7U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 5U;
    deBruijnGraph[edge(v3, v1, deBruijnGraph).first].counter_ = 5U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 5U;
    EdgeNormalization<DeBruijnGraph> edgeNormalization(deBruijnGraph, 3, 10ULL, 1);
    edgeNormalization.normalizeEdges();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v1, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(edgeNormalization.getNormalizationRate(), 0.518518507F);
}

BOOST_AUTO_TEST_CASE(EdgeNormalization5)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v2, v0};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v1, v4, v4};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 5);
    deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_ = 5U;
    deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_ = 7U;
    deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_ = 5U;
    deBruijnGraph[edge(v3, v1, deBruijnGraph).first].counter_ = 5U;
    deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_ = 5U;
    deBruijnGraph[edge(v0, v4, deBruijnGraph).first].counter_ = 0U;
    EdgeNormalization<DeBruijnGraph> edgeNormalization(deBruijnGraph, 3, 10ULL, 0);
    edgeNormalization.normalizeEdges();
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 5);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 6);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v2, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 4U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v3, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v1, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v2, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v4, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(edgeNormalization.getNormalizationRate(), 0.518518507F);
}

BOOST_AUTO_TEST_SUITE_END()
