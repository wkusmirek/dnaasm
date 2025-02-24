#include <boost/test/unit_test.hpp>
#include <sstream>
#include <iostream>
#include "../../../src/bst/GraphBuilder.hpp"
#include "../../../src/bst/Blast.hpp"

using namespace dnaasm::bst;
using namespace std;
using namespace boost;

class F : public GraphBuilder {
public:
    F() : GraphBuilder() {}
};
using seqV = vector<string>;
bool operator==(const As& a, const As& b)
{
    return a.start0_ == b.start0_ &&
           a.start1_ == b.start1_ &&
           a.end0_   == b.end0_   &&
           a.end1_   == b.end1_;
}

BOOST_FIXTURE_TEST_SUITE(GraphBuilderTests, F)

BOOST_AUTO_TEST_CASE(graphbuilder_build_boost_graph)
{
    OverlapGraph g(2);
    As a(1,2,3,4);
    add_edge(0, 1, EP(a), g);
    auto e = edges(g);
    auto asioejszons = get(&EP::assoc_, g);
    As as = asioejszons[*e.first];
    BOOST_CHECK(as == a);
}

BOOST_AUTO_TEST_CASE(graphbuilder_build_graph_two_seq)
{
    auto associationTable_ = std::make_unique<std::vector<WordAssoc> []>(2);
    associationTable_[0].emplace_back(Word(1,0), 4);
    associationTable_[1].emplace_back(Word(0,4), 0);
    buildOverlapGraph(0, 5, 2, std::move(associationTable_));
    auto e = edges(*graph_);
    auto a = get(&EP::assoc_, *graph_);
    auto i = e.first;
    As as0 = a[*i++];
    BOOST_CHECK(as0 == As(4, 0, 8, 4));
    BOOST_CHECK(i == e.second);
}

BOOST_AUTO_TEST_CASE(graphbuilder_graph_full)
{
    seqV s = {"CGTACGTGTACATATAGTCGTAA",
              "CGGTCGCCCTCTGCGTACGTGTA",
              "TTAGTCGTAGTATCGTATGGAGA"};
    Blast b(5, 1);
    b.findWords(s);
    b.createAssociationTable();
    buildOverlapGraph(0, 5, 3, std::move(b.sortAssociationTable()));
    auto e10 = edge(1, 0, *graph_);
    auto e02 = edge(0, 2, *graph_);
    auto a = get(&EP::assoc_, *graph_);
    BOOST_CHECK(e10.second);
    BOOST_CHECK(e02.second);
    BOOST_CHECK(a[e10.first] == As(13, 0, 22, 9));
    BOOST_CHECK(a[e02.first] == As(14, 1, 21, 8));
    BOOST_CHECK_EQUAL(num_edges(*graph_), 2);
    BOOST_CHECK_EQUAL(a[e10.first].score_, (float)1);
}

BOOST_AUTO_TEST_CASE(graphbuilder_graph_remove_transitive_edges)
{
    seqV s = {"GTGCCGGTT",
              "CTACGTGCC",
              "ACGTGCCGG"};
    Blast b(5, 1);
    b.findWords(s);
    b.createAssociationTable();
    buildOverlapGraph(0, 5, 3, std::move(b.sortAssociationTable()));
    BOOST_CHECK_EQUAL(num_edges(*graph_), 3);
    removeTransitiveEdges();
    BOOST_CHECK_EQUAL(num_edges(*graph_), 2);
    auto e12 = edge(1, 2, *graph_);
    auto e20 = edge(2, 0, *graph_);
    BOOST_CHECK(e12.second);
    BOOST_CHECK(e20.second);
}

BOOST_AUTO_TEST_CASE(graphbuilder_remove_cycles_simple)
{
    graph_ = std::make_unique<OverlapGraph>(3);
    As a(1,2,3,4);
    boost::add_edge(0, 1, EP(a), *graph_);
    boost::add_edge(1, 2, EP(a), *graph_);
    boost::add_edge(2, 0, EP(a), *graph_);
    BOOST_CHECK_EQUAL(num_edges(*graph_), 3);
    removeCycles();
    BOOST_CHECK_EQUAL(num_edges(*graph_), 2);
}

BOOST_AUTO_TEST_CASE(graphbuilder_dont_remove_cycle)
{
    graph_ = std::make_unique<OverlapGraph>(3);
    As a(1,2,3,4);
    boost::add_edge(0, 1, EP(a), *graph_);
    boost::add_edge(1, 2, EP(a), *graph_);
    boost::add_edge(0, 2, EP(a), *graph_);
    BOOST_CHECK_EQUAL(num_edges(*graph_), 3);
    removeCycles();
    BOOST_CHECK_EQUAL(num_edges(*graph_), 3);
}

BOOST_AUTO_TEST_CASE(graphbuilder_two_cycles)
{
    graph_ = std::make_unique<OverlapGraph>(3);
    As a(1,2,3,4);
    boost::add_edge(0, 1, EP(a), *graph_);
    boost::add_edge(1, 2, EP(a), *graph_);
    boost::add_edge(1, 0, EP(a), *graph_);
    boost::add_edge(2, 0, EP(a), *graph_);
    BOOST_CHECK_EQUAL(num_edges(*graph_), 4);
    removeCycles();
    BOOST_CHECK_EQUAL(num_edges(*graph_), 2);
    auto e01 = edge(0, 1, *graph_);
    auto e12 = edge(1, 2, *graph_);
    BOOST_CHECK(e01.second);
    BOOST_CHECK(e12.second);
}

BOOST_AUTO_TEST_CASE(graphbuilder_getLayouts)
{
    seqV s = {"GTGCCGGTT",
              "CTACGTGCC",
              "ACGTGCCGG"}; // 1 2 0
    Blast b(5, 1);
    b.findWords(s);
    b.createAssociationTable();
    buildOverlapGraph(0, 5, 3, std::move(b.sortAssociationTable()));
    removeTransitiveEdges();
    auto layouts = getLayouts();
    BOOST_CHECK_EQUAL(1, layouts[0][0].first);
    BOOST_CHECK_EQUAL(2, layouts[0][1].first);
    BOOST_CHECK_EQUAL(0, layouts[0][2].first);
}

BOOST_AUTO_TEST_CASE(graphbuilder_longest_path)
{
    graph_ = std::make_unique<OverlapGraph>(7);
    readsCount_ = 7;
    As a(1,2,3,4);
    boost::add_edge(0, 1, EP(a), *graph_);
    boost::add_edge(1, 2, EP(a), *graph_);
    boost::add_edge(1, 3, EP(a), *graph_);
    boost::add_edge(2, 4, EP(a), *graph_);
    boost::add_edge(2, 5, EP(a), *graph_);
    boost::add_edge(5, 6, EP(a), *graph_);
    auto layouts = getLayouts();
    BOOST_CHECK_EQUAL(layouts.size(), 1);
    BOOST_CHECK_EQUAL(layouts[0].size(), 5);
}

BOOST_AUTO_TEST_SUITE_END()
