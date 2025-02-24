/**
 * \file TestFileReader.cpp
 * \brief the C++ file with implementation of tests for FileReader class
 *
 */

#include <fstream>
#include <boost/test/unit_test.hpp>
#include "../../../src/common/FileReader.hpp"

using namespace dnaasm;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestFileReader)

BOOST_AUTO_TEST_CASE(readData_singleRead1)
{
    Read read(0);
    istringstream in;
    in.str(">desc1\nAACC\n>desc2\nCCAT\n>desc3\nAA\n>desc4\nAT\n>desc5\nATA\n>desc6\nTTT\n");
    InputFile inputFile(in);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AACC");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc1");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CCAT");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc2");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AA");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc3");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AT");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc4");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "ATA");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc5");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "TTT");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc6");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    //fileReader.readData(read);
    //BOOST_CHECK_EQUAL(read.getRead(), "");
    //BOOST_CHECK_EQUAL(read.getQuality(), "");
    //BOOST_CHECK_EQUAL(read.getDescription(), "");
    //BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_singleRead2)
{
    Read read(0);
    istringstream in;
    in.str(">desc1\nAACC\n>desc2\nCCAT\n>desc3\nAA\n>desc4\nAT\n>desc5\nATA\n>desc6\nTTT\n");
    InputFile inputFile(in);
    FileReader fileReader;
    fileReader.setInputFile2(&inputFile);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AACC");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc1");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CCAT");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc2");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AA");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc3");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AT");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc4");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "ATA");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc5");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "TTT");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc6");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    //fileReader.readData(read);
    //BOOST_CHECK_EQUAL(read.getRead(), "");
    //BOOST_CHECK_EQUAL(read.getQuality(), "");
    //BOOST_CHECK_EQUAL(read.getDescription(), "");
    //BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_singleRead3)
{
    Read read(0);
    istringstream in1, in2;
    in1.str(">desc1\nAACC\n>desc2\nCCAT\n>desc3\nAA\n>desc4\nAT\n>desc5\nATA\n>desc6\nTTT\n");
    in2.str(">desc7\nAAA\n>desc8\nCCC\n");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AACC");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc1");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CCAT");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc2");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AA");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc3");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AT");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc4");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "ATA");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc5");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "TTT");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc6");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    //fileReader.readData(read);
    //BOOST_CHECK_EQUAL(read.getRead(), "");
    //BOOST_CHECK_EQUAL(read.getQuality(), "");
    //BOOST_CHECK_EQUAL(read.getDescription(), "");
    //BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AAA");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc7");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CCC");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc8");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    //fileReader.readData(read);
    //BOOST_CHECK_EQUAL(read.getRead(), "");
    //BOOST_CHECK_EQUAL(read.getQuality(), "");
    //BOOST_CHECK_EQUAL(read.getDescription(), "");
    //BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_singleRead4)
{
    Read read(0);
    istringstream in;
    in.str("");
    InputFile inputFile1(in);
    InputFile inputFile2(in);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_singleRead5)
{
    Read read(0);
    FileReader fileReader;
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_singleRead6)
{
    Read read(0);
    istringstream in;
    in.str("@desc1\nCC\n+desc1\nqual1\n@desc2\nCA\n+desc2\nqual2\n");
    InputFile inputFile(in);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc1");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CA");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc2");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_singleRead7)
{
    Read read(0);
    istringstream in;
    in.str("@desc1\nCC\n+desc1\nqual1\n@desc2\nCA\n+desc2\nqual2\n");
    InputFile inputFile(in);
    FileReader fileReader;
    fileReader.setInputFile2(&inputFile);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc1");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CA");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc2");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_singleRead8)
{
    Read read(0);
    istringstream in1, in2;
    in1.str("@desc1\nCC\n+desc1\nqual1\n@desc2\nCA\n+desc2\nqual2\n");
    in2.str("@desc3\nCCC\n+desc3\nqual3");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc1");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CA");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc2");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CCC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual3");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc3");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_singleRead9)
{
    Read read(0);
    istringstream in1, in2;
    in1.str("@desc1\nCC\n+desc1\nqual1\n@desc2\nCA\n+desc2\nqual2\n");
    in2.str(">desc3\nCCC\n");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc1");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CA");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc2");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "CCC");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc3");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    //fileReader.readData(read);
    //BOOST_CHECK_EQUAL(read.getRead(), "");
    //BOOST_CHECK_EQUAL(read.getQuality(), "");
    //BOOST_CHECK_EQUAL(read.getDescription(), "");
    //BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(getNumOfReads_2_FASTQ)
{
    istringstream in1, in2;
    in1.str("@desc1\nCC\n+desc1\nqual1\n@desc2\nCA\n+desc2\nqual2\n");
    in2.str("@desc3\nCCC\n+desc3\nqual3");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    BOOST_CHECK_EQUAL(fileReader.getNumOfReads(), 3U);
}

