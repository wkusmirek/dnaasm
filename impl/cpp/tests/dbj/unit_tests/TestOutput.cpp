/**
 * \file TestOutput.cpp
 * \brief the C++ file with implementation of tests for Output class
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/Output.hpp"

using namespace dnaasm::dbj;
using namespace std;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;
typedef std::vector<DeBruijnGraphVertex> Unitig;
typedef std::vector<Unitig> Unitigs;

BOOST_AUTO_TEST_SUITE(TestOutput)

BOOST_AUTO_TEST_CASE(OutputBasicTest1)
{
    string result;
    string idPrefix = "";
    Statistics statistics;
    Unitigs unitigs;
    vector<char> firstChars;
    vector<bitset<2*MAX_KMER_LENGTH>> sequences;
    unsigned short K1 = 2;
    ResultantSequencesGenerator<DeBruijnGraph> resultantSequencesGenerator(unitigs, firstChars, sequences, K1, statistics);
    Output<DeBruijnGraph> output(result, statistics, resultantSequencesGenerator, idPrefix);
    output.generateApplicationOutput();
    BOOST_CHECK_EQUAL(result, "");
}

BOOST_AUTO_TEST_CASE(OutputBasicTest2)
{
    vector<char> firstChars;
    vector<bitset<2*MAX_KMER_LENGTH>> sequences;
    string read = "AATC";
    string read2 = "TAT";
    firstChars.push_back('A');
    firstChars.push_back('A');
    firstChars.push_back('T');
    firstChars.push_back('T');
    firstChars.push_back('A');
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("01110000")));    //AATC
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("011100")));    //ATC
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("0111")));    //TC
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("110011")));    //TAT
    sequences.push_back(bitset<2*MAX_KMER_LENGTH>(string("1100")));    //AT
    string result;
    string idPrefix = "test";
    Statistics statistics;
    Unitigs unitigs;
    Unitig unitig;
    unitig.push_back(0ULL);
    unitig.push_back(1ULL);
    unitig.push_back(2ULL);
    unitigs.push_back(unitig);
    Unitig unitig2;
    unitig2.push_back(3ULL);
    unitig2.push_back(4ULL);
    unitigs.push_back(unitig2);
    unsigned short K1 = 2;
    ResultantSequencesGenerator<DeBruijnGraph> resultantSequencesGenerator(unitigs, firstChars, sequences, K1, statistics);
    Output<DeBruijnGraph> output(result, statistics, resultantSequencesGenerator, idPrefix);
    output.generateApplicationOutput();
    BOOST_CHECK_EQUAL(result, ">test_0_4\r\n"+read+"\r\n>test_1_3\r\n"+read2+"\r\n");
}

BOOST_AUTO_TEST_SUITE_END()
