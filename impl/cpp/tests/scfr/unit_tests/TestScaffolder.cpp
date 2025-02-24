/**
 * \file TestScaffolder.cpp
 * \brief the C++ file with implementation of tests for Scaffolder class
 *
 */

#include <iostream>
#include <cstdlib>
#include <boost/test/unit_test.hpp>
#include "../../../src/scfr/Scaffolder.hpp"
#include "../../../src/scfr/MatepairGraph.hpp"

using namespace dnaasm::scfr;

struct FixSCFR {

    FixSCFR() : matepairGraph(2)  {}
    ~FixSCFR() {}

    unsigned short int minLinks = 1;
    unsigned short int minReads = 1;
    unsigned short int minLinksPerRead = 1;
    float maxRatio = 0.3;
    bool gapFilling = false;
    ContigPairGraph pairs;
    ContigSeqHashMap contigs;
    ReadSeqHashMap reads;
    MatepairGraph matepairGraph;
    std::stringstream scaffoldsCSV;
    std::stringstream scaffoldsFASTA;

    Vertex addMpVertex(const std::string& k) {
        return matepairGraph.add_vertex(k);
    }

    using MGEP = MatepairGraphEdgeProperties;
    Edge addMpEdge(Vertex v1, Vertex v2, MGEP p = MGEP()) {
        return boost::add_edge(v1, v2, p, matepairGraph.graph()).first;
    }

    std::vector<GapInfo> createFakeMGEdgesVec(
        unsigned int count = 1,
        int gapSum = 0)
    {
        BOOST_ASSERT(count > 0);
        auto e = addMpEdge(addMpVertex("AC"), addMpVertex("GT"));
        auto gapLength = std::div(gapSum, count);
        if (gapLength.rem == 0) {
            GapInfo gi(e, 0U, gapLength.quot);
            return std::vector<GapInfo>(count, gi);
        } else {
            std::vector<GapInfo> res;
            GapInfo gi(e, 0U, (int32_t) gapLength.quot);
            GapInfo gi_last(e, 0U, (int32_t) gapLength.rem);
            res.insert(res.end(), count - 1, gi);
            res.emplace_back(gi_last);
            return res;
        }
    }

};

BOOST_FIXTURE_TEST_SUITE(TestScaffolder, FixSCFR)

