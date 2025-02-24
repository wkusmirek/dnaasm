/**
 * \file HashTableKeyHash.cpp
 * \brief the C++ file with implementation of structure for hashing key value
 *
 */

#include "HashTableKeyHash.hpp"

namespace dnaasm {

    HashTableKeyHash::HashTableKeyHash(): hashFunction_() {}

    size_t HashTableKeyHash::operator()(std::bitset<2*MAX_KMER_LENGTH> binaryStr) const {
        return hashFunction_(binaryStr);
    }

}
