/**
 * \file TestInputFile.cpp
 * \brief the C++ file with implementation of tests for InputFile class
 *
 */

#include <fstream>
#include <boost/test/unit_test.hpp>
#include "../../../src/common/InputFile.hpp"

using namespace dnaasm;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestInputFile)

BOOST_AUTO_TEST_CASE(readSingleRead_empty_file)
{
    Read read(0);
    istringstream in;
    in.str("");
    InputFile inputFile(in);
    BOOST_CHECK_EQUAL(inputFile.getNumOfLinesInFile(), 0U);
    BOOST_CHECK_EQUAL(inputFile.getFileCompressionType(), InputFile::FileCompressionType::TEXT);
    BOOST_CHECK_EQUAL(inputFile.getFileFormat(), InputFile::FileFormat::NONE);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readSingleRead_TEXT_FASTQ)
{
    Read read(0);
    ifstream in("cpp/tests/dbj/unit_tests/test_data/file.fq");
    InputFile inputFile(in);
    BOOST_CHECK_EQUAL(inputFile.getNumOfLinesInFile(), 8U);
    BOOST_CHECK_EQUAL(inputFile.getFileCompressionType(), InputFile::FileCompressionType::TEXT);
    BOOST_CHECK_EQUAL(inputFile.getFileFormat(), InputFile::FileFormat::FASTQ);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "ACGT");
    BOOST_CHECK_EQUAL(read.getQuality(), "EEEE");
    BOOST_CHECK_EQUAL(read.getDescription(), "@test1");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), true);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AAAA");
    BOOST_CHECK_EQUAL(read.getQuality(), "FFFF");
    BOOST_CHECK_EQUAL(read.getDescription(), "@test2");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), true);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readSingleRead_GZ_FASTQ)
{
    Read read(0);
    ifstream in("cpp/tests/dbj/unit_tests/test_data/file.fq.gz");
    InputFile inputFile(in);
    BOOST_CHECK_EQUAL(inputFile.getNumOfLinesInFile(), 8U);
    BOOST_CHECK_EQUAL(inputFile.getFileCompressionType(), InputFile::FileCompressionType::GZ);
    BOOST_CHECK_EQUAL(inputFile.getFileFormat(), InputFile::FileFormat::FASTQ);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "ACGT");
    BOOST_CHECK_EQUAL(read.getQuality(), "EEEE");
    BOOST_CHECK_EQUAL(read.getDescription(), "@test1");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), true);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AAAA");
    BOOST_CHECK_EQUAL(read.getQuality(), "FFFF");
    BOOST_CHECK_EQUAL(read.getDescription(), "@test2");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), true);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readSingleRead_TEXT_FASTA)
{
    Read read(0);
    ifstream in("cpp/tests/dbj/unit_tests/test_data/file.fa");
    InputFile inputFile(in);
    BOOST_CHECK_EQUAL(inputFile.getNumOfLinesInFile(), 6U);
    BOOST_CHECK_EQUAL(inputFile.getFileCompressionType(), InputFile::FileCompressionType::TEXT);
    BOOST_CHECK_EQUAL(inputFile.getFileFormat(), InputFile::FileFormat::FASTA);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "ACGTTGCATCTG");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">test1");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), true);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AAAA");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">test2");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), false);
    //inputFile.readSingleRead(read);
    //BOOST_CHECK_EQUAL(read.getRead(), "");
    //BOOST_CHECK_EQUAL(read.getQuality(), "");
    //BOOST_CHECK_EQUAL(read.getDescription(), "");
    //BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(readSingleRead_GZ_FASTA)
{
    Read read(0);
    ifstream in("cpp/tests/dbj/unit_tests/test_data/file.fa.gz");
    InputFile inputFile(in);
    BOOST_CHECK_EQUAL(inputFile.getNumOfLinesInFile(), 5U);
    BOOST_CHECK_EQUAL(inputFile.getFileCompressionType(), InputFile::FileCompressionType::GZ);
    BOOST_CHECK_EQUAL(inputFile.getFileFormat(), InputFile::FileFormat::FASTA);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "ACGTTGCA");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">test1");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), true);
    inputFile.readSingleRead(read);
    BOOST_CHECK_EQUAL(read.getRead(), "AAAA");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), ">test2");
    BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), true);
    //inputFile.readSingleRead(read);
    //BOOST_CHECK_EQUAL(read.getRead(), "");
    //BOOST_CHECK_EQUAL(read.getQuality(), "");
    //BOOST_CHECK_EQUAL(read.getDescription(), "");
    //BOOST_CHECK_EQUAL(inputFile.getIsMoreSequences(), false);
}

BOOST_AUTO_TEST_CASE(check_file_format_NONE)
{
    Read read(0);
    istringstream in;
    in.str("");
    InputFile inputFile(in);
    BOOST_CHECK_EQUAL(inputFile.getFileFormat(), InputFile::FileFormat::NONE);
}

BOOST_AUTO_TEST_CASE(check_file_format_FASTA)
{
    Read read(0);
    istringstream in;
    in.str(">desc1\nAA\n>desc2\nA\nA\n");
    InputFile inputFile(in);
    BOOST_CHECK_EQUAL(inputFile.getFileFormat(), InputFile::FileFormat::FASTA);
}

BOOST_AUTO_TEST_CASE(check_file_format_FASTQ)
{
    Read read(0);
    istringstream in;
    in.str("@desc1\nAA\n+desc2\nST\n");
    InputFile inputFile(in);
    BOOST_CHECK_EQUAL(inputFile.getFileFormat(), InputFile::FileFormat::FASTQ);
}

BOOST_AUTO_TEST_CASE(check_file_format_FASTQ_ILLUMINA)
{
    Read read(0);
    istringstream in;
    in.str("@HWI-M02221:10:000000000-A5VFM:1:1101:18064:2058 1:N:0:CTAATGGACTGCATA\nAA\n+desc2\nST\n");
    InputFile inputFile(in);
    BOOST_CHECK_EQUAL(inputFile.getFileFormat(), InputFile::FileFormat::FASTQ_ILLUMINA);
}

BOOST_AUTO_TEST_SUITE_END()
