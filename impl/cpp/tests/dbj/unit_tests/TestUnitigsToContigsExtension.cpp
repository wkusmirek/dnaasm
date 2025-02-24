/**
 * \file TestUnitigsToContigsExtension.cpp
 * \brief the C++ file with implementation of tests for UnitigsToContigsExtension class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/UnitigsToContigsExtension.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestUnitigsToContigsExtension)

/*******************************build unitigs graph tests********************************************/

BOOST_AUTO_TEST_CASE(buildUnitigsGraph_empty_unitigs)
{
    unsigned short K1 = 0U;
    float insertSizeMean = 0.0;
    float insertSizeStdDev = 0.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str("");
    vector<bool> isOriginal;
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 0);
    BOOST_CHECK_EQUAL(K1, 0U);
    BOOST_CHECK_EQUAL(insertSizeMean, 0.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 0.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 0);
}

BOOST_AUTO_TEST_CASE(buildUnitigsGraph_not_empty_unitigs)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTTTTTT\n>\nACCA");
    vector<bool> isOriginal(3);
    isOriginal[0] = true;
    isOriginal[1] = true;
    isOriginal[2] = false;
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, false);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

/*******************************add paired reads tests********************************************/

BOOST_AUTO_TEST_CASE(addPairedReads_not_existed_unitigs_linked_by_paired_reads)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    vector<bool> isOriginal(3);
    isOriginal[0] = true;
    isOriginal[1] = true;
    isOriginal[2] = false;
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.addPairedReads("GGGGG", "GGGGG");
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, false);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

BOOST_AUTO_TEST_CASE(addPairedReads_without_self_linking)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    vector<bool> isOriginal(3);
    isOriginal[0] = true;
    isOriginal[1] = true;
    isOriginal[2] = false;
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.addPairedReads("AAAA", "AAAA");
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, false);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

BOOST_AUTO_TEST_CASE(addPairedReads_without_linking_first_k1_mers)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    vector<bool> isOriginal(3);
    isOriginal[0] = true;
    isOriginal[1] = true;
    isOriginal[2] = false;
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.addPairedReads("AAC", "ACC");
    unitigsToContigsExtension.addPairedReads("AAC", "TAA");
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, false);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

BOOST_AUTO_TEST_CASE(addPairedReads_with_linking_last_k1_mers_in_unitig_with_size_equal_to_2)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    vector<bool> isOriginal(3);
    isOriginal[0] = true;
    isOriginal[1] = true;
    isOriginal[2] = false;
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.addPairedReads("ACC", "AAT");
    unitigsToContigsExtension.addPairedReads("AAA", "AAC");
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, false);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

BOOST_AUTO_TEST_CASE(addPairedReads_without_linking_from_short_not_original_unitigs_to_another_unitigs)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    vector<bool> isOriginal(3);
    isOriginal[0] = true;
    isOriginal[1] = true;
    isOriginal[2] = false;
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.addPairedReads("ACC", "AAA");
    unitigsToContigsExtension.addPairedReads("CCA", "AAA");
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, false);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

BOOST_AUTO_TEST_CASE(addPairedReads_linking_from_each_of_vertex_containing_the_same_k_mer)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA\n>\nTAAAT");
    vector<bool> isOriginal(4);
    isOriginal[0] = true;
    isOriginal[1] = true;
    isOriginal[2] = false;
    isOriginal[3] = true;
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.addPairedReads("ACC", "AAA");
    unitigsToContigsExtension.addPairedReads("CCA", "AAA");
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 4);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[3].isOriginal_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 4);
}

/*******************************extend long unitigs tests********************************************/

/*******************************tests for another type of start vertex********************************************/

BOOST_AUTO_TEST_CASE(extendUnitigs_2_connected_long_original_unitigs_extend_with_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginal(2);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].counter_ = 5U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0].size(), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][1], 1);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].counter_, 5U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_2_connected_long_not_original_unitigs_extend_with_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginal(2);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_2_connected_short_original_unitigs_extend_with_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginal(2);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = false;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_2_connected_short_not_original_unitigs_extend_with_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginal(2);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = false;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
}

/*******************************tests for another structure of input unitigs graph********************************************/

BOOST_AUTO_TEST_CASE(extendUnitigs_2_disconnected_long_unitigs_extend_without_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginal(2);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 0);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_2_connected_long_unitigs_extend_without_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginal(2);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_2_disconnected_long_unitigs_extend_with_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginal(2);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 3U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0].size(), 4);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][1], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][2], 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][3], 1);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_3_connected_long_unitigs_extend_with_paired_edges)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginal(3);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_ = true;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(1, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0].size(), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][1], 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[1].size(), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[1][0], 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[1][1], 2);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

