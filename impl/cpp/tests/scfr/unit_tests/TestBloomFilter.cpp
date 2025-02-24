/**
 * \file TestBloomFilter.cpp
 * \brief the C++ file with implementation of tests for BloomFilter class
 *
 */

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../../../src/common/BloomFilter.hpp"

//using namespace dnaasm::scfr;
using namespace dnaasm::common;

BOOST_AUTO_TEST_SUITE(TestBloomFilter)

BOOST_AUTO_TEST_CASE(contructor_wrong_requiredElems)
{
    uint64_t requiredElements = 0;
    uint32_t kmerSize = 3;
    float fpr = 0.0001;
    BloomFilter<std::string> bf(requiredElements, kmerSize, fpr);

    BOOST_CHECK( requiredElements < 1 );
}

BOOST_AUTO_TEST_CASE(contructor_wrong_fpr)
{
    uint64_t requiredElements = 2;
    uint32_t kmerSize = 3;
    float fpr = 0.0;
    BloomFilter<std::string> bf(requiredElements, kmerSize, fpr);

    BOOST_CHECK( fpr <= 0.0 );
}

BOOST_AUTO_TEST_CASE(insert_oneKmer)
{
    // false positive rate (fpr) = 0.000026 for:
    // filterSize (m)=100,
    // number of hash functions (k)=3
    // number of elems inserted (n)=1
    uint64_t size = 100;
    uint8_t numHashes = 3;
    uint32_t kmerSize = 3;
    BloomFilter<std::string> bf(size, numHashes, kmerSize);

    std::string k1 = "ACT";
    bf.insert(k1);
    BOOST_CHECK_EQUAL(bf.contains(k1), true);

    std::string k2 = "ACG";
    BOOST_CHECK_EQUAL(bf.contains(k2), false);
}

BOOST_AUTO_TEST_CASE(insert_checkFPr)
{
    // fpr ~ 0.45, n = 64
    uint64_t size = 128;
    uint8_t numHashes = 2;
    uint32_t kmerSize = 3;
    BloomFilter<std::string> bf(size, numHashes, kmerSize);

    std::vector<std::string> chars = {"A", "T", "C", "G"};
    for (auto s1 : chars) {
        for (auto s2 : chars) {
            for (auto s3 : chars) {
                bf.insert(s1+s2+s3);
            }
        }
    }
    std::vector<std::string> chars2 = {"Z", "R", "Q", "P"};
    double counter = 0.0;
    for (auto s1 : chars2) {
        for (auto s2 : chars2) {
            for (auto s3 : chars2) {
                if (bf.contains(s1+s2+s3)) {
                    ++counter;
                }
            }
        }
    }

    // check if fpr is correct
    BOOST_CHECK_CLOSE(counter / 64, 0.45, 10);
}

//BOOST_AUTO_TEST_CASE(insertKmersFromSeq)
//{
//    // size and numHashed calculated for p=0.01 and n=8
//    uint64_t size = 77;
//    uint8_t numHashes = 7;
//    uint32_t kmerSize = 3;
//    BloomFilter<std::string> bf(size, numHashes, kmerSize);
//
//    std::string seq = "ATTGACATGC";
//    bf.insertKmersFromSeq(seq);
//
//    std::vector<std::string> kmers = {"ATT", "TTG", "TGA", "GAC",
//                                      "ACA", "CAT", "ATG", "TGC"};
//    std::vector<std::string> kmersNotInSeq = {"TTC", "GGA", "AGA", "CAG"};
//
//    for (auto kmer : kmers) {
//        BOOST_CHECK_EQUAL(bf.contains(kmer), true);
//    }
//    for (auto kmer : kmersNotInSeq) {
//        BOOST_CHECK_EQUAL(bf.contains(kmer), false);
//    }
//}

//BOOST_AUTO_TEST_CASE(insertKmersFromSeq_sequence_shorter_than_kmer)
//{
//    // size and numHashed calculated for p=0.01 and n=8
//    uint64_t size = 77;
//    uint8_t numHashes = 7;
//    uint32_t kmerSize = 30;
//    BloomFilter<std::string> bf(size, numHashes, kmerSize);
//
//    std::string seq = "ATTGACATGC";
//    bf.insertKmersFromSeq(seq);
//
//    BOOST_CHECK(seq.size() < kmerSize);
//}

BOOST_AUTO_TEST_SUITE_END()
