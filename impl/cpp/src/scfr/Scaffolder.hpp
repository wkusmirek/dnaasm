/**
 * \file Scaffolder.hpp
 * \brief the C++ file with declaration of class responsible for
 * creating scaffolds from paired contigs
 */

#ifndef SCAFFOLDER_HPP
#define SCAFFOLDER_HPP

#include "../common/FileReader.hpp"
#include "ContigPairGraph.hpp"
#include "ContigPairValidator.hpp"
#include "common.hpp"

namespace dnaasm { namespace scfr {

    using ContigPath =
        std::vector<ContigPairGraphEdge>;

    using ContigPathHashMap =
        std::unordered_map<std::string, ContigPath>;

    /**
     * Class responsible for building scaffolds from contigs pairs
     */
    class Scaffolder {
    public:
        /**
         * Scaffolder c-tor.
         *
         * @param minLinks minimum number of linkages between contigs
         *        to consired them in scaffolding
         * @param maxRatio maximum link ratio between two best contig pairs
         */
        CALC_DLL(Scaffolder(
            unsigned short int minLinks,
            unsigned short int minReads,
            unsigned short int minLinksPerRead,
            float maxRatio,
            const MatepairGraph& matepairGraph
        );)

        /**
         * Builds scaffolds from contigs pairs.
         *
         * @param pairs reference to contig pair graph
         * @param contigLength reference to hash map with contig lengths
         * @param scaffolds reference to stringstream where layouts of
         *        scaffolds will be stored in CSV format
         */
        CALC_DLL(void buildScaffolds(
            ContigPairGraph &pairs,
            const ContigSeqHashMap &contigs,
            std::stringstream &scaffolds
        );)

        /**
         * Creates scaffold sequences and saves them in given string stream.
         *
         * @param contigs reference to hash map with contig sequences
         * @param scaffoldsCSV reference to string stream with scaffold layouts
         *        in SCV format
         * @param outputFasta reference to stringstream where scaffolds in
         *        FASTA format will be stored
         */
        CALC_DLL(void saveScaffoldsToFasta(
            const ContigSeqHashMap &contigs,
            const ReadSeqHashMap &reads,
            std::stringstream &scaffoldsCSV,
            std::stringstream &outputFasta,
            bool gapFilling
        );)

        CALC_DLL(const ContigPathHashMap& getContigPaths() const;)

    private:
        unsigned short int minLinks_;
        unsigned short int minReads_;
        unsigned short int minLinksPerRead_;
        float maxRatio_;
        const MatepairGraph& matepairGraph_;
        ContigPathHashMap contigPathsForScaffolds_;

        enum ExtensionType {Left, Right};

        void computeLayout(
            const std::string &scaffoldId,
            ExtensionType extType,
            std::string &chain,
            const std::string &contig,
            unsigned int seedContigId,
            const ContigPairGraph &pairs,
            const ContigSeqHashMap &contigs,
            unsigned int &totalLength,
            VisitedHashMap &visited
        );

        void extendScaffold(
            ExtensionType extType,
            std::string &scaffold,
            const std::string &newContig,
            unsigned int newContigLength,
            const ContigPairValidator& cpv,
            float ratio
        );

        std::pair<std::string, bool> createGapSequenceFromLayout(
            const std::string& layout,
            const ReadSeqHashMap &reads,
            bool gapFilling
        );

        Scaffolder(const Scaffolder&) = delete;
        Scaffolder& operator=(const Scaffolder&) = delete;
    };

}} //namespace dnaasm::scfr

#endif //SCAFFOLDER_HPP
