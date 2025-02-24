/**
 * \file TestContigsToScaffoldsExtension.cpp
 * \brief the C++ file with implementation of tests for ContigsToScaffoldsExtension class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/ContigsToScaffoldsExtension.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestContigsToScaffoldsExtension)

/*******************************build contigs graph tests********************************************/

BOOST_AUTO_TEST_CASE(buildContigsGraph_empty_contigs)
{
    unsigned short K1 = 0U;
    float insertSizeMean = 0.0;
    float insertSizeStdDev = 0.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str("");
    contigsFile.str("");
    vector<bool> isOriginalUnitig;
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 0);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 0);
    BOOST_CHECK_EQUAL(K1, 0U);
    BOOST_CHECK_EQUAL(insertSizeMean, 0.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 0.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 0);
}

BOOST_AUTO_TEST_CASE(buildContigsGraph_not_empty_contigs)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTTTTTT\n>\nACCA");
    contigsFile.str(">\nAACC\n>\nTTTTTT\n>\nACCA");
    vector<bool> isOriginalUnitig(3);
    isOriginalUnitig[0] = true;
    isOriginalUnitig[1] = true;
    isOriginalUnitig[2] = false;
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}

/*******************************add paired reads tests********************************************/

BOOST_AUTO_TEST_CASE(addPairedReads_not_existed_contigs_linked_by_paired_reads)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    vector<bool> isOriginalUnitig(3);
    isOriginalUnitig[0] = true;
    isOriginalUnitig[1] = true;
    isOriginalUnitig[2] = false;
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = false;
    contigsToScaffoldsExtension.addPairedReads("GGGGG", "GGGGG");
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}

BOOST_AUTO_TEST_CASE(addPairedReads_without_self_linking)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    vector<bool> isOriginalUnitig(3);
    isOriginalUnitig[0] = true;
    isOriginalUnitig[1] = true;
    isOriginalUnitig[2] = false;
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = false;
    contigsToScaffoldsExtension.addPairedReads("AAAA", "AAAA");
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}

BOOST_AUTO_TEST_CASE(addPairedReads_without_linking_from_not_long_contigs_to_another_contigs)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nACCA");
    vector<bool> isOriginalUnitig(3);
    isOriginalUnitig[0] = true;
    isOriginalUnitig[1] = true;
    isOriginalUnitig[2] = true;
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = false;
    contigsToScaffoldsExtension.addPairedReads("ACC", "AAA");
    contigsToScaffoldsExtension.addPairedReads("CCA", "AAA");
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}

BOOST_AUTO_TEST_CASE(addPairedReads_linking_from_each_of_vertex_containing_the_same_k_mer)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAAGCC\n>\nTAAAT\n");
    contigsFile.str(">\nAAGCC\n>\nTAAAT\n");
    vector<bool> isOriginalUnitig(2);
    isOriginalUnitig[0] = true;
    isOriginalUnitig[1] = true;
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.addPairedReads("AAGCC", "TAAAT");
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 2);
    //BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 1);
    //BOOST_CHECK_EQUAL(edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    //BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    //BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 2);
}

/*******************************extend long contigs tests********************************************/

/*******************************tests for another type of start vertex********************************************/

BOOST_AUTO_TEST_CASE(extendContigs_2_connected_long_contigs_extend_with_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    contigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginalUnitig(2);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 3U;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].counter_ = 5U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0].size(), 4);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][1], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][2], 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][3], 1);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].counter_, 5U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 2);
}

BOOST_AUTO_TEST_CASE(extendContigs_2_connected_short_contigs_extend_with_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    contigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginalUnitig(2);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = false;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 3U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, false);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 2);
}

/*******************************tests for another structure of input contigs graph********************************************/

BOOST_AUTO_TEST_CASE(extendContigs_2_disconnected_long_contigs_extend_without_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    contigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginalUnitig(2);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 0);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 2);
}

BOOST_AUTO_TEST_CASE(extendContigs_2_connected_long_contigs_extend_without_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    contigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginalUnitig(2);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 5U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, false);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 5U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 2);
}

BOOST_AUTO_TEST_CASE(extendContigs_2_disconnected_long_contigs_extend_with_paired_edge)
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT");
    contigsFile.str(">\nAACC\n>\nTAAAT");
    vector<bool> isOriginalUnitig(2);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 3U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0].size(), 4);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][1], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][2], 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][3], 1);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 2);
}

BOOST_AUTO_TEST_CASE(extendContigs_3_connected_long_contigs_extend_with_paired_edges_0_1_and_1_2)   //connected contigs: 0->1->2 paired reads: 0->1 and 1->2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginalUnitig(3);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = true;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 1U;
    add_edge(1, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 2U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0].size(), 4);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][1], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][2], 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][3], 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[1].size(), 4);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[1][0], 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[1][1], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[1][2], 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[1][3], 2);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 1U);
    BOOST_CHECK_EQUAL(edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 2U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}

