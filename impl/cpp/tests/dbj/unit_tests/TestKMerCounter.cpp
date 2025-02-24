/**
 * \file TestKMerCounter.cpp
 * \brief the C++ file with implementation of tests for KMerCounter class
 *
 */

#include <boost/test/unit_test.hpp>
#include <fstream>
#include "../../../src/dbj/KMerCounter.hpp"

using namespace dnaasm::dbj;
using namespace dnaasm;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestKMerCounter)

BOOST_AUTO_TEST_CASE(empty_reads_files)
{
    istringstream in;
    in.str("");
    InputFile inputFile(in);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile);
    unsigned short K1 = 5U;
    unsigned short qualityThreshold = 0U;
    string kmerOccurrenceTableFilename = CALC_TMP_DIR+string("kmerOccurrenceTable");
    KMerCounter kMerCounter(fileReader, K1, qualityThreshold, kmerOccurrenceTableFilename, NULL);
    kMerCounter.calcKMersOccurrenceTable();
    ifstream bfcounterFile(kmerOccurrenceTableFilename);
    string kMer = "";
    string numOfOccurrence = "";
    bfcounterFile >> kMer >> numOfOccurrence;
    BOOST_CHECK_EQUAL(kMer, "");
    BOOST_CHECK_EQUAL(numOfOccurrence, "");
}

BOOST_AUTO_TEST_CASE(basic_test)
{
    istringstream in;
    in.str(">\nACTG\n>\nG\n>\nAGTT\n");
    InputFile inputFile(in);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile);
    unsigned short K1 = 2U;
    unsigned short qualityThreshold = 0U;
    string kmerOccurrenceTableFilename = CALC_TMP_DIR+string("kmerOccurrenceTable");
    KMerCounter kMerCounter(fileReader, K1, qualityThreshold, kmerOccurrenceTableFilename, NULL);
    kMerCounter.calcKMersOccurrenceTable();
    ifstream bfcounterFile(kmerOccurrenceTableFilename);
    string kMer = "";
    string numOfOccurrence = "";
    bfcounterFile >> kMer >> numOfOccurrence;
    BOOST_CHECK_EQUAL(kMer, "CAG");
    BOOST_CHECK_EQUAL(numOfOccurrence, "1");
    kMer = "";
    numOfOccurrence = "";
    bfcounterFile >> kMer >> numOfOccurrence;
    BOOST_CHECK_EQUAL(kMer, "AAC");
    BOOST_CHECK_EQUAL(numOfOccurrence, "1");
    kMer = "";
    numOfOccurrence = "";
    bfcounterFile >> kMer >> numOfOccurrence;
    BOOST_CHECK_EQUAL(kMer, "AGT");
    BOOST_CHECK_EQUAL(numOfOccurrence, "2");
    kMer = "";
    numOfOccurrence = "";
    bfcounterFile >> kMer >> numOfOccurrence;
    BOOST_CHECK_EQUAL(kMer, "");
    BOOST_CHECK_EQUAL(numOfOccurrence, "");
}

BOOST_AUTO_TEST_SUITE_END()