BOOST_AUTO_TEST_CASE(buildScaffolds_basic)
{
    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);

    // empty contig pair graph - empty result
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(), "");

    // two not paired contigs - result is two scaffolds sorted from longest
    // to shortest
    contigs.emplace(1, std::string("x", 10));
    contigs.emplace(2, std::string("x", 20));
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(), "scaffold1,20,f2Z20\nscaffold2,10,f1Z10\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_right_extension_1)
{
    // prepare contig pairs
    // f1 -> f2, f2 -> f3
    std::string f1 = "f1", f2 = "f2", f3 = "f3";
    auto v1 = boost::add_vertex(f1, f1, pairs);
    auto v2 = boost::add_vertex(f2, f2, pairs);
    auto v3 = boost::add_vertex(f3, f3, pairs);
    ContigPairGraphEdgeProperties ep1, ep2;
    ep1.distance_ = 500;
    ep2.distance_ = -1;
    ep1.bridges_ = createFakeMGEdgesVec(1, 15);
    ep2.bridges_ = createFakeMGEdgesVec(1, -9);
    boost::add_edge(v1, v2, ep1, pairs);
    boost::add_edge(v2, v3, ep2, pairs);

    contigs.emplace(1, std::string("x", 30));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 10));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // result is single scaffold: f1->f2->f3
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,60,f1Z30k1a0.00n1i+0o0m15_f2z20k1a0.00n1i+0o0m-9_f3z10\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_right_extension_2)
{
    // prepare contig pairs
    // f1 -> r2, r2 -> f3
    std::string f1 = "f1", r2 = "r2", f3 = "f3";
    auto v1 = boost::add_vertex(f1, f1, pairs);
    auto v2 = boost::add_vertex(r2, r2, pairs);
    auto v3 = boost::add_vertex(f3, f3, pairs);
    ContigPairGraphEdgeProperties ep1, ep2;
    ep1.distance_ = 500;
    ep2.distance_ = -1;
    ep1.bridges_ = createFakeMGEdgesVec(1, 15);
    ep2.bridges_ = createFakeMGEdgesVec(1, -9);
    boost::add_edge(v1, v2, ep1, pairs);
    boost::add_edge(v2, v3, ep2, pairs);

    contigs.emplace(1, std::string("x", 30));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 10));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // result is single scaffold: f1->r2->f3
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,60,f1Z30k1a0.00n1i+0o0m15_r2z20k1a0.00n1i+0o0m-9_f3z10\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_left_extension_1)
{
    // prepare contig pairs
    // r1 -> r2, r2 -> r3
    std::string r1 = "r1", r2 = "r2", r3 = "r3";
    auto v1 = boost::add_vertex(r1, r1, pairs);
    auto v2 = boost::add_vertex(r2, r2, pairs);
    auto v3 = boost::add_vertex(r3, r3, pairs);
    ContigPairGraphEdgeProperties ep1, ep2;
    ep1.distance_ = 500;
    ep2.distance_ = -1;
    ep1.bridges_ = createFakeMGEdgesVec(1, 15);
    ep2.bridges_ = createFakeMGEdgesVec(1, -9);
    boost::add_edge(v1, v2, ep1, pairs);
    boost::add_edge(v2, v3, ep2, pairs);

    contigs.emplace(1, std::string("x", 30));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 10));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // result is single scaffold: f3->f2->f1
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,60,f3z10k1a0.00n1i+0o0m-9_f2z20k1a0.00n1i+0o0m15_f1Z30\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_left_extension_2)
{
    // prepare contig pairs
    // r1 -> f2, f2 -> r3
    std::string r1 = "r1", f2 = "f2", r3 = "r3";
    auto v1 = boost::add_vertex(r1, r1, pairs);
    auto v2 = boost::add_vertex(f2, f2, pairs);
    auto v3 = boost::add_vertex(r3, r3, pairs);
    ContigPairGraphEdgeProperties ep1, ep2;
    ep1.distance_ = 500;
    ep2.distance_ = -1;
    ep1.bridges_ = createFakeMGEdgesVec(1, 15);
    ep2.bridges_ = createFakeMGEdgesVec(1, -9);
    boost::add_edge(v1, v2, ep1, pairs);
    boost::add_edge(v2, v3, ep2, pairs);

    contigs.emplace(1, std::string("x", 30));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 10));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // result is single scaffold: f3->r2->f1
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,60,f3z10k1a0.00n1i+0o0m-9_r2z20k1a0.00n1i+0o0m15_f1Z30\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_both_direction_extension_1)
{
    // prepare contig pairs
    // f1 -> f2, r1 -> r3
    std::string f1 = "f1", r1 = "r1", f2 = "f2", r3 = "r3";
    auto v1 = boost::add_vertex(f1, f1, pairs);
    auto v2 = boost::add_vertex(r1, r1, pairs);
    auto v3 = boost::add_vertex(f2, f2, pairs);
    auto v4 = boost::add_vertex(r3, r3, pairs);
    ContigPairGraphEdgeProperties ep1, ep2;
    ep1.distance_ = 500;
    ep2.distance_ = -1;
    ep1.bridges_ = createFakeMGEdgesVec(1, 15);
    ep2.bridges_ = createFakeMGEdgesVec(1, -9);
    boost::add_edge(v1, v3, ep1, pairs);
    boost::add_edge(v2, v4, ep2, pairs);

    contigs.emplace(1, std::string("x", 30));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 10));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // result is single scaffold: f3->f1->f2
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,60,f3z10k1a0.00n1i+0o0m-9_f1Z30k1a0.00n1i+0o0m15_f2z20\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_both_direction_extension_2)
{
    // prepare contig pairs
    // f1 -> r2, r1 -> f3
    std::string f1 = "f1", r1 = "r1", r2 = "r2", f3 = "f3";
    auto v1 = boost::add_vertex(f1, f1, pairs);
    auto v2 = boost::add_vertex(r1, r1, pairs);
    auto v3 = boost::add_vertex(r2, r2, pairs);
    auto v4 = boost::add_vertex(f3, f3, pairs);
    ContigPairGraphEdgeProperties ep1, ep2;
    ep1.distance_ = 500;
    ep2.distance_ = -1;
    ep1.bridges_ = createFakeMGEdgesVec(1, 15);
    ep2.bridges_ = createFakeMGEdgesVec(1, -9);
    boost::add_edge(v1, v3, ep1, pairs);
    boost::add_edge(v2, v4, ep2, pairs);

    contigs.emplace(1, std::string("x", 30));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 10));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // result is single scaffold: r3->f1->r2
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,60,r3z10k1a0.00n1i+0o0m-9_f1Z30k1a0.00n1i+0o0m15_r2z20\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_two_scaffolds_1)
{
    // prepare contig pairs
    // f1 -> f2, r3 -> f1
    std::string f1 = "f1", f2 = "f2", r3 = "r3";
    auto v1 = boost::add_vertex(f1, f1, pairs);
    auto v2 = boost::add_vertex(f2, f2, pairs);
    auto v3 = boost::add_vertex(r3, r3, pairs);
    ContigPairGraphEdgeProperties ep1, ep2;
    ep1.distance_ = 500;
    ep2.distance_ = -1;
    ep1.bridges_ = createFakeMGEdgesVec(1, 15);
    ep2.bridges_ = createFakeMGEdgesVec(1, -9);
    boost::add_edge(v1, v2, ep1, pairs);
    boost::add_edge(v3, v1, ep2, pairs);

    contigs.emplace(1, std::string("x", 30));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 10));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // results is two scaffolds: f1->f2 and r3
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,50,f1Z30k1a0.00n1i+0o0m15_f2z20\nscaffold2,10,f3Z10\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_two_scaffolds_2)
{
    // prepare contig pairs
    // f1 -> f2, r1 -> r3
    std::string f1 = "f1", r1 = "r1", f2 = "f2", r3 = "r3";
    auto v1 = boost::add_vertex(f1, f1, pairs);
    auto v2 = boost::add_vertex(r1, r1, pairs);
    auto v3 = boost::add_vertex(f2, f2, pairs);
    auto v4 = boost::add_vertex(r3, r3, pairs);
    ContigPairGraphEdgeProperties ep1, ep2;
    ep1.distance_ = 500;
    ep2.distance_ = -1;
    ep1.bridges_ = createFakeMGEdgesVec(1, 15);
    ep2.bridges_ = createFakeMGEdgesVec(1, -9);
    boost::add_edge(v1, v3, ep1, pairs);
    boost::add_edge(v2, v4, ep2, pairs);

    contigs.emplace(1, std::string("x", 20));
    contigs.emplace(2, std::string("x", 30)); // now 2nd contig is the longest
    contigs.emplace(3, std::string("x", 10));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // results is two scaffolds: f2 and f3->f1
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,30,f2Z30\nscaffold2,30,f3z10k1a0.00n1i+0o0m-9_f1Z20\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_min_links_not_satisfied)
{
    // prepare contig pairs
    // f1 -> f2, f2 -> f3
    std::string f1 = "f1", f2 = "f2", f3 = "f3";
    auto v1 = boost::add_vertex(f1, f1, pairs);
    auto v2 = boost::add_vertex(f2, f2, pairs);
    auto v3 = boost::add_vertex(f3, f3, pairs);
    ContigPairGraphEdgeProperties ep1, ep2;
    ep1.distance_ = 500;
    ep2.distance_ = 1000;
    ep1.bridges_ = createFakeMGEdgesVec(2, 250);
    ep2.bridges_ = createFakeMGEdgesVec(1, 1500);
    boost::add_edge(v1, v2, ep1, pairs);
    boost::add_edge(v2, v3, ep2, pairs);

    contigs.emplace(1, std::string("x", 50));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 10));

    unsigned int minLinks = 2;
    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // results is two scaffolds: f1->f2 and f3
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,70,f1Z50k2a0.00n1i+0o0m125_f2z20\nscaffold2,10,f3Z10\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_max_ratio_satisfied)
{
    // prepare contig pairs
    // f1 -> f2, f2 -> f3, f2 -> f4
    std::string f1 = "f1", f2 = "f2", f3 = "f3", f4 = "f4";
    auto v1 = boost::add_vertex(f1, f1, pairs);
    auto v2 = boost::add_vertex(f2, f2, pairs);
    auto v3 = boost::add_vertex(f3, f3, pairs);
    auto v4 = boost::add_vertex(f4, f4, pairs);
    ContigPairGraphEdgeProperties ep1, ep2, ep3;
    ep1.distance_ = 500;
    ep2.distance_ = ep3.distance_ = 1000;
    ep1.bridges_ = createFakeMGEdgesVec(1, 250);
    ep2.bridges_ = createFakeMGEdgesVec(10, 1500);
    ep3.bridges_ = createFakeMGEdgesVec(40, 1200);
    boost::add_edge(v1, v2, ep1, pairs);
    boost::add_edge(v2, v3, ep2, pairs);
    boost::add_edge(v2, v4, ep3, pairs);

    contigs.emplace(1, std::string("x", 50));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 15));
    contigs.emplace(4, std::string("x", 10));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // results is two scaffolds: f1->f2->f4 and f3
    // ratio 10/40 is not geater than default maxRatio = 0.3
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,80,f1Z50k1a0.00n1i+0o0m250_f2z20k40a0.25n1i+0o0m30_f4z10\nscaffold2,15,f3Z15\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_max_ratio_not_satisfied)
{
    // prepare contig pairs
    // f1 -> f2, f2 -> f3, f2 -> f4
    std::string f1 = "f1", f2 = "f2", f3 = "f3", f4 = "f4";
    auto v1 = boost::add_vertex(f1, f1, pairs);
    auto v2 = boost::add_vertex(f2, f2, pairs);
    auto v3 = boost::add_vertex(f3, f3, pairs);
    auto v4 = boost::add_vertex(f4, f4, pairs);
    ContigPairGraphEdgeProperties ep1, ep2, ep3;
    ep1.distance_ = 500;
    ep2.distance_ = ep3.distance_ = 1000;
    ep1.bridges_ = createFakeMGEdgesVec(1, 250);
    ep2.bridges_ = createFakeMGEdgesVec(10, 1500);
    ep3.bridges_ = createFakeMGEdgesVec(30, 1200);
    boost::add_edge(v1, v2, ep1, pairs);
    boost::add_edge(v2, v3, ep2, pairs);
    boost::add_edge(v2, v4, ep3, pairs);

    contigs.emplace(1, std::string("x", 50));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 15));
    contigs.emplace(4, std::string("x", 10));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // results is three scaffolds: f1->f2, f3 and f4
    // ratio 10/30 is geater than default maxRatio = 0.3
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                      "scaffold1,70,f1Z50k1a0.00n1i+0o0m250_f2z20\nscaffold2,15,f3Z15\nscaffold3,10,f4Z10\n");
}