/*
BOOST_AUTO_TEST_CASE(extendContigs_3_connected_long_contigs_extend_with_paired_edges_0_1_and_0_2)   //connected contigs: 0->1->2 paired reads: 0->1 and 0->2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginalUnitig(3);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = true;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 1U;
    add_edge(0, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 2U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0].size(), 7);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][1], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][2], 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][3], 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][4], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][5], 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][6], 2);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 1U);
    BOOST_CHECK_EQUAL(edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 2U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}
*/
/*
BOOST_AUTO_TEST_CASE(extendContigs_3_connected_long_contigs_extend_with_paired_edges_0_1_and_1_2_and_0_2)   //connected contigs: 0->1->2 paired reads: 0->1, 1->2 and 0->2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginalUnitig(3);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = true;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 1U;
    add_edge(1, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 2U;
    add_edge(0, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 3U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0].size(), 7);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][1], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][2], 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][3], 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][4], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][5], 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][6], 2);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 1U);
    BOOST_CHECK_EQUAL(edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 2U);
    BOOST_CHECK_EQUAL(edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, false);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}
*/
BOOST_AUTO_TEST_CASE(addPairedReads_2_connected_contigs_1_disconnected_contig_extend_with_paired_edge)   // 0 -> 1 and 2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginalUnitig(3);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = true;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 3U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0].size(), 4);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][1], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][2], 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][3], 1);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 1);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}

BOOST_AUTO_TEST_CASE(extendContigs_5_cross_connected_contigs_extend_without_paired_reads)   //without testing contigsGraph structure
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG\n>\nCCCCC\n>\nTTTTTT");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG\n>\nCCCCC\n>\nTTTTTT");
    vector<bool> isOriginalUnitig(5);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[3].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[4].isLongNode_ = true;
    add_edge(0, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(1, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(2, 3, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 3, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 3, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 3, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 0U;
    add_edge(2, 4, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 4, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 4, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 4, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 0U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 5);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 4);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 5);
}
/*
BOOST_AUTO_TEST_CASE(extendContigs_5_cross_connected_contigs_extend_with_paired_reads)   //without testing contigsGraph structure
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG\n>\nCCCCC\n>\nTTTTTT");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG\n>\nCCCCC\n>\nTTTTTT");
    vector<bool> isOriginalUnitig(5);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[3].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[4].isLongNode_ = true;
    add_edge(0, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 1U;
    add_edge(1, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 1U;
    add_edge(2, 3, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 3, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 3, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 3, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 2U;
    add_edge(2, 4, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 4, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 4, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(2, 4, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 2U;
    add_edge(0, 3, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 3, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 3, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 3, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 3U;
    add_edge(1, 4, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 4, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 4, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(1, 4, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 3U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0].size(), 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][1], 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][2], 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[1].size(), 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[1][0], 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[1][1], 2);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[1][2], 4);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 5);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 6);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 5);
}
*/

/*******************************tests for situations of bad contigs graph structure********************************************/

BOOST_AUTO_TEST_CASE(extendContigs_3_connected_contigs_bad_structure_target_long_original)   // 0->1, 0->2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginalUnitig(3);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = false;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 3U;
    add_edge(0, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 4U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 1);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0].size(), 4);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][0], 0);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][1], std::numeric_limits<unsigned long>::max());
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][2], 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences()[0][3], 1);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_, false);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 4U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}

BOOST_AUTO_TEST_CASE(extendContigs_3_connected_contigs_bad_structure_target_short_not_original)   // 0->1, 0->2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginalUnitig(3);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = false;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = false;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 3U;
    add_edge(0, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 4U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, false);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_, false);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 4U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}

BOOST_AUTO_TEST_CASE(extendContigs_3_connected_contigs_bad_structure_2_targets_long_original)   // 0->1, 0->2
{
    unsigned short K1 = 3U;
    float insertSizeMean = 6500.0;
    float insertSizeStdDev = 1000.0;
    unsigned short readLength = 100U;
    unsigned short pairedReadsThrFrom = 0U;
    unsigned short pairedReadsThrTo = 0U;
    istringstream unitigsFile;
    istringstream contigsFile;
    unitigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    contigsFile.str(">\nAACC\n>\nTAAAT\n>\nGGGGGG");
    vector<bool> isOriginalUnitig(3);
    ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMean, insertSizeStdDev, readLength, pairedReadsThrFrom, pairedReadsThrTo, unitigsFile, contigsFile, isOriginalUnitig, NULL);
    contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_ = true;
    add_edge(0, 1, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 3U;
    add_edge(0, 2, contigsToScaffoldsExtension.getContigsGraph());
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_ = true;
    contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_ = 4U;
    contigsToScaffoldsExtension.extend();
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getExtendedSequences().size(), 0);
    BOOST_CHECK_EQUAL(num_vertices(contigsToScaffoldsExtension.getContigsGraph()), 3);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[0].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[1].isLongNode_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[2].isLongNode_, true);
    BOOST_CHECK_EQUAL(num_edges(contigsToScaffoldsExtension.getContigsGraph()), 2);
    BOOST_CHECK_EQUAL(edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 1, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 3U);
    BOOST_CHECK_EQUAL(edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).second, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForConnectedSequences_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].isForPairedReads_, true);
    BOOST_CHECK_EQUAL(contigsToScaffoldsExtension.getContigsGraph()[edge(0, 2, contigsToScaffoldsExtension.getContigsGraph()).first].estimatedDistance_, 4U);
    BOOST_CHECK_EQUAL(K1, 3U);
    BOOST_CHECK_EQUAL(insertSizeMean, 6500.0);
    BOOST_CHECK_EQUAL(insertSizeStdDev, 1000.0);
    BOOST_CHECK_EQUAL(readLength, 100U);
    BOOST_CHECK_EQUAL(pairedReadsThrFrom, 0U);
    BOOST_CHECK_EQUAL(pairedReadsThrTo, 0U);
    BOOST_CHECK_EQUAL(isOriginalUnitig.size(), 3);
}

BOOST_AUTO_TEST_SUITE_END()
