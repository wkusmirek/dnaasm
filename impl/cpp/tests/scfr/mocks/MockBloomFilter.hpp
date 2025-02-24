/**
 * \file MockBloomFilter.hpp
 * \brief the C++ file with implementation of mock for BloomFilter class
 *
 */

#ifndef MOCKBLOOMFILTER_HPP
#define MOCKBLOOMFILTER_HPP

#include <gmock/gmock.h>
#include "../../../src/common/BloomFilter.hpp"

class MockBloomFilter : public dnaasm::common::BloomFilter<std::string> {
public:
    MockBloomFilter() : BloomFilter((uint64_t)1, (uint8_t)0, (uint32_t)0)
    {}

    //MOCK_METHOD1(insertKmersFromSeq, void(const std::string& seq));
    MOCK_CONST_METHOD1(contains, bool(const std::string &kmer));
};

#endif //MOCKBLOOMFILTER_HPP
