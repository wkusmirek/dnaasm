/**
 * \file MatepairGraphBuilder.hpp
 * \brief the C++ file with declaration of class for Matepair Graph Builder
 *
 */

#ifndef MATEPAIRGRAPHBUILDER_HPP
#define MATEPAIRGRAPHBUILDER_HPP

#include "../common/common.hpp"
#include "../common/FileReader.hpp"

#include "common.hpp"
#include "../common/BloomFilter.hpp"
#include "MatepairGraph.hpp"

namespace dnaasm { namespace scfr {

    /**
     * Class responsible for building matepair graph (graph of k-mer pairs)
     */
    class MatepairGraphBuilder {
    public:
        /**
         * MatepairGraphBuilder c-tor.
         *
         * @param matepairGraph reference to matepair graph
         * @param bloomFilter reference to Bloom filter
         * @param readsInputFile reference to file with reads
         * @param kmerSize k-mer length
         * @param distance distance that will be used for k-mer pairs extraction
         * @param step length of sliding window two subsequent between k-mer pairs
         */
        CALC_DLL(MatepairGraphBuilder(MatepairGraph &matepairGraph,
                                      const common::BloomFilter<std::string> &bloomFilter,
                                      InputFile &readsInputFile,
                                      unsigned short int kmerSize,
                                      unsigned short int distance,
                                      unsigned short int step);)

        /**
         * Extracts k-mer pairs from reads and stores them in graph.
         *
         * @return number of reads (sequences) in file
         */
        CALC_DLL( unsigned int buildGraph();)

        using ReadRegionsMap =
            std::unordered_map<unsigned int, std::vector<std::pair<size_t, size_t>>>;

        CALC_DLL( const ReadRegionsMap& getReadRegionsMap() const;)

        CALC_DLL( const ReadSeqHashMap& getReadSeqHashMap() const;)

    private:
        MatepairGraph &matepairGraph_;
        const common::BloomFilter<std::string> &bloomFilter_;
        InputFile &readsInputFile_;
        ReadRegionsMap readsRegions_;
        ReadSeqHashMap readSeqs_;

        unsigned short int kmerSize_;
        unsigned short int distance_;
        unsigned short int step_;

        void kmerizeRead(const std::string &seq, unsigned int readId);

        MatepairGraphBuilder(const MatepairGraphBuilder&) = delete;
        MatepairGraphBuilder& operator=(const MatepairGraphBuilder&) = delete;
    };

}} //namespace dnaasm::scfr
#endif //MATEPAIRGRAPHBUILDER_HPP
