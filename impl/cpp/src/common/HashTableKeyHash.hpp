/**
 * \file HashTableKeyHash.hpp
 * \brief the C++ file with declaration of structure for hashing key value
 *
 */

#ifndef HASH_TABLE_KEY_HASH_HPP
#define HASH_TABLE_KEY_HASH_HPP

#include <bitset>

#include "common.hpp"

namespace dnaasm {
    struct HashTableKeyHash {
        CALC_DLL(explicit HashTableKeyHash();)
        CALC_DLL(size_t operator()(std::bitset<2*MAX_KMER_LENGTH>) const;)
        std::hash<std::bitset<2*MAX_KMER_LENGTH>> hashFunction_;
    };
}

#endif  // HASH_TABLE_KEY_HASH_HPP
