/**
 * \file TestHashTableMultipleValue.cpp
 * \brief the C++ file with implementation of tests for HashTableMultipleValue type
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/HashTableMultipleValue.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestHashTableMultipleValue)

BOOST_AUTO_TEST_CASE(HashTableMultipleValue_clear)
{
    unsigned short K1 = 3U;
    HashTableMultipleValue hashTableMultipleValue(K1);
    bitset<2*MAX_KMER_LENGTH> testBitset(string("11"));
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableSingle().size(), 0);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableMultiple().size(), 0);
    hashTableMultipleValue.getHashTableSingle().insert(HashTableMultipleValue::HashTableSingleValueType::value_type(testBitset, make_pair(0U, 0U)));
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableSingle().size(), 1);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableMultiple().size(), 0);
    hashTableMultipleValue.getHashTableMultiple().insert(HashTableMultipleValue::HashTableMultipleValueType::value_type(testBitset, make_pair(0U, 0U)));
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableSingle().size(), 1);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableMultiple().size(), 1);
    hashTableMultipleValue.clear();
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableSingle().size(), 0);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableMultiple().size(), 0);
}

BOOST_AUTO_TEST_CASE(HashTableMultipleValue_size)
{
    unsigned short K1 = 3U;
    HashTableMultipleValue hashTableMultipleValue(K1);
    bitset<2*MAX_KMER_LENGTH> testBitset(string("11"));
    BOOST_CHECK_EQUAL(hashTableMultipleValue.size(), 0);
    hashTableMultipleValue.getHashTableSingle().insert(HashTableMultipleValue::HashTableSingleValueType::value_type(testBitset, make_pair(0U, 0U)));
    BOOST_CHECK_EQUAL(hashTableMultipleValue.size(), 1);
    hashTableMultipleValue.getHashTableMultiple().insert(HashTableMultipleValue::HashTableMultipleValueType::value_type(testBitset, make_pair(0U, 0U)));
    BOOST_CHECK_EQUAL(hashTableMultipleValue.size(), 2);
    hashTableMultipleValue.getHashTableSingle().clear();
    hashTableMultipleValue.getHashTableMultiple().clear();
    BOOST_CHECK_EQUAL(hashTableMultipleValue.size(), 0);
}

BOOST_AUTO_TEST_CASE(HashTableMultipleValue_isValid)
{
    unsigned short K1 = 3U;
    HashTableMultipleValue hashTableMultipleValue(K1);
    string correct_string = "AACTGACTACTAGCTC";
    string incorrect_string_1 = "NAACTGACTACTAGCTC";
    string incorrect_string_2 = "AACTgACTACTAGCTC";
    BOOST_CHECK_EQUAL(hashTableMultipleValue.isValid(correct_string.data(), K1), true);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.isValid(correct_string.data(), correct_string.size()), true);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.isValid(incorrect_string_1.data(), K1), false);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.isValid(incorrect_string_1.data(), incorrect_string_1.size()), false);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.isValid(incorrect_string_2.data(), K1), true);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.isValid(incorrect_string_2.data(), incorrect_string_2.size()), false);
}

BOOST_AUTO_TEST_CASE(HashTableMultipleValue_basic_find_and_insert_test)   // common tests for find and insert functions
{
    unsigned short K1 = 3U;
    HashTableMultipleValue hashTableMultipleValue(K1);
    string str_1 = "AAA";
    string str_2 = "TTT";
    string str_3 = "AAATTT";
    bitset<2*MAX_KMER_LENGTH> bits_1(string("000000"));
    bitset<2*MAX_KMER_LENGTH> bits_2(string("111111"));
    bitset<2*MAX_KMER_LENGTH> bits_3(string("111111000000"));
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableSingle().size(), 0);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableMultiple().size(), 0);

    hashTableMultipleValue.insert(str_1.data(), 0U, 0U);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableSingle().size(), 1);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableMultiple().size(), 0);
    vector<pair<HashTableMultipleValue::DeBruijnGraphVertex, unsigned short>> findResult = hashTableMultipleValue.find(str_1.data());
    BOOST_CHECK_EQUAL(findResult.size(), 1);
    BOOST_CHECK_EQUAL(findResult[0].first, 0U);
    BOOST_CHECK_EQUAL(findResult[0].second, 0U);
    findResult = hashTableMultipleValue.find(bits_1);
    BOOST_CHECK_EQUAL(findResult.size(), 1);
    BOOST_CHECK_EQUAL(findResult[0].first, 0U);
    BOOST_CHECK_EQUAL(findResult[0].second, 0U);
    findResult = hashTableMultipleValue.find(str_3.data());
    BOOST_CHECK_EQUAL(findResult.size(), 1);
    BOOST_CHECK_EQUAL(findResult[0].first, 0U);
    BOOST_CHECK_EQUAL(findResult[0].second, 0U);
    findResult = hashTableMultipleValue.find(bits_3);
    BOOST_CHECK_EQUAL(findResult.size(), 1);
    BOOST_CHECK_EQUAL(findResult[0].first, 0U);
    BOOST_CHECK_EQUAL(findResult[0].second, 0U);

    hashTableMultipleValue.insert(str_3.data(), 0U, 0U);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableSingle().size(), 1);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableMultiple().size(), 1);
    findResult = hashTableMultipleValue.find(str_1.data());
    BOOST_CHECK_EQUAL(findResult.size(), 2);
    BOOST_CHECK_EQUAL(findResult[0].first, 0U);
    BOOST_CHECK_EQUAL(findResult[0].second, 0U);
    BOOST_CHECK_EQUAL(findResult[1].first, 0U);
    BOOST_CHECK_EQUAL(findResult[1].second, 0U);
    findResult = hashTableMultipleValue.find(bits_1);
    BOOST_CHECK_EQUAL(findResult.size(), 2);
    BOOST_CHECK_EQUAL(findResult[0].first, 0U);
    BOOST_CHECK_EQUAL(findResult[0].second, 0U);
    BOOST_CHECK_EQUAL(findResult[1].first, 0U);
    BOOST_CHECK_EQUAL(findResult[1].second, 0U);
    findResult = hashTableMultipleValue.find(str_3.data());
    BOOST_CHECK_EQUAL(findResult.size(), 2);
    BOOST_CHECK_EQUAL(findResult[0].first, 0U);
    BOOST_CHECK_EQUAL(findResult[0].second, 0U);
    BOOST_CHECK_EQUAL(findResult[1].first, 0U);
    BOOST_CHECK_EQUAL(findResult[1].second, 0U);
    findResult = hashTableMultipleValue.find(bits_3);
    BOOST_CHECK_EQUAL(findResult.size(), 2);
    BOOST_CHECK_EQUAL(findResult[0].first, 0U);
    BOOST_CHECK_EQUAL(findResult[0].second, 0U);
    BOOST_CHECK_EQUAL(findResult[1].first, 0U);
    BOOST_CHECK_EQUAL(findResult[1].second, 0U);

	hashTableMultipleValue.insert(str_3.data(), 1U, 1U);
	BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableSingle().size(), 1);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableMultiple().size(), 2);
    findResult = hashTableMultipleValue.find(str_1.data());
    BOOST_CHECK_EQUAL(findResult.size(), 3);
	BOOST_CHECK_EQUAL(2, std::count_if(findResult.begin(), findResult.end(), 
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 0U && vert.second == 0U;
		})
	);
	BOOST_CHECK_EQUAL(1, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 1U && vert.second == 1U;
		})
	);
    findResult = hashTableMultipleValue.find(bits_1);
    BOOST_CHECK_EQUAL(findResult.size(), 3);
	BOOST_CHECK_EQUAL(2, std::count_if(findResult.begin(), findResult.end(), 
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 0U && vert.second == 0U;
		})
	);
	BOOST_CHECK_EQUAL(1, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 1U && vert.second == 1U;
		})
	);
    findResult = hashTableMultipleValue.find(str_3.data());
    BOOST_CHECK_EQUAL(findResult.size(), 3);
	BOOST_CHECK_EQUAL(2, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 0U && vert.second == 0U;
		})
	);
	BOOST_CHECK_EQUAL(1, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 1U && vert.second == 1U;
		})
	);
    findResult = hashTableMultipleValue.find(bits_3);
    BOOST_CHECK_EQUAL(findResult.size(), 3);
	BOOST_CHECK_EQUAL(2, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 0U && vert.second == 0U;
		})
	);
	BOOST_CHECK_EQUAL(1, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 1U && vert.second == 1U;
		})
	);

    hashTableMultipleValue.insert(str_2.data(), 1U, 1U);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableSingle().size(), 2);
    BOOST_CHECK_EQUAL(hashTableMultipleValue.getHashTableMultiple().size(), 2);
    findResult = hashTableMultipleValue.find(str_1.data());
    BOOST_CHECK_EQUAL(findResult.size(), 3);
	BOOST_CHECK_EQUAL(2, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 0U && vert.second == 0U;
		})
	);
	BOOST_CHECK_EQUAL(1, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 1U && vert.second == 1U;
		})
	);
    findResult = hashTableMultipleValue.find(bits_1);
    BOOST_CHECK_EQUAL(findResult.size(), 3);
	BOOST_CHECK_EQUAL(2, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 0U && vert.second == 0U;
		})
	);
	BOOST_CHECK_EQUAL(1, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 1U && vert.second == 1U;
		})
	);
    findResult = hashTableMultipleValue.find(str_3.data());
    BOOST_CHECK_EQUAL(findResult.size(), 3);
	BOOST_CHECK_EQUAL(2, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 0U && vert.second == 0U;
		})
	);
	BOOST_CHECK_EQUAL(1, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 1U && vert.second == 1U;
		})
	);
    findResult = hashTableMultipleValue.find(bits_3);
    BOOST_CHECK_EQUAL(findResult.size(), 3);
	BOOST_CHECK_EQUAL(2, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 0U && vert.second == 0U;
		})
	);
	BOOST_CHECK_EQUAL(1, std::count_if(findResult.begin(), findResult.end(),
		[](const HashTableMultipleValue::VertexOffsetType &vert) {
			return vert.first == 1U && vert.second == 1U;
		})
	);
    findResult = hashTableMultipleValue.find(str_2.data());
    BOOST_CHECK_EQUAL(findResult.size(), 1);
    BOOST_CHECK_EQUAL(findResult[0].first, 1U);
    BOOST_CHECK_EQUAL(findResult[0].second, 1U);
    findResult = hashTableMultipleValue.find(bits_2);
    BOOST_CHECK_EQUAL(findResult.size(), 1);
    BOOST_CHECK_EQUAL(findResult[0].first, 1U);
    BOOST_CHECK_EQUAL(findResult[0].second, 1U);
}

BOOST_AUTO_TEST_SUITE_END()

