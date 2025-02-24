/**
 * \file TestSmithWatermanAligner.cpp
 * \brief the C++ file with implementation of tests for alignment functor
 * based on Smith-Waterman algorithm
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/olc/common.hpp"
#include "../../../src/olc/OverlapGraph.hpp"
#include "../../../src/olc/OvlpGraphBuilder.hpp"
#include "../../../src/olc/SmithWatermanAligner.hpp"

using namespace dnaasm::olc;

BOOST_AUTO_TEST_SUITE(TestSmithWatermanAligner)

BOOST_AUTO_TEST_CASE(alignEmptyStrings_test)
{
    LongRead r1 = "";
    LongRead r2 = "";
    SmithWatermanAligner aligner(1,-1, -1);
    auto result = aligner(r1, r2);
    BOOST_CHECK_EQUAL(result.score, 0);
    BOOST_CHECK_EQUAL(result.orient, Orientation::EQ);
}

BOOST_AUTO_TEST_CASE(basicAlignTest_01)
{
    LongRead r1 = "TGTTACGG";
    LongRead r2 = "GGTTGACTA";
    SmithWatermanAligner aligner(3,-3, -2);
    auto result = aligner(r1, r2);
    BOOST_CHECK_EQUAL(result.score, 13);
    BOOST_CHECK_EQUAL(result.orient, Orientation::EQ);
}

BOOST_AUTO_TEST_CASE(basicAlignTest_02)
{
    LongRead r1 = "TAAAGTGG";
    LongRead r2 = "AGTCGG";
    SmithWatermanAligner aligner(1,-1, -1);
    auto result = aligner(r1, r2);
    BOOST_CHECK_EQUAL(result.score, 4);
    BOOST_CHECK_EQUAL(result.orient, Orientation::LR);
}

BOOST_AUTO_TEST_CASE(basicAlignTest_03)
{
    LongRead r1 = "A";
    LongRead r2 = "A";
    SmithWatermanAligner aligner(1,-1, -1);
    auto result = aligner(r1, r2);
    BOOST_CHECK_EQUAL(result.score, 1);
    BOOST_CHECK_EQUAL(result.orient, Orientation::EQ);
}

BOOST_AUTO_TEST_CASE(basicAlignTest_04)
{
    LongRead r1 = "TCGG";
    LongRead r2 = "AGCG";
    SmithWatermanAligner aligner(1,-1, -1);
    auto result = aligner(r1, r2);
    BOOST_CHECK_EQUAL(result.score, 2);
    BOOST_CHECK_EQUAL(result.orient, Orientation::RL);
}

BOOST_AUTO_TEST_CASE(basicAlignTest_05)
{
    LongRead r1 = "CGTTCTA";
    LongRead r2 = "AACGTTGG";
    SmithWatermanAligner aligner(5,-3, -4);
    auto result = aligner(r1, r2);
    BOOST_CHECK_EQUAL(result.score, 20);
    BOOST_CHECK_EQUAL(result.orient, Orientation::RL);
}

BOOST_AUTO_TEST_SUITE_END()
