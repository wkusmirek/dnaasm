/**
 * \file BloomFilterFiller.cpp
 * \brief the C++ file with implementation of class responsible for
 * filling Bloom filter with k-mers
 *
 */

#include "common.hpp"
#include "BloomFilterFiller.hpp"

namespace dnaasm {
    namespace scfr {

        void BloomFilterFiller::fillBloomFilter(const ContigSeqHashMap &contigs,
                                                common::BloomFilter<std::string> &bf) {
            std::for_each(contigs.begin(), contigs.end(), [&bf](const auto &pair) {
                insertKmersFromSeq(bf, pair.second);
                insertKmersFromSeq(bf, getReverseComplementary(pair.second));
            });
        }

        void BloomFilterFiller::insertKmersFromSeq(common::BloomFilter<std::string> &bf,
                                                   const std::string &seq) {
            auto kmerSize_ = bf.getDataSize();

            if (kmerSize_ > seq.size()) {
                logWarning("Bloom: input sequence is shorter than kmer size!");
                return;
            }

            // convert sequence to upper case
            std::string seqUpperCase = seq;
            std::transform(seqUpperCase.begin(), seqUpperCase.end(),
                           seqUpperCase.begin(), ::toupper);

            for (std::size_t i = 0; i < seqUpperCase.size() - kmerSize_ + 1; ++i) {
                bf.insert(seqUpperCase.substr(i, kmerSize_));
            }
        }

    }
} //namespace dnaasm::scfr