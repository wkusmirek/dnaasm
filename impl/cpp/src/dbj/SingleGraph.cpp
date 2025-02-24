/**
 * \file SingleGraph.cpp
 * \brief the C++ file with implementation of class for building a single graph from set of reads
 *
 */

#include <fstream>

#include "SingleGraph.hpp"
#include "../common/Read.hpp"
#include "../common/log.hpp"

using namespace std;

namespace dnaasm { namespace dbj {

    SingleGraph::SingleGraph(DeBruijnGraph& deBruijnGraph,
                             std::istream& occurrenceTable,
                             unsigned short K1,
                             unsigned int threshold)
        : deBruijnGraph_(deBruijnGraph)
        , occurrenceTable_(occurrenceTable)
        , K1_(K1), threshold_(threshold)
        , dnaSequenceRepresentationConverter_(K1_)
    {}

    DeBruijnGraph& SingleGraph::getGraph() {   //added to testing process
        return deBruijnGraph_;
    }

    void SingleGraph::fillVectors(vector<uint48>& sources,
                                  vector<uint48>& targets,
                                  vector<DeBruijnGraphEdgeProperties>& counters,
                                  vector<char>& firstChars,
                                  unsigned long long& numOfVertices) {
        logInfo("Counting number of lines...");
        unsigned long long numOfLines = 0ULL;

        while (true) {
            string kMer = "";
            unsigned int numOfOccurrence = 0U;
            occurrenceTable_ >> kMer >> numOfOccurrence;

            if (kMer == "") {
                break;
            }

            if (numOfOccurrence >= threshold_ && static_cast<unsigned short>(kMer.size()) == K1_ + 1U) {
                ++numOfLines;
                if (numOfLines % 10000000 == 0) {
                    logInfo("processing line number: " + to_string(numOfLines));
                }
            }
        }

        occurrenceTable_.clear();
        occurrenceTable_.seekg(ios::beg);
        logInfo("Num of lines: " + std::to_string(numOfLines));
        HashTable hashTable(K1_);
        sources.resize(numOfLines*2ULL);
        targets.resize(numOfLines*2ULL);
        counters.resize(numOfLines*2ULL);
        firstChars.resize(numOfLines*4ULL);
        unsigned long long int actualVertex = 0ULL;
        size_t i = 0U;

        while (true) {
            string kMer = "";
            unsigned int numOfOccurrence = 0U;
            occurrenceTable_ >> kMer >> numOfOccurrence;

            if (kMer == "") {
                numOfVertices = hashTable.size();
                return;
            }

            if (numOfOccurrence >= threshold_ && static_cast<unsigned short>(kMer.size()) == K1_ + 1U) {
                Read read(0U);
                read.setRead(kMer);
                read.makeComplementaryStrand();
                SingleGraph::DeBruijnGraphVertex v0 = addK1mer(hashTable, kMer.data(), actualVertex, firstChars);
                SingleGraph::DeBruijnGraphVertex v1 = addK1mer(hashTable, kMer.data()+1, actualVertex, firstChars);
                SingleGraph::DeBruijnGraphVertex v2 = addK1mer(hashTable, read.getRead().data(), actualVertex, firstChars);
                SingleGraph::DeBruijnGraphVertex v3 = addK1mer(hashTable, read.getRead().data()+1, actualVertex, firstChars);
                sources[i].v = v0;
                targets[i].v = v1;
                counters[i].counter_ = numOfOccurrence;
                ++i;
                sources[i].v = v2;
                targets[i].v = v3;
                counters[i].counter_ = numOfOccurrence;
                ++i;

                if (i % 10000000 == 0) {
                    logInfo("processing line number: " + to_string(i));
                }
            }
        }
    }

    void SingleGraph::convertVectors(vector<uint48>& inputSources,
                                     vector<uint48>& inputTargets,
                                     vector<DeBruijnGraphVertex>& outputSources,
                                     vector<DeBruijnGraphVertex>& outputTargets) {
        outputSources.resize(inputSources.size());
        outputTargets.resize(inputTargets.size());

        for (size_t i = 0; i < inputSources.size(); ++i) {
            outputSources[i] = inputSources[i].v;
            outputTargets[i] = inputTargets[i].v;
        }
    }

    void SingleGraph::buildGraph(std::vector<DeBruijnGraphVertex>& sources,
                                 std::vector<DeBruijnGraphVertex>& targets,
                                 std::vector<DeBruijnGraphEdgeProperties>& counters,
                                 unsigned long long numOfVertices) {

        if (sources.size() == targets.size() && targets.size() == counters.size() && numOfVertices != 0ULL) {
            deBruijnGraph_ = DeBruijnGraph(boost::construct_inplace_from_sources_and_targets, sources, targets, counters, numOfVertices);
        }
    }

    void SingleGraph::buildSequencesVector(std::vector<std::bitset<2*MAX_KMER_LENGTH>>& sequences,
                                           std::vector<uint48>& targets) {
        occurrenceTable_.clear();
        occurrenceTable_.seekg(ios::beg);
        size_t i = 0U;

        while (true) {
            string kMer = "";
            unsigned int numOfOccurrence = 0U;
            occurrenceTable_ >> kMer >> numOfOccurrence;

            if (kMer == "") {
                return;
            }

            if (numOfOccurrence >= threshold_ && static_cast<unsigned short>(kMer.size()) == K1_ + 1U) {
                Read read(0U);
                read.setRead(kMer);
                read.makeComplementaryStrand();
                sequences[targets[i].v] = dnaSequenceRepresentationConverter_.convertToBitset(kMer.data()+1);
                ++i;
                sequences[targets[i].v] = dnaSequenceRepresentationConverter_.convertToBitset(read.getRead().data()+1);
                ++i;

                if (i % 10000000 == 0) {
                    logInfo("processing line number: " + to_string(i));
                }
            }
        }
    }

    SingleGraph::DeBruijnGraphVertex SingleGraph::addK1mer(HashTable& hashTable,
                                                    const char* k1Mer,
                                                    unsigned long long int& actualVertex,
                                                    vector<char>& firstChars) {
        bitset<2*MAX_KMER_LENGTH> bitsetK1Mer = dnaSequenceRepresentationConverter_.convertToBitset(k1Mer);
        HashTable::iterator vertexIt = hashTable.find(bitsetK1Mer);

        if (vertexIt == hashTable.end()) {
            hashTable.insert(bitsetK1Mer, actualVertex);
            firstChars[actualVertex] = k1Mer[0];
            ++actualVertex;
            return actualVertex-1;
        }

        return vertexIt->second;
    }

}}

