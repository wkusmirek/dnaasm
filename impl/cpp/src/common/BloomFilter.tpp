/**
 * \file BloomFilter.tpp
 * \brief the C++ file with implementation of Bloom filter class
 */
#include "log.hpp"
#include <cmath>

namespace dnaasm {
    namespace common {

        template<typename T>
        BloomFilter<T>::BloomFilter(uint64_t size,
                                    uint8_t numHashes,
                                    uint32_t dataSize)
                : array_(size), numHashes_(numHashes), dataSize_(dataSize) {}

        template<typename T>
        BloomFilter<T>::BloomFilter(uint64_t requiredElems,
                                    uint32_t dataSize,
                                    float fpr)
                : dataSize_(dataSize) {
            if (requiredElems < 1) {
                dnaasm::logWarning("Bloom: requiredElems must be greater than 0! Used 1 instead.");
                requiredElems = 1;
            }

            if (fpr <= 0.0) {
                dnaasm::logWarning("Bloom: fpr must be greater than 0.0! Used 0.0001 instead.");
                fpr = 0.0001;
            }

            auto ln2 = std::log(2);
            auto filterSize = static_cast<uint64_t>(
                    std::ceil(-(requiredElems * std::log(fpr)) / (ln2 * ln2)));
            filterSize += 64 - (filterSize % 64); // size must be multiple of 64

            array_.resize(filterSize);
            numHashes_ = static_cast<uint8_t>(floor((filterSize / requiredElems) * ln2));

            dnaasm::logInfo("Bloom filter specs:");
            dnaasm::logInfo("elements = " + std::to_string(requiredElems));
            dnaasm::logInfo("size (bits) = " + std::to_string(filterSize));
            dnaasm::logInfo("hash functions = " + std::to_string(numHashes_));
            dnaasm::logInfo("fpr = " + std::to_string(fpr) + "\n");
        }

        template<typename T>
        void BloomFilter<T>::insert(const T &value) {
            auto hashes = hash(value);

            for (uint8_t n = 0; n < numHashes_; n++) {
                array_[nthHash(n, hashes[0], hashes[1], array_.size())] = true;
            }
        }

        template<typename T>
        bool BloomFilter<T>::contains(const T &value) const {
            auto hashes = hash(value);

            for (uint8_t n = 0; n < numHashes_; n++) {
                if (!array_[nthHash(n, hashes[0], hashes[1], array_.size())]) {
                    return false;
                }
            }

            return true;
        }

        template<typename T>
        uint64_t BloomFilter<T>::nthHash(uint8_t n, uint64_t hash1,
                                         uint64_t hash2, uint64_t filterSize) const {
            return (hash1 + n * hash2) % filterSize;
        }

        template<>
        inline std::array<uint64_t, 2> BloomFilter<std::string>::hash(const std::string &value) const {
            std::array<uint64_t, 2> hashValue;
            MurmurHash3_x64_128(value.data(), dataSize_, 0, hashValue.data());

            return hashValue;
        }

//        template<>
//        inline std::array<uint64_t, 2> BloomFilter<long>::hash(const long &value) const {
//            std::array<uint64_t, 2> hashValue;
//            MurmurHash3_x64_128(&value, sizeof(long), 0, hashValue.data());
//
//            return hashValue;
//        }
    }
} //namespace dnaasm::common