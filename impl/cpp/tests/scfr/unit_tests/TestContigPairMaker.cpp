/**
 * \file TestContigPairMaker.cpp
 * \brief the C++ file with implementation of tests for ContigPairMaker class
 *
 */
#include <gmock/gmock.h>
#include <boost/test/unit_test.hpp>
#include <vector>
#include "../../../src/scfr/common.hpp"
#include "../../../src/scfr/ContigPairMaker.hpp"

using namespace dnaasm::scfr;
using namespace std;

struct Fix_CPM {
    Fix_CPM() : matepairGraph(2) {}
    ~Fix_CPM() {}

    void checkEdge(string v1, string v2, int16_t distance,
                   uint32_t links, int32_t gapSum) {
        auto v1_desc = pairs.vertex(v1);
        auto v2_desc = pairs.vertex(v2);
        BOOST_REQUIRE_MESSAGE(v1_desc != pairs.graph().null_vertex(),
                              v1 + " vertex is null");
        BOOST_REQUIRE_MESSAGE(v2_desc != pairs.graph().null_vertex(),
                              v2 + " vertex is null");
        BOOST_CHECK_MESSAGE(pairs.graph()[v1_desc].contig_ == v1,
                            v1 + " property contig_ != " + v1);
        BOOST_CHECK_MESSAGE(pairs.graph()[v2_desc].contig_ == v2,
                            v2 + " property contig_ != " + v2);
        BOOST_REQUIRE_MESSAGE(boost::edge(v1_desc, v2_desc, pairs.graph()).second == true,
                              "edge " + v1 + "->" + v1 + " doesn't exist");
        auto &e = pairs[boost::edge(v1_desc, v2_desc, pairs.graph()).first];
        BOOST_CHECK_MESSAGE(e.distance_ == distance,
                            v1 + "->" + v1+ "edge property distance_ != " + to_string(distance));
        BOOST_CHECK_MESSAGE(e.bridges_.size() == (size_t)links,
                            v1 + "->" + v1 + "edge property links_ != " + to_string(distance));
        BOOST_CHECK_MESSAGE(e.gapSum() == gapSum,
                            v1 + "->" + v1 + "edge property gapSum_ != " + to_string(distance));
    }

    MatepairGraph matepairGraph;
    ContigSeqHashMap contigs;
    ContigPairGraph pairs;
};

BOOST_FIXTURE_TEST_SUITE(TestContigPairMaker, Fix_CPM)

BOOST_AUTO_TEST_CASE(do_not_pair_if_kmers_arent_unique)
{
    // create some contigs
    contigs.insert({{1, "GGAAT"}, {2, "CCAT"}});

    // pair 2 k-mers
    auto k1_desc = matepairGraph.add_vertex("AA");
    auto k2_desc = matepairGraph.add_vertex("CC");
    auto &k1 = matepairGraph.graph()[k1_desc];
    auto &k2 = matepairGraph.graph()[k2_desc];
    k1.contigId_ = 1U;
    k2.contigId_ = UINT32_MAX; // not unique so pairing conditions aren't satisfied
    boost::add_edge(k1_desc, k2_desc, matepairGraph.graph());

    // pair contigs
    unsigned int distance = 5; // distance between k-mers 5'-ends (insert size)
                               // not important in this case
    ContigPairMaker contigPairMaker(matepairGraph,
                                    contigs,
                                    pairs, distance);
    contigPairMaker.pairContigs();

    // no pairs should be created
    BOOST_CHECK_EQUAL(num_vertices(pairs.graph()), 0);
    BOOST_CHECK_EQUAL(num_edges(pairs.graph()), 0);

    // dummy test for better coverage result
    // just calling ContigPairGraphEdgeProperties default c-tor
    ContigPairGraphEdgeProperties ep;
    BOOST_CHECK_EQUAL(ep.distance_, 0);
    BOOST_CHECK_EQUAL(ep.bridges_.size(), 0);
    BOOST_CHECK_EQUAL(ep.gapSum(), 0);
}