BOOST_AUTO_TEST_CASE(getNumOfReads_2_FASTA)
{
    istringstream in1, in2;
    in1.str(">test\nAAAA\n>test\nAAAA");
    in2.str(">test\nAAAA");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    BOOST_CHECK_EQUAL(fileReader.getNumOfReads(), 3U);
}

BOOST_AUTO_TEST_CASE(getNumOfReads_2_long_FASTA)
{
    istringstream in1, in2;
    in1.str(">test\nAAAA\n>test\nAAAA\nAAAA\nAAAA\nAAAA\nAAAA");
    in2.str(">test\nAAAA");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    BOOST_CHECK_EQUAL(fileReader.getNumOfReads(), 3U);
}

BOOST_AUTO_TEST_CASE(getNumOfReads_1_FASTA_1_FASTQ)
{
    istringstream in1, in2;
    in1.str(">test\nAAAA\n>test\nAAAA");
    in2.str("@desc3\nCCC\n+desc3\nqual3");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    BOOST_CHECK_EQUAL(fileReader.getNumOfReads(), 3U);
}

BOOST_AUTO_TEST_CASE(getNumOfReads_0_reads)
{
    istringstream in1, in2;
    in1.str("");
    in2.str("");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    BOOST_CHECK_EQUAL(fileReader.getNumOfReads(), 0U);
}

BOOST_AUTO_TEST_CASE(readData_pairedRead_inputFile1_FASTQ_ILLUMINA1)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1;
    in1.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual1\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual2\n");
    InputFile inputFile1(in1);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 2U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 0U);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 2U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 0U);
}

BOOST_AUTO_TEST_CASE(readData_pairedRead_inputFile1_FASTQ_ILLUMINA2)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1;
    in1.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual1\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual2\n");
    InputFile inputFile1(in1);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 0U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 2U);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_pairedRead_inputFile1_FASTQ_ILLUMINA3)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1;
    in1.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual1\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual2\n");
    InputFile inputFile1(in1);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 0U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 2U);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_pairedRead_inputFile1_FASTQ_ILLUMINA4)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1;
    in1.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual1\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual2\n");
    InputFile inputFile1(in1);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 0U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 2U);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_pairedRead_inputFile1_FASTQ_ILLUMINA5_121211212)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1;
    in1.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual1\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual2\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual3\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual4\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual5\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual6\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual7\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual8\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual9\n");
    InputFile inputFile1(in1);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual3");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual4");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual6");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual7");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual8");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual9");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 8U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 1U);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_pairedRead_inputFile1_FASTQ_ILLUMINA6_121221212)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1;
    in1.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual1\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual2\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual3\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual4\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual5\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual6\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual7\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual8\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual9\n");
    InputFile inputFile1(in1);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual3");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual4");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual6");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual7");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual8");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual9");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 8U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 1U);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_pairedRead_inputFile1_FASTQ_ILLUMINA7_one_pair_no_paired)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1;
    in1.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual1\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual2\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual3\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual4\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual6\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGTAGGACTGCATA\nCA\n+\nqual7\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual8\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual9\n");
    InputFile inputFile1(in1);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual3");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual4");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual8");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual9");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 6U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 2U);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_pairedRead_inputFile2_NO_FASTQ_ILLUMINA)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in2;
    in2.str("@desc1\nCC\n+desc1\nqual1\n@desc2\nCA\n+desc2\nqual2\n@desc3\nCC\n+desc3\nqual3\n@desc4\nCA\n+desc4\nqual4\n");
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile2(&inputFile2);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc1");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@desc2");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual3");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc3");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual4");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@desc4");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 0U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 0U);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}
/*
//dobry test przy odkomentowanych dwóch fragmentach (dwie pętle while)w FileReader.cpp, zamiast testu tego niżej
BOOST_AUTO_TEST_CASE(readData_pairedRead_two_files_FASTQ_ILLUMINA8_one_pair_no_paired)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1, in2;
    in1.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual1\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual15\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual3\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGTAGGACTGCATA\nCA\n+\nqual5\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual7\n");
    in2.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual2\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual4\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual6\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual15\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual8\n");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual3");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual4");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual7");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual8");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 6U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 4U);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}
*/

