/**
 * \file BloomFilterFiller.hpp
 * \brief the C++ file with declaration of class responsible for
 * filling Bloom filter with k-mers
 *
 */

#ifndef BLOOMFILTERFILLER_HPP
#define BLOOMFILTERFILLER_HPP

#include "../common/common.hpp"
#include "../common/FileReader.hpp"

#include "common.hpp"
#include "../common/BloomFilter.hpp"

namespace dnaasm { namespace scfr {

    namespace BloomFilterFiller {

        /**
         * Inserts all sequences (k-merized) from given file into given Bloom filter.
         *
         * @param contigsFile reference to input file with contigs
         * @param bf reference to BloomFilter class
         */
        CALC_DLL( void fillBloomFilter(const ContigSeqHashMap &contigs,
                                       common::BloomFilter<std::string> &bf); )

        CALC_DLL(void insertKmersFromSeq(common::BloomFilter<std::string> &bf,
                                         const std::string &seq);)
    } //namespace BloomFilterFiller

}} //namespace dnaasm::scfr

#endif //BLOOMFILTERFILLER_HPP
