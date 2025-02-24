/**
 * \file TestHirschbergAlgorithm.cpp
 * \brief the C++ file with implementation of tests for HirschbergAlgorithm class
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/HirschbergAlgorithm.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestHirschbergAlgorithm)

BOOST_AUTO_TEST_CASE(align_wiki_test)
{
    string xStr = "AGTACGCA";
    string yStr = "TATGC";
    short int d = -2;
    short int substitutionMatrix[4][4] = {{2, -1, -1, -1}, {-1, 2, -1, -1}, {-1, -1, 2, -1}, {-1, -1, -1, 2}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, true);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "AGTACGCA");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "--TATGC-");
}

BOOST_AUTO_TEST_CASE(align_same_str)
{
    string xStr = "AACTTTAC";
    string yStr = "AACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, true);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "AACTTTAC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(align_1_substitution_in_middle)
{
    string xStr = "AACTCTAC";
    string yStr = "AACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, true);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "AACTCTAC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(align_1_del_in_middle_xStr)
{
    string xStr = "AACTTAC";
    string yStr = "AACTCTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -3, -3, -3}, {-3, 1, -3, -3}, {-3, -3, 1, -3}, {-3, -3, -3, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, true);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "AACT-TAC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AACTCTAC");
}

BOOST_AUTO_TEST_CASE(align_2_del_in_middle_yStr)
{
    string xStr = "AACTCTAC";
    string yStr = "AACTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -3, -3, -3}, {-3, 1, -3, -3}, {-3, -3, 1, -3}, {-3, -3, -3, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, true);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "AACTCTAC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AA--CTAC");
}

BOOST_AUTO_TEST_CASE(align_2_del_in_middle_xStr)
{
    string xStr = "AACTAC";
    string yStr = "AACTGGAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -3, -3, -3}, {-3, 1, -3, -3}, {-3, -3, 1, -3}, {-3, -3, -3, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, true);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "AACT--AC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AACTGGAC");
}

BOOST_AUTO_TEST_CASE(align_1_del_in_middle_yStr)
{
    string xStr = "AACTCTAC";
    string yStr = "AACTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -3, -3, -3}, {-3, 1, -3, -3}, {-3, -3, 1, -3}, {-3, -3, -3, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, true);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "AACTCTAC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AACT-TAC");
}

BOOST_AUTO_TEST_CASE(align_1_del_in_middle_different_madtrix_d)
{
    string xStr = "GAATTC";
    string yStr = "GATTA";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{10, -3, -1, -4}, {-3, 9, -5, 0}, {-1, -5, 7, -3}, {-4, 0, -3, 8}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, true);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "GAATTC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "G-ATTA");
}

BOOST_AUTO_TEST_CASE(align_1_substitution_in_end)
{
    string xStr = "TACTTTAC";
    string yStr = "AACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, true);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "TACTTTAC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(align_circular_genome_without_errors)
{
    string xStr = "TTTACAAC";
    string yStr = "AACTTTACAACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, false);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "---TTTACAAC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AACTTTACAAC");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_genome_substitution_error)
{
    string xStr = "TTTCCAAC";
    string yStr = "AACTTTACAACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, false);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "---TTTCCAAC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AACTTTACAAC");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_genome_del_in_xStr_begin)
{
    string xStr = "TTTAC";
    string yStr = "AACTTTACAACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, false);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "---TTTAC");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_genome_del_in_xStr)
{
    string xStr = "CGTTTACAACTTA";
    string yStr = "AACTTACGTGTCTTACAACTTACGTGTCTTAC";
    short int d = -1;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, false);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "--------CGT-TTACAACTTA");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "AACTTACGTGTCTTACAACTTA");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_genome_del_in_yStr)   //this test shows weakness of alignment circular sequences using Hirschberg and Needelman-Wunsch algorithms witohout end panalties
{
    string xStr = "GGGAACTTTACGGG";
    string yStr = "GGGGGAATACGGGGGGAATACG";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, false);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "--GGGATTACGGG");    //--GGGAACTTTACGGG
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "GGGGGAATACGGG");    //GGGGGAA---TACGGG
}

BOOST_AUTO_TEST_CASE(alignTest_circular_sub_in_end_test_mod_ref_len)
{
    string xStr = "GGGCCCAAACTT";
    string yStr = "TTTGGGCCCAAATTTGGGCCCAAA";
    short int d = -2;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, false);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "---GGGCCCAAACTT");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_same_sub_in_both_end)
{
    string xStr = "CTTGGGCCCAAACTT";
    string yStr = "TTTGGGCCCAAATTTGGGCCCAAA";
    short int d = -3;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, false);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "CTTGGGCCCAAACTT");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_another_sub_in_both_end)
{
    string xStr = "ATTGGGCCCAAACTT";
    string yStr = "TTTGGGCCCAAATTTGGGCCCAAA";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    HirschbergAlgorithm::OutStrings resultStrings;
    HirschbergAlgorithm hirschbergAlgorithm(d, substitutionMatrix, NULL, 0U, 0U);
    resultStrings = hirschbergAlgorithm.align(xStr, yStr, false);
    BOOST_CHECK_EQUAL(resultStrings.xStrOut, "ATTGGGCCCAAACTT");
    BOOST_CHECK_EQUAL(resultStrings.yStrOut, "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_SUITE_END()
