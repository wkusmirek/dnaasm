/**
 * \file ContigPairValidator.cpp
 * \brief the C++ file with definition of Contig Pair Validator class
 *
 */

#include "ContigPairValidator.hpp"

namespace dnaasm { namespace scfr {

    ContigPairValidator::ContigPairValidator(const ContigPairGraphEdgeProperties &pair)
        : pair_(pair)
        , isValid_(false)
        , numLinks_(pair.bridges_.size())
        , numReads_(0)
        , gapReadId_(0)
        , gapOffset_(0)
        , isGapReversed_(false)
        , meanDistance_(0)
    {
        if (numLinks_) {
            meanDistance_ = std::floor((float)pair_.gapSum() / (float)numLinks_);
        }
    }

    unsigned int ContigPairValidator::getNumLinks() const
    {
        return numLinks_;
    }

    unsigned int ContigPairValidator::getNumReads() const
    {
        return numReads_;
    }

    unsigned int ContigPairValidator::getGapReadId() const
    {
        return gapReadId_;
    }

    unsigned int ContigPairValidator::getGapOffset() const
    {
        return gapOffset_;
    }

    bool ContigPairValidator::getIsGapReversed() const
    {
        return isGapReversed_;
    }

    int ContigPairValidator::getMeanDistance() const
    {
        return  meanDistance_;
    }

    bool ContigPairValidator::isValid(const MatepairGraph& matepairs,
                                      unsigned int minLinks,
                                      unsigned int minReads,
                                      unsigned int minLinksPerRead)
    {
        LinksPerReadVec lprCounters = createLinksPerReadVec(pair_, matepairs);

        numReads_ = std::count_if(lprCounters.begin(), lprCounters.end(),
            [minLinksPerRead](auto &c) { return c.second >= minLinksPerRead; }
        );

        // FIXME: as for now, gapReadId_ is id of read
        // which overlaps pair of contigs with the greatest number
        // of links
        if (numReads_) {
            gapReadId_ = lprCounters.begin()->first;
            auto found = std::find_if(
                pair_.bridges_.begin(),
                pair_.bridges_.end(),
                [&matepairs, this](const GapInfo& gi){
                    return matepairs.graph()[gi.mpEdge_].readId_ == gapReadId_;
            });
            gapOffset_ = found->offset_;
            isGapReversed_ = found->reversed_;
            //meanDistance_ = found->length_;
        }


        bool cond1 = numLinks_ >= minLinks;
        bool cond2 = numReads_ >= minReads;

        return cond1 && cond2;
    }
}}