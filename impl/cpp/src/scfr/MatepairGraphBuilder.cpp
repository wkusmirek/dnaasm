/**
 * \file MatepairGraphBuilder.cpp
 * \brief the C++ file with definition of class for Matepair Graph Builder
 *
 */

#include "MatepairGraphBuilder.hpp"

namespace dnaasm { namespace scfr {

    MatepairGraphBuilder::MatepairGraphBuilder(MatepairGraph &matepairGraph,
                                               const common::BloomFilter<std::string> &bloomFilter,
                                               InputFile &readsInputFile,
                                               unsigned short int kmerSize,
                                               unsigned short int distance,
                                               unsigned short int step)
        : matepairGraph_(matepairGraph)
        , bloomFilter_(bloomFilter)
        , readsInputFile_(readsInputFile)
        , kmerSize_(kmerSize)
        , distance_(distance)
        , step_(step)
    {}

    unsigned int MatepairGraphBuilder::buildGraph()
    {
        unsigned int readCounter = 0;
        Read read(0U);
        std::string readStr;

        while (true) {
            readsInputFile_.readSingleRead(read);
            readStr = read.getRead();

            if (readStr == "")
                break;

            ++readCounter;
            kmerizeRead(readStr, readCounter);
        }

        return readCounter;
    }

    const MatepairGraphBuilder::ReadRegionsMap& MatepairGraphBuilder::getReadRegionsMap() const{
        return readsRegions_;
    }


    const ReadSeqHashMap& MatepairGraphBuilder::getReadSeqHashMap() const {
        return readSeqs_;
    }

    void MatepairGraphBuilder::kmerizeRead(const std::string &seq,
                                           unsigned int readId)
    {
        std::string k1, k2;
        size_t secondStart = 0, regionBegin = 0, regionEnd = 0;
        bool anyImportantRegion = false;
        std::vector<std::pair<size_t, size_t>> importantRegions;

        // convert read to upper case to ensure alg. will work
        // for lowercase letters in reads
        std::string seqUpperCase = seq;
        std::transform(seqUpperCase.begin(), seqUpperCase.end(),
                       seqUpperCase.begin(), ::toupper);

        for (size_t pos = 0; pos <= seq.size() - distance_; pos += step_) {
            k1 = seqUpperCase.substr(pos, kmerSize_);
            secondStart = pos + distance_ - kmerSize_;
            if (secondStart + kmerSize_ > seq.size()) {
                break;
            }
            k2 = seqUpperCase.substr(secondStart, kmerSize_);

            // save pair in graph only if both kmers exist in Bloom filter
            if (bloomFilter_.contains(k1) && bloomFilter_.contains(k2)) {
                // save information about important fragments of the read
                if (!anyImportantRegion) {
                    anyImportantRegion = true;
                    regionBegin = pos;
                } else if (pos > regionEnd) { // begin of new interesting region
                    importantRegions.emplace_back(regionBegin, regionEnd);
                    regionBegin = pos;
                }
                regionEnd = pos + distance_;

                // add vertices or get descriptors of existing vertices
                auto v1 = matepairGraph_.add_vertex(k1);
                auto v2 = matepairGraph_.add_vertex(k2);

                // add edge if it doesn't exist
                if (!(boost::edge(v1, v2, matepairGraph_.graph()).second)) {
                    MatepairGraphEdgeProperties ep(readId, (uint32_t)pos);
                    boost::add_edge(v1, v2, ep, matepairGraph_.graph());
                }
            }
        }

        // save read sequence and info about important regions if at least
        // one pair of k-mers was extracted from this read
        if (anyImportantRegion) {
            importantRegions.emplace_back(regionBegin, regionEnd);
            readsRegions_[readId] = importantRegions;
            readSeqs_[readId] = seq;
        }
    }

}} //namespace dnaasm::scfr