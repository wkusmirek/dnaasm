/**
 * \file TestResultantSequencesGenerator.cpp
 * \brief the C++ file with implementation of tests for ResultantSequencesGenerator class
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/ResultantSequencesGenerator.hpp"
#include "../../../src/dbj/UnitigsToContigsExtension.hpp"

using namespace dnaasm::dbj;
using namespace std;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;
typedef std::vector<DeBruijnGraphVertex> Unitig;
typedef std::vector<Unitig> Unitigs;
typedef std::vector<UnitigsToContigsExtension::UnitigsGraphVertex> Contig;
typedef std::vector<Contig> Contigs;

BOOST_AUTO_TEST_SUITE(TestResultantSequencesGenerator)

BOOST_AUTO_TEST_CASE(ResultantSequencesGenerator1_unitigs)
{
    Unitigs unitigs;
    vector<char> firstChars;
    vector<bitset<2*MAX_KMER_LENGTH>> sequences;
    unsigned short K1 = 2;
    Statistics statistics;
    ResultantSequencesGenerator<DeBruijnGraph> resultantSequencesGenerator(unitigs, firstChars, sequences, K1, statistics);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 0.0);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 0.0);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(0), "");
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 0);
}

BOOST_AUTO_TEST_CASE(ResultantSequencesGenerator2_unitigs)
{
    vector<char> firstChars;
    vector<bitset<2*MAX_KMER_LENGTH>> sequences;
    firstChars.push_back('A');
    firstChars.push_back('T');
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("1100")));    //AT
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("0111")));    //TC
    Unitigs unitigs;
    Unitig unitig;
    unitig.push_back(0ULL);
    unitig.push_back(1ULL);
    unitigs.push_back(unitig);
    unsigned short K1 = 2;
    Statistics statistics;
    ResultantSequencesGenerator<DeBruijnGraph> resultantSequencesGenerator(unitigs, firstChars, sequences, K1, statistics);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 3.0);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 3.0);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 3UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 3UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 3UL);
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(0),"ATC");
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(1), "");
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 1);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].first, 3U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].second, 1U);
}

BOOST_AUTO_TEST_CASE(ResultantSequencesGenerator3_unitigs)
{
    vector<char> firstChars;
    vector<bitset<2*MAX_KMER_LENGTH>> sequences;
    firstChars.push_back('A');
    firstChars.push_back('T');
    firstChars.push_back('C');
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("10011100")));    //ATCG
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("100111")));    //TCG
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("1001")));    //CG
    Unitigs unitigs;
    Unitig unitig;
    unitig.push_back(0ULL);
    unitig.push_back(1ULL);
    unitigs.push_back(unitig);
    Unitig unitig2;
    unitig2.push_back(2ULL);
    unitigs.push_back(unitig2);
    unsigned short K1 = 2;
    Statistics statistics;
    ResultantSequencesGenerator<DeBruijnGraph> resultantSequencesGenerator(unitigs, firstChars, sequences, K1, statistics);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 2.5);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 2.5);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 3UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 3UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 5UL);
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(0), "ATC");
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(1), "CG");
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(2), "");
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 2);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].first, 2U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].second, 1U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].first, 3U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].second, 1U);
}

BOOST_AUTO_TEST_CASE(ResultantSequencesGenerator4_unitigs)
{
    vector<char> firstChars;
    vector<bitset<2*MAX_KMER_LENGTH>> sequences;
    firstChars.push_back('A');
    firstChars.push_back('T');
    firstChars.push_back('C');
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("10011100")));    //ATCG
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("100111")));    //TCG
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("1001")));    //CG
    Unitigs unitigs;
    Unitig unitig;
    unitig.push_back(0ULL);
    unitig.push_back(1ULL);
    unitigs.push_back(unitig);
    Unitig unitig2;
    unitig2.push_back(0ULL);
    unitig2.push_back(1ULL);
    unitig2.push_back(2ULL);
    unitigs.push_back(unitig2);
    Unitig unitig3;
    unitig3.push_back(0ULL);
    unitig3.push_back(1ULL);
    unitig3.push_back(2ULL);
    unitig3.push_back(0ULL);
    unitig3.push_back(1ULL);
    unitig3.push_back(2ULL);
    unitig3.push_back(2ULL);
    unitigs.push_back(unitig3);
    unsigned short K1 = 2;
    Statistics statistics;
    ResultantSequencesGenerator<DeBruijnGraph> resultantSequencesGenerator(unitigs, firstChars, sequences, K1, statistics);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 5.0);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 4.0);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 8UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 8UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 15UL);
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(0), "ATC");
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(1), "ATCG");
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(2), "ATCATCCG");
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 3);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].first, 3U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].second, 1U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].first, 4U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].second, 1U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[2].first, 8U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[2].second, 1U);
}

BOOST_AUTO_TEST_CASE(ResultantSequencesGenerator1_contigs)
{
    Contigs contigs;
    istringstream unitigsFile;
    unitigsFile.str(">\nAAA\n>\nCCC\n>\nTTT");
    unsigned short K1 = 2;
    Statistics statistics;
    ResultantSequencesGenerator<UnitigsToContigsExtension::UnitigsGraph> resultantSequencesGenerator(contigs, unitigsFile, K1, statistics);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 0.0);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 0.0);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 0UL);
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(0), "");
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 0);
}

BOOST_AUTO_TEST_CASE(ResultantSequencesGenerator2_contigs)
{
    Contigs contigs;
    Contig contig0;
    contig0.push_back(0ULL);
    contigs.push_back(contig0);
    istringstream unitigsFile;
    unitigsFile.str(">\nACTGA\n");
    unsigned short K1 = 2;
    Statistics statistics;
    ResultantSequencesGenerator<UnitigsToContigsExtension::UnitigsGraph> resultantSequencesGenerator(contigs, unitigsFile, K1, statistics);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 5.0);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 5.0);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 5UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 5UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 5UL);
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(0), "ACTGA");
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 1);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].first, 5U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].second, 1U);
}

BOOST_AUTO_TEST_CASE(ResultantSequencesGenerator3_contigs)
{
    Contigs contigs;
    Contig contig0;
    contig0.push_back(0ULL);
    contig0.push_back(1ULL);
    contig0.push_back(2ULL);
    contigs.push_back(contig0);
    istringstream unitigsFile;
    unitigsFile.str(">\nTAA\n>\nAAC\n>\nACT");
    unsigned short K1 = 2;
    Statistics statistics;
    ResultantSequencesGenerator<UnitigsToContigsExtension::UnitigsGraph> resultantSequencesGenerator(contigs, unitigsFile, K1, statistics);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 5.0);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 5.0);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 5UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 5UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 5UL);
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(0), "TAACT");
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 1);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].first, 5U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].second, 1U);
}

BOOST_AUTO_TEST_CASE(ResultantSequencesGenerator4_contigs)
{
    Contigs contigs;
    Contig contig0;
    contig0.push_back(0ULL);
    contig0.push_back(1ULL);
    contig0.push_back(2ULL);
    contigs.push_back(contig0);
    Contig contig1;
    contig1.push_back(0ULL);
    contig1.push_back(1ULL);
    contigs.push_back(contig1);
    istringstream unitigsFile;
    unitigsFile.str(">\nTAA\n>\nAAC\n>\nACT");
    unsigned short K1 = 2;
    Statistics statistics;
    ResultantSequencesGenerator<UnitigsToContigsExtension::UnitigsGraph> resultantSequencesGenerator(contigs, unitigsFile, K1, statistics);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::AVG_SEQUENCE_SIZE)), 4.5);
    BOOST_CHECK_EQUAL(boost::get<float>(statistics.get(Statistics::Key::MEDIAN_SEQUENCE_SIZE)), 4.5);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::N50_SEQUENCE_SIZE)), 5UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::MAX_SEQUENCE_SIZE)), 5UL);
    BOOST_CHECK_EQUAL(boost::get<unsigned long>(statistics.get(Statistics::Key::SUM_SEQUENCES_SIZE)), 9UL);
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(0), "TAACT");
    BOOST_CHECK_EQUAL(resultantSequencesGenerator.getOut(1), "TAAC");
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer().size(), 2);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].first, 4U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[0].second, 1U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].first, 5U);
    BOOST_CHECK_EQUAL(statistics.getSequencesLengthsHistogramContainer()[1].second, 1U);
}

BOOST_AUTO_TEST_SUITE_END()

