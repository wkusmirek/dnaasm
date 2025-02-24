/**
 * \file ContigPairMaker.hpp
 * \brief the C++ file with declaration of Contig Pair Maker class
 *
 */

#ifndef CONTIGPAIRMAKER_HPP
#define CONTIGPAIRMAKER_HPP

#include "../common/common.hpp"

#include "common.hpp"
#include "MatepairGraph.hpp"
#include "ContigPairGraph.hpp"

namespace dnaasm { namespace scfr {

    /**
     * Class responsible for building graph of contig pairs
     */
    class ContigPairMaker {
    public:
        /**
         * ContigPairMaker c-tor.
         *
         * @param matepairGraph reference to matepair graph
         * @param contigLength reference to hash map with contig lengths
         * @param contigPairGraph reference to contigpair graph
         * @param insertSize insert size of mate pairs
         *        (distance used for extraction of k-mer pairs)
         * @param stdDevOfDistance standard deviation on insert size
         *        (distance), default 0.1
         */
        CALC_DLL(ContigPairMaker(MatepairGraph &matepairGraph,
                                 const ContigSeqHashMap &contigSeqs,
                                 ContigPairGraph &contigPairGraph,
                                 unsigned int insertSize,
                                 float stdDevOfDistance = 0.1);)

        /**
         * Pairs contigs and stores information about paired contigs in graph
         */
        CALC_DLL( void pairContigs(); )

    private:
        MatepairGraph &matepairGraph_;
        const ContigSeqHashMap &contigSeqs_;
        ContigPairGraph &contigPairGraph_;
        unsigned int insertSize_;
        float stdDevOfDistance_;

        void pairTwoContigs(
            unsigned int id1,
            unsigned int id2,
            unsigned int length1,
            unsigned int length2,
            unsigned int start1,
            unsigned int end2,
            bool rev1, bool rev2,
            Edge mpEdgeDesc
        );

        void createOrUpdatePair(
            std::string c1,
            std::string c2,
            int distCategory,
            int gapsIncrement,
            unsigned int gapSeqOffset,
            bool gapReversed,
            Edge mpEdgeDesc
        );

        int calculateGapOrOverlap(
            unsigned int lengthR1,
            unsigned int startK1,
            unsigned int endK2
        ) const;

        int getDistanceCategory(int d) const;

        ContigPairMaker(const ContigPairMaker&) = delete;
        ContigPairMaker& operator=(const ContigPairMaker&) = delete;
    };

}} //namespace dnaasm::scfr

#endif //CONTIGPAIRMAKER_HPP