BOOST_AUTO_TEST_CASE(do_not_pair_if_kmers_located_on_same_contig)
{
    // create some contigs
    contigs.insert({{1, "GGAAT"}, {2, "CCAT"}});

    // pair 2 k-mers
    auto k1_desc = matepairGraph.add_vertex("AA");
    auto k2_desc = matepairGraph.add_vertex("CC");
    auto &k1 = matepairGraph.graph()[k1_desc];
    auto &k2 = matepairGraph.graph()[k2_desc];
    //k1.multiple_ = k2.multiple_ = 1U; // other conditions for pairing are satisfied
    k1.contigId_ = k2.contigId_ = 1; // same contig so pairing conditions aren't satisfied
    boost::add_edge(k1_desc, k2_desc, matepairGraph.graph());

    // pair contigs
    unsigned int distance = 5; // distance between k-mers 5'-ends (insert size)
                               // not important in this case
    ContigPairMaker contigPairMaker(matepairGraph,
                                    contigs,
                                    pairs, distance);
    contigPairMaker.pairContigs();

    // no pairs should be created
    BOOST_CHECK_EQUAL(num_vertices(pairs.graph()), 0);
    BOOST_CHECK_EQUAL(num_edges(pairs.graph()), 0);
}

BOOST_AUTO_TEST_CASE(pair_fA_fB)
{
    // 1st case
    //
    // -> -> ::: A-> B->  /  rB-> rA->
    //*******************************************
    // A = GGAAT.CCAT = B                 gap = 1
    //       ||  ||
    //       AA  CC
    //       <---->    distance (insert size) = 6
    //*******************************************

    // create some contigs
    contigs.insert({{1, "GGAAT"}, {2, "CCAT"}});

    // pair 2 k-mers
    auto k1_desc = matepairGraph.add_vertex("AA");
    auto k2_desc = matepairGraph.add_vertex("CC");
    auto &k1 = matepairGraph.graph()[k1_desc];
    auto &k2 = matepairGraph.graph()[k2_desc];
    k1.contigId_ = 1;
    //k1.multiple_ = 1U;
    k1.start_ = 2;
    k1.end_ = 4; // k1.start + kmer_size
    k2.contigId_ = 2;
    //k2.multiple_ = 1;
    k2.start_ = 0;
    k2.end_ = 2;
    boost::add_edge(k1_desc, k2_desc, matepairGraph.graph());

    // pair contigs
    unsigned int distance = 6; // distance between k-mers 5'-ends (insert size)
    ContigPairMaker contigPairMaker(matepairGraph,
                                    contigs,
                                    pairs, distance);
    contigPairMaker.pairContigs();

    BOOST_CHECK_EQUAL(num_vertices(pairs.graph()), 4);
    BOOST_CHECK_EQUAL(num_edges(pairs.graph()), 2);

    // check edges
    int16_t dist = 500; // 6 quantified to 500
    uint32_t links = 1;
    int32_t gapSum = 1;
    checkEdge("f1", "f2", dist, links, gapSum);
    checkEdge("r2", "r1", dist, links, gapSum);
}

BOOST_AUTO_TEST_CASE(pair_fA_rB)
{
    // 2nd case
    //
    // -> <- ::: A-> rB->  / B-> rA->
    //*******************************************
    // A = GGAAT..ATGG = rB               gap = 2
    //       ||     ||
    //       AA     GG
    //       <-------> distance (insert size) = 9
    //*******************************************

    // create some contigs
    contigs.insert({{1, "GGAAT"}, {2, "CCAT"}});

    // pair 2 k-mers
    auto k1_desc = matepairGraph.add_vertex("AA");
    auto k2_desc = matepairGraph.add_vertex("GG");
    auto &k1 = matepairGraph.graph()[k1_desc];
    auto &k2 = matepairGraph.graph()[k2_desc];
    k1.contigId_ = 1;
    //k1.multiple_ = 1U;
    k1.start_ = 2;
    k1.end_ = 3;
    k2.contigId_ = 2;
    //k2.multiple_ = 1;
    k2.start_ = 2;
    k2.end_ = 0;
    boost::add_edge(k1_desc, k2_desc, matepairGraph.graph());

    // pair contigs
    unsigned int distance = 9; // distance between k-mers 5'-ends (insert size)
    ContigPairMaker contigPairMaker(matepairGraph,
                                    contigs,
                                    pairs, distance);
    contigPairMaker.pairContigs();

    BOOST_CHECK_EQUAL(num_vertices(pairs.graph()), 4);
    BOOST_CHECK_EQUAL(num_edges(pairs.graph()), 2);

    // check edges
    int16_t dist = 500; // 9 quantified to 500
    uint32_t links = 1;
    int32_t gapSum = 2;
    checkEdge("f1", "r2", dist, links, gapSum);
    checkEdge("f2", "r1", dist, links, gapSum);
}