BOOST_AUTO_TEST_CASE(buildScaffolds_contig_paired_on_multiple_distances)
{
    // prepare contig pairs
    // f1 -> f2, f1 -> f3
    std::string f1 = "f1", f2 = "f2", f3 = "f3";
    auto v1 = boost::add_vertex(f1, f1, pairs);
    auto v2 = boost::add_vertex(f2, f2, pairs);
    auto v3 = boost::add_vertex(f3, f3, pairs);
    ContigPairGraphEdgeProperties ep1, ep2;
    ep1.distance_ = 5000;
    ep2.distance_ = 500;
    ep1.bridges_ = createFakeMGEdgesVec(1, 4500);
    ep2.bridges_ = createFakeMGEdgesVec(1, 490);
    boost::add_edge(v1, v2, ep1, pairs);
    boost::add_edge(v1, v3, ep2, pairs);

    contigs.emplace(1, std::string("x", 50));
    contigs.emplace(2, std::string("x", 20));
    contigs.emplace(3, std::string("x", 15));

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.buildScaffolds(pairs, contigs, scaffoldsCSV);

    // results is three scaffolds: f1->f3 and f2
    // f1 was finally paired with f3 because distance between f1 and f3
    // was smaller than between f1 and f2
    BOOST_CHECK_EQUAL(scaffoldsCSV.str(),
                     "scaffold1,65,f1Z50k1a0.00n1i+0o0m490_f3z15\nscaffold2,20,f2Z20\n");
}

