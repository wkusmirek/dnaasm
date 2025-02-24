/**
 * \file TestSingleGraph.cpp
 * \brief the C++ file with implementation of tests for SingleGraph class
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/SingleGraph.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestSingleGraph)

BOOST_AUTO_TEST_CASE(fillVectors_empty_input)
{
    DeBruijnGraph deBruijnGraph;
    vector<uint48> sources;
    vector<uint48> targets;
    vector<DeBruijnGraphEdgeProperties> counters;
    vector<char> firstChars;
    unsigned long long numOfVertices = 0ULL;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("");
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.fillVectors(sources, targets, counters, firstChars, numOfVertices);
    BOOST_CHECK_EQUAL(num_vertices(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(sources.size(), 0);
    BOOST_CHECK_EQUAL(targets.size(), 0);
    BOOST_CHECK_EQUAL(counters.size(), 0);
    BOOST_CHECK_EQUAL(firstChars.size(), 0);
    BOOST_CHECK_EQUAL(numOfVertices, 0ULL);
}

BOOST_AUTO_TEST_CASE(fillVectors_threshold_equal_to_0)
{
    DeBruijnGraph deBruijnGraph;
    vector<uint48> sources;
    vector<uint48> targets;
    vector<DeBruijnGraphEdgeProperties> counters;
    vector<char> firstChars;
    unsigned long long numOfVertices = 0ULL;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("AAA\t3\nCCC\t5\nTTT\t5");
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.fillVectors(sources, targets, counters, firstChars, numOfVertices);
    BOOST_CHECK_EQUAL(sources.size(), 6);
    BOOST_CHECK_EQUAL(sources[0].v, 0ULL);    //AA
    BOOST_CHECK_EQUAL(sources[1].v, 1ULL);    //TT
    BOOST_CHECK_EQUAL(sources[2].v, 2ULL);    //CC
    BOOST_CHECK_EQUAL(sources[3].v, 3ULL);    //GG
    BOOST_CHECK_EQUAL(sources[4].v, 1ULL);    //TT
    BOOST_CHECK_EQUAL(sources[5].v, 0ULL);    //AA
    BOOST_CHECK_EQUAL(targets.size(), 6);
    BOOST_CHECK_EQUAL(targets[0].v, 0ULL);    //AA
    BOOST_CHECK_EQUAL(targets[1].v, 1ULL);    //TT
    BOOST_CHECK_EQUAL(targets[2].v, 2ULL);    //CC
    BOOST_CHECK_EQUAL(targets[3].v, 3ULL);    //GG
    BOOST_CHECK_EQUAL(targets[4].v, 1ULL);    //TT
    BOOST_CHECK_EQUAL(targets[5].v, 0ULL);    //AA
    BOOST_CHECK_EQUAL(counters.size(), 6);
    BOOST_CHECK_EQUAL(counters[0].counter_, 3U);
    BOOST_CHECK_EQUAL(counters[1].counter_, 3U);
    BOOST_CHECK_EQUAL(counters[2].counter_, 5U);
    BOOST_CHECK_EQUAL(counters[3].counter_, 5U);
    BOOST_CHECK_EQUAL(counters[4].counter_, 5U);
    BOOST_CHECK_EQUAL(counters[5].counter_, 5U);
    BOOST_CHECK_EQUAL(firstChars.size(), 12);
    BOOST_CHECK_EQUAL(firstChars[0], 'A');
    BOOST_CHECK_EQUAL(firstChars[1], 'T');
    BOOST_CHECK_EQUAL(firstChars[2], 'C');
    BOOST_CHECK_EQUAL(firstChars[3], 'G');
    BOOST_CHECK_EQUAL(numOfVertices, 4ULL);
}

BOOST_AUTO_TEST_CASE(fillVectors_threshold_equal_to_4)
{
    DeBruijnGraph deBruijnGraph;
    vector<uint48> sources;
    vector<uint48> targets;
    vector<DeBruijnGraphEdgeProperties> counters;
    vector<char> firstChars;
    unsigned long long numOfVertices = 0ULL;
    unsigned short K1 = 2U;
    unsigned int threshold = 4U;
    istringstream in;
    in.str("AAA\t3\nCCG\t5\nCGT\t6\n");
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.fillVectors(sources, targets, counters, firstChars, numOfVertices);
    BOOST_CHECK_EQUAL(num_vertices(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(sources.size(), 4);
    BOOST_CHECK_EQUAL(sources[0].v, 0ULL);    //CC
    BOOST_CHECK_EQUAL(sources[1].v, 1ULL);    //CG
    BOOST_CHECK_EQUAL(sources[2].v, 1ULL);    //CG
    BOOST_CHECK_EQUAL(sources[3].v, 4ULL);    //AC
    BOOST_CHECK_EQUAL(targets.size(), 4);
    BOOST_CHECK_EQUAL(targets[0].v, 1ULL);    //CG
    BOOST_CHECK_EQUAL(targets[1].v, 2ULL);    //GG
    BOOST_CHECK_EQUAL(targets[2].v, 3ULL);    //GT
    BOOST_CHECK_EQUAL(targets[3].v, 1ULL);    //CG
    BOOST_CHECK_EQUAL(counters.size(), 4);
    BOOST_CHECK_EQUAL(counters[0].counter_, 5U);
    BOOST_CHECK_EQUAL(counters[1].counter_, 5U);
    BOOST_CHECK_EQUAL(counters[2].counter_, 6U);
    BOOST_CHECK_EQUAL(counters[3].counter_, 6U);
    BOOST_CHECK_EQUAL(firstChars.size(), 8);
    BOOST_CHECK_EQUAL(firstChars[0], 'C');
    BOOST_CHECK_EQUAL(firstChars[1], 'C');
    BOOST_CHECK_EQUAL(firstChars[2], 'G');
    BOOST_CHECK_EQUAL(firstChars[3], 'G');
    BOOST_CHECK_EQUAL(numOfVertices, 5ULL);
}

BOOST_AUTO_TEST_CASE(fillVectors_threshold_equal_to_0_sequences_in_occurrence_table_too_short)
{
    DeBruijnGraph deBruijnGraph;
    vector<uint48> sources;
    vector<uint48> targets;
    vector<DeBruijnGraphEdgeProperties> counters;
    vector<char> firstChars;
    unsigned long long numOfVertices = 0ULL;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("AA\t3");
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.fillVectors(sources, targets, counters, firstChars, numOfVertices);
    BOOST_CHECK_EQUAL(num_vertices(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(sources.size(), 0);
    BOOST_CHECK_EQUAL(targets.size(), 0);
    BOOST_CHECK_EQUAL(counters.size(), 0);
    BOOST_CHECK_EQUAL(firstChars.size(), 0);
    BOOST_CHECK_EQUAL(numOfVertices, 0ULL);
}

BOOST_AUTO_TEST_CASE(buildGraph_empty_vectors)
{
    DeBruijnGraph deBruijnGraph;
    vector<SingleGraph::DeBruijnGraphVertex> sources;
    vector<SingleGraph::DeBruijnGraphVertex> targets;
    vector<DeBruijnGraphEdgeProperties> counters;
    unsigned long long numOfVertices = 0ULL;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("");
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.buildGraph(sources, targets, counters, numOfVertices);
    BOOST_CHECK_EQUAL(num_vertices(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(singleGraph.getGraph()), 0);
}

BOOST_AUTO_TEST_CASE(buildGraph_numOfVertices_equal_to_zero)
{
    DeBruijnGraph deBruijnGraph;
    vector<SingleGraph::DeBruijnGraphVertex> sources(1);
    vector<SingleGraph::DeBruijnGraphVertex> targets(1);
    vector<DeBruijnGraphEdgeProperties> counters(1);
    unsigned long long numOfVertices = 0ULL;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("");
    sources[0] = 0ULL;
    targets[0] = 0ULL;
    counters[0].counter_ = 0ULL;
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.buildGraph(sources, targets, counters, numOfVertices);
    BOOST_CHECK_EQUAL(num_vertices(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(singleGraph.getGraph()), 0);
}

BOOST_AUTO_TEST_CASE(buildGraph_another_size_of_vectors)
{
    DeBruijnGraph deBruijnGraph;
    vector<SingleGraph::DeBruijnGraphVertex> sources;
    vector<SingleGraph::DeBruijnGraphVertex> targets(1);
    vector<DeBruijnGraphEdgeProperties> counters(1);
    unsigned long long numOfVertices = 1ULL;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("");
    targets[0] = 0ULL;
    counters[0].counter_ = 0ULL;
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.buildGraph(sources, targets, counters, numOfVertices);
    BOOST_CHECK_EQUAL(num_vertices(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(singleGraph.getGraph()), 0);
}

BOOST_AUTO_TEST_CASE(buildGraph_valid_graph)
{
    SingleGraph::DeBruijnGraphVertex v0 = 0;
    SingleGraph::DeBruijnGraphVertex v1 = 1;
    SingleGraph::DeBruijnGraphVertex v2 = 2;
    SingleGraph::DeBruijnGraphVertex v3 = 3;
    SingleGraph::DeBruijnGraphVertex v4 = 4;
    SingleGraph::DeBruijnGraphVertex v5 = 5;
    DeBruijnGraph deBruijnGraph;
    vector<SingleGraph::DeBruijnGraphVertex> sources(5);
    vector<SingleGraph::DeBruijnGraphVertex> targets(5);
    vector<DeBruijnGraphEdgeProperties> counters(5);
    unsigned long long numOfVertices = 6ULL;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("");
    sources[0] = v0;
    sources[1] = v1;
    sources[2] = v1;
    sources[3] = v3;
    sources[4] = v4;
    targets[0] = v1;
    targets[1] = v2;
    targets[2] = v3;
    targets[3] = v4;
    targets[4] = v5;
    counters[0].counter_ = 0U;
    counters[1].counter_ = 1U;
    counters[2].counter_ = 2U;
    counters[3].counter_ = 3U;
    counters[4].counter_ = 4U;
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.buildGraph(sources, targets, counters, numOfVertices);
    BOOST_CHECK_EQUAL(num_vertices(singleGraph.getGraph()), 6);
    BOOST_CHECK_EQUAL(num_edges(singleGraph.getGraph()), 5);
    BOOST_CHECK_EQUAL(edge(v0, v1, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v2, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v1, v3, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v3, v4, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(edge(v4, v5, deBruijnGraph).second, true);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v0, v1, deBruijnGraph).first].counter_, 0U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v2, deBruijnGraph).first].counter_, 1U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v1, v3, deBruijnGraph).first].counter_, 2U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v3, v4, deBruijnGraph).first].counter_, 3U);
    BOOST_CHECK_EQUAL(deBruijnGraph[edge(v4, v5, deBruijnGraph).first].counter_, 4U);
}

BOOST_AUTO_TEST_CASE(convertVectors_all_vectors_empty)
{
    DeBruijnGraph deBruijnGraph;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("");
    vector<uint48> inputSources;
    vector<uint48> inputTargets;
    vector<SingleGraph::DeBruijnGraphVertex> outputSources;
    vector<SingleGraph::DeBruijnGraphVertex> outputTargets;
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.convertVectors(inputSources, inputTargets, outputSources, outputTargets);
    BOOST_CHECK_EQUAL(inputSources.size(), 0);
    BOOST_CHECK_EQUAL(inputTargets.size(), 0);
    BOOST_CHECK_EQUAL(outputSources.size(), 0);
    BOOST_CHECK_EQUAL(outputTargets.size(), 0);
}

BOOST_AUTO_TEST_CASE(convertVectors_input_vectors_not_empty_output_vectors_empty)
{
    DeBruijnGraph deBruijnGraph;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("");
    vector<uint48> inputSources(2);
    vector<uint48> inputTargets(2);
    inputSources[0].v = 0ULL;
    inputSources[1].v = 1ULL;
    inputTargets[0].v = 2ULL;
    inputTargets[1].v = 3ULL;
    vector<SingleGraph::DeBruijnGraphVertex> outputSources;
    vector<SingleGraph::DeBruijnGraphVertex> outputTargets;
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.convertVectors(inputSources, inputTargets, outputSources, outputTargets);
    BOOST_CHECK_EQUAL(inputSources.size(), 2);
    BOOST_CHECK_EQUAL(inputTargets.size(), 2);
    BOOST_CHECK_EQUAL(outputSources.size(), 2);
    BOOST_CHECK_EQUAL(outputTargets.size(), 2);
    BOOST_CHECK_EQUAL(inputSources[0].v, 0ULL);
    BOOST_CHECK_EQUAL(inputSources[1].v, 1ULL);
    BOOST_CHECK_EQUAL(inputTargets[0].v, 2ULL);
    BOOST_CHECK_EQUAL(inputTargets[1].v, 3ULL);
    BOOST_CHECK_EQUAL(outputSources[0], 0ULL);
    BOOST_CHECK_EQUAL(outputSources[1], 1ULL);
    BOOST_CHECK_EQUAL(outputTargets[0], 2ULL);
    BOOST_CHECK_EQUAL(outputTargets[1], 3ULL);
}

BOOST_AUTO_TEST_CASE(convertVectors_input_vectors_not_empty_output_vectors_not_empty)
{
    DeBruijnGraph deBruijnGraph;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("");
    vector<uint48> inputSources(2);
    vector<uint48> inputTargets(2);
    inputSources[0].v = 0ULL;
    inputSources[1].v = 1ULL;
    inputTargets[0].v = 2ULL;
    inputTargets[1].v = 3ULL;
    vector<SingleGraph::DeBruijnGraphVertex> outputSources(4);
    vector<SingleGraph::DeBruijnGraphVertex> outputTargets(8);
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.convertVectors(inputSources, inputTargets, outputSources, outputTargets);
    BOOST_CHECK_EQUAL(inputSources.size(), 2);
    BOOST_CHECK_EQUAL(inputTargets.size(), 2);
    BOOST_CHECK_EQUAL(outputSources.size(), 2);
    BOOST_CHECK_EQUAL(outputTargets.size(), 2);
    BOOST_CHECK_EQUAL(inputSources[0].v, 0ULL);
    BOOST_CHECK_EQUAL(inputSources[1].v, 1ULL);
    BOOST_CHECK_EQUAL(inputTargets[0].v, 2ULL);
    BOOST_CHECK_EQUAL(inputTargets[1].v, 3ULL);
    BOOST_CHECK_EQUAL(outputSources[0], 0ULL);
    BOOST_CHECK_EQUAL(outputSources[1], 1ULL);
    BOOST_CHECK_EQUAL(outputTargets[0], 2ULL);
    BOOST_CHECK_EQUAL(outputTargets[1], 3ULL);
}

BOOST_AUTO_TEST_CASE(buildSequencesVector_empty_input)
{
    DeBruijnGraph deBruijnGraph;
    vector<bitset<2*MAX_KMER_LENGTH>> sequences;
    vector<uint48> targets;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("");
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.buildSequencesVector(sequences, targets);
    BOOST_CHECK_EQUAL(num_vertices(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(targets.size(), 0);
    BOOST_CHECK_EQUAL(sequences.size(), 0);
}

BOOST_AUTO_TEST_CASE(buildSequencesVector_threshold_equal_to_0)
{
    DeBruijnGraph deBruijnGraph;
    vector<bitset<2*MAX_KMER_LENGTH>> sequences(4);
    vector<uint48> targets(6);
    targets[0].v = 0ULL;
    targets[1].v = 1ULL;
    targets[2].v = 2ULL;
    targets[3].v = 3ULL;
    targets[4].v = 1ULL;
    targets[5].v = 0ULL;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("AAA\t3\nCCC\t5\nTTT\t5");
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.buildSequencesVector(sequences, targets);
    BOOST_CHECK_EQUAL(targets.size(), 6);
    BOOST_CHECK_EQUAL(targets[0].v, 0ULL);    //AA
    BOOST_CHECK_EQUAL(targets[1].v, 1ULL);    //TT
    BOOST_CHECK_EQUAL(targets[2].v, 2ULL);    //CC
    BOOST_CHECK_EQUAL(targets[3].v, 3ULL);    //GG
    BOOST_CHECK_EQUAL(targets[4].v, 1ULL);    //TT
    BOOST_CHECK_EQUAL(targets[5].v, 0ULL);    //AA
    BOOST_CHECK_EQUAL(sequences.size(), 4);
    BOOST_CHECK_EQUAL(sequences[0], bitset<2*MAX_KMER_LENGTH>("0000"));    //AA
    BOOST_CHECK_EQUAL(sequences[1], bitset<2*MAX_KMER_LENGTH>("1111"));    //TT
    BOOST_CHECK_EQUAL(sequences[2], bitset<2*MAX_KMER_LENGTH>("0101"));    //CC
    BOOST_CHECK_EQUAL(sequences[3], bitset<2*MAX_KMER_LENGTH>("1010"));    //GG
}

BOOST_AUTO_TEST_CASE(buildSequencesVector_threshold_equal_to_4)
{
    DeBruijnGraph deBruijnGraph;
    vector<bitset<2*MAX_KMER_LENGTH>> sequences(4);
    vector<uint48> targets(4);
    targets[0].v = 1ULL;
    targets[1].v = 2ULL;
    targets[2].v = 3ULL;
    targets[3].v = 1ULL;
    unsigned short K1 = 2U;
    unsigned int threshold = 4U;
    istringstream in;
    in.str("AAA\t3\nCCG\t5\nCGT\t6\n");
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.buildSequencesVector(sequences, targets);
    BOOST_CHECK_EQUAL(num_vertices(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(targets.size(), 4);
    BOOST_CHECK_EQUAL(targets[0].v, 1ULL);    //CG
    BOOST_CHECK_EQUAL(targets[1].v, 2ULL);    //GG
    BOOST_CHECK_EQUAL(targets[2].v, 3ULL);    //GT
    BOOST_CHECK_EQUAL(targets[3].v, 1ULL);    //CG
    BOOST_CHECK_EQUAL(sequences.size(), 4);
    BOOST_CHECK_EQUAL(sequences[0], bitset<2*MAX_KMER_LENGTH>("0000"));    //undefined
    BOOST_CHECK_EQUAL(sequences[1], bitset<2*MAX_KMER_LENGTH>("1001"));    //CG
    BOOST_CHECK_EQUAL(sequences[2], bitset<2*MAX_KMER_LENGTH>("1010"));    //GG
    BOOST_CHECK_EQUAL(sequences[3], bitset<2*MAX_KMER_LENGTH>("1110"));    //GT
}

BOOST_AUTO_TEST_CASE(buildSequencesVector_threshold_equal_to_0_sequences_in_occurrence_table_too_short)
{
    DeBruijnGraph deBruijnGraph;
    vector<bitset<2*MAX_KMER_LENGTH>> sequences;
    vector<uint48> targets;
    unsigned short K1 = 2U;
    unsigned int threshold = 0U;
    istringstream in;
    in.str("AA\t3");
    SingleGraph singleGraph(deBruijnGraph, in, K1, threshold);
    singleGraph.buildSequencesVector(sequences, targets);
    BOOST_CHECK_EQUAL(num_vertices(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(singleGraph.getGraph()), 0);
    BOOST_CHECK_EQUAL(targets.size(), 0);
    BOOST_CHECK_EQUAL(sequences.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
