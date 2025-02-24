/**
 * \file TestOutwardPairedReadsAdding.cpp
 * \brief the C++ file with implementation of tests for OutwardPairedReadsAdding class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/OutwardPairedReadsAdding.hpp"
#include "../../../src/dbj/UnitigsToContigsExtension.hpp"

using namespace dnaasm::dbj;
using namespace dnaasm;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestOutwardPairedReadsAdding)

BOOST_AUTO_TEST_CASE(basic_single_test)
{
    unsigned short K1 = 2U;
    float insertSizeMean = 0.0;
    float insertSizeStdDev = 0.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    vector<bool> isOriginal(2);
    istringstream unitigsFile;
    unitigsFile.str(">0\nAACT\n>1\nCTAG");
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].insertSizeOffsetVector_.size(), 0U);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);

    istringstream in;
    in.str("");
    InputFile inputFile(in);
    FileReader fileReader;
    fileReader.setInputFile1(&inputFile);
    OutwardPairedReadsAdding< UnitigsToContigsExtension > addOutwardPairedReads(fileReader, unitigsToContigsExtension, 10, NULL);
    addOutwardPairedReads();
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].insertSizeOffsetVector_.size(), 0U);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);

    istringstream in2;
    in2.str(">desc1\nAGTT\n>desc2\nCTAG\n");
    InputFile inputFile2(in2);
    FileReader fileReader2;
    fileReader2.setInputFile1(&inputFile2);
    OutwardPairedReadsAdding< UnitigsToContigsExtension > addOutwardPairedReads2(fileReader2, unitigsToContigsExtension, 10, NULL);
    addOutwardPairedReads2();
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].insertSizeOffsetVector_.size(), 0U);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);

    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    addOutwardPairedReads2();
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].insertSizeOffsetVector_.size(), 1U);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
}

BOOST_AUTO_TEST_SUITE_END()

