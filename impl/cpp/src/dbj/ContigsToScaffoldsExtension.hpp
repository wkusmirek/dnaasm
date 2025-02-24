/**
 * \file ContigsToScaffoldsExtension.hpp
 * \brief the C++ file with declaration of class for extension contigs using mate pairs
 */

#ifndef CONTIGS_TO_SCAFFOLDS_EXTENSION_HPP
#define CONTIGS_TO_SCAFFOLDS_EXTENSION_HPP

#include "HashTableMultipleValue.hpp"
#include "../common/DnaSequenceRepresentationConverter.hpp"
#include "globals.hpp"
#include <mt4cpp/Scheduler.hpp>

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to extend contigs using mate pairs
    */
    class ContigsToScaffoldsExtension {
    public:
        struct ContigsGraphVertexProperties {
            ContigsGraphVertexProperties() {
                sequenceSize_ = 0U;
                isLongNode_ = false;
                isExtended_ = false;
            };

            unsigned int sequenceSize_;
            bool isLongNode_;
            bool isExtended_;
        };
        struct ContigsGraphEdgeProperties {
            ContigsGraphEdgeProperties() {
                isForConnectedSequences_ = false;
                isForPairedReads_ = false;
                estimatedDistance_ = 0U;
                counter_ = 0U;
            };

            bool isForConnectedSequences_;
            bool isForPairedReads_;
            std::vector<unsigned short> insertSizeOffsetVector_;
            unsigned short estimatedDistance_;
            unsigned short counter_;
        };
        typedef boost::adjacency_list<boost::vecS,
                                      boost::vecS,
                                      boost::directedS,
                                      ContigsGraphVertexProperties,
                                      ContigsGraphEdgeProperties,
                                      boost::no_property,
                                      boost::vecS> ContigsGraph;

        typedef typename boost::graph_traits<ContigsGraph>::vertex_descriptor ContigsGraphVertex;
        typedef typename boost::graph_traits<ContigsGraph>::edge_descriptor ContigsGraphEdge;
        typedef std::vector<ContigsGraphVertex> Contig;
        typedef std::vector<Contig> Contigs;

        /**
         * \brief ContigsToScaffoldsExtension constructor.
         *
         * \param contigs set of contigs from uncompressed graph (without using paired-end tags)
         * \param K1 length of strings stored in graph vertices (K1 + 1 = k form k-spectrum)
         * \param insertSizeMean
         * \param insertSizeStdDev
         * \param progress actual task's progress
         */
        CALC_DLL(ContigsToScaffoldsExtension(unsigned short K1,
                                  float insertSizeMean,
                                  float insertSizeStdDev,
                                  unsigned short readLength,
                                  unsigned short pairedReadsThrFrom,
                                  unsigned short pairedReadsThrTo,
                                  std::istream& unitigsFile,
                                  std::istream& contigsFile,
                                  std::vector<bool>& isOriginalUnitig,
                                  mt4cpp::Progress* progress);
                )

        /**
         * \brief Adds paired reads to a graph with contigs (adds only edges to graph with contigs), both reads are in FF orientation.
         *
         * \param read first read in pair
         * \param pairedRead second read in pair
         * \return returns void
         */
        CALC_DLL(void addPairedReads(const std::string& read, const std::string& pairedRead);)

        /**
         * \brief Extends contigs using paired-end tags.
         *
         * \return returns set of extended contigs
         */
        CALC_DLL(Contigs& extendContigs();)

        CALC_DLL(void extend();)

        CALC_DLL(void estimateDistancesBetweenContigs();)

        /**
         * \brief Gets the reference to ContigsGraph object.
         *
         * \return returns reference to ContigsGraph object
         */
        CALC_DLL(ContigsGraph& getContigsGraph();)

        CALC_DLL(std::vector< std::vector<ContigsGraphVertex> >& getExtendedSequences();)

    private:
        Contigs outContigs_;
        unsigned short K1_;
        float insertSizeMean_;
        float insertSizeStdDev_;
        unsigned short maxInsertSize_;
        unsigned short readLength_;
        unsigned short pairedReadsThrFrom_;
        unsigned short pairedReadsThrTo_;
        HashTableMultipleValue hashTableMultipleValue_;
        std::istream& unitigsFile_;
        std::istream& contigsFile_;
        ContigsGraph contigsGraph_;
        std::vector< std::vector<ContigsGraphVertex> > extendedSequences_;
        std::vector<bool>& isOriginalUnitig_;
        DnaSequenceRepresentationConverter dnaSequenceRepresentationConverter_;
        mt4cpp::Progress* progress_;
        ContigsToScaffoldsExtension& operator=(const ContigsToScaffoldsExtension&)= delete;

        /**
         * \brief Builds contigs graph - adds all vertices and edges, which represent connected contigs (same first and last vertex in contig).
         *
         * \return returns void
         */
        void buildContigsGraph();

        /**
         * \brief Finds contigs, which contain read.
         *
         * \param read pointer to string, which represent single read from set of input reads
         * \return returns set of contigs, which contains read
         */
        std::vector<std::pair<ContigsGraphVertex, unsigned short>> findContigsGraphVertices(const char* k1Mer, std::bitset<2*MAX_KMER_LENGTH>& bitsetK1Mer, bool isWholeReadValid);

        /**
         * \brief Marks long contigs (with size greater than maximum value of insert size).
         *
         * \return returns void
         */
        void markLongContigs();

        /**
         * \brief Generates set of extended contigs (using information, which contigs should be merged).
         *
         * \return returns void
         */
        void generateOutContigs();

        void initMaxInsertSize();

        void buildHashTable();

        void extendLongUnitigsToScaffolds();

    };
}}

#endif    // CONTIGS_TO_SCAFFOLDS_EXTENSION_HPP
