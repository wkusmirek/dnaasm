/**
 * \file SingleGraphBuilder.hpp
 * \brief the C++ file with declaration of class for building a single graph from set of reads
 *
 */

#ifndef SINGLE_GRAPH_BUILDER_HPP
#define SINGLE_GRAPH_BUILDER_HPP

#include "SingleGraph.hpp"
#include "Statistics.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to build a single graph from set of reads.
     */
    class SingleGraphBuilder {

    public:
        typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;

        /**
         * \brief SingleGraphBuilder constructor.
         *
         * \param singleGraph reference to SingleGraph object
         * \param statistics reference to Statistics object to collect reads statistics
         * \param progress actual task's progress
         */
        CALC_DLL(SingleGraphBuilder(SingleGraph& singleGraph, Statistics& statistics, mt4cpp::Progress* progress);)

        /**
         * \brief Build single graph from set of reads.
         *
         * \param firstChars vector of chars (for which vertex first char is stored here)
         * \param compressedTargets vector of compressed targets
         * \return returns void
         */
        CALC_DLL(void build(std::vector<char>& firstChars, std::vector<uint48>& compressedTargets);)

    private:
        SingleGraph& singleGraph_;
        Statistics& statistics_;
        mt4cpp::Progress* progress_;
        SingleGraphBuilder& operator=(const SingleGraphBuilder&)= delete;

        /**
         * \brief Fills some vectors with information from BFCounter output file.
         *
         * \param compressedTargets vector of compressed targets
         * \param uncompressedSources vector of uncompressed sources
         * \param uncompressedTargets vector of uncompressed targets
         * \param counters vector of counter for each edge
         * \param firstChars vector of chars (for which vertex first char is stored here)
         * \param numOfVertices number of vertices
         * \return returns void
         */
        CALC_DLL(void fillVectors(std::vector<uint48>& compressedTargets,
                                  std::vector<DeBruijnGraphVertex>& uncompressedSources,
                                  std::vector<DeBruijnGraphVertex>& uncompressedTargets,
                                  std::vector<DeBruijnGraphEdgeProperties>& counters,
                                  std::vector<char>& firstChars,
                                  unsigned long long& numOfVertices);
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
                                 unsigned long long& numOfVertices);
                )

    };
}}

#endif    // SINGLE_GRAPH_BUILDER_HPP