BOOST_AUTO_TEST_CASE(addPairedReads_2_connected_unitigs_1_disconnected_unitig_extend_with_paired_edge)   // 0 -> 1 and 2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginal(3);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_ = true;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0].size(), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][1], 1);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

// w tym teście wydaje mi się, że nic nie powinno się łączyć, ale w sumie nie wiem jak powinna działać aplikacja w takich przypadkach, trzeba to zbadać
/*BOOST_AUTO_TEST_CASE(addPairedReads_2_circular_connected_unitigs_NOT_extend_with_paired_edge)   //0 -> 1 -> 0
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginal(2);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(1, 0, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 0, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 0, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 0, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(edge(1, 0, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 0, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 0, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 0, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 2);
}*/

BOOST_AUTO_TEST_CASE(extendUnitigs_5_cross_connected_unitigs_extend_without_paired_reads)   //without testing contigsGraph structure
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG\n>\nCCCCC\n>\nTTTTTT");
    vector<bool> isOriginal(5);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[3].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[4].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[3].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[4].isLongNode_ = true;
    add_edge(0, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(1, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(2, 3, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 3, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(2, 4, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 4, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 4, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 4, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 5);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 4);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 5);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_5_cross_connected_unitigs_extend_with_paired_reads)   //without testing contigsGraph structure
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG\n>\nCCCCC\n>\nTTTTTT");
    vector<bool> isOriginal(5);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[3].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[4].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[3].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[4].isLongNode_ = true;
    add_edge(0, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(1, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(2, 3, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 3, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(2, 4, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 4, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 4, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 4, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(0, 3, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 3, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(1, 4, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 4, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 4, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 4, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0].size(), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][1], 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][2], 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[1].size(), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[1][0], 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[1][1], 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[1][2], 4);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 5);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 6);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 5);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_3_linear_connected_unitigs)   //connected unitigs: 0->1->2 paired reads: 0->1->2 and 0->2, reult: one unitig, all unitigs are long and original
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginal(3);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_ = true;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(1, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(0, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0].size(), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][1], 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][2], 2);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_4_connected_unitigs_with_loop)   // 0->1, 1->2, 2->1, 1->3
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG\n>\nCCCCC");
    vector<bool> isOriginal(4);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[3].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[3].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].sequenceSize_ = 5U;
    unitigsToContigsExtension.getUnitigsGraph()[1].sequenceSize_ = 3U;
    unitigsToContigsExtension.getUnitigsGraph()[2].sequenceSize_ = 3U;
    unitigsToContigsExtension.getUnitigsGraph()[3].sequenceSize_ = 5U;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(1, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(2, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(2, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(1, 3, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(1, 3, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(0, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(0, 3, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 3, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 15U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0].size(), 7);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][1], 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][2], 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][3], 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][4], 2);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][5], 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][6], 3);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 4);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[3].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[3].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 6);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(edge(2, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(2, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(2, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(2, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(edge(1, 3, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(1, 3, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 0U);
    BOOST_CHECK_EQUAL(edge(0, 3, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 3, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 3, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 15U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 4);
}

/*******************************tests for situations of bad unitigs graph structure********************************************/

BOOST_AUTO_TEST_CASE(extendUnitigs_3_connected_unitigs_bad_structure_target_long_original)   // 0->1, 0->2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginal(3);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_ = false;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 3U;
    add_edge(0, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 4U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0].size(), 4);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][1], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][2], 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences()[0][3], 1);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_, false);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 4U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_3_connected_unitigs_bad_structure_target_short_not_original)   // 0->1, 0->2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginal(3);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = false;
    unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_ = false;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 3U;
    add_edge(0, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 4U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_, false);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 4U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

BOOST_AUTO_TEST_CASE(extendUnitigs_3_connected_unitigs_bad_structure_2_targets_long_original)   // 0->1, 0->2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 400.0;
    float insertSizeStdDev = 20.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginal(3);
    UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, isOriginal, NULL);
    unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_ = true;
    add_edge(0, 1, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 3U;
    add_edge(0, 2, unitigsToContigsExtension.getUnitigsGraph());
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_ = true;
    unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_ = 4U;
    unitigsToContigsExtension.extend();
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(unitigsToContigsExtension.getUnitigsGraph()), 3);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isOriginal_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[2].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(unitigsToContigsExtension.getUnitigsGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 1, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).second, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(unitigsToContigsExtension.getUnitigsGraph()[edge(0, 2, unitigsToContigsExtension.getUnitigsGraph()).first].estimatedDistance_, 4U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 400.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 20.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginal.size(), 3);
}

BOOST_AUTO_TEST_SUITE_END()
