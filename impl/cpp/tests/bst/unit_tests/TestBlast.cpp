#include <boost/test/unit_test.hpp>
#include <sstream>
#include <iostream>
#include "../../../src/bst/Blast.hpp"

using namespace dnaasm::bst;
using namespace std;
class F : public Blast {
public:
    F() : Blast(5, 1) {}
};
using seqV = vector<string>;

BOOST_FIXTURE_TEST_SUITE(BlastTests, F)

BOOST_AUTO_TEST_CASE(blast_create_words_map)
{
    seqV s = {};
    findWords(s);
    BOOST_CHECK_EQUAL(wordsMap_[1023].size(), 0);
}

BOOST_AUTO_TEST_CASE(blast_hash)
{
    BOOST_CHECK_EQUAL(hash("GCATG"), 590);
}

BOOST_AUTO_TEST_CASE(blast_hash_sequence)
{
    seqV s = {"CACAC", "GCTTA"};
    findWords(s);
    Word w1 = wordsMap_[273].front();
    Word w2 = wordsMap_[636].front();
    BOOST_CHECK_EQUAL(w1.index(), 0);
    BOOST_CHECK_EQUAL(w1.sequence(), 0);
    BOOST_CHECK_EQUAL(w2.index(), 0);
    BOOST_CHECK_EQUAL(w2.sequence(), 1);
}

BOOST_AUTO_TEST_CASE(blast_association_table_elements_size)
{
    seqV s = {"GGCCAA", "GCCAAC"};
    findWords(s);
    createAssociationTable();
    std::vector<WordAssoc>* at0 = &associationTable_[0];
    std::vector<WordAssoc>* at1 = &associationTable_[1];
    BOOST_CHECK_EQUAL((*at0).size(), 1);
    BOOST_CHECK_EQUAL((*at1).size(), 1);
}

BOOST_AUTO_TEST_CASE(blast_create_association_table_onevector)
{
    seqV s = {"GGCCAA", "GCCAAC"};
    findWords(s);
    createAssociationTable();
    std::vector<WordAssoc>* at0 = &associationTable_[0];
    std::vector<WordAssoc>* at1 = &associationTable_[1];
    auto s0 = (*at0)[0];
    auto s1 = (*at1)[0];
    BOOST_CHECK_EQUAL(s0.index(), 0);
    BOOST_CHECK_EQUAL(s0.sequence(), 1);
    BOOST_CHECK_EQUAL(s0.selfIndex(), 1);
    BOOST_CHECK_EQUAL(s1.index(), 1);
    BOOST_CHECK_EQUAL(s1.sequence(), 0);
    BOOST_CHECK_EQUAL(s1.selfIndex(), 0);
}

BOOST_AUTO_TEST_CASE(blast_sort_arays)
{
    associationTable_ = std::make_unique<std::vector<WordAssoc> []>(1);
    associationTable_[0].emplace_back(Word(3,5), 4);
    associationTable_[0].emplace_back(Word(1,2), 2);
    associationTable_[0].emplace_back(Word(3,4), 5);
    readsCount_ = 1;
    auto table = sortAssociationTable();
    BOOST_CHECK_EQUAL(table[0][0].sequence(), 1);
    BOOST_CHECK_EQUAL(table[0][1].sequence(), 3);
    BOOST_CHECK_EQUAL(table[0][2].sequence(), 3);
    BOOST_CHECK_EQUAL(table[0][0].index(), 2);
    BOOST_CHECK_EQUAL(table[0][1].index(), 5);
    BOOST_CHECK_EQUAL(table[0][2].index(), 4);
}

BOOST_AUTO_TEST_CASE(blast_association_create)
{
    Association a(1,2,3,4);
    BOOST_CHECK_EQUAL(a.start0_, 1);
    BOOST_CHECK_EQUAL(a.end1_, 4);
}

BOOST_AUTO_TEST_CASE(blast_dont_associate_in_same_read)
{
    seqV s = {"ACTGACTGACTGACTG"};
    findWords(s);
    createAssociationTable();
    BOOST_CHECK(associationTable_[0].empty());
}


BOOST_AUTO_TEST_SUITE_END()
