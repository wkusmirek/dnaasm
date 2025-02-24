/**
 * \file TestSingleGraphBuilder.cpp
 * \brief the C++ file with implementation of tests for SingleGraphBuilder class
 *
 */

#include <fstream>
#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/SingleGraphBuilder.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestSingleGraphBuilder)

BOOST_AUTO_TEST_CASE(buildTest_empty_input_file)
{
    Statistics statistics;
    istringstream bfcFile;
    DeBruijnGraph deBruijnGraph;
    unsigned short K1 = 2U;
    unsigned int threshold = 5U;
    vector<char> firstChars;
    vector<uint48> compressedTargets;
    SingleGraph singleGraph(deBruijnGraph, bfcFile, K1, threshold);
    bfcFile.str("");
    SingleGraphBuilder singleGraphBuilder(singleGraph, statistics, NULL);
    singleGraphBuilder.build(firstChars, compressedTargets);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(compressedTargets.size(), 0);
    BOOST_CHECK_EQUAL(firstChars.size(), 0);
}

BOOST_AUTO_TEST_CASE(buildTest_threshold_equal_to_0)
{
    Statistics statistics;
    istringstream bfcFile;
    DeBruijnGraph deBruijnGraph;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    vector<char> firstChars;
    vector<uint48> compressedTargets;
    SingleGraph singleGraph(deBruijnGraph, bfcFile, K1, threshold);
    bfcFile.str("AAA\t2\nGGG\t15\n");
    SingleGraphBuilder singleGraphBuilder(singleGraph, statistics, NULL);
    singleGraphBuilder.build(firstChars, compressedTargets);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(edge((SingleGraph::DeBruijnGraphVertex)0ULL, (SingleGraph::DeBruijnGraphVertex)0ULL, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge((SingleGraph::DeBruijnGraphVertex)1ULL, (SingleGraph::DeBruijnGraphVertex)1ULL, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge((SingleGraph::DeBruijnGraphVertex)2ULL, (SingleGraph::DeBruijnGraphVertex)2ULL, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge((SingleGraph::DeBruijnGraphVertex)3ULL, (SingleGraph::DeBruijnGraphVertex)3ULL, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge((SingleGraph::DeBruijnGraphVertex)0ULL, (SingleGraph::DeBruijnGraphVertex)0ULL, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge((SingleGraph::DeBruijnGraphVertex)1ULL, (SingleGraph::DeBruijnGraphVertex)1ULL, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge((SingleGraph::DeBruijnGraphVertex)2ULL, (SingleGraph::DeBruijnGraphVertex)2ULL, deBruijnGraph).first].counter_, 15U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge((SingleGraph::DeBruijnGraphVertex)3ULL, (SingleGraph::DeBruijnGraphVertex)3ULL, deBruijnGraph).first].counter_, 15U);
    BOOST_CHECK_EQUAL(compressedTargets.size(), 4);
    BOOST_CHECK_EQUAL(compressedTargets[0].v, 0ULL);
    BOOST_CHECK_EQUAL(compressedTargets[1].v, 1ULL);
    BOOST_CHECK_EQUAL(compressedTargets[2].v, 2ULL);
    BOOST_CHECK_EQUAL(compressedTargets[3].v, 3ULL);
    BOOST_CHECK_EQUAL(firstChars.size(), 8);
    BOOST_CHECK_EQUAL(firstChars[0], 'A');
    BOOST_CHECK_EQUAL(firstChars[1], 'T');
    BOOST_CHECK_EQUAL(firstChars[2], 'G');
    BOOST_CHECK_EQUAL(firstChars[3], 'C');
    BOOST_CHECK_EQUAL(firstChars[4], 0);
    BOOST_CHECK_EQUAL(firstChars[5], 0);
    BOOST_CHECK_EQUAL(firstChars[6], 0);
    BOOST_CHECK_EQUAL(firstChars[7], 0);
}

BOOST_AUTO_TEST_CASE(buildTest_threshold_equal_to_0_another_example)
{
    Statistics statistics;
    istringstream bfcFile;
    DeBruijnGraph deBruijnGraph;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    vector<char> firstChars;
    vector<uint48> compressedTargets;
    SingleGraph singleGraph(deBruijnGraph, bfcFile, K1, threshold);
    bfcFile.str("CTA\t2\nTAT\t15\n");
    SingleGraphBuilder singleGraphBuilder(singleGraph, statistics, NULL);
    singleGraphBuilder.build(firstChars, compressedTargets);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 4);
    BOOST_CHECK_EQUAL(edge((SingleGraph::DeBruijnGraphVertex)0ULL, (SingleGraph::DeBruijnGraphVertex)1ULL, deBruijnGraph).second, true);    //CTA
    BOOST_CHECK_EQUAL(edge((SingleGraph::DeBruijnGraphVertex)1ULL, (SingleGraph::DeBruijnGraphVertex)2ULL, deBruijnGraph).second, true);    //TAG
    BOOST_CHECK_EQUAL(edge((SingleGraph::DeBruijnGraphVertex)1ULL, (SingleGraph::DeBruijnGraphVertex)3ULL, deBruijnGraph).second, true);    //TAT
    BOOST_CHECK_EQUAL(edge((SingleGraph::DeBruijnGraphVertex)3ULL, (SingleGraph::DeBruijnGraphVertex)1ULL, deBruijnGraph).second, true);    //ATA
    BOOST_CHECK_EQUAL(deBruijnGraph[edge((SingleGraph::DeBruijnGraphVertex)0ULL, (SingleGraph::DeBruijnGraphVertex)1ULL, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge((SingleGraph::DeBruijnGraphVertex)1ULL, (SingleGraph::DeBruijnGraphVertex)2ULL, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge((SingleGraph::DeBruijnGraphVertex)1ULL, (SingleGraph::DeBruijnGraphVertex)3ULL, deBruijnGraph).first].counter_, 15U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge((SingleGraph::DeBruijnGraphVertex)3ULL, (SingleGraph::DeBruijnGraphVertex)1ULL, deBruijnGraph).first].counter_, 15U);
    BOOST_CHECK_EQUAL(compressedTargets.size(), 4);
    BOOST_CHECK_EQUAL(compressedTargets[0].v, 1ULL);
    BOOST_CHECK_EQUAL(compressedTargets[1].v, 2ULL);
    BOOST_CHECK_EQUAL(compressedTargets[2].v, 3ULL);
    BOOST_CHECK_EQUAL(compressedTargets[3].v, 1ULL);
    BOOST_CHECK_EQUAL(firstChars.size(), 8);
    BOOST_CHECK_EQUAL(firstChars[0], 'C');
    BOOST_CHECK_EQUAL(firstChars[1], 'T');
    BOOST_CHECK_EQUAL(firstChars[2], 'A');
    BOOST_CHECK_EQUAL(firstChars[3], 'A');
    BOOST_CHECK_EQUAL(firstChars[4], 0);
    BOOST_CHECK_EQUAL(firstChars[5], 0);
    BOOST_CHECK_EQUAL(firstChars[6], 0);
    BOOST_CHECK_EQUAL(firstChars[7], 0);
}

BOOST_AUTO_TEST_CASE(buildTest_threshold_equal_to_5)
{
    Statistics statistics;
    istringstream bfcFile;
    DeBruijnGraph deBruijnGraph;
    unsigned short K1 = 2U;
    unsigned int threshold = 5U;
    vector<char> firstChars;
    vector<uint48> compressedTargets;
    SingleGraph singleGraph(deBruijnGraph, bfcFile, K1, threshold);
    bfcFile.str("AAA\t2\nGGG\t15\n");
    SingleGraphBuilder singleGraphBuilder(singleGraph, statistics, NULL);
    singleGraphBuilder.build(firstChars, compressedTargets);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 2);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 2);
    BOOST_CHECK_EQUAL(edge((SingleGraph::DeBruijnGraphVertex)0ULL, (SingleGraph::DeBruijnGraphVertex)0ULL, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge((SingleGraph::DeBruijnGraphVertex)1ULL, (SingleGraph::DeBruijnGraphVertex)1ULL, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge((SingleGraph::DeBruijnGraphVertex)0ULL, (SingleGraph::DeBruijnGraphVertex)0ULL, deBruijnGraph).first].counter_, 15U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge((SingleGraph::DeBruijnGraphVertex)1ULL, (SingleGraph::DeBruijnGraphVertex)1ULL, deBruijnGraph).first].counter_, 15U);
    BOOST_CHECK_EQUAL(compressedTargets.size(), 2);
    BOOST_CHECK_EQUAL(compressedTargets[0].v, 0ULL);
    BOOST_CHECK_EQUAL(compressedTargets[1].v, 1ULL);
    BOOST_CHECK_EQUAL(firstChars.size(), 4);
    BOOST_CHECK_EQUAL(firstChars[0], 'G');
    BOOST_CHECK_EQUAL(firstChars[1], 'C');
    BOOST_CHECK_EQUAL(firstChars[2], 0);
    BOOST_CHECK_EQUAL(firstChars[3], 0);
}

BOOST_AUTO_TEST_CASE(buildTest_K1_not_set_properly)
{
    Statistics statistics;
    istringstream bfcFile;
    DeBruijnGraph deBruijnGraph;
    unsigned short K1 = 4U;
    unsigned int threshold = 5U;
    vector<char> firstChars;
    vector<uint48> compressedTargets;
    SingleGraph singleGraph(deBruijnGraph, bfcFile, K1, threshold);
    bfcFile.str("AAA\t2\nGGG\t15\n");
    SingleGraphBuilder singleGraphBuilder(singleGraph, statistics, NULL);
    singleGraphBuilder.build(firstChars, compressedTargets);
    BOOST_CHECK_EQUAL(num_edges(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(num_vertices(deBruijnGraph), 0);
    BOOST_CHECK_EQUAL(compressedTargets.size(), 0);
    BOOST_CHECK_EQUAL(firstChars.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
