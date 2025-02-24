/**
 * \file HashTableMultipleValue.cpp
 * \brief the C++ file with implementation of hash table class (with multiple key values)
 *
 */

#include "HashTableMultipleValue.hpp"

using namespace std;

namespace dnaasm { namespace dbj {

    HashTableMultipleValue::HashTableMultipleValue(unsigned short K1)
        : K1_(K1)
        , hashTableSingle_(K1, HashTableKeyHash(), HashTableKeyEqual())
        , dnaSequenceRepresentationConverter_(K1)
    {}

    void HashTableMultipleValue::clear() {
        hashTableSingle_.clear();
        hashTableMultiple_.clear();
    }

    size_t HashTableMultipleValue::size() const {
        return hashTableSingle_.size() + hashTableMultiple_.size();
    }

    vector<pair<HashTableMultipleValue::DeBruijnGraphVertex, unsigned short>> HashTableMultipleValue::find(const char* read) {
        bitset<2*MAX_KMER_LENGTH> bitsetRead = dnaSequenceRepresentationConverter_.convertToBitset(read);
        vector<pair<HashTableMultipleValue::DeBruijnGraphVertex, unsigned short>> result;
        HashTableSingleValueType::iterator singleIt = hashTableSingle_.find(bitsetRead);

        if (singleIt != hashTableSingle_.end()) {
            result.push_back(singleIt->second);
        }

        pair<HashTableMultipleValueType::iterator,
             HashTableMultipleValueType::iterator> multipleIt = hashTableMultiple_.equal_range(bitsetRead);

        for (auto it = multipleIt.first; it != multipleIt.second; ++it) {
            result.push_back(it->second);
        }

        return result;
    }

    vector<pair<HashTableMultipleValue::DeBruijnGraphVertex, unsigned short>> HashTableMultipleValue::find(bitset<2*MAX_KMER_LENGTH> bitsetRead) {
        for (int i = 0; i < (MAX_KMER_LENGTH - K1_) * 2; ++i) {
            bitsetRead.set((2*MAX_KMER_LENGTH)-1-i, 0);
        }
        vector<pair<HashTableMultipleValue::DeBruijnGraphVertex, unsigned short>> result;
        HashTableSingleValueType::iterator singleIt = hashTableSingle_.find(bitsetRead);

        if (singleIt != hashTableSingle_.end()) {
            result.push_back(singleIt->second);
        }

        pair<HashTableMultipleValueType::iterator,
             HashTableMultipleValueType::iterator> multipleIt = hashTableMultiple_.equal_range(bitsetRead);

        for (auto it = multipleIt.first; it != multipleIt.second; ++it) {
            result.push_back(it->second);
        }

        return result;
    }

    void HashTableMultipleValue::insert(const char* read, HashTableMultipleValue::DeBruijnGraphVertex vertex, unsigned short offset) {
        bitset<2*MAX_KMER_LENGTH> bitsetRead = dnaSequenceRepresentationConverter_.convertToBitset(read);

        if (hashTableSingle_.find(bitsetRead) != hashTableSingle_.end()) {
            hashTableMultiple_.insert(HashTableMultipleValueType::value_type(bitsetRead, make_pair(vertex, offset)));
        } else {
            hashTableSingle_.insert(HashTableSingleValueType::value_type(bitsetRead, make_pair(vertex, offset)));
        }
    }

    bool HashTableMultipleValue::isValid(const char* read, size_t size) {
        if (string(read, size).find_first_not_of("ACGT") == std::string::npos) {
            return true;
        } else {
            return false;
        }
    }

    HashTableMultipleValue::HashTableMultipleValueType& HashTableMultipleValue::getHashTableMultiple() {
        return hashTableMultiple_;
    }

    HashTableMultipleValue::HashTableSingleValueType& HashTableMultipleValue::getHashTableSingle() {
        return hashTableSingle_;
    }
}}

