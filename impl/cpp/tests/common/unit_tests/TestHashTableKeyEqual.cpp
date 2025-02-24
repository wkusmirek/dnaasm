/**
 * \file TestHashTableKeyEqual.cpp
 * \brief the C++ file with implementation of tests for HashTableKeyEqual structure
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/common/HashTableKeyEqual.hpp"

using namespace dnaasm;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestHashTableKeyEqual)

BOOST_AUTO_TEST_CASE(HashTableKeyEqual_empty_bitsets)
{
    HashTableKeyEqual hashTableKeyEqual;
    bitset<2*MAX_KMER_LENGTH> bitset0(string(""));
    bitset<2*MAX_KMER_LENGTH> bitset1(string(""));
    BOOST_CHECK_EQUAL(hashTableKeyEqual(bitset0, bitset1), true);
}

BOOST_AUTO_TEST_CASE(HashTableKeyEqual_equal_bitsets)
{
    HashTableKeyEqual hashTableKeyEqual;
    bitset<2*MAX_KMER_LENGTH> bitset0(string("000111"));
    bitset<2*MAX_KMER_LENGTH> bitset1(string("000111"));
    BOOST_CHECK_EQUAL(hashTableKeyEqual(bitset0, bitset1), true);
}

BOOST_AUTO_TEST_CASE(HashTableKeyEqual_not_equal_bitsets)
{
    HashTableKeyEqual hashTableKeyEqual;
    bitset<2*MAX_KMER_LENGTH> bitset0(string("001111"));
    bitset<2*MAX_KMER_LENGTH> bitset1(string("000111"));
    BOOST_CHECK_EQUAL(hashTableKeyEqual(bitset0, bitset1), false);
}

BOOST_AUTO_TEST_SUITE_END()

