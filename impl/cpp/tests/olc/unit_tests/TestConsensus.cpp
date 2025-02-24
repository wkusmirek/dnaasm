#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../../../src/olc/Consensus.hpp"

using namespace dnaasm::olc;
using namespace std;

class F : public Consensus {
public:
    F() : Consensus(1) {}
};

BOOST_FIXTURE_TEST_SUITE(ConsensusTests, F)

BOOST_AUTO_TEST_CASE(consensus_add)
{
    string s = "CAG";
    add(s);
    auto it = consensus_.begin();
    BOOST_CHECK_EQUAL(it->B[bA], 0);
    BOOST_CHECK_EQUAL(it->B[bC], 1);
    BOOST_CHECK_EQUAL(it++->sum, 1);
    BOOST_CHECK_EQUAL(it->B[bA], 1);
    BOOST_CHECK_EQUAL(it->B[bC], 0);
    BOOST_CHECK_EQUAL(it++->sum, 1);
    BOOST_CHECK_EQUAL(it->B[bG], 1);
    BOOST_CHECK_EQUAL(it++->sum, 1);
    BOOST_CHECK(it == consensus_.end());
}

BOOST_AUTO_TEST_CASE(consensus_score)
{
    string a = "AC", b = "GC";
    add(a);
    iter_ = consensus_.begin();
    add(b);
    auto it = consensus_.begin();
    BOOST_CHECK_EQUAL((*it++).score('A'), 0.0f);
    BOOST_CHECK_EQUAL((*it).score('C'), 1.0f);
}

BOOST_AUTO_TEST_CASE(consensus_compare_1)
{
    string a = "ACG", b = "CGT";
    add(a);
    compare(b);
    BOOST_CHECK_EQUAL(toString(), "ACGT");
}

BOOST_AUTO_TEST_CASE(consensus_run_1)
{
    vector<string> s{"CAC", "CTC", "CAC"};
    Layout l{0U, 1U, 2U};
    Consensus c(1);
    c.run(l, s);
    BOOST_CHECK_EQUAL(c.toString(), "CAC");
}

BOOST_AUTO_TEST_CASE(consensus_run_2)
{
    vector<string> s{"ACG", "CGT"};
    Layout l{0U, 1U};
    Consensus c(1);
    c.run(l, s);
    BOOST_CHECK_EQUAL(c.toString(), "ACGT");
}

BOOST_AUTO_TEST_CASE(consensus_run_3)
{
    vector<string> s{"AACCTTGG", "CCTTGGAA"};
    Layout l{0U, 1U};
    Consensus c(1);
    c.run(l, s);
    BOOST_CHECK_EQUAL(c.toString(), "AACCTTGGAA");
}

BOOST_AUTO_TEST_CASE(consensus_run_4)
{
    vector<string> s{"GTA", "TA"};
    Layout l{0U, 1U};
    Consensus c(1);
    c.run(l, s);
    BOOST_CHECK_EQUAL(c.toString(), "GTA");
}

BOOST_AUTO_TEST_CASE(consensus_run_5)
{
    vector<string> s{"ACGGT", "ACGTC", "CGTCA"};
    Layout l{0U, 1U, 2U};
    Consensus c(1);
    c.run(l, s);
    BOOST_CHECK_EQUAL(c.toString(), "ACGTCA");
}

BOOST_AUTO_TEST_CASE(consensus_run_7_errors)
{
    vector<string> s{"CTAGA", "TCGCC"};
    Layout l{0U, 1U};
    Consensus c(1);
    c.run(l, s);
    BOOST_CHECK_EQUAL(c.toString(), "CTAGAC");
}

BOOST_AUTO_TEST_CASE(consensus_run_8_cornercut)
{
    vector<string> s{"ACTG", "ACTG"};
    Layout l{0U, 1U};
    Consensus c(2);
    c.run(l, s);
    BOOST_CHECK_EQUAL(c.toString(), "ACTG");
}

BOOST_AUTO_TEST_CASE(consensus_run_9_multiple)
{
    vector<string> s{"GCGT", "GTAA"};
    Layout l{0U, 1U};
    Consensus c(1);
    c.run(l, s);
    BOOST_CHECK_EQUAL(c.toString(), "GCGTAA");
}

BOOST_AUTO_TEST_SUITE_END()
