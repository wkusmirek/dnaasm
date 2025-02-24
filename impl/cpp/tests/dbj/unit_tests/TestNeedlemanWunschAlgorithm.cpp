/**
 * \file TestNeedlemanWunschAlgorithm.cpp
 * \brief the C++ file with implementation of tests for NeedlemanWunschAlgorithm class
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/NeedlemanWunschAlgorithm.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestNeedlemanWunschAlgorithm)

BOOST_AUTO_TEST_CASE(alignTest_one_same_sign_with_ends_penalties)
{
    string sequence = "A";
    string reference = "A";
    short int d = -2;
    short int substitutionMatrix[4][4] = {{2, -1, -1, -1}, {-1, 2, -1, -1}, {-1, -1, 2, -1}, {-1, -1, -1, 2}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(true);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "A");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "A");
}

BOOST_AUTO_TEST_CASE(alignTest_same_sequence_with_ends_penalties)
{
    string sequence = "AACTTTAC";
    string reference = "AACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(true);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "AACTTTAC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(alignTest_1_substitution_in_middle_with_ends_penalties)
{
    string sequence = "AACTCTAC";
    string reference = "AACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(true);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "AACTCTAC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(alignTest_1_del_in_middle_sequence_with_ends_penalties)
{
    string sequence = "AACTTAC";
    string reference = "AACTCTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -3, -3, -3}, {-3, 1, -3, -3}, {-3, -3, 1, -3}, {-3, -3, -3, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(true);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "AACT-TAC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AACTCTAC");
}

BOOST_AUTO_TEST_CASE(alignTest_2_del_in_middle_reference_with_ends_penalties)
{
    string sequence = "AACTCTAC";
    string reference = "AACTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -3, -3, -3}, {-3, 1, -3, -3}, {-3, -3, 1, -3}, {-3, -3, -3, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(true);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "AACTCTAC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AA--CTAC");
}

BOOST_AUTO_TEST_CASE(alignTest_1_del_in_middle_reference_with_ends_penalties)
{
    string sequence = "AACTCTAC";
    string reference = "AACTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -3, -3, -3}, {-3, 1, -3, -3}, {-3, -3, 1, -3}, {-3, -3, -3, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(true);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "AACTCTAC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AACT-TAC");
}

BOOST_AUTO_TEST_CASE(alignTest_2_del_in_middle_sequence_with_ends_penalties)
{
    string sequence = "AACTAC";
    string reference = "AACTCTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -3, -3, -3}, {-3, 1, -3, -3}, {-3, -3, 1, -3}, {-3, -3, -3, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(true);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "AA--CTAC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AACTCTAC");
}

BOOST_AUTO_TEST_CASE(alignTest_1_del_in_middle_different_madtrix_d_with_ends_penalties)
{
    string sequence = "GAATTC";
    string reference = "GATTA";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{10, -3, -1, -4}, {-3, 9, -5, 0}, {-1, -5, 7, -3}, {-4, 0, -3, 8}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(true);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "GAATTC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "G-ATTA");
}

BOOST_AUTO_TEST_CASE(alignTest_1_substitution_in_end_with_ends_penalties)
{
    string sequence = "TACTTTAC";
    string reference = "AACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(true);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "TACTTTAC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_genome_same_sign_without_ends_penalties)
{
    string sequence = "T";
    string reference = "T";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(false);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "T");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "T");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_genome_no_errors_without_ends_penalties)
{
    string sequence = "TTTACAAC";
    string reference = "AACTTTACAACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(false);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "---TTTACAAC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AACTTTACAAC");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_genome_substitution_error_without_ends_penalties)
{
    string sequence = "TTTCCAAC";
    string reference = "AACTTTACAACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(false);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "---TTTCCAAC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AACTTTACAAC");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_genome_del_in_sequence_begin_without_ends_penalties)
{
    string sequence = "TTTAC";
    string reference = "AACTTTACAACTTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(false);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "---TTTAC");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_genome_del_in_sequence_without_ends_penalties)
{
    string sequence = "CGTTTACAACTTA";
    string reference = "AACTTACGTGTCTTACAACTTACGTGTCTTAC";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(false);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "---------CGTTTACAACTTA");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "AACTTACGTGTCTTACAACTTA");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_genome_del_in_reference_without_ends_penalties)
{
    string sequence = "GGGAACTTTACGGG";
    string reference = "GGGGGAATACGGGGGGAATACG";
    short int d = -2;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(false);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "--GGGAACTTTACGGG");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "GGGGGAA---TACGGG");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_sub_in_end_test_mod_ref_len_without_ends_penalties)
{
    string sequence = "GGGCCCAAACTT";
    string reference = "TTTGGGCCCAAATTTGGGCCCAAA";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(false);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "---GGGCCCAAACTT");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_same_sub_in_both_end_without_ends_penalties)
{
    string sequence = "CTTGGGCCCAAACTT";
    string reference = "TTTGGGCCCAAATTTGGGCCCAAA";
    short int d = -3;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(false);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "CTTGGGCCCAAACTT");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_CASE(alignTest_circular_another_sub_in_both_end_without_ends_penalties)
{
    string sequence = "ATTGGGCCCAAACTT";
    string reference = "TTTGGGCCCAAATTTGGGCCCAAA";
    short int d = -5;
    short int substitutionMatrix[4][4] = {{1, -1, -1, -1}, {-1, 1, -1, -1}, {-1, -1, 1, -1}, {-1, -1, -1, 1}};
    NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence, reference, d, substitutionMatrix, NULL, 0U, 0U);
    needlemanWunschAlgorithm.align(false);
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getXStrOut(), "ATTGGGCCCAAACTT");
    BOOST_CHECK_EQUAL(needlemanWunschAlgorithm.getYStrOut(), "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_SUITE_END()
