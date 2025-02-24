/**
 * \file TestHashTableKeyHash.cpp
 * \brief the C++ file with implementation of tests for HashTableKeyHash structure
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/common/HashTableKeyHash.hpp"

using namespace dnaasm;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestHashTableKeyHash)
/*
BOOST_AUTO_TEST_CASE(HashTableKeyHash_empty_string)
{
    HashTableKeyHash hashTableKeyHash;
    bitset<2*MAX_KMER_LENGTH> bitset0(string(""));
    BOOST_CHECK_EQUAL(hashTableKeyHash(bitset0), 10936482868491892836U);
}

BOOST_AUTO_TEST_CASE(HashTableKeyHash_basic_test)
{
    HashTableKeyHash hashTableKeyHash;
    bitset<2*MAX_KMER_LENGTH> bitset0(string("10110100"));    //ACTG
    BOOST_CHECK_EQUAL(hashTableKeyHash(bitset0), 3398599682373655185U);
    BOOST_CHECK_EQUAL(hashTableKeyHash(bitset0), hashTableKeyHash(bitset0));
}
*/
BOOST_AUTO_TEST_SUITE_END()

