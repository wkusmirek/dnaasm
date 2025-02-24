/**
 * \file KmerPositionFinder.hpp
 * \brief the C++ file with declaration of class for Kmer Position Finder
 *
 */

#ifndef KMERPOSITIONFINDER_HPP
#define KMERPOSITIONFINDER_HPP

#include "../common/common.hpp"
#include "../common/FileReader.hpp"

#include "common.hpp"
#include "MatepairGraph.hpp"

namespace dnaasm { namespace scfr {

    /**
     * Class responsible for finding position of k-mer on contig
     */
    class KmerPositionFinder {
    public:
        /**
         * KmerPositionFinder c-tor
         *
         * @param matepairGraph reference to matepair graph
         * @param contigs reference to hash map with contig sequences
         * @param kmerSize k-mer length
         * @param minContigLength minimum length of contig to be considered
         */
        CALC_DLL(KmerPositionFinder(MatepairGraph &matepairGraph,
                                    const ContigSeqHashMap &contigs,
                                    unsigned short int kmerSize,
                                    unsigned int minContigLength);)

        /**
         * Finds positions of k-mers from matepair graph on contigs
         *
         * @return number of contigs with length grater or equal to minContigLength
         */
        CALC_DLL( unsigned int findKmerPositionOnContigs(); )

    private:
        MatepairGraph &matepairGraph_;
        const ContigSeqHashMap &contigs_;
        unsigned short int kmerSize_;
        unsigned int minContigLength_;

        void kmerizeContig(const std::string &contig,
                           unsigned int contigId,
                           bool reverseComplement);

        KmerPositionFinder(const KmerPositionFinder&) = delete;
        KmerPositionFinder& operator=(const KmerPositionFinder&) = delete;
    };

}} //namespace dnaasm::scfr
#endif //KMERPOSITIONFINDER_HPP