BOOST_AUTO_TEST_CASE(saveScaffoldsToFasta_wrong_csv)
{
    scaffoldsCSV << "hello,there\nmy,friend\n";

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.saveScaffoldsToFasta(contigs, reads, scaffoldsCSV, scaffoldsFASTA, gapFilling);
    BOOST_CHECK_EQUAL(scaffoldsFASTA.str(), "");
}

BOOST_AUTO_TEST_CASE(saveScaffoldsToFasta_not_recognized_contig_id_in_csv)
{
    scaffoldsCSV << "scaffold1,999,f3Z999\n";

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.saveScaffoldsToFasta(contigs, reads, scaffoldsCSV, scaffoldsFASTA, gapFilling);
    BOOST_CHECK_EQUAL(scaffoldsFASTA.str(), ">scaffold1,999,f3Z999\n");
}

BOOST_AUTO_TEST_CASE(saveScaffoldsToFasta_one_contig)
{
    scaffoldsCSV << "scaffold1,999,f1Z999\n";
    contigs.emplace(1, "ACGA");

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.saveScaffoldsToFasta(contigs, reads, scaffoldsCSV, scaffoldsFASTA, gapFilling);
    BOOST_CHECK_EQUAL(scaffoldsFASTA.str(), ">scaffold1,999,f1Z999\nACGA\n");
}

