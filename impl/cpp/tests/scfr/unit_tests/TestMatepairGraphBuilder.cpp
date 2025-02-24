/**
 * \file TestMatepairGraphBuilder.cpp
 * \brief the C++ file with implementation of tests for MatepairGraphBuilder class
 *
 */

#include <boost/test/unit_test.hpp>
#include <sstream>
#include "../../../src/common/InputFile.hpp"
#include "../../../src/scfr/MatepairGraphBuilder.hpp"
#include "../mocks/MockBloomFilter.hpp"

using namespace dnaasm::scfr;
using namespace std;
using ::testing::Return;
using ::testing::StrEq;

struct FixMGB {
    FixMGB() : mpg(2) {}
    ~FixMGB() {}

    void checkGraph(const vector<string> &kmers) {
        for (size_t i=0, j=1; j < kmers.size(); i+=2, j+=2) {
            auto v1 = mpg.vertex(kmers[i]);
            auto v2 = mpg.vertex(kmers[j]);
            BOOST_REQUIRE(v1 != mpg.graph().null_vertex());
            BOOST_REQUIRE(v2 != mpg.graph().null_vertex());
            BOOST_CHECK_EQUAL(mpg.graph()[v1].contigId_, 0);
            BOOST_CHECK_EQUAL(mpg.graph()[v1].start_, 0);
            BOOST_CHECK_EQUAL(mpg.graph()[v1].end_, 0);
            //BOOST_CHECK_EQUAL(mpg.graph()[v1].multiple_, 0);
            BOOST_CHECK_EQUAL(mpg.graph()[v2].contigId_, 0);
            BOOST_CHECK_EQUAL(mpg.graph()[v2].start_, 0);
            BOOST_CHECK_EQUAL(mpg.graph()[v2].end_, 0);
            //BOOST_CHECK_EQUAL(mpg.graph()[v2].multiple_, 0);
            BOOST_REQUIRE_EQUAL(boost::edge(v1, v2, mpg.graph()).second, true);
        }
    }

    MatepairGraph mpg;
    MockBloomFilter mbf;
    unsigned short int kmerSize = 2;
    unsigned short int distance = 5;
    unsigned short int step = 1;
    unsigned int readCounter = 0U;
};

BOOST_FIXTURE_TEST_SUITE(TestMatepairGraphBuilder, FixMGB)

BOOST_AUTO_TEST_CASE(buildGraph_all_kmers_in_bloom_and_unique)
{
    string readsStr = ">1\nACCGAT\n>2\nTAGGT\n";
    istringstream reads(readsStr);
    dnaasm::InputFile readsFile(reads);

    MatepairGraphBuilder mpGraphBuilder(mpg, mbf, readsFile,
                                        kmerSize, distance, step);

    // extracted 2-mer pairs from reads are:
    // AC -> GA ->
    // CC -> AT ->
    // TA -> GT ->
    vector<string> kmers = {"AC", "GA", "CC", "AT", "TA", "GT"};
    for (auto &kmer : kmers) {
        EXPECT_CALL(mbf, contains(StrEq(kmer))).Times(1)
                                               .WillOnce(Return(true));
    }

    BOOST_CHECK_EQUAL(2, mpGraphBuilder.buildGraph());
    BOOST_CHECK_EQUAL(6, num_vertices(mpg.graph()));
    BOOST_CHECK_EQUAL(3, num_edges(mpg.graph()));

    checkGraph(kmers);
}

