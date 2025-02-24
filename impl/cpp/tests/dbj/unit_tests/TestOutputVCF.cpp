/**
 * \file TestOutputVCF.cpp
 * \brief the C++ file with implementation of tests for OutputVCF class
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/OutputVCF.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestOutputVCF)

BOOST_AUTO_TEST_CASE(generateVCFOutput_single_test)
{
    string seq0 = "A";
    string ref0 = "G";
    unsigned int pos0 = 1U;
    string seqId0 = "id1";
    Mismatch mismatch0(seq0, ref0, pos0, seqId0);
    string seq1 = "A";
    string ref1 = "G";
    unsigned int pos1 = 7U;
    string seqId1 = "id2";
    Mismatch mismatch1(seq1, ref1, pos1, seqId1);
    string seq2 = "C";
    string ref2 = "G";
    unsigned int pos2 = 7U;
    string seqId2 = "";
    Mismatch mismatch2(seq2, ref2, pos2, seqId2);
    string seq3 = "A";
    string ref3 = "T";
    unsigned int pos3 = 1U;
    string seqId3 = "id3";
    Mismatch mismatch3(seq3, ref3, pos3, seqId3);
    vector<Mismatch> mismatches;
    mismatches.push_back(mismatch0);
    mismatches.push_back(mismatch1);
    mismatches.push_back(mismatch3);
    mismatches.push_back(mismatch1);
    mismatches.push_back(mismatch1);
    mismatches.push_back(mismatch2);
    mismatches.push_back(mismatch3);
    mismatches.push_back(mismatch0);
    mismatches.push_back(mismatch1);
    mismatches.push_back(mismatch3);
    mismatches.push_back(mismatch2);
    OutputVCF outputVCF(mismatches);
    BOOST_CHECK_EQUAL(outputVCF.generateVCFOutput(), "##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n.\t1\tid1\tG\tA\t.\t.\t.\r\n.\t1\tid3\tT\tA\t.\t.\t.\r\n.\t7\tid2\tG\tA\t.\t.\t.\r\n.\t7\t.\tG\tC\t.\t.\t.\r\n");
}

BOOST_AUTO_TEST_SUITE_END()
