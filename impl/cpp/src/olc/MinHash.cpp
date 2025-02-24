/**
 * \file MinHash.cpp
 * \brief the C++ file with definition of class used to calculate
 * Jaccard similarity between long reads
 *
 */
#include "MinHash.hpp"

namespace dnaasm {
    namespace olc {

        MinHash::MinHash() : MinHash(128) {}

        MinHash::MinHash(size_t numPerm) {
            const uint64_t MaxHash = (1ULL << 32) - 1;
            hashValues_ = HashEntryVector(numPerm, {MaxHash, 0U});
        }

        MinHash::MinHash(const MinHash &oth) : hashValues_(oth.hashValues_) {}

        void MinHash::update(const LongRead &kmer,
                             size_t pos,
                             HashObj &hashObj,
                             const PermutationVector &permutations) {
            /**
             * Create matrix for hashes
             */
            const size_t numPerm = permutations[0].size();
            const uint64_t MersennePrime = (1ULL << 61) - 1;
            const uint64_t MaxHash = (1ULL << 32) - 1;
            auto initHashes = HashVector(numPerm);
            const auto &p0 = permutations[0];
            const auto &p1 = permutations[1];
            uint32_t hash = hashObj(kmer);

            for (size_t i = 0; i < numPerm; ++i) {
                initHashes[i] = ((p0[i] * hash + p1[i]) % MersennePrime) & MaxHash;
            }

            for (size_t i = 0; i < numPerm; ++i) {
                hashValues_[i] = std::min(hashValues_[i], { initHashes[i], pos }, [](const auto &lhs, const auto &rhs) {
                    return lhs.hash < rhs.hash;
                });
            }
        }

        float MinHash::estJaccardSimilarity(const MinHash &oth) const {
            /**
             * Find all common hash values
             */
            int common = 0;
            for (size_t i = 0; i < hashValues_.size(); ++i) {
                if (hashValues_[i].hash && hashValues_[i].hash == oth.hashValues_[i].hash)
                    ++common;
            }

            return common / static_cast<float>(hashValues_.size());
        }

        //static function
        void MinHash::initialize(size_t seed, size_t numPerm,
                                 PermutationVector &permutations) {
            //in case that permutations vector has been already initialized
            permutations.clear();

            permutations = PermutationVector(2, HashVector(numPerm));
            const uint64_t MersennePrime = (1ULL << 61) - 1;

            std::mt19937_64 mt_rand(seed);
            std::uniform_int_distribution<uint64_t> first(1, MersennePrime);
            std::uniform_int_distribution<uint64_t> second(0, MersennePrime);

            std::for_each(permutations[0].begin(), permutations[0].end(),
                          [&](uint64_t &perm) { perm = first(mt_rand); }
            );

            std::for_each(permutations[1].begin(), permutations[1].end(),
                          [&](uint64_t &perm) { perm = second(mt_rand); }
            );
        }

        void MinHash::clear() { hashValues_.clear(); }

    }
} //namespace dnaasm::olc
