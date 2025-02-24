#include <boost/test/unit_test.hpp>
#include <sstream>
#include <iostream>
#include "../../../src/bst/WordAssoc.hpp"
using namespace dnaasm::bst;

BOOST_AUTO_TEST_SUITE(WordTests)

BOOST_AUTO_TEST_CASE(word_get_index)
{
    Word w(0, 42);
    BOOST_CHECK_EQUAL( w.sequence(), 0);
    BOOST_CHECK_EQUAL( w.index(), 42 );
}

BOOST_AUTO_TEST_CASE(word_wordassoc_constructor)
{
    Word w(0,10);
    WordAssoc wa(w, 5);
    BOOST_CHECK_EQUAL( wa.sequence(), 0);
    BOOST_CHECK_EQUAL( wa.index(), 10);
    BOOST_CHECK_EQUAL( wa.selfIndex(), 5);
}

BOOST_AUTO_TEST_CASE(word_assoc_less_operator_by_sequence)
{
    WordAssoc w1(Word(0, 10), 5);
    WordAssoc w2(Word(1, 10), 2);
    BOOST_CHECK(w1 < w2);
}

BOOST_AUTO_TEST_CASE(word_assoc_less_operator_by_self_index)
{
    WordAssoc w1(Word(0, 10), 5);
    WordAssoc w2(Word(0, 20), 2);
    BOOST_CHECK(w2 < w1);
}

BOOST_AUTO_TEST_SUITE_END()
