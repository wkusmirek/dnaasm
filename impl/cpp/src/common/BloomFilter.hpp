/**
 * \file BloomFilter.hpp
 * \brief the C++ file with declaration of Bloom filter class
 */

#ifndef BLOOMFILTER_HPP
#define BLOOMFILTER_HPP

#include <vector>
#include <array>

#include "MurmurHash3.hpp"
#include "common.hpp"

namespace dnaasm {
    namespace common {

        /**
         * Class representing Bloom Filter with double hashing.
         */

        template<typename T>
        class BloomFilter {
        public:
            /**
                 * BloomFilter c-tor.
                 *
                 * Creates filter with given size, number of hash functions and k-mer size.
                 *
                 * @param size size of filter bit array
                 * @param numHashes number of hash functions
                 * @param kmerSize  length of k-mer
                 */
            CALC_DLL(BloomFilter(uint64_t size,
                                 uint8_t  numHashes,
                                 uint32_t dataSize);)

            /**
             * BloomFilter c-tor.
             *
             * Filter size will be calculated based on parameters given.
             *
             * @param requiredElems number of elements that will be inserted to filter
             * @param kmerSize length of k-mer
             * @param fpr desired false-positive ratio (default 0.001)
             */
            CALC_DLL(BloomFilter(uint64_t requiredElems,
                                 uint32_t dataSize,
                                 float fpr = 0.001);)

            /**
             * Inserts given k-mer to filter.
             *
             * @param kmer reference to k-mer to be inserted
             */
            CALC_DLL(void insert(const T &value);)

            /**
             * Test whether given k-mer exists in filter.
             *
             * @param kmer reference to k-mer to be tested
             * @return true if k-mer exists in filter, false otherwise
             */
            CALC_DLL(virtual bool contains(const T &value) const;)

            CALC_DLL(uint32_t getDataSize( )const {return dataSize_;} )

        private:
            std::vector<bool> array_;
            uint8_t numHashes_;
            uint32_t dataSize_;

            std::array<uint64_t, 2> hash(const T &data) const {
                std::array<uint64_t, 2> hashValue;
                MurmurHash3_x64_128(&data, dataSize_, 0, hashValue.data());

                return hashValue;
            }

            uint64_t nthHash(uint8_t n, uint64_t hashA,
                             uint64_t hashB, uint64_t filterSize) const;
        };


    }
} //namespace dnaasm::common

#include "BloomFilter.tpp"
#endif //BLOOMFILTER_HPP
