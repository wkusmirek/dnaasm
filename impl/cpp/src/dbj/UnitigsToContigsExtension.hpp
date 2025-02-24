/**
 * \file UnitigsToContigsExtension.hpp
 * \brief the C++ file with declaration of class for extension contigs using paired-end tags
 *
 */

#ifndef UNITIGS_TO_CONTIGS_EXTENSION_HPP
#define UNITIGS_TO_CONTIGS_EXTENSION_HPP

#include "HashTableMultipleValue.hpp"
#include "../common/DnaSequenceRepresentationConverter.hpp"
#include "globals.hpp"
#include <mt4cpp/Scheduler.hpp>

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to extend contigs using paired-end tags
    */
    class UnitigsToContigsExtension {
    public:
        struct UnitigsGraphVertexProperties {
            UnitigsGraphVertexProperties() {
                sequence_ = "";
                sequenceSize_ = 0U;
                isLongNode_ = false;
                isOriginal_ = false;
                isExtended_ = false;
            };

            std::string sequence_;
            unsigned int sequenceSize_;
            bool isLongNode_;
            bool isOriginal_;
            bool isExtended_;
        };
        struct UnitigsGraphEdgeProperties {
            UnitigsGraphEdgeProperties() {
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
                                      /*boost::bidirectionalS,*/
                                      UnitigsGraphVertexProperties,
                                      UnitigsGraphEdgeProperties,
                                      boost::no_property,
                                      boost::vecS> UnitigsGraph;

        typedef typename boost::graph_traits<UnitigsGraph>::vertex_descriptor UnitigsGraphVertex;
        typedef typename boost::graph_traits<UnitigsGraph>::edge_descriptor UnitigsGraphEdge;
        typedef std::vector<UnitigsGraphVertex> Contig;
        typedef std::vector<Contig> Contigs;

        /**
         * \brief UnitigsToContigsExtension constructor.
         *
         * \param contigs set of contigs from uncompressed graph (without using paired-end tags)
         * \param K1 length of strings stored in graph vertices (K1 + 1 = k form k-spectrum)
         * \param insertSizeMean
         * \param insertSizeStdDev
         * \param progress actual task's progress
         */
        CALC_DLL(UnitigsToContigsExtension(unsigned short K1,
                                  float insertSizeMean,
                                  float insertSizeStdDev,
                                  unsigned short readLength,
                                  unsigned short pairedReadsThrFrom,
                                  unsigned short pairedReadsThrTo,
                                  std::istream& unitigsFile,
                                  std::vector<bool>& isOriginal,
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
         * \brief Gets the reference to UnitigsGraph object.
         *
         * \return returns reference to UnitigsGraph object
         */
        CALC_DLL(UnitigsGraph& getUnitigsGraph();)

        CALC_DLL(std::vector< std::vector<UnitigsGraphVertex> >& getExtendedSequences();)

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
        UnitigsGraph unitigsGraph_;
        std::vector< std::vector<UnitigsGraphVertex> > extendedSequences_;
        std::vector<bool>& isOriginal_;
        DnaSequenceRepresentationConverter dnaSequenceRepresentationConverter_;
        mt4cpp::Progress* progress_;
        UnitigsToContigsExtension& operator=(const UnitigsToContigsExtension&)= delete;

        /**
         * \brief Builds contigs graph - adds all vertices and edges, which represent connected contigs (same first and last vertex in contig).
         *
         * \return returns void
         */
        void buildUnitigsGraph();

        /**
         * \brief Finds contigs, which contain read.
         *
         * \param read pointer to string, which represent single read from set of input reads
         * \return returns set of contigs, which contains read
         */
        std::vector<std::pair<UnitigsGraphVertex, unsigned short>> findUnitigsGraphVertices(const char* k1Mer, std::bitset<2*MAX_KMER_LENGTH>& bitsetK1Mer, bool isWholeReadValid);

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

        void correctOriginality();

        void initMaxInsertSize();

        void buildHashTable();

        void extendLongUnitigsToContigs();

        void extendLongUnitigsToScaffolds();

    };
}}

#endif    // UNITIGS_TO_CONTIGS_EXTENSION_HPP
