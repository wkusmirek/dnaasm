/**
 * \file ContigPairValidator.hpp
 * \brief the C++ file with declaration of Contig Pair Validator class
 *
 */

#ifndef CONTIGPAIRVALIDATOR_HPP
#define CONTIGPAIRVALIDATOR_HPP


#include "common.hpp"
#include "ContigPairGraph.hpp"

namespace dnaasm { namespace scfr {

    /**
     * Class responsible for checking if given pair of contigs
     * meets links/reads constrains
     */
    class ContigPairValidator {
    public:
        /**
         * ContigPairValidator c-tor.
         *
         * @param pair reference to edge props structure from ContigPairGraph
         */
        ContigPairValidator(const ContigPairGraphEdgeProperties& pair);

        /**
         * Checks if contig pair meets given constrains.
         *
         * @param matepairs reference to MatepairGraph related to contig pair
         * @param minLinks minimum number of links pair must have
         * @param minReads minimum number of reads for which minLinksPerRead
         *        threshold must be fulfilled
         * @param minLinksPerRead minimum number of links that must come
         *        from a single read
         * @return true if contig pair is valid, false otherwise
         */
        bool isValid(const MatepairGraph& matepairs,
                     unsigned int minLinks,
                     unsigned int minReads,
                     unsigned int minLinksPerRead);

        unsigned int getNumLinks() const;
        unsigned int getNumReads() const;
        unsigned int getGapReadId() const;
        unsigned int getGapOffset() const;
        bool getIsGapReversed() const;
        int getMeanDistance() const;

    private:
        const ContigPairGraphEdgeProperties &pair_;
        bool isValid_;
        unsigned int numLinks_;
        unsigned int numReads_;
        unsigned int gapReadId_;
        unsigned int gapOffset_;
        bool isGapReversed_;
        int meanDistance_;

        ContigPairValidator(const ContigPairValidator&) = delete;
        ContigPairValidator& operator=(const ContigPairValidator&) = delete;
    };

}}

#endif //CONTIGPAIRVALIDATOR_HPP
