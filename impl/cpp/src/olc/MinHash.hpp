/**
 * \file MinHash.hpp
 * \brief the C++ file with declaration of class used to calculate
 * Jaccard similarity between long reads
 *
 */

#ifndef MINHASH_HPP
#define MINHASH_HPP

#include <algorithm>
#include <chrono>
#include <climits>
#include <cstdint>
#include <iostream>
#include <random>
#include <set>
#include <vector>

#include "../common/common.hpp"
#include "common.hpp"
#include "HashObj.hpp"

namespace dnaasm {
    namespace olc {

        struct HashEntry {
            uint64_t hash;
            size_t pos;
        };

        using HashEntryVector = std::vector<HashEntry>;

        class MinHash {
        public:
            CALC_DLL(MinHash();)

            CALC_DLL(MinHash(size_t);)

            CALC_DLL(MinHash(const MinHash &oth);)

            virtual ~MinHash() {}

            CALC_DLL(void update(const LongRead &, size_t, HashObj &, const PermutationVector &);)

            CALC_DLL(float estJaccardSimilarity(const MinHash &) const;)

            CALC_DLL(static void initialize(size_t, size_t, PermutationVector &);)

            void clear();

        private:
            std::vector<HashEntry> hashValues_;
        };

    }
} //namespace dnaasm::olc

#endif //MINHASH_HPP