BOOST_AUTO_TEST_CASE(buildGraph_all_kmers_in_bloom_one_not_unique)
{
    string readsStr = ">1\nACCGAT\n>2\nACGGT\n";
    istringstream reads(readsStr);
    dnaasm::InputFile readsFile(reads);

    MatepairGraphBuilder mpGraphBuilder(mpg, mbf, readsFile,
                                        kmerSize, distance, step);

    // extracted 2-mer pairs from reads are:
    // AC -> GA ->
    // CC -> AT ->
    // AC -> GT ->
    // 2-mer AC appears 2 times
    vector<string> uniqueKmers = {"GA", "CC", "AT", "GT"};
    for (auto &kmer : uniqueKmers) {
        EXPECT_CALL(mbf, contains(StrEq(kmer))).Times(1)
                                               .WillOnce(Return(true));
    }
    string nonUniqueKmer = "AC";
    EXPECT_CALL(mbf, contains(StrEq(nonUniqueKmer))).Times(2)
                                                    .WillOnce(Return(true))
                                                    .WillOnce(Return(true));

    BOOST_CHECK_EQUAL(2, mpGraphBuilder.buildGraph());
    BOOST_CHECK_EQUAL(5, num_vertices(mpg.graph())); // one vertex for k-mer AC
    BOOST_CHECK_EQUAL(3, num_edges(mpg.graph()));

    vector<string> kmers = {"AC", "GA", "CC", "AT", "AC", "GT"};
    checkGraph(kmers);
}

BOOST_AUTO_TEST_CASE(buildGraph_not_all_kmers_in_bloom)
{
    string readsStr = ">1\nACCGAT\n>2\nTAGGT\n";
    istringstream reads(readsStr);
    dnaasm::InputFile readsFile(reads);

    MatepairGraphBuilder mpGraphBuilder(mpg, mbf, readsFile,
                                        kmerSize, distance, step);

    // extracted 2-mer pairs from reads are:
    // AC -> GA ->
    // CC -> AT ->
    // TA -> GT ->
    // GT is not in Bloom Filter
    vector<string> kmersInBloom = {"AC", "GA", "CC", "AT", "TA"};
    for (auto &kmer : kmersInBloom) {
        EXPECT_CALL(mbf, contains(StrEq(kmer))).Times(1)
                                               .WillOnce(Return(true));
    }
    string notInBloom = "GT";
    EXPECT_CALL(mbf, contains(StrEq(notInBloom))).Times(1)
                                                 .WillOnce(Return(false));

    BOOST_CHECK_EQUAL(2, mpGraphBuilder.buildGraph());
    // edge TA - GT should NOT be created
    BOOST_CHECK_EQUAL(4, num_vertices(mpg.graph()));
    BOOST_CHECK_EQUAL(2, num_edges(mpg.graph()));

    vector<string> kmers = {"AC", "GA", "CC", "AT"};
    checkGraph(kmers);
}

BOOST_AUTO_TEST_CASE(buildGraph_all_kmers_in_bloom_multiple_kmer_pair)
{
    string readsStr = ">1\nACCGAT\n>2\nACGGA\n";
    istringstream reads(readsStr);
    dnaasm::InputFile readsFile(reads);

    MatepairGraphBuilder mpGraphBuilder(mpg, mbf, readsFile,
                                        kmerSize, distance, step);

    // extracted 2-mer pairs from reads are:
    // AC -> GA -> x2
    // CC -> AT -> x1
    EXPECT_CALL(mbf, contains(StrEq("CC"))).Times(1)
                                           .WillOnce(Return(true));
    EXPECT_CALL(mbf, contains(StrEq("AT"))).Times(1)
                                           .WillOnce(Return(true));
    EXPECT_CALL(mbf, contains(StrEq("AC"))).Times(2)
                                           .WillRepeatedly(Return(true));
    EXPECT_CALL(mbf, contains(StrEq("GA"))).Times(2)
                                           .WillRepeatedly(Return(true));

    BOOST_CHECK_EQUAL(2, mpGraphBuilder.buildGraph());
    BOOST_CHECK_EQUAL(4, num_vertices(mpg.graph()));
    BOOST_CHECK_EQUAL(2, num_edges(mpg.graph())); // only 1 edge for pair AC - GA

    vector<string> kmers = {"AC", "GA", "CC", "AT"};
    checkGraph(kmers);
}

BOOST_AUTO_TEST_SUITE_END()