BOOST_AUTO_TEST_CASE(pair_rA_B)
{
    // 3rd case
    //
    // <- -> ::: rA-> B-> / rB-> A->
    //*******************************************
    // rA = ATTCC...CCAT = B              gap = 3
    //       ||     ||
    //       TT     CC
    //       <-------> distance (insert size) = 9
    //*******************************************

    // create some contigs
    contigs.insert({{1, "GGAAT"}, {2, "CCAT"}});

    // pair 2 k-mers
    auto k1_desc = matepairGraph.add_vertex("TT");
    auto k2_desc = matepairGraph.add_vertex("CC");
    auto &k1 = matepairGraph.graph()[k1_desc];
    auto &k2 = matepairGraph.graph()[k2_desc];
    k1.contigId_ = 1;
    //k1.multiple_ = 1U;
    k1.start_ = 4;
    k1.end_ = 2;
    k2.contigId_ = 2;
    //k2.multiple_ = 1;
    k2.start_ = 0;
    k2.end_ = 2;
    boost::add_edge(k1_desc, k2_desc, matepairGraph.graph());

    // pair contigs
    unsigned int distance = 9; // distance between k-mers 5'-ends (insert size)
    ContigPairMaker contigPairMaker(matepairGraph,
                                    contigs,
                                    pairs, distance);
    contigPairMaker.pairContigs();

    BOOST_CHECK_EQUAL(num_vertices(pairs.graph()), 4);
    BOOST_CHECK_EQUAL(num_edges(pairs.graph()), 2);

    // check edges
    int16_t dist = 500; // 9 quantified to 500
    uint32_t links = 1;
    int32_t gapSum = 3;
    checkEdge("r1", "f2", dist, links, gapSum);
    checkEdge("r2", "f1", dist, links, gapSum);
}

BOOST_AUTO_TEST_CASE(pair_rA_rB)
{
    // 4th case
    //
    // <- <- ::: rA-> rB-> / B-> A->
    //*******************************************
    // rA = ATTCCATGG = rB                gap = 0
    //       ||    ||
    //       TT    GG
    //       <------>  distance (insert size) = 8
    //*******************************************

    // create some contigs
    contigs.insert({{1, "GGAAT"}, {2, "CCAT"}});

    // pair 2 k-mers
    auto k1_desc = matepairGraph.add_vertex("TT");
    auto k2_desc = matepairGraph.add_vertex("GG");
    auto &k1 = matepairGraph.graph()[k1_desc];
    auto &k2 = matepairGraph.graph()[k2_desc];
    k1.contigId_ = 1;
    //k1.multiple_ = 1U;
    k1.start_ = 4;
    k1.end_ = 2;
    k2.contigId_ = 2;
    //k2.multiple_ = 1;
    k2.start_ = 2;
    k2.end_ = 0;
    boost::add_edge(k1_desc, k2_desc, matepairGraph.graph());

    // pair contigs
    unsigned int distance = 8; // distance between k-mers 5'-ends (insert size)
    ContigPairMaker contigPairMaker(matepairGraph,
                                    contigs,
                                    pairs, distance);
    contigPairMaker.pairContigs();

    BOOST_CHECK_EQUAL(num_vertices(pairs.graph()), 4);
    BOOST_CHECK_EQUAL(num_edges(pairs.graph()), 2);

    // check edges
    int16_t dist = 500; // 8 quantified to 500
    uint32_t links = 1;
    int32_t gapSum = 0;
    checkEdge("r1", "r2", dist, links, gapSum);
    checkEdge("f2", "f1", dist, links, gapSum);
}