BOOST_AUTO_TEST_CASE(readData_pairedRead_two_files_FASTQ_ILLUMINA8_one_pair_no_paired)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1, in2;
    in1.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual1\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual15\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual3\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGTAGGACTGCATA\nCA\n+\nqual5\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual7\n");
    in2.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual2\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual4\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual6\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA\nCC\n+\nqual15\n@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA\nCA\n+\nqual8\n");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual3");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CC");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual6");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual7");
    BOOST_CHECK_EQUAL(read.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CA");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual8");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 2:N:0:CAGAGAGGACTGCATA");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 6U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 4U);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_pairedRead_two_files_NO_FASTQ_ILLUMINA1)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1, in2;
    in1.str("@desc1\nCC\n+desc1\nqual1\n@desc2\nCA\n+desc2\nqual2\n");
    in2.str("@desc3\nCCC\n+desc3\nqual3");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual1");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc1");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CCC");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "qual3");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "@desc3");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CA");
    BOOST_CHECK_EQUAL(read.getQuality(), "qual2");
    BOOST_CHECK_EQUAL(read.getDescription(), "@desc2");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getNumOfPairedReads(), 0U);
    BOOST_CHECK_EQUAL(fileReader.getNumOfUnpairedReads(), 0U);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readData_pairedRead_two_files_different_format)
{
    Read read(0);
    Read pairedRead(0);
    istringstream in1, in2;
    in1.str("@desc1\nCC\n+desc1\nqual1\n@desc2\nCA\n+desc2\nqual2\n");
    in2.str(">desc3\nCCC\n");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(resetTest)
{
    Read read(0);
    Read pairedRead(0);
istringstream in1, in2;
    in1.str(">desc1\nCC\n");
    in2.str(">desc3\nCCC\n");
    InputFile inputFile1(in1);
    InputFile inputFile2(in2);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile1);
    fileReader.setInputFile2(&inputFile2);
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), true);
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc1");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CCC");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), ">desc3");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
    //fileReader.readData(read, pairedRead);
    //BOOST_CHECK_EQUAL(read.getRead(), "");
    //BOOST_CHECK_EQUAL(read.getQuality(), "");
    //BOOST_CHECK_EQUAL(read.getDescription(), "");
    //BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    //BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    //BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    //BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
    fileReader.reset();
    fileReader.readData(read, pairedRead);
    BOOST_CHECK_EQUAL(read.getRead(), "CC");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">desc1");
    BOOST_CHECK_EQUAL(pairedRead.getRead(), "CCC");
    BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    BOOST_CHECK_EQUAL(pairedRead.getDescription(), ">desc3");
    BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
    //fileReader.readData(read, pairedRead);
    //BOOST_CHECK_EQUAL(read.getRead(), "");
    //BOOST_CHECK_EQUAL(read.getQuality(), "");
    //BOOST_CHECK_EQUAL(read.getDescription(), "");
    //BOOST_CHECK_EQUAL(pairedRead.getRead(), "");
    //BOOST_CHECK_EQUAL(pairedRead.getQuality(), "");
    //BOOST_CHECK_EQUAL(pairedRead.getDescription(), "");
    //BOOST_CHECK_EQUAL(fileReader.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_SUITE_END()
