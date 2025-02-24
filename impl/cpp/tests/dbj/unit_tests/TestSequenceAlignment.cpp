/**
 * \file TestSequenceAlignment.cpp
 * \brief the C++ file with implementation of tests for SequenceAlignment class
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/SequenceAlignment.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestSequenceAlignment)

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_empty_inputs)
{
    string sequence = "";
    string reference = "";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_small_genome_no_errors)
{
    string sequence = "T";
    string reference = "T";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "T");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "T");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_genome_no_errors)
{
    string sequence = "TTTACAAC";
    string reference = "TTTACAAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "TTTACAAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "TTTACAAC");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_genome_substitution_error)
{
    string sequence = "AACTTTCC";
    string reference = "AACTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 7U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "AACTTTCC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_genome_del_in_sequence_begin)
{
    string sequence = "TTTAC";
    string reference = "CTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "CT");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "-TTTAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "CTTTAC");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_genome_del_in_sequence_end)
{
    string sequence = "CTTTA";
    string reference = "CTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "AC");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CTTTA-");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "CTTTAC");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_genome_del_in_reference_begin)
{
    string sequence = "CTTTAC";
    string reference = "TTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "CT");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CTTTAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "-TTTAC");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_genome_del_in_reference_end)
{
    string sequence = "CTTTAC";
    string reference = "CTTTA";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "AC");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CTTTAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "CTTTA-");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_genome_del_in_sequence)
{
    string sequence = "CGTTTCA";
    string reference = "CGTTTACA";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "TA");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CGTTT-CA");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "CGTTTACA");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_genome_del_in_reference)
{
    string sequence = "CGTTTACA";
    string reference = "CGTTTCA";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "TA");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CGTTTACA");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "CGTTT-CA");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_linear_sub_in_both_ends)
{
    string sequence = "CGGCCCAAATTA";
    string reference = "GGGCCCAAATTT";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 2);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "G");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(mismatches[1].getOriginalRefIdx(), 12U);
    BOOST_CHECK_EQUAL(mismatches[1].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CGGCCCAAATTA");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "GGGCCCAAATTT");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_circular_empty_inputs)
{
    string sequence = "";
    string reference = "";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_circular_genome_no_errors)
{
    string sequence = "TTTACAAC";
    string reference = "AACTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "---TTTACAAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "AACTTTACAAC");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_circular_genome_substitution_error)
{
    string sequence = "TTTCCAAC";
    string reference = "AACTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 7U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "---TTTCCAAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "AACTTTACAAC");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_circular_genome_del_in_sequence_begin)
{
    string sequence = "TTTAC";
    string reference = "AACTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "---TTTAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_circular_genome_del_in_sequence)
{
    string sequence = "CGTTTACAACTTA";
    string reference = "AACTTACGTGTCTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 3);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 10U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "G");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(mismatches[1].getOriginalRefIdx(), 11U);
    BOOST_CHECK_EQUAL(mismatches[1].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceMismatch(), "G");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(mismatches[2].getOriginalRefIdx(), 12U);
    BOOST_CHECK_EQUAL(mismatches[2].getReferenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[2].getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[2].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "---------CGTTTACAACTTA");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "AACTTACGTGTCTTACAACTTA");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_circular_genome_del_in_reference)
{
    string sequence = "GGGAACTTTACGGG";
    string reference = "GGGGGAATACG";
    string sequenceId = "seqId";
    short int d = -1;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 7U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "ACTT");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "--GGGAACTTTACGGG");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "GGGGGAA---TACGGG");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_circular_sub_in_end_test_mod_ref_len)
{
    string sequence = "GGGCCCAAACTT";
    string reference = "TTTGGGCCCAAA";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "---GGGCCCAAACTT");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_circular_same_sub_in_both_end)
{
    string sequence = "CTTGGGCCCAAACTT";
    string reference = "TTTGGGCCCAAA";
    string sequenceId = "seqId";
    short int d = -3;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 2);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(mismatches[1].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[1].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CTTGGGCCCAAACTT");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_CASE(alignSeqNeeWunAlgTest_circular_another_sub_in_both_end)
{
    string sequence = "ATTGGGCCCAAACTT";
    string reference = "TTTGGGCCCAAA";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqNeeWunAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 2);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(mismatches[1].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[1].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "ATTGGGCCCAAACTT");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "TTTGGGCCCAAATTT");
}


// alignment with Hirschberg algorithm below

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_empty_inputs)
{
    string sequence = "";
    string reference = "";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_small_genome_no_errors)
{
    string sequence = "T";
    string reference = "T";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "T");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "T");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_genome_no_errors)
{
    string sequence = "TTTACAAC";
    string reference = "TTTACAAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "TTTACAAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "TTTACAAC");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_genome_substitution_error)
{
    string sequence = "AACTTTCC";
    string reference = "AACTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 7U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "AACTTTCC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_genome_del_in_sequence_begin)
{
    string sequence = "TTTAC";
    string reference = "CTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "CT");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "-TTTAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "CTTTAC");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_genome_del_in_sequence_end)
{
    string sequence = "CTTTA";
    string reference = "CTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "AC");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CTTTA-");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "CTTTAC");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_genome_del_in_reference_begin)
{
    string sequence = "CTTTAC";
    string reference = "TTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "CT");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CTTTAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "-TTTAC");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_genome_del_in_reference_end)
{
    string sequence = "CTTTAC";
    string reference = "CTTTA";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "AC");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CTTTAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "CTTTA-");
}


BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_genome_del_in_sequence)
{
    string sequence = "CGTTTCA";
    string reference = "CGTTTACA";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "TA");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CGTTT-CA");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "CGTTTACA");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_genome_del_in_reference)
{
    string sequence = "CGTTTACA";
    string reference = "CGTTTCA";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "TA");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CGTTTACA");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "CGTTT-CA");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_linear_sub_in_both_ends)
{
    string sequence = "CGGCCCAAATTA";
    string reference = "GGGCCCAAATTT";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(false);
    BOOST_CHECK_EQUAL(mismatches.size(), 2);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "G");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(mismatches[1].getOriginalRefIdx(), 12U);
    BOOST_CHECK_EQUAL(mismatches[1].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CGGCCCAAATTA");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "GGGCCCAAATTT");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_circular_empty_inputs)
{
    string sequence = "";
    string reference = "";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_circular_genome_no_errors)
{
    string sequence = "TTTACAAC";
    string reference = "AACTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "---TTTACAAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "AACTTTACAAC");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_circular_genome_substitution_error)
{
    string sequence = "TTTCCAAC";
    string reference = "AACTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 7U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "---TTTCCAAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "AACTTTACAAC");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_circular_genome_del_in_sequence_begin)
{
    string sequence = "TTTAC";
    string reference = "AACTTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 0);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "---TTTAC");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "AACTTTAC");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_circular_genome_del_in_sequence)
{
    string sequence = "CGTTTACAACTTA";
    string reference = "AACTTACGTGTCTTAC";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 2);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 10U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "G");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(mismatches[1].getOriginalRefIdx(), 12U);
    BOOST_CHECK_EQUAL(mismatches[1].getReferenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "------CGTTTACAACTTA");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "AACTTACGTGTCCAACTTA");
}

//this test shows weakness of alignment circular sequences using Hirschberg and Needelman-Wunsch algorithms witohout end panalties
BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_circular_genome_del_in_reference)
{
    string sequence = "GGGAACTTTACGGG";
    string reference = "GGGGGAATACG";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 7U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "--GGGATTACGGG");    //--GGGAACTTTACGGG---------
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "GGGGGAATACGGG");    //GGGGGAA---TACGGGGGGAATACG
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_circular_sub_in_end_test_mod_ref_len)
{
    string sequence = "GGGCCCAAACTT";
    string reference = "TTTGGGCCCAAA";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 1);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "---GGGCCCAAACTT");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_circular_same_sub_in_both_end)
{
    string sequence = "CTTGGGCCCAAACTT";
    string reference = "TTTGGGCCCAAA";
    string sequenceId = "seqId";
    short int d = -3;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 2);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(mismatches[1].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[1].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "CTTGGGCCCAAACTT");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_CASE(alignSeqHirAlgTest_circular_another_sub_in_both_end)
{
    string sequence = "ATTGGGCCCAAACTT";
    string reference = "TTTGGGCCCAAA";
    string sequenceId = "seqId";
    short int d = -5;
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d, substitutionMatrixValues, NULL, 0U, 0U);
    vector<Mismatch> mismatches = sequenceAlignment.alignSeqHirAlg(true);
    BOOST_CHECK_EQUAL(mismatches.size(), 2);
    BOOST_CHECK_EQUAL(mismatches[0].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[0].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatches[0].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(mismatches[1].getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatches[1].getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatches[1].getSequenceId(), sequenceId);
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputSequence(),  "ATTGGGCCCAAACTT");
    BOOST_CHECK_EQUAL(sequenceAlignment.getOutputReference(), "TTTGGGCCCAAATTT");
}

BOOST_AUTO_TEST_SUITE_END()
