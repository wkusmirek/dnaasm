/**
 * \file KmerPositionFinder.cpp
 * \brief the C++ file with definition of class for Kmer Position Finder
 *
 */

#include "KmerPositionFinder.hpp"

namespace dnaasm { namespace scfr {

    KmerPositionFinder::KmerPositionFinder(MatepairGraph &matepairGraph,
                                           const ContigSeqHashMap &contigs,
                                           unsigned short int kmerSize,
                                           unsigned int minContigLength)
        : matepairGraph_(matepairGraph)
        , contigs_(contigs)
        , kmerSize_(kmerSize)
        , minContigLength_(minContigLength)
    {}

    unsigned int KmerPositionFinder::findKmerPositionOnContigs()
    {
        unsigned int filteredCount = 0U;

        std::for_each(contigs_.begin(), contigs_.end(),
                      [this, &filteredCount](const auto& pair) {
            if (pair.second.size() >= minContigLength_) {
                ++filteredCount;
                this->kmerizeContig(pair.second, pair.first, false);
                this->kmerizeContig(getReverseComplementary(pair.second), pair.first, true);
            }
        });

        return filteredCount;
    }

    void KmerPositionFinder::kmerizeContig(
        const std::string &contig,
        unsigned int contigId,
        bool reverseComplement)
    {
        // convert contig to upper case to ensure compatibility
        // with k-mers saved in k-mer graph
        // note: input contigs may contain lowercase letters if they
        // were an output (were scaffolds) from another scaffolder run
        std::string contigUpperCase = contig;
        std::transform(contigUpperCase.begin(), contigUpperCase.end(),
                       contigUpperCase.begin(), ::toupper);

        for (size_t pos = 0; pos < contig.size() - kmerSize_ + 1; ++pos) {
            std::string kmer = contigUpperCase.substr(pos, kmerSize_);
            auto v_desc = matepairGraph_.vertex(kmer);

            if (v_desc != MatepairGraphInternal::null_vertex()) {
                auto &v = matepairGraph_.graph()[v_desc];

                if (v.contigId_ != 0U) {
                    // if kmer is not unique (some contig id was already set for it),
                    // then set contig id to defined constant
                    v.contigId_ = static_cast<uint32_t>(MatepairGraph::CONTIG_ID_FOR_NOT_UNIQUE_KMER);
                } else {
                    v.contigId_ = static_cast<uint32_t>(contigId);

                    if (reverseComplement) {
                        v.start_ = static_cast<uint32_t>(contig.size() - pos);
                        v.end_ = static_cast<uint32_t>(contig.size() - (pos + kmerSize_));
                    } else {
                        v.start_ = static_cast<uint32_t>(pos);
                        v.end_ = static_cast<uint32_t>(pos + kmerSize_);
                    }
                }
            }
        }
    }

}} //namespace dnaasm::scfr
