/**
 * \file TestMismatch.cpp
 * \brief the C++ file with implementation of tests for Mismatch class
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/Mismatch.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestMismatch)

BOOST_AUTO_TEST_CASE(appointCircularTest_no_errors)
{
    string reference = "GGGAACTTTACGGG";
    string sequence =  "---AACTTTAC---";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 4U;
    unsigned int refIdx = 3U;
    unsigned int seqIdx = 3U;
    Mismatch mismatch;
    mismatch.appointCircular(originalRefIdx, seqIdx, refIdx, sequence, reference, static_cast<unsigned int>(reference.size()), sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 0U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "");
    BOOST_CHECK_EQUAL(originalRefIdx, 4U);
    BOOST_CHECK_EQUAL(seqIdx, 3U);
    BOOST_CHECK_EQUAL(refIdx, 3U);
}

BOOST_AUTO_TEST_CASE(appointCircularTest_substitution_error)
{
    string reference = "GGGAACTTTACGGG";
    string sequence =  "---AAGTTTAC---";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 6U;
    unsigned int refIdx = 5U;
    unsigned int seqIdx = 5U;
    Mismatch mismatch;
    mismatch.appointCircular(originalRefIdx, seqIdx, refIdx, sequence, reference, static_cast<unsigned int>(reference.size()), sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 6U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "G");
    BOOST_CHECK_EQUAL(originalRefIdx, 7U);
    BOOST_CHECK_EQUAL(seqIdx, 6U);
    BOOST_CHECK_EQUAL(refIdx, 6U);
}

BOOST_AUTO_TEST_CASE(appointCircularTest_single_del_in_sequence)
{
    string reference = "GGGAACTTTACGGG";
    string sequence =  "---AA-TTTAC---";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 6U;
    unsigned int refIdx = 5U;
    unsigned int seqIdx = 5U;
    Mismatch mismatch;
    mismatch.appointCircular(originalRefIdx, seqIdx, refIdx, sequence, reference, static_cast<unsigned int>(reference.size()), sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "AC");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(originalRefIdx, 7U);
    BOOST_CHECK_EQUAL(seqIdx, 6U);
    BOOST_CHECK_EQUAL(refIdx, 6U);
}

BOOST_AUTO_TEST_CASE(appointCircularTest_long_del_in_sequence)
{
    string reference = "GGGAACTTTACGGG";
    string sequence =  "---AA---TAC---";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 6U;
    unsigned int refIdx = 5U;
    unsigned int seqIdx = 5U;
    Mismatch mismatch;
    mismatch.appointCircular(originalRefIdx, seqIdx, refIdx, sequence, reference, static_cast<unsigned int>(reference.size()), sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "ACTT");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(originalRefIdx, 9U);
    BOOST_CHECK_EQUAL(seqIdx, 8U);
    BOOST_CHECK_EQUAL(refIdx, 8U);
}

BOOST_AUTO_TEST_CASE(appointCircularTest_single_del_in_reference)
{
    string reference = "GGGAA-TTTACGGG";
    string sequence =  "---AACTTTAC---";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 6U;
    unsigned int refIdx = 5U;
    unsigned int seqIdx = 5U;
    Mismatch mismatch;
    mismatch.appointCircular(originalRefIdx, seqIdx, refIdx, sequence, reference, static_cast<unsigned int>(reference.size()), sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "AC");
    BOOST_CHECK_EQUAL(originalRefIdx, 6U);
    BOOST_CHECK_EQUAL(seqIdx, 6U);
    BOOST_CHECK_EQUAL(refIdx, 6U);
}

BOOST_AUTO_TEST_CASE(appointCircularTest_long_del_in_reference)
{
    string reference = "GGGAA---TACGGG";
    string sequence =  "---AACTTTAC---";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 6U;
    unsigned int refIdx = 5U;
    unsigned int seqIdx = 5U;
    Mismatch mismatch;
    mismatch.appointCircular(originalRefIdx, seqIdx, refIdx, sequence, reference, static_cast<unsigned int>(reference.size()), sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 5U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "ACTT");
    BOOST_CHECK_EQUAL(originalRefIdx, 6U);
    BOOST_CHECK_EQUAL(seqIdx, 8U);
    BOOST_CHECK_EQUAL(refIdx, 8U);
}

BOOST_AUTO_TEST_CASE(appointCircularTest_single_del_in_begining)
{
    string reference = "C-TTACTAACTTA";
    string sequence =  "-ATTACTAACTTA";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 1U;
    unsigned int refIdx = 0U;
    unsigned int seqIdx = 0U;
    Mismatch mismatch;
    Mismatch mismatch2;
    mismatch.appointCircular(originalRefIdx, seqIdx, refIdx, sequence, reference, static_cast<unsigned int>(reference.size())-1U, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(originalRefIdx, 2U);
    BOOST_CHECK_EQUAL(seqIdx, 2U);
    BOOST_CHECK_EQUAL(refIdx, 2U);
    mismatch2.appointCircular(originalRefIdx, seqIdx, refIdx, sequence, reference, static_cast<unsigned int>(reference.size())-1U, sequenceId);
    BOOST_CHECK_EQUAL(mismatch2.getOriginalRefIdx(), 0U);
    BOOST_CHECK_EQUAL(mismatch2.getReferenceMismatch(), "");
    BOOST_CHECK_EQUAL(mismatch2.getSequenceMismatch(), "");
}

BOOST_AUTO_TEST_CASE(appointCircularTest_double_del_in_begining_2)
{
    string reference = "-TTTGGGCCCAAATTTGGGCCCAAA";
    string sequence =  "C-TTGGGCCCAAACTT---------";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 1U;
    unsigned int refIdx = 0U;
    unsigned int seqIdx = 0U;
    Mismatch mismatch;
    Mismatch mismatch2;
    mismatch.appointCircular(originalRefIdx, seqIdx, refIdx, sequence, reference, static_cast<unsigned int>(reference.size())-1U, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(originalRefIdx, 2U);
    BOOST_CHECK_EQUAL(seqIdx, 2U);
    BOOST_CHECK_EQUAL(refIdx, 2U);
    originalRefIdx = 13U;
    refIdx = 13U;
    seqIdx = 13U;
    mismatch2.appointCircular(originalRefIdx, seqIdx, refIdx, sequence, reference, 12, sequenceId);
    BOOST_CHECK_EQUAL(mismatch2.getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatch2.getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatch2.getSequenceMismatch(), "C");
}

BOOST_AUTO_TEST_CASE(appointLinearTest_no_errors)
{
    string reference = "AACTTTAC";
    string sequence =  "AACTTTAC";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 4U;
    unsigned int refIdx = 3U;
    unsigned int seqIdx = 3U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 0U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "");
    BOOST_CHECK_EQUAL(originalRefIdx, 4U);
    BOOST_CHECK_EQUAL(seqIdx, 3U);
    BOOST_CHECK_EQUAL(refIdx, 3U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_substitution_error)
{
    string reference = "AACTTTAC";
    string sequence =  "AAGTTTAC";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 3U;
    unsigned int refIdx = 2U;
    unsigned int seqIdx = 2U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 3U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "G");
    BOOST_CHECK_EQUAL(originalRefIdx, 4U);
    BOOST_CHECK_EQUAL(seqIdx, 3U);
    BOOST_CHECK_EQUAL(refIdx, 3U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_single_del_in_sequence)
{
    string reference = "AACTTTAC";
    string sequence =  "AA-TTTAC";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 3U;
    unsigned int refIdx = 2U;
    unsigned int seqIdx = 2U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 2U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "AC");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(originalRefIdx, 4U);
    BOOST_CHECK_EQUAL(seqIdx, 3U);
    BOOST_CHECK_EQUAL(refIdx, 3U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_long_del_in_sequence)
{
    string reference = "AACTTTAC";
    string sequence =  "AA---TAC";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 3U;
    unsigned int refIdx = 2U;
    unsigned int seqIdx = 2U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 2U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "ACTT");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(originalRefIdx, 6U);
    BOOST_CHECK_EQUAL(seqIdx, 5U);
    BOOST_CHECK_EQUAL(refIdx, 5U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_single_del_in_reference)
{
    string reference = "AA-TTTAC";
    string sequence =  "AACTTTAC";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 3U;
    unsigned int refIdx = 2U;
    unsigned int seqIdx = 2U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 2U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "AC");
    BOOST_CHECK_EQUAL(originalRefIdx, 3U);
    BOOST_CHECK_EQUAL(seqIdx, 3U);
    BOOST_CHECK_EQUAL(refIdx, 3U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_long_del_in_reference)
{
    string reference = "AA---TAC";
    string sequence =  "AACTTTAC";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 3U;
    unsigned int refIdx = 2U;
    unsigned int seqIdx = 2U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 2U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "A");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "ACTT");
    BOOST_CHECK_EQUAL(originalRefIdx, 3U);
    BOOST_CHECK_EQUAL(seqIdx, 5U);
    BOOST_CHECK_EQUAL(refIdx, 5U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_single_del_in_begin_of_sequence)
{
    string reference = "ATTACTAACTTA";
    string sequence =  "-TTACTAACTTA";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 1U;
    unsigned int refIdx = 0U;
    unsigned int seqIdx = 0U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "AT");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(originalRefIdx, 2U);
    BOOST_CHECK_EQUAL(seqIdx, 1U);
    BOOST_CHECK_EQUAL(refIdx, 1U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_single_del_in_begin_of_reference)
{
    string reference = "-TTACTAACTTA";
    string sequence =  "ATTACTAACTTA";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 1U;
    unsigned int refIdx = 0U;
    unsigned int seqIdx = 0U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "AT");
    BOOST_CHECK_EQUAL(originalRefIdx, 1U);
    BOOST_CHECK_EQUAL(seqIdx, 1U);
    BOOST_CHECK_EQUAL(refIdx, 1U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_long_del_in_begin_of_sequence)
{
    string reference = "AATTACTAACTTA";
    string sequence =  "--TTACTAACTTA";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 1U;
    unsigned int refIdx = 0U;
    unsigned int seqIdx = 0U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "AAT");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(originalRefIdx, 3U);
    BOOST_CHECK_EQUAL(seqIdx, 2U);
    BOOST_CHECK_EQUAL(refIdx, 2U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_long_del_in_begin_of_reference)
{
    string reference = "--TTACTAACTTA";
    string sequence =  "AATTACTAACTTA";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 1U;
    unsigned int refIdx = 0U;
    unsigned int seqIdx = 0U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "AAT");
    BOOST_CHECK_EQUAL(originalRefIdx, 1U);
    BOOST_CHECK_EQUAL(seqIdx, 2U);
    BOOST_CHECK_EQUAL(refIdx, 2U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_single_del_in_end_of_sequence)
{
    string reference = "ATTACTAACTTA";
    string sequence =  "ATTACTAACTT-";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 12U;
    unsigned int refIdx = 11U;
    unsigned int seqIdx = 11U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 11U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "TA");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(originalRefIdx, 13U);
    BOOST_CHECK_EQUAL(seqIdx, 12U);
    BOOST_CHECK_EQUAL(refIdx, 12U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_single_del_in_end_of_reference)
{
    string reference = "ATTACTAACTT-";
    string sequence =  "ATTACTAACTTA";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 12U;
    unsigned int refIdx = 11U;
    unsigned int seqIdx = 11U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 11U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "TA");
    BOOST_CHECK_EQUAL(originalRefIdx, 12U);
    BOOST_CHECK_EQUAL(seqIdx, 12U);
    BOOST_CHECK_EQUAL(refIdx, 12U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_long_del_in_end_of_sequence)
{
    string reference = "AATTACTAACTTA";
    string sequence =  "AATTACTAACT--";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 12U;
    unsigned int refIdx = 11U;
    unsigned int seqIdx = 11U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 11U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "TTA");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "T");
    BOOST_CHECK_EQUAL(originalRefIdx, 14U);
    BOOST_CHECK_EQUAL(seqIdx, 13U);
    BOOST_CHECK_EQUAL(refIdx, 13U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_long_del_in_end_of_reference)
{
    string reference = "AATTACTAACT--";
    string sequence =  "AATTACTAACTTA";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 12U;
    unsigned int refIdx = 11U;
    unsigned int seqIdx = 11U;
    Mismatch mismatch;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 11U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "TTA");
    BOOST_CHECK_EQUAL(originalRefIdx, 12U);
    BOOST_CHECK_EQUAL(seqIdx, 13U);
    BOOST_CHECK_EQUAL(refIdx, 13U);
}

BOOST_AUTO_TEST_CASE(appointLinearTest_single_del_in_begining)
{
    string reference = "C-TTACTAACTTA";
    string sequence =  "-ATTACTAACTTA";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 1U;
    unsigned int refIdx = 0U;
    unsigned int seqIdx = 0U;
    Mismatch mismatch;
    Mismatch mismatch2;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "C");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "A");
    BOOST_CHECK_EQUAL(originalRefIdx, 2U);
    BOOST_CHECK_EQUAL(seqIdx, 2U);
    BOOST_CHECK_EQUAL(refIdx, 2U);
    mismatch2.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch2.getOriginalRefIdx(), 0U);
    BOOST_CHECK_EQUAL(mismatch2.getReferenceMismatch(), "");
    BOOST_CHECK_EQUAL(mismatch2.getSequenceMismatch(), "");
}

BOOST_AUTO_TEST_CASE(appointLinearTest_double_del_in_begining_2)
{
    string reference = "-TTTGGGCCCAAATTT";
    string sequence =  "C-TTGGGCCCAAACTT";
    string sequenceId = "seqId";
    unsigned int originalRefIdx = 1U;
    unsigned int refIdx = 0U;
    unsigned int seqIdx = 0U;
    Mismatch mismatch;
    Mismatch mismatch2;
    mismatch.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch.getOriginalRefIdx(), 1U);
    BOOST_CHECK_EQUAL(mismatch.getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatch.getSequenceMismatch(), "C");
    BOOST_CHECK_EQUAL(originalRefIdx, 2U);
    BOOST_CHECK_EQUAL(seqIdx, 2U);
    BOOST_CHECK_EQUAL(refIdx, 2U);
    originalRefIdx = 13U;
    refIdx = 13U;
    seqIdx = 13U;
    mismatch2.appointLinear(originalRefIdx, seqIdx, refIdx, sequence, reference, sequenceId);
    BOOST_CHECK_EQUAL(mismatch2.getOriginalRefIdx(), 13U);
    BOOST_CHECK_EQUAL(mismatch2.getReferenceMismatch(), "T");
    BOOST_CHECK_EQUAL(mismatch2.getSequenceMismatch(), "C");
}

BOOST_AUTO_TEST_SUITE_END()