BOOST_AUTO_TEST_CASE(do_not_pair_fA_fB_too_big_distance_between_contigs)
{
    // -> -> ::: A-> B->  /  rB-> rA->
    // distance between 5'-ends of k-mers on *contigs* is greater than
    // the same distance between k-mers on *read*
    // (exceeded error allowed on this distance)

    // create some contigs
    contigs.insert({{1, "GGAATGCTT"}, {2, "CCAT"}});

    // pair 2 k-mers
    auto k1_desc = matepairGraph.add_vertex("AA");
    auto k2_desc = matepairGraph.add_vertex("CC");
    auto &k1 = matepairGraph.graph()[k1_desc];
    auto &k2 = matepairGraph.graph()[k2_desc];
    k1.contigId_ = 1;
    //k1.multiple_ = 1U;
    k1.start_ = 2;
    k1.end_ = 3;
    k2.contigId_ = 2;
    //k2.multiple_ = 1;
    k2.start_ = 0;
    k2.end_ = 1;
    boost::add_edge(k1_desc, k2_desc, matepairGraph.graph());

    // pair contigs
    unsigned int distance = 5; // distance between k-mers 5'-ends (insert size)
    ContigPairMaker contigPairMaker(matepairGraph,
                                    contigs,
                                    pairs, distance);
    contigPairMaker.pairContigs();

    // no pairs should be created
    BOOST_CHECK_EQUAL(num_vertices(pairs.graph()), 0);
    BOOST_CHECK_EQUAL(num_edges(pairs.graph()), 0);
}

BOOST_AUTO_TEST_CASE(pair_fA_fB_multiple_links)
{
    // -> -> ::: A-> B->  /  rB-> rA->

    // create some contigs
    contigs.insert({{1, "GGAAT"}, {2, "CCAT"}});

    // create 2 k-mer pairs linking 2 contigs
    auto k1_desc = matepairGraph.add_vertex("AA");
    auto k2_desc = matepairGraph.add_vertex("CC");
    auto &k1 = matepairGraph.graph()[k1_desc];
    auto &k2 = matepairGraph.graph()[k2_desc];
    k1.contigId_ = 1;
    //k1.multiple_ = 1U;
    k1.start_ = 2;
    k1.end_ = 3;
    k2.contigId_ = 2;
    //k2.multiple_ = 1;
    k2.start_ = 0;
    k2.end_ = 1;
    boost::add_edge(k1_desc, k2_desc, matepairGraph.graph());

    auto k3_desc = matepairGraph.add_vertex("AT");
    auto k4_desc = matepairGraph.add_vertex("CA");
    auto &k3 = matepairGraph.graph()[k3_desc];
    auto &k4 = matepairGraph.graph()[k4_desc];
    k3.contigId_ = 1;
    //k3.multiple_ = 1;
    k3.start_ = 3;
    k3.end_ = 4;
    k4.contigId_ = 2;
    //k4.multiple_ = 1;
    k4.start_ = 1;
    k4.end_ = 2;
    boost::add_edge(k3_desc, k4_desc, matepairGraph.graph());

    // pair contigs
    unsigned int distance = 5; // distance between k-mers 5'-ends (insert size)
    ContigPairMaker contigPairMaker(matepairGraph,
                                    contigs,
                                    pairs, distance);
    contigPairMaker.pairContigs();

    BOOST_CHECK_EQUAL(num_vertices(pairs.graph()), 4);
    BOOST_CHECK_EQUAL(num_edges(pairs.graph()), 2);

    // check edges
    int16_t dist = 500; // 5 quantified to 500
    uint32_t links = 2;
    int32_t gapSum = 2;
    checkEdge("f1", "f2", dist, links, gapSum);
    checkEdge("r2", "r1", dist, links, gapSum);
}

BOOST_AUTO_TEST_SUITE_END()
