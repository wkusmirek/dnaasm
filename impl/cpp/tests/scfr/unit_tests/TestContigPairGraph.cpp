/**
 * \file TestContigPairGraph.cpp
 * \brief the C++ file with implementation of tests for ContigPairGraph module
 *
 */
#include <boost/test/unit_test.hpp>
#include <vector>
#include "../../../src/scfr/ContigPairGraph.hpp"

using namespace dnaasm::scfr;
using namespace std;

struct Fix_CPG {

    Fix_CPG() : matepairGraph(2)  {}
    ~Fix_CPG() {}

    MatepairGraph matepairGraph;

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

BOOST_FIXTURE_TEST_SUITE(TestContigPairGraph, Fix_CPG)

BOOST_AUTO_TEST_CASE(ContigPairGraphEdgeProperties_gapSum)
{
    int16_t distanceCat1 = -1;
    int16_t distanceCat2 = 500;

    ContigPairGraphEdgeProperties ep1(distanceCat1);
    ContigPairGraphEdgeProperties ep2(distanceCat2);

    // check gapSum method when no links
    BOOST_CHECK_EQUAL(ep1.gapSum(), 0);
    BOOST_CHECK_EQUAL(ep2.gapSum(), 0);

    // add some links (bridges) for contig pairs
    int someGapSum1 = -300;
    int someGapSum2 = 500;
    ep1.bridges_ = createFakeMGEdgesVec(10, someGapSum1);
    ep2.bridges_ = createFakeMGEdgesVec(20, someGapSum2);

    // check gapSum method
    BOOST_CHECK_EQUAL(ep1.gapSum(), someGapSum1);
    BOOST_CHECK_EQUAL(ep2.gapSum(), someGapSum2);
}

BOOST_AUTO_TEST_CASE(getAllParallelEdges)
{
    ContigPairGraph graph;
    using ParEdgeVec = std::vector<ContigPairGraphEdge>;

    // add some vertices to graph
    std::string c1 = "ACT";
    std::string c2 = "TGC";
    std::string c3 = "CAT";
    auto v1 = boost::add_vertex(c1, c1, graph);
    auto v2 = boost::add_vertex(c2, c2, graph);
    auto v3 = boost::add_vertex(c3, c3, graph);

    // test getAllParallelEdges when no edges at all
    ParEdgeVec pev1v2_before =
        dnaasm::scfr::getAllParallelEdges(v1, v2, graph);
    ParEdgeVec pev1v3_before =
        dnaasm::scfr::getAllParallelEdges(v1, v3, graph);
    ParEdgeVec pev2v3_before =
        dnaasm::scfr::getAllParallelEdges(v2, v3, graph);
    BOOST_CHECK(pev1v2_before.empty());
    BOOST_CHECK(pev1v3_before.empty());
    BOOST_CHECK(pev2v3_before.empty());


    // add some edges to graph (one directional)
    ContigPairGraphEdgeProperties ep1(-1);
    ContigPairGraphEdgeProperties ep2(500);
    ContigPairGraphEdgeProperties ep3(1000);
    auto e1 = boost::add_edge(v1, v2, ep1, graph).first;
    auto e2 = boost::add_edge(v1, v2, ep2, graph).first;
    auto e3 = boost::add_edge(v1, v3, ep3, graph).first;

    // test getAllParallelEdges
    ParEdgeVec expPEv1v2 {e1, e2};
    ParEdgeVec expPEv1v3 {e3};
    ParEdgeVec pev1v2 = dnaasm::scfr::getAllParallelEdges(v1, v2, graph);
    ParEdgeVec pev1v3 = dnaasm::scfr::getAllParallelEdges(v1, v3, graph);
    ParEdgeVec pev2v3 = dnaasm::scfr::getAllParallelEdges(v2, v3, graph);

    BOOST_CHECK_EQUAL_COLLECTIONS(pev1v2.begin(), pev1v2.end(),
                                  expPEv1v2.begin(), expPEv1v2.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(pev1v3.begin(), pev1v3.end(),
                                  expPEv1v3.begin(), expPEv1v3.end());
    BOOST_CHECK(pev2v3.empty());

    // and check reversed parallel edges - should return empty vec
    // since edge in graph are one directional
    ParEdgeVec pev2v1 = dnaasm::scfr::getAllParallelEdges(v2, v1, graph);
    ParEdgeVec pev3v1 = dnaasm::scfr::getAllParallelEdges(v3, v1, graph);
    ParEdgeVec pev3v2 = dnaasm::scfr::getAllParallelEdges(v3, v2, graph);

    BOOST_CHECK(pev2v1.empty());
    BOOST_CHECK(pev3v1.empty());
    BOOST_CHECK(pev3v2.empty());
}

BOOST_AUTO_TEST_CASE(createLinksPerReadVec)
{
    // create some edges in matepair graph
    auto mpV1 = addMpVertex("ABCD");
    auto mpV2 = addMpVertex("EFGH");
    auto mpV3 = addMpVertex("IJKL");
    auto mpV4 = addMpVertex("MNOP");
    auto mpV5 = addMpVertex("RSTU");
    auto mpV6 = addMpVertex("VWXY");
    uint32_t readId1 = 11;
    uint32_t readId2 = 44;
    MGEP mpep1 = MGEP(readId1, 0U);
    MGEP mpep2 = MGEP(readId1, 100U);
    MGEP mpep3 = MGEP(readId2, 0U);
    auto mpe1 = addMpEdge(mpV1, mpV2, mpep1);
    auto mpe2 = addMpEdge(mpV3, mpV4, mpep2);
    auto mpe3 = addMpEdge(mpV5, mpV6, mpep3);

    ContigPairGraph graph;

    // create one edge in contig graph
    std::string c1 = "ACT";
    std::string c2 = "TGC";
    auto v1 = boost::add_vertex(c1, c1, graph);
    auto v2 = boost::add_vertex(c2, c2, graph);

    int16_t distanceCat = 500;
    ContigPairGraphEdgeProperties ep(distanceCat);
    ep.bridges_.emplace_back(mpe1, 0U, 10);
    ep.bridges_.emplace_back(mpe2, 0U, 10);
    ep.bridges_.emplace_back(mpe3, 0U, 10);
    auto e_desc = boost::add_edge(v1, v2, ep, graph).first;
    auto pair = graph[e_desc];


    // check gapSum method when no links
    LinksPerReadVec lprVec =
        dnaasm::scfr::createLinksPerReadVec(pair, matepairGraph);

    BOOST_CHECK_EQUAL(lprVec.size(), 2);
    BOOST_CHECK_EQUAL(lprVec[0].first, readId1);
    BOOST_CHECK_EQUAL(lprVec[0].second, 2);
    BOOST_CHECK_EQUAL(lprVec[1].first, readId2);
    BOOST_CHECK_EQUAL(lprVec[1].second, 1);
}

BOOST_AUTO_TEST_SUITE_END()