BOOST_AUTO_TEST_CASE(saveScaffoldsToFasta_two_contigs_with_gap)
{
    scaffoldsCSV << "scaffold1,9,f1Z4k10a0.12n1i+0o0m3_r2z5\n";
    contigs.emplace(1, "ACGA");
    contigs.emplace(2, "GTACG");

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.saveScaffoldsToFasta(contigs, reads, scaffoldsCSV, scaffoldsFASTA, gapFilling);
    BOOST_CHECK_EQUAL(scaffoldsFASTA.str(),
                      ">scaffold1,9,f1Z4k10a0.12n1i+0o0m3_r2z5\nACGANNNCGTAC\n");
}

BOOST_AUTO_TEST_CASE(saveScaffoldsToFasta_two_contigs_with_overlap)
{
    scaffoldsCSV << "scaffold1,9,f1Z4k10a0.12n1i+0o0m-3_r2z5\n";
    contigs.emplace(1, "ACGA");
    contigs.emplace(2, "GTACG");

    Scaffolder scfr(minLinks, minReads, minLinksPerRead, maxRatio, matepairGraph);
    scfr.saveScaffoldsToFasta(contigs, reads, scaffoldsCSV, scaffoldsFASTA, gapFilling);
    BOOST_CHECK_EQUAL(scaffoldsFASTA.str(),
                      ">scaffold1,9,f1Z4k10a0.12n1i+0o0m-3_r2z5\nACGAnCGTAC\n");
}
BOOST_AUTO_TEST_SUITE_END()
