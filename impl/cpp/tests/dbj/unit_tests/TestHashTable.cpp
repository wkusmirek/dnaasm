/**
 * \file TestHashTable.cpp
 * \brief the C++ file with implementation of tests for HashTable type
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/globals.hpp"

using namespace dnaasm::dbj;
using namespace std;


BOOST_AUTO_TEST_SUITE(TestHashTable)

BOOST_AUTO_TEST_CASE(HashTable_clear)
{
    unsigned short K1 = 3U;
    HashTable hashTable(K1);
    bitset<2*MAX_KMER_LENGTH> testBitset(string("11"));
    BOOST_CHECK_EQUAL(hashTable.getHashTable().size(), 0);
    hashTable.getHashTable().insert(HashTable::HashTableType::value_type(testBitset, 0U));
    BOOST_CHECK_EQUAL(hashTable.getHashTable().size(), 1);
    hashTable.clear();
    BOOST_CHECK_EQUAL(hashTable.getHashTable().size(), 0);
}

BOOST_AUTO_TEST_CASE(HashTable_size)
{
    unsigned short K1 = 3U;
    HashTable hashTable(K1);
    bitset<2*MAX_KMER_LENGTH> testBitset(string("11"));
    BOOST_CHECK_EQUAL(hashTable.size(), 0);
    hashTable.getHashTable().insert(HashTable::HashTableType::value_type(testBitset, 0U));
    BOOST_CHECK_EQUAL(hashTable.size(), 1);
    hashTable.getHashTable().clear();
    BOOST_CHECK_EQUAL(hashTable.size(), 0);
}

BOOST_AUTO_TEST_CASE(HashTable_begin)
{
    unsigned short K1 = 3U;
    HashTable hashTable(K1);
    bitset<2*MAX_KMER_LENGTH> testBitset(string("11"));
    BOOST_CHECK_EQUAL(hashTable.begin() == hashTable.getHashTable().begin(), true);
    hashTable.getHashTable().insert(HashTable::HashTableType::value_type(testBitset, 0U));
    BOOST_CHECK_EQUAL(hashTable.begin() == hashTable.getHashTable().begin(), true);
}

BOOST_AUTO_TEST_CASE(HashTable_end)
{
    unsigned short K1 = 3U;
    HashTable hashTable(K1);
    bitset<2*MAX_KMER_LENGTH> testBitset(string("11"));
    BOOST_CHECK_EQUAL(hashTable.end() == hashTable.getHashTable().end(), true);
    hashTable.getHashTable().insert(HashTable::HashTableType::value_type(testBitset, 0U));
    BOOST_CHECK_EQUAL(hashTable.end() == hashTable.getHashTable().end(), true);
}

BOOST_AUTO_TEST_CASE(HashTable_isValid)
{
    unsigned short K1 = 3U;
    HashTable hashTable(K1);
    string correct_string = "AACTGACTACTAGCTC";
    string incorrect_string_1 = "NAACTGACTACTAGCTC";
    string incorrect_string_2 = "AACTgACTACTAGCTC";
    BOOST_CHECK_EQUAL(hashTable.isValid(correct_string.data(), K1), true);
    BOOST_CHECK_EQUAL(hashTable.isValid(correct_string.data(), correct_string.size()), true);
    BOOST_CHECK_EQUAL(hashTable.isValid(incorrect_string_1.data(), K1), false);
    BOOST_CHECK_EQUAL(hashTable.isValid(incorrect_string_1.data(), incorrect_string_1.size()), false);
    BOOST_CHECK_EQUAL(hashTable.isValid(incorrect_string_2.data(), K1), true);
    BOOST_CHECK_EQUAL(hashTable.isValid(incorrect_string_2.data(), incorrect_string_2.size()), false);
}

BOOST_AUTO_TEST_CASE(HashTable_basic_find_and_insert_test)   // common tests for find and insert functions
{
    unsigned short K1 = 3U;
    HashTable hashTable(K1);
    string str_1 = "AAA";
    string str_2 = "TTT";
    string str_3 = "AAATTT";
    string str_4 = "TTTAAA";
    BOOST_CHECK_EQUAL(hashTable.getHashTable().size(), 0);
    hashTable.insert(str_1.data(), 0U);
    BOOST_CHECK_EQUAL(hashTable.getHashTable().size(), 1);
    BOOST_CHECK_EQUAL(hashTable.find(str_1.data())->second, 0U);
    BOOST_CHECK_EQUAL(hashTable.find(str_3.data())->second, 0U);
    hashTable.insert(str_3.data(), 0U);
    BOOST_CHECK_EQUAL(hashTable.getHashTable().size(), 1);
    BOOST_CHECK_EQUAL(hashTable.find(str_1.data())->second, 0U);
    BOOST_CHECK_EQUAL(hashTable.find(str_3.data())->second, 0U);
    hashTable.insert(str_3.data(), 1U);
    BOOST_CHECK_EQUAL(hashTable.getHashTable().size(), 1);
    BOOST_CHECK_EQUAL(hashTable.find(str_1.data())->second, 0U);
    BOOST_CHECK_EQUAL(hashTable.find(str_3.data())->second, 0U);
    hashTable.insert(str_2.data(), 2U);
    hashTable.insert(str_4.data(), 1U);
    BOOST_CHECK_EQUAL(hashTable.getHashTable().size(), 2);
    BOOST_CHECK_EQUAL(hashTable.find(str_1.data())->second, 0U);
    BOOST_CHECK_EQUAL(hashTable.find(str_3.data())->second, 0U);
    BOOST_CHECK_EQUAL(hashTable.find(str_2.data())->second, 2U);
    BOOST_CHECK_EQUAL(hashTable.find(str_4.data())->second, 2U);
}

BOOST_AUTO_TEST_SUITE_END()

