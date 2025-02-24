/**
 * \file TestKmerPositionFinder.cpp
 * \brief the C++ file with implementation of tests for KmerPositionFinder class
 *
 */

#include <boost/test/unit_test.hpp>
#include <sstream>
#include "../../../src/common/InputFile.hpp"
#include "../../../src/scfr/KmerPositionFinder.hpp"

using namespace dnaasm::scfr;
using namespace std;

struct FixKPF {

    FixKPF() : matepairGraph(2) {}
    ~FixKPF() {}

    void checkVertexOfUniqueKmer(string kmer, uint32_t contigId,
                                 uint32_t start, uint32_t end
                                 /*, uint16_t multiple*/) {
        auto v_desc = matepairGraph.vertex(kmer);
        BOOST_REQUIRE(v_desc != matepairGraph.graph().null_vertex());
        BOOST_CHECK_MESSAGE(matepairGraph.graph()[v_desc].contigId_ == contigId,
                            kmer + " vertex property contigId_ != " + to_string(contigId));
        //BOOST_CHECK_MESSAGE(matepairGraph.graph()[v_desc].multiple_ == multiple,
        //                    kmer + " vertex property multiple_ != " + to_string(multiple));
        BOOST_CHECK_MESSAGE(matepairGraph.graph()[v_desc].start_ == start,
                            kmer + " vertex property start_ != " + to_string(start));
        BOOST_CHECK_MESSAGE(matepairGraph.graph()[v_desc].end_ == end,
                            kmer + " vertex property end_ != " + to_string(end));
    }

    void checkVertexOfNotUniqueKmer(string kmer) {
        auto v_desc = matepairGraph.vertex(kmer);
        BOOST_CHECK_EQUAL(matepairGraph.graph()[v_desc].contigId_, UINT32_MAX);
    }

    unsigned short int kmerSize = 2;
    unsigned int minContigLength = 3;
    MatepairGraph matepairGraph;
    ContigSeqHashMap contigs;
};

BOOST_FIXTURE_TEST_SUITE(TestKmerPositionFinder, FixKPF)

BOOST_AUTO_TEST_CASE(findKmerPositionOnContigs)
{
    contigs.insert({1, "ACCTG"});
    contigs.insert({2, "TAGC"});
    contigs.insert({3, "GT"});

    // insert some 2-mers into MatepairGraph
    matepairGraph.add_vertex("AA"); // not on contigs
    matepairGraph.add_vertex("AC"); // once on f1
    matepairGraph.add_vertex("CC"); // once on f1
    matepairGraph.add_vertex("CA"); // once on r1
    matepairGraph.add_vertex("CT"); // twice on contigs (incl. reversed)
    matepairGraph.add_vertex("TA"); // twice on contigs (incl. reversed)
    matepairGraph.add_vertex("AG"); // twice on contigs (incl. reversed)
    // These 2-mers exist on contigs (incl. reversed) but are not in Matepair graph:
    // TG, GC, GG, GT

    KmerPositionFinder kpf(matepairGraph, contigs, kmerSize, minContigLength);
    BOOST_CHECK_EQUAL(kpf.findKmerPositionOnContigs(), 2);

    // check updated vertices of unique kmers
    // checkVertexOfUniqueKmer(kmer, contigId, start, end, multiple)
    checkVertexOfUniqueKmer("AA", 0, 0, 0); // not on contigs
    checkVertexOfUniqueKmer("AC", 1, 0, 2); // once on f1
    checkVertexOfUniqueKmer("CC", 1, 1, 3); // once on f1
    checkVertexOfUniqueKmer("CA", 1, 5, 3); // once on r1

    // check updated vertices of non-unique kmers
    checkVertexOfNotUniqueKmer("CT");
    checkVertexOfNotUniqueKmer("TA");
    checkVertexOfNotUniqueKmer("AG");

    // k-mers which exist on contigs but doesn't exist on reads
    // shoudn't be added to graph
    BOOST_CHECK_EQUAL(matepairGraph.vertex("TG"), matepairGraph.graph().null_vertex());
    BOOST_CHECK_EQUAL(matepairGraph.vertex("GC"), matepairGraph.graph().null_vertex());
    BOOST_CHECK_EQUAL(matepairGraph.vertex("GG"), matepairGraph.graph().null_vertex());
    BOOST_CHECK_EQUAL(matepairGraph.vertex("GT"), matepairGraph.graph().null_vertex());
}

BOOST_AUTO_TEST_CASE(findKmerPositionOnContigs_too_short_contigs)
{
    contigs.insert({1, "GT"});

    // insert some 2-mers into MatepairGraph
    matepairGraph.add_vertex("GT");
    matepairGraph.add_vertex("AC");

    KmerPositionFinder kpf(matepairGraph, contigs, kmerSize, minContigLength);
    BOOST_CHECK_EQUAL(kpf.findKmerPositionOnContigs(), 0);

    // contig is shorter than minContigLength
    // so it should not be kmerized
    checkVertexOfUniqueKmer("GT", 0, 0, 0);
    checkVertexOfUniqueKmer("AC", 0, 0, 0);
}

BOOST_AUTO_TEST_SUITE_END()
