/**
 * \file TestOvlpGraphBuilder.cpp
 * \brief the C++ file with implementation of tests for Overlap graph build process
 *
 */

#include <boost/test/unit_test.hpp>
#include <fstream>
#include <memory>

#include "../../../src/olc/common.hpp"
#include "../../../src/olc/OverlapGraph.hpp"
#include "../../../src/olc/OvlpGraphBuilder.hpp"
#include "../../../src/olc/SmithWatermanAligner.hpp"

using namespace dnaasm::olc;

BOOST_AUTO_TEST_SUITE(TestOvlpGraphBuilder)

BOOST_AUTO_TEST_CASE(SimpleGraphBuildTest01)
{
    HashObj hashObj;
    //no similarity at all
    std::vector<LongRead> readVec = {
        "AAAA",
        "CCCC",
        "TTTT",
        "GGGG"
    };

    std::unique_ptr<Aligner<LocalAlignment>> aligner(new SmithWatermanAligner(1, -1, -1));
    OvlpGraphBuilder ovlpGraphBuilder(hashObj, readVec, aligner);
    auto ovlpGraph = ovlpGraphBuilder.buildGraph(1, 4, 0.0f, 1, nullptr);

    BOOST_CHECK_EQUAL(boost::num_edges(ovlpGraph), 0);
}

BOOST_AUTO_TEST_CASE(FullGraphBuildTest02)
{
    HashObj hashObj;
    std::vector<LongRead> readVec = {
        "CGTACG",
        "TACGTA",
        "ACGTAC",
        "GTACGT",
        "GTACGA",
        "TACGAT"
    };

    std::unique_ptr<Aligner<LocalAlignment>> aligner(new SmithWatermanAligner(1, -1, -1));
    OvlpGraphBuilder ovlpGraphBuilder(hashObj, readVec, aligner);
    auto ovlpGraph = ovlpGraphBuilder.buildGraph(2, 5, 0.0f, 1, nullptr);

    auto numOfVertices = boost::num_vertices(ovlpGraph);

    BOOST_CHECK_EQUAL(boost::num_edges(ovlpGraph), numOfVertices*(numOfVertices-1) / 2);
}

BOOST_AUTO_TEST_CASE(BuildGraphLongOverlapsNoMinHash01)
{
    HashObj hashObj;
    std::vector<LongRead> readVec = {
        "CGTACG",
        "TACGTA",
        "ACGTAC",
        "GTACGT",
        "GTACGA",
        "TACGAT"
    };
    std::unique_ptr<Aligner<LocalAlignment>> aligner(new SmithWatermanAligner(1, 0, 0));
    OvlpGraphBuilder ovlpGraphBuilder(hashObj, readVec, aligner);
    //more than 5 symbols match => add edge
    auto ovlpGraph = ovlpGraphBuilder.buildGraph(2, 5, 0.0f, 5, nullptr);

    BOOST_CHECK_EQUAL(boost::num_edges(ovlpGraph), 10);
}

BOOST_AUTO_TEST_CASE(BuildGraphLongOverlapsMinHash01)
{
    HashObj hashObj;
    std::vector<LongRead> readVec = {
        "CGTACG",
        "TACGTA",
        "ACGTAC",
        "GTACGT",
        "GTACGA",
        "TACGAT"
    };

    std::unique_ptr<Aligner<LocalAlignment>> aligner(new SmithWatermanAligner(1, 0, 0));
    OvlpGraphBuilder ovlpGraphBuilder(hashObj, readVec, aligner);
    //more than 5 symbols match => add edge
    auto ovlpGraph = ovlpGraphBuilder.buildGraph(2, 5, 0.2f, 5, nullptr);

    BOOST_CHECK_EQUAL(boost::num_edges(ovlpGraph), 10);
}

BOOST_AUTO_TEST_SUITE_END()
