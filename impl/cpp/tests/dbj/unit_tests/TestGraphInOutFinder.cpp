/**
 * \file TestGraphInOutFinder.cpp
 * \brief the C++ file with implementation of tests for GraphInOutFinder class
 *
 */

#include <boost/test/unit_test.hpp>

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
//unknown pragma
//#pragma warning(disable:4068)
#endif

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#include "../../../src/dbj/GraphInOutFinder.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

using namespace dnaasm::dbj;
using namespace std;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

BOOST_AUTO_TEST_SUITE(TestGraphInOutFinder)

BOOST_AUTO_TEST_CASE(findInVertices_emptyGraph)
{
    DeBruijnGraph deBruijnGraph;
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> inVertices;
    graphInOutFinder.findInVertices(inVertices);
    BOOST_CHECK_EQUAL(inVertices.size(), 0);
}

BOOST_AUTO_TEST_CASE(findOutVertices_emptyGraph)
{
    DeBruijnGraph deBruijnGraph;
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> outVertices;
    graphInOutFinder.findOutVertices(outVertices);
    BOOST_CHECK_EQUAL(outVertices.size(), 0);
}

BOOST_AUTO_TEST_CASE(findInVertices_singlePath)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    std::vector<DeBruijnGraphVertex> sources = {v0};
    std::vector<DeBruijnGraphVertex> targets = {v1};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 2);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> inVertices;
    graphInOutFinder.findInVertices(inVertices);
    BOOST_CHECK_EQUAL(inVertices.size(), 1);
    BOOST_CHECK_EQUAL(inVertices[0], v0);
}

BOOST_AUTO_TEST_CASE(findOutVertices_singlePath)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    std::vector<DeBruijnGraphVertex> sources = {v0};
    std::vector<DeBruijnGraphVertex> targets = {v1};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 2);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> outVertices;
    graphInOutFinder.findOutVertices(outVertices);
    BOOST_CHECK_EQUAL(outVertices.size(), 1);
    BOOST_CHECK_EQUAL(outVertices[0], v1);
}

BOOST_AUTO_TEST_CASE(findInVertices_disconnectedGraphWithSinglePaths)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    std::vector<DeBruijnGraphVertex> sources = {v0, v2};
    std::vector<DeBruijnGraphVertex> targets = {v1, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 4);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> inVertices;
    graphInOutFinder.findInVertices(inVertices);
    BOOST_CHECK_EQUAL(inVertices.size(), 2);
    BOOST_CHECK_EQUAL(inVertices[0], v0);
    BOOST_CHECK_EQUAL(inVertices[1], v2);
}

BOOST_AUTO_TEST_CASE(findOutVertices_disconnectedGraphWithSinglePaths)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    std::vector<DeBruijnGraphVertex> sources = {v0, v2};
    std::vector<DeBruijnGraphVertex> targets = {v1, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 4);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> outVertices;
    graphInOutFinder.findOutVertices(outVertices);
    BOOST_CHECK_EQUAL(outVertices.size(), 2);
    BOOST_CHECK_EQUAL(outVertices[0], v1);
    BOOST_CHECK_EQUAL(outVertices[1], v3);
}

BOOST_AUTO_TEST_CASE(findInVertices_singleLongerPathWithLoop)
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
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> inVertices;
    graphInOutFinder.findInVertices(inVertices);
    BOOST_CHECK_EQUAL(inVertices.size(), 1);
    BOOST_CHECK_EQUAL(inVertices[0], v0);
}

BOOST_AUTO_TEST_CASE(findOutVertices_singleLongerPathWithLoop)
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
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> outVertices;
    graphInOutFinder.findOutVertices(outVertices);
    BOOST_CHECK_EQUAL(outVertices.size(), 1);
    BOOST_CHECK_EQUAL(outVertices[0], v5);
}

BOOST_AUTO_TEST_CASE(findInVertices_1In_2Out)
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
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v3, v7, v8};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v8, v9};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 10);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> inVertices;
    graphInOutFinder.findInVertices(inVertices);
    BOOST_CHECK_EQUAL(inVertices.size(), 1);
    BOOST_CHECK_EQUAL(inVertices[0], v0);
}

BOOST_AUTO_TEST_CASE(findOutVertices_1In_2Out)
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
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v3, v7, v8};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v4, v5, v6, v7, v8, v9};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 10);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> outVertices;
    graphInOutFinder.findOutVertices(outVertices);
    BOOST_CHECK_EQUAL(outVertices.size(), 2);
    BOOST_CHECK_EQUAL(outVertices[0], v6);
    BOOST_CHECK_EQUAL(outVertices[1], v9);
}

BOOST_AUTO_TEST_CASE(findInVertices_2In_1Out)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v7, v5, v6, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 8);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> inVertices;
    graphInOutFinder.findInVertices(inVertices);
    BOOST_CHECK_EQUAL(inVertices.size(), 2);
    BOOST_CHECK_EQUAL(inVertices[0], v0);
    BOOST_CHECK_EQUAL(inVertices[1], v4);
}

BOOST_AUTO_TEST_CASE(findOutVertices_2In_1Out)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    DeBruijnGraphVertex v4 = 4;
    DeBruijnGraphVertex v5 = 5;
    DeBruijnGraphVertex v6 = 6;
    DeBruijnGraphVertex v7 = 7;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3, v4, v5, v6};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v7, v5, v6, v3};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 8);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> outVertices;
    graphInOutFinder.findOutVertices(outVertices);
    BOOST_CHECK_EQUAL(outVertices.size(), 1);
    BOOST_CHECK_EQUAL(outVertices[0], v7);
}

BOOST_AUTO_TEST_CASE(findInVertices_4_vertices_loop)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v0};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 4);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> inVertices;
    graphInOutFinder.findInVertices(inVertices);
    BOOST_CHECK_EQUAL(inVertices.size(), 0);
}

BOOST_AUTO_TEST_CASE(findOutVertices_4_vertices_loop)
{
    DeBruijnGraphVertex v0 = 0;
    DeBruijnGraphVertex v1 = 1;
    DeBruijnGraphVertex v2 = 2;
    DeBruijnGraphVertex v3 = 3;
    std::vector<DeBruijnGraphVertex> sources = {v0, v1, v2, v3};
    std::vector<DeBruijnGraphVertex> targets = {v1, v2, v3, v0};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 4);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> outVertices;
    graphInOutFinder.findOutVertices(outVertices);
    BOOST_CHECK_EQUAL(outVertices.size(), 0);
}

BOOST_AUTO_TEST_CASE(findInVertices_self_loop)
{
    DeBruijnGraphVertex v0 = 0;
    std::vector<DeBruijnGraphVertex> sources = {v0};
    std::vector<DeBruijnGraphVertex> targets = {v0};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 1);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> inVertices;
    graphInOutFinder.findInVertices(inVertices);
    BOOST_CHECK_EQUAL(inVertices.size(), 0);
}

BOOST_AUTO_TEST_CASE(findOutVertices_self_loop)
{
    DeBruijnGraphVertex v0 = 0;
    std::vector<DeBruijnGraphVertex> sources = {v0};
    std::vector<DeBruijnGraphVertex> targets = {v0};
    DeBruijnGraph deBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, 1);
    GraphInOutFinder<DeBruijnGraph> graphInOutFinder(deBruijnGraph);
    vector<DeBruijnGraphVertex> outVertices;
    graphInOutFinder.findOutVertices(outVertices);
    BOOST_CHECK_EQUAL(outVertices.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
