/**
 * \file SingleGraphBuilder.cpp
 * \brief the C++ file with implementation of class for building a single graph from set of reads
 *
 */

#include "SingleGraphBuilder.hpp"
#include "../common/log.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    SingleGraphBuilder::SingleGraphBuilder(SingleGraph& singleGraph,
                                           Statistics& statistics,
                                           mt4cpp::Progress* progress)
        : singleGraph_(singleGraph)
        , statistics_(statistics)
        , progress_(progress)
    {}

    void SingleGraphBuilder::build(vector<char>& firstChars, vector<uint48>& compressedTargets) {
        unsigned long long numOfVertices = 0ULL;
        std::vector<DeBruijnGraphVertex> uncompressedSources;
        std::vector<DeBruijnGraphVertex> uncompressedTargets;
        std::vector<DeBruijnGraphEdgeProperties> counters;
        fillVectors(compressedTargets, uncompressedSources, uncompressedTargets, counters, firstChars, numOfVertices);
        buildGraph(uncompressedSources, uncompressedTargets, counters, numOfVertices);
    }

    void SingleGraphBuilder::fillVectors(vector<uint48>& compressedTargets,
                                         vector<DeBruijnGraphVertex>& uncompressedSources,
                                         vector<DeBruijnGraphVertex>& uncompressedTargets,
                                         std::vector<DeBruijnGraphEdgeProperties>& counters,
                                         vector<char>& firstChars,
                                         unsigned long long& numOfVertices) {
        vector<uint48> compressedSources;
        singleGraph_.fillVectors(compressedSources, compressedTargets, counters, firstChars, numOfVertices);
        singleGraph_.convertVectors(compressedSources, compressedTargets, uncompressedSources, uncompressedTargets);
    }

    void SingleGraphBuilder::buildGraph(vector<DeBruijnGraphVertex>& sources,
                                        vector<DeBruijnGraphVertex>& targets,
                                        std::vector<DeBruijnGraphEdgeProperties>& counters,
                                        unsigned long long& numOfVertices) {
        logInfo("building de Bruijn graph...");
        singleGraph_.buildGraph(sources, targets, counters, numOfVertices);
        logInfo("graph is built...");
        logInfo("number of edges: " + to_string(num_edges(singleGraph_.getGraph())));
        logInfo("number of vertices: " + to_string(num_vertices(singleGraph_.getGraph())));
    }

}}

