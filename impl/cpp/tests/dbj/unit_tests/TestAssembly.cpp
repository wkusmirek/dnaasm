/**
 * \file TestAssembly.cpp
 * \brief the C++ file with implementation of tests for assembly.hpp and assembly.cpp files
 *
 */

#include <fstream>
#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/assembly.hpp"

using namespace dnaasm;
using namespace dnaasm::dbj;
using namespace std;


BOOST_AUTO_TEST_SUITE(TestAssembly)

/*BOOST_AUTO_TEST_CASE(assemblyModeBasicTest0)
{
    istringstream i1_1;
    i1_1.str(">test description1\nAGGTAACCTT\n>test description1\nATCG");
    istringstream i1_2;
    i1_2.str("");
    istringstream o1_1;
    o1_1.str("");
    istringstream o1_2;
    o1_2.str("");
    istringstream bfcFile;
    bfcFile.str("");
    //BOOST_CHECK_EQUAL(assemblyMode(2, 14, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, i1_1, i1_2, o1_1, o1_2, bfcFile, 0U, false, "test", NULL), ">test_0_10\r\nAGGTAACCTT\r\n>test_1_4\r\nATCG\r\n");
    TODO: segfault when Result tuple is initialized in default way
    BOOST_CHECK_EQUAL(assemblyMode(2, 14, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0, i1_1, i1_2, o1_1, o1_2, bfcFile, 0U, false, "test", NULL), "");

}*/

/*BOOST_AUTO_TEST_CASE(assemblyModeBasicTest1)
{
    istringstream i1_1;
    i1_1.str(">test description1\nAGGTAACCTT\n>test description1\nATCG");
    istringstream i1_2;
    i1_2.str("");
    istringstream o1_1;
    o1_1.str("");
    istringstream o1_2;
    o1_2.str("");
    istringstream bfcFile;
    bfcFile.str("");
    //BOOST_CHECK_EQUAL(assemblyMode(2, 10, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, i1_1, i1_2, o1_1, o1_2, bfcFile, 0U, true, "test", NULL), ">test_0_10\r\nAGGTAACCTT\r\n");
    TODO: segfault when Result tuple is initialized in default way
    BOOST_CHECK_EQUAL(assemblyMode(2, 10, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0, i1_1, i1_2, o1_1, o1_2, bfcFile, 0U, true, "test", NULL), "");
}*/

BOOST_AUTO_TEST_CASE(assemblyModeBasicTest2)
{
    istringstream i1_1;
    i1_1.str(">test description1\nTTTTTTTTT\n>test1\nAAAAAAAAA");
    istringstream i1_2;
    i1_2.str("");
    istringstream o1_1;
    o1_1.str("");
    istringstream o1_2;
    o1_2.str("");
    istringstream bfcFile;
    bfcFile.str("");
    //BOOST_CHECK_EQUAL(assemblyMode(5, 30, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, i1_1, i1_2, o1_1, o1_2, bfcFile, 1U, false, "test", NULL), ">test_0_17\r\nTTTTTTTTTTTTTTTTT\r\n>test_1_17\r\nAAAAAAAAAAAAAAAAA\r\n");
    BOOST_CHECK_EQUAL(assemblyMode(5, 30, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0, i1_1, i1_2, o1_1, o1_2, bfcFile, 1U, false, "test", NULL), "");
}

BOOST_AUTO_TEST_CASE(assemblyModeBasicTest3)
{
    istringstream i1_1;
    i1_1.str(">test description1\nACGT\n>test1\nTAAC\n>test description2\nCGG\n>test2\nCCG");
    istringstream i1_2;
    i1_2.str("");
    istringstream o1_1;
    o1_1.str("");
    istringstream o1_2;
    o1_2.str("");
    istringstream bfcFile;
    bfcFile.str("");
    //BOOST_CHECK_EQUAL(assemblyMode(2, 10, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, i1_1, i1_2, o1_1, o1_2, bfcFile, 1U, false, "test", NULL), ">test_0_10\r\nCCGTTAACGT\r\n>test_1_3\r\nCGG\r\n");
    BOOST_CHECK_EQUAL(assemblyMode(2, 10, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0, 0, i1_1, i1_2, o1_1, o1_2, bfcFile, 1U, false, "test", NULL), "");
}

BOOST_AUTO_TEST_CASE(alignModeBasicTest_circular_Hirschberg)
{
    istringstream issSequence, issReference;
    issSequence.str(">seq1\nGGCAAAACTCTCTAGGC\n>seq2\nGGCTAAACTCTTTAGGC");
    issReference.str(">ref\nACTCTCTAGGCTAA");
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    BOOST_CHECK_EQUAL(alignMode(issSequence, issReference, true, true, -5, substitutionMatrixValues, NULL), "##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n.\t6\tseq2\tC\tT\t.\t.\t.\r\n.\t12\tseq1\tT\tA\t.\t.\t.\r\n");
}

BOOST_AUTO_TEST_CASE(alignModeBasicTest_circular_NeedlemanWunsch)
{
    istringstream issSequence, issReference;
    issSequence.str(">seq1\nGGCAAAACTCTCTAGGC\n>seq2\nGGCTAAACTCTTTAGGC");
    issReference.str(">ref\nACTCTCTAGGCTAA");
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    BOOST_CHECK_EQUAL(alignMode(issSequence, issReference, false, true, -5, substitutionMatrixValues, NULL), "##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n.\t6\tseq2\tC\tT\t.\t.\t.\r\n.\t12\tseq1\tT\tA\t.\t.\t.\r\n");
}

BOOST_AUTO_TEST_CASE(alignModeBasicTest_linear_Hirschberg)
{
    istringstream issSequence, issReference;
    issSequence.str(">seq1\nCTCTCTAGGCTAA\n>seq2\nACTCTCTAGGTTAA");
    issReference.str(">ref\nACTCTCTAGGCTAA");
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    BOOST_CHECK_EQUAL(alignMode(issSequence, issReference, true, false, -5, substitutionMatrixValues, NULL), "##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n.\t1\tseq1\tAC\tC\t.\t.\t.\r\n.\t11\tseq2\tC\tT\t.\t.\t.\r\n");
}

BOOST_AUTO_TEST_CASE(alignModeBasicTest_linear_NeedlemanWunsch)
{
    istringstream issSequence, issReference;
    issSequence.str(">seq1\nCTCTCTAGGCTAA\n>seq2\nACTCTCTAGGTTAA");
    issReference.str(">ref\nACTCTCTAGGCTAA");
    short int substitutionMatrixValues[] = {1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1};
    BOOST_CHECK_EQUAL(alignMode(issSequence, issReference, false, false, -5, substitutionMatrixValues, NULL), "##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n.\t1\tseq1\tAC\tC\t.\t.\t.\r\n.\t11\tseq2\tC\tT\t.\t.\t.\r\n");
}

BOOST_AUTO_TEST_SUITE_END()
