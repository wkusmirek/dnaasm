/**
 * \file HashTableKeyEqual.hpp
 * \brief the C++ file with declaration of structure for checking if keys are equal
 *
 */

#ifndef HASH_TABLE_KEY_EQUAL_HPP
#define HASH_TABLE_KEY_EQUAL_HPP

#include <bitset>

#include "common.hpp"

namespace dnaasm {

    struct HashTableKeyEqual {
        CALC_DLL(HashTableKeyEqual();)
        CALC_DLL(bool operator()(std::bitset<2*MAX_KMER_LENGTH>, std::bitset<2*MAX_KMER_LENGTH>) const;)
    };

}

#endif    //HASH_TABLE_KEY_EQUAL_HPP
