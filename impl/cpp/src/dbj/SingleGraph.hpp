/**
 * \file SingleGraph.hpp
 * \brief the C++ file with declaration of class for building a single graph from set of reads
 *
 */

#ifndef SINGLE_GRAPH_HPP
#define SINGLE_GRAPH_HPP

#include <mt4cpp/Scheduler.hpp>
#include "globals.hpp"

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to build a single graph from set of reads.
     */
    class SingleGraph {

    public:
        typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

        /**
         * \brief SingleGraph constructor.
         *
         * \param deBruijnGraph reference to DeBruijnGraph object
         * \param occurrenceTable output file (text) from BFCounter application
         * \param K1 length of strings stored in graph vertices (K1 + 1 = k form k-spectrum)
         * \param threshold k-mers, which occurre less often than threshold are discarded
         */
        CALC_DLL(SingleGraph(DeBruijnGraph& deBruijnGraph, std::istream& occurrenceTable, unsigned short K1, unsigned int threshold);)

        /**
         * \brief Gets the reference to DeBruijnGraph object.
         *
         * \return returns reference to DeBruijnGraph object
         */
         CALC_DLL(DeBruijnGraph& getGraph();)

        /**
         * \brief Fills some vectors with information from BFCounter output file.
         *
         * \param sources vector of compressed sources
         * \param targets vector of compressed targets
         * \param counters vector of counter for each edge
         * \param firstChars vector of chars (for which vertex first char is stored here)
         * \param numOfVertices number of vertices
         * \return returns void
         */
         CALC_DLL(void fillVectors(std::vector<uint48>& sources,
                                   std::vector<uint48>& targets,
                                   std::vector<DeBruijnGraphEdgeProperties>& counters,
                                   std::vector<char>& firstChars,
                                   unsigned long long& numOfVertices);
                 )

        /**
         * \brief Converts vectors of sources and vectors from compressed representation to uncompressed representation.
         *
         * \param inputSources vector of compressed sources
         * \param inputTargets vector of compressed targets
         * \param outputSources vector of decompressed sources
         * \param outputTargets vector of decompressed targets
         * \return returns void
         */
         CALC_DLL(void convertVectors(std::vector<uint48>& inputSources,
                                      std::vector<uint48>& inputTargets,
                                      std::vector<DeBruijnGraphVertex>& outputSources,
                                      std::vector<DeBruijnGraphVertex>& outputTargets);
                 )

        /**
         * \brief Builds graph from vectors of sources, targets and counters.
         *
         * \param sources vector of source id for each edge
         * \param targets vector of target id for each edge
         * \param counters vector of counter for each edge
         * \param numOfVertices number of vertices
         * \return returns void
         */
         CALC_DLL(void buildGraph(std::vector<DeBruijnGraphVertex>& sources, 
                                  std::vector<DeBruijnGraphVertex>& targets, 
                                  std::vector<DeBruijnGraphEdgeProperties>& counters, 
                                  unsigned long long numOfVertices);
                 )

        /**
         * \brief Builds vector of sequences, each sequence contains k1 signs, only targets considered.
         *
         * \param sequences vector of sequences for each target of each edge
         * \param targets vector of target id for each edge
         * \return returns void
         */
         CALC_DLL(void buildSequencesVector(std::vector<std::bitset<2*MAX_KMER_LENGTH>>& sequences, 
                                            std::vector<uint48>& targets);
                 )

    private:
        DeBruijnGraph& deBruijnGraph_;
        std::istream& occurrenceTable_;
        unsigned short K1_;
        unsigned int threshold_;
        DnaSequenceRepresentationConverter dnaSequenceRepresentationConverter_;
        SingleGraph& operator=(const SingleGraph&)= delete;

        /**
         * \brief Checks if vertex is present in hash table, if not, add it, store first char for this vertex etc.
         *
         * \param hashTable object seduced to map k1-mer on specified vertex
         * \param k1Mer string representing k1-mer (k1 + 1 equal to graph dimension)
         * \param actualVertex if vertex should be added, it should have id equal to actualVertex
         * \param firstChars vector of chars (for which vertex first char is stored here)
         * \return returns id of vertex
         */
        CALC_DLL(DeBruijnGraphVertex addK1mer(HashTable& hashTable,
                                       const char* k1Mer, 
                                       unsigned long long int& actualVertex, 
                                       std::vector<char>& firstChars);
                )

    };
}}

#endif    // SINGLE_GRAPH_HPP
