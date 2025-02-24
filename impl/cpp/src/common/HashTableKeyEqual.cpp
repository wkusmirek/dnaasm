/**
 * \file HashTableKeyEqual.cpp
 * \brief the C++ file with implementation of structure for checking if keys are equal
 *
 */

#include "HashTableKeyEqual.hpp"

namespace dnaasm {

    HashTableKeyEqual::HashTableKeyEqual() {}

    bool HashTableKeyEqual::operator()(std::bitset<2*MAX_KMER_LENGTH> bitset1,
                                       std::bitset<2*MAX_KMER_LENGTH> bitset2) const {
        return bitset1 == bitset2;
    }

}
