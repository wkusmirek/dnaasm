/**
 * \file UnitigsToContigsExtension.cpp
 * \brief the C++ file with implementation of template class for extension contigs using paired-end tags
 *
 */

#include "UnitigsToContigsExtension.hpp"
#include "CalcMaxGapSize.hpp"
#include "JoinExtendedSequences.hpp"
#include "ExtendContigsSubgraph.hpp"
#include "ConnectedVerticesMarker.hpp"
#include "RemoveTips.hpp"
#include <iostream>
#include <algorithm>
#include <boost/graph/strong_components.hpp>
#include <fstream>
#include "DistanceEstimator.hpp"
#include "DistanceArrayBuilder.hpp"
#include "FilterGraph.hpp"
#include "ClearGraph.hpp"
#include "RemoveLowCounterEdges.hpp"
#include "LowCounterEdgesCoverUncover.hpp"

using namespace std;

namespace dnaasm { namespace dbj {

    /**
     * \brief Checks if one vector is contained in another vector.
     *
     * \param a first vector
     * \param b second vector
     * \return returns information about containing
     */
    template <typename T1, typename T2>
    bool contains(std::vector<T1> const& a, std::vector<T2> const& b) {
        for (typename std::vector<T1>::const_iterator i = a.begin(), y = a.end(); i != y; ++i) {
            bool match = true;
            typename std::vector<T1>::const_iterator ii = i;
            for (typename std::vector<T2>::const_iterator j = b.begin(), z = b.end(); j != z; ++j) {
                if (ii == a.end()|| *j != *ii) {
                    match = false;
                    break;
                }
                ii++;
            }
            if (match)
                return true;
        }
        return false;
    }

    UnitigsToContigsExtension::UnitigsToContigsExtension(unsigned short K1,
                                       float insertSizeMean,
                                       float insertSizeStdDev,
                                       unsigned short readLength,
                                       unsigned short pairedReadsThrFrom,
                                       unsigned short pairedReadsThrTo,
                                       istream& unitigsFile,
                                       vector<bool>& isOriginal,
                                       mt4cpp::Progress* progress)
        : K1_(K1)
        , insertSizeMean_(insertSizeMean)
        , insertSizeStdDev_(insertSizeStdDev)
        , maxInsertSize_(0U)
        , readLength_(readLength)
        , pairedReadsThrFrom_(pairedReadsThrFrom)
        , pairedReadsThrTo_(pairedReadsThrTo)
        , hashTableMultipleValue_(K1)
        , unitigsFile_(unitigsFile)
        , isOriginal_(isOriginal)
        , dnaSequenceRepresentationConverter_(MAX_KMER_LENGTH)
        , progress_(progress)
    {initMaxInsertSize(); buildHashTable(); buildUnitigsGraph(); correctOriginality();}


        void UnitigsToContigsExtension::addPairedReads(const string& read, const string& pairedRead)
        {
            if (read.size() < K1_ || pairedRead.size() < K1_ || read.size() != pairedRead.size())
                return;
            vector<UnitigsGraphEdge> consideredEdges;
            const char* readPtr = read.data();
            const char* lastReadPtr = readPtr + read.size()- K1_;
            bitset<2*MAX_KMER_LENGTH> lastReadBitset = dnaSequenceRepresentationConverter_.convertToBitset(lastReadPtr);
            const char* pairedReadPtr = pairedRead.data();
            const char* lastPairedReadPtr = pairedReadPtr + pairedRead.size() - K1_;
            bitset<2*MAX_KMER_LENGTH> lastPairedReadBitset = dnaSequenceRepresentationConverter_.convertToBitset(lastPairedReadPtr);
            bool isWholeReadValid = hashTableMultipleValue_.isValid(readPtr, read.size());
            bool isWholePairedReadValid = hashTableMultipleValue_.isValid(pairedReadPtr, pairedRead.size());
            vector<pair<UnitigsGraphVertex, unsigned short>> lastReadPtrVertices = findUnitigsGraphVertices(lastReadPtr, lastReadBitset, isWholeReadValid);
            vector<pair<UnitigsGraphVertex, unsigned short>> lastPairedReadPtrVertices = findUnitigsGraphVertices(lastPairedReadPtr, lastPairedReadBitset, isWholePairedReadValid);
            vector<pair<UnitigsGraphVertex, unsigned short>> prevFromVertices;
            vector<pair<UnitigsGraphVertex, unsigned short>> prevToVertices;
            bitset<2*MAX_KMER_LENGTH> readBitset = dnaSequenceRepresentationConverter_.convertToBitset(read.data());
            unsigned short readBitsetOffset = 0U;
            for (; readPtr <= lastReadPtr; ++readPtr)
            {
                if (readBitsetOffset == MAX_KMER_LENGTH - K1_ - 1) {
                    readBitset = dnaSequenceRepresentationConverter_.convertToBitset(readPtr);
                    readBitsetOffset = 0U;
                }
                const char* pairedReadPtr = pairedRead.data();
                const char* lastPairedReadPtr = pairedReadPtr + pairedRead.size() - K1_;
                vector<pair<UnitigsGraphVertex, unsigned short>> fromVertices = findUnitigsGraphVertices(readPtr, readBitset, isWholeReadValid);
                readBitset = readBitset >> 2;
                readBitsetOffset += 1U;
                if (fromVertices == prevFromVertices) {
                    continue;
                }

                prevFromVertices = fromVertices;
                bitset<2*MAX_KMER_LENGTH> pairedReadBitset = dnaSequenceRepresentationConverter_.convertToBitset(pairedRead.data());
                unsigned short pairedReadBitsetOffset = 0U;
                for (; pairedReadPtr <= lastPairedReadPtr; ++pairedReadPtr)
                {
                    if (pairedReadBitsetOffset == MAX_KMER_LENGTH - K1_ - 1) {
                        pairedReadBitset = dnaSequenceRepresentationConverter_.convertToBitset(pairedReadPtr);
                        pairedReadBitsetOffset = 0U;
                    }
                    vector<pair<UnitigsGraphVertex, unsigned short>> toVertices = findUnitigsGraphVertices(pairedReadPtr, pairedReadBitset, isWholeReadValid);
                    pairedReadBitset = pairedReadBitset >> 2;
                    pairedReadBitsetOffset += 1U;
                    if (toVertices == prevToVertices) {
                        continue;
                    }

                    prevToVertices = toVertices;
                    for (typename vector<pair<UnitigsGraphVertex, unsigned short>>::iterator fromIt = fromVertices.begin(); fromIt != fromVertices.end(); ++fromIt)
                    {
                        if (unitigsGraph_[fromIt->first].isOriginal_ == true || unitigsGraph_[fromIt->first].isLongNode_ == true) {
                            for (typename vector<pair<UnitigsGraphVertex, unsigned short>>::iterator toIt = toVertices.begin(); toIt != toVertices.end(); ++toIt)
                            {
                                if (fromIt->first == toIt->first)   //without self-loops
                                {
                                    continue;
                                }
                                else
                                {
                                    pair<UnitigsGraphEdge,bool> unitigsGraphEdge = edge(fromIt->first, toIt->first, unitigsGraph_);
                                    if (unitigsGraphEdge.second && unitigsGraph_[unitigsGraphEdge.first].estimatedDistance_ == 1U)   // edge was considered
                                    {
                                        continue;
                                    }
                                    if (unitigsGraphEdge.second && unitigsGraph_[unitigsGraphEdge.first].insertSizeOffsetVector_.size() > 10)
                                        continue;
                                    unsigned short fromOffset = fromIt->second;
                                    if (unitigsGraph_[fromIt->first].sequence_.size() <= 2U * maxInsertSize_)
                                        fromOffset = unitigsGraph_[fromIt->first].sequence_.size() - fromIt->second;
                                    unsigned short totalOffset
                                        = fromOffset+toIt->second
                                        + static_cast<unsigned short>(readPtr-read.data()
                                                                      + readLength_
                                                                      - pairedRead.size()
                                                                      + lastPairedReadPtr
                                                                      - pairedReadPtr+K1_);
                                    if (!unitigsGraphEdge.second)   // if edge does not exist
                                    {
                                        unitigsGraphEdge = add_edge(fromIt->first, toIt->first, unitigsGraph_);
                                    }
                                    unitigsGraph_[unitigsGraphEdge.first].isForPairedReads_ = true;
                                    unitigsGraph_[unitigsGraphEdge.first].insertSizeOffsetVector_.push_back(totalOffset);
                                    consideredEdges.push_back(unitigsGraphEdge.first);
                                    unitigsGraph_[unitigsGraphEdge.first].estimatedDistance_ = 1U;
                                    ++unitigsGraph_[unitigsGraphEdge.first].counter_;
                                }

                            }
                        }
                    }
                    if (toVertices == lastPairedReadPtrVertices) {
                        break;
                    }
                }
                if (fromVertices == lastReadPtrVertices && fromVertices.size() == 1 &&
                    unitigsGraph_[fromVertices[0].first].isLongNode_)
                {
                    break;
                }
            }
            for(auto it = consideredEdges.begin(); it != consideredEdges.end(); ++it) {
                unitigsGraph_[*it].estimatedDistance_ = 0U;
            }
        }

        void UnitigsToContigsExtension::estimateDistancesBetweenContigs()
        {
            DistanceEstimator distanceEstimator(insertSizeMean_, insertSizeStdDev_, maxInsertSize_);
            typename boost::graph_traits<UnitigsGraph>::edge_iterator ei, ei_end;
            std::size_t i = 1;
            for (boost::tie(ei, ei_end)= edges(unitigsGraph_); ei != ei_end; ++ei, ++i)
            {
                if (i % 10000 == 0)
                {
                    logInfo("processing edge number: " + to_string(i));
                }
                unitigsGraph_[*ei].estimatedDistance_ = distanceEstimator.estimateDistanceBetweenSequences(unitigsGraph_[*ei].insertSizeOffsetVector_);
                vector<unsigned short>().swap(unitigsGraph_[*ei].insertSizeOffsetVector_);   // free memory allocated by vector
            }
        }

        /**
         * \brief Extends contigs using paired-end tags.
         *
         * \return returns set of extended contigs
         */
        UnitigsToContigsExtension::Contigs& UnitigsToContigsExtension::extendContigs()
        {
            markLongContigs();
            correctOriginality();
            logInfo("Distances between unitigs estimation...");
            estimateDistancesBetweenContigs();

            extend();

            JoinExtendedSequences<UnitigsGraph> joinExtendedSequences(unitigsGraph_, extendedSequences_);
            joinExtendedSequences();

            generateOutContigs();
            return outContigs_;
        }

        void UnitigsToContigsExtension::extend()
        {
            logInfo("Extending unitigs to contigs...");
            LowCounterEdgesCoverUncover<UnitigsGraph> lowCounterEdgesCoverUncover(unitigsGraph_);
            for (unsigned short pairedReadsThr = pairedReadsThrFrom_; pairedReadsThr <= pairedReadsThrTo_; ++pairedReadsThr) {
                lowCounterEdgesCoverUncover.cover(pairedReadsThr);
                extendLongUnitigsToContigs();
            }
            lowCounterEdgesCoverUncover.uncover();
            logInfo("Extending unitigs to scaffolds...");
            for (unsigned short pairedReadsThr = pairedReadsThrFrom_; pairedReadsThr <= pairedReadsThrTo_; ++pairedReadsThr) {
                lowCounterEdgesCoverUncover.cover(pairedReadsThr);
                extendLongUnitigsToScaffolds();
            }
            lowCounterEdgesCoverUncover.uncover();
        }

        void UnitigsToContigsExtension::extendLongUnitigsToContigs()
        {
            unsigned int longStartUnitigBadStructure = 0U;
            unsigned int longStartUnitigGoodStructure = 0U;
            unsigned int progress = 0U;
            FilterGraph<UnitigsGraph> filterGraph(unitigsGraph_);
            DistanceArrayBuilder<UnitigsGraph> distanceArrayBuilder(unitigsGraph_);
            typename boost::graph_traits<UnitigsGraph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end)= vertices(unitigsGraph_); vi != vi_end; ++vi)
            {
                ++progress;
                if (progress % 1000000 == 0)
                {
                    logInfo("Processing vertex number: " + to_string(progress));
                    if (progress_ != NULL)
                        progress_->setProgress(0.875+static_cast<float>(progress)/static_cast<float>(num_vertices(unitigsGraph_))/8.0);
                }

                if (unitigsGraph_[*vi].isLongNode_ && unitigsGraph_[*vi].isOriginal_ && !unitigsGraph_[*vi].isExtended_)
                {
                    UnitigsGraphVertex sourceVertex = *vi;
                    vector<bool> isConnected(num_vertices(unitigsGraph_), false);

                    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph_, sourceVertex, isConnected);
                    connectedVerticesMarker();

                    UnitigsGraph copyUnitigsGraph;
                    vector<UnitigsToContigsExtension::UnitigsGraphVertex> connectedVerticesId = filterGraph(copyUnitigsGraph, isConnected);

                    vector<UnitigsGraphVertex> inVertices;
                    vector<UnitigsGraphVertex> outVertices;
                    GraphInOutFinder<UnitigsGraph> graphInOutFinder(copyUnitigsGraph);

                    RemoveTips<UnitigsGraph> removeTips(copyUnitigsGraph);
                    removeTips();

                    unsigned int prevVertices = static_cast<unsigned int>(count(isConnected.begin(), isConnected.begin()+*vi, true));
                    UnitigsGraphVertex startVertex = prevVertices;
                    
                    ClearGraph<UnitigsGraph> clearGraph(copyUnitigsGraph);
                    clearGraph.removeInEdgesForStartVertex(startVertex);
                    clearGraph.removeOutEdgesForEndVertex(startVertex);

                    inVertices.clear();
                    graphInOutFinder.findInVertices(inVertices);
                    outVertices.clear();
                    graphInOutFinder.findOutVertices(outVertices);

                    if (inVertices.size() != 1 || outVertices.size() != 1 || !copyUnitigsGraph[inVertices[0]].isLongNode_ ||
                        !copyUnitigsGraph[outVertices[0]].isLongNode_ || !copyUnitigsGraph[inVertices[0]].isOriginal_ ||
                        !copyUnitigsGraph[outVertices[0]].isOriginal_)
                    {
                        ++longStartUnitigBadStructure;
                        continue;
                    }
                    ++longStartUnitigGoodStructure;
                    boost::multi_array<unsigned short, 2> distanceArray = distanceArrayBuilder.buildDistanceArray(copyUnitigsGraph, connectedVerticesId);

                    ExtendContigsSubgraph<UnitigsGraph> extendContigsSubgraph(copyUnitigsGraph, distanceArray);
                    vector<UnitigsGraphVertex> tmpOutContigs = extendContigsSubgraph.extendContigsSubgraph(true);
                    if (tmpOutContigs.size() > 1) {
                        unitigsGraph_[*vi].isExtended_ = true;
                        extendedSequences_.push_back(vector<UnitigsGraphVertex>());
                        for (typename vector<UnitigsGraphVertex>::iterator it = tmpOutContigs.begin(); it != tmpOutContigs.end(); ++it) {
                            if (*it == std::numeric_limits<std::size_t>::max()) {
                                extendedSequences_.back().push_back(std::numeric_limits<std::size_t>::max());
                                ++it;
                                extendedSequences_.back().push_back(*it);
                            } else {
                                extendedSequences_.back().push_back(connectedVerticesId[*it]);
                            }
                        }
                    }

                }
            }
            logInfo("Long start unitig bad structure: " + to_string(longStartUnitigBadStructure));
            logInfo("Long start unitig good structure: " + to_string(longStartUnitigGoodStructure));
        }

        void UnitigsToContigsExtension::extendLongUnitigsToScaffolds()
        {
            unsigned int longStartUnitigBadStructure = 0U;
            unsigned int longStartUnitigGoodStructure = 0U;
            unsigned int progress = 0U;
            FilterGraph<UnitigsGraph> filterGraph(unitigsGraph_);
            DistanceArrayBuilder<UnitigsGraph> distanceArrayBuilder(unitigsGraph_);
            typename boost::graph_traits<UnitigsGraph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end)= vertices(unitigsGraph_); vi != vi_end; ++vi)
            {
                ++progress;
                if (progress % 1000000 == 0)
                {
                    logInfo("Processing vertex number: " + to_string(progress));
                    if (progress_ != NULL)
                        progress_->setProgress(0.875+static_cast<float>(progress)/static_cast<float>(num_vertices(unitigsGraph_))/8.0);
                }

                if (unitigsGraph_[*vi].isLongNode_ && unitigsGraph_[*vi].isOriginal_ && !unitigsGraph_[*vi].isExtended_)
                {
                    UnitigsGraphVertex sourceVertex = *vi;
                    vector<bool> isConnected(num_vertices(unitigsGraph_), false);

                    ConnectedVerticesMarker<UnitigsGraph> connectedVerticesMarker(unitigsGraph_, sourceVertex, isConnected);
                    connectedVerticesMarker();

                    UnitigsGraph copyUnitigsGraph;
                    vector<UnitigsToContigsExtension::UnitigsGraphVertex> connectedVerticesId = filterGraph(copyUnitigsGraph, isConnected);

                    GraphInOutFinder<UnitigsGraph> graphInOutFinder(copyUnitigsGraph);

                    RemoveTips<UnitigsGraph> removeTips(copyUnitigsGraph);
                    removeTips();

                    unsigned int prevVertices = static_cast<unsigned int>(count(isConnected.begin(), isConnected.begin()+*vi, true));
                    UnitigsGraphVertex startVertex = prevVertices;
                    
                    ClearGraph<UnitigsGraph> clearGraph(copyUnitigsGraph);
                    clearGraph.removeInEdgesForStartVertex(startVertex);
                    clearGraph.removeOutEdgesForEndVertex(startVertex);

                    unsigned short numOfLongAndOriginalNodes = 0U;
                    typename boost::graph_traits<UnitigsGraph>::vertex_iterator vi_copy, vi_end_copy;
                    for (boost::tie(vi_copy, vi_end_copy)= vertices(copyUnitigsGraph); vi_copy != vi_end_copy; ++vi_copy)
                    {
                        if (copyUnitigsGraph[*vi_copy].isLongNode_ && copyUnitigsGraph[*vi_copy].isOriginal_) {
                            ++numOfLongAndOriginalNodes;
                        }
                    }
                    if (numOfLongAndOriginalNodes == 2U) {
                        unitigsGraph_[*vi].isExtended_ = true;
                        unsigned short distance = 0U;
                        boost::multi_array<unsigned short, 2> distanceArray = distanceArrayBuilder.buildDistanceArray(copyUnitigsGraph, connectedVerticesId);
                        extendedSequences_.push_back(vector<UnitigsGraphVertex>());
                        extendedSequences_.back().push_back(*vi); // actual vertex
                        std::size_t source = 0UL;
                        for (boost::tie(vi_copy, vi_end_copy)= vertices(copyUnitigsGraph); vi_copy != vi_end_copy; ++vi_copy) {
                            if (connectedVerticesId[*vi_copy] == *vi) {
                                source = *vi_copy;
                            }
                        }
                        for (boost::tie(vi_copy, vi_end_copy)= vertices(copyUnitigsGraph); vi_copy != vi_end_copy; ++vi_copy) {
                            if (connectedVerticesId[*vi_copy] != *vi && copyUnitigsGraph[*vi_copy].isLongNode_ && copyUnitigsGraph[*vi_copy].isOriginal_) {
                                if (distanceArray[source][*vi_copy] != 0U) {
                                    distance = distanceArray[source][*vi_copy];
                                }
                                extendedSequences_.back().push_back(std::numeric_limits<std::size_t>::max());
                                extendedSequences_.back().push_back(distance);
                                extendedSequences_.back().push_back(connectedVerticesId[*vi_copy]);
                                break;
                            }
                        }
                        if (distance == 0U || distance > 700) {   // not properly linked
                            extendedSequences_.pop_back();
                            unitigsGraph_[*vi].isExtended_ = false;
                        } else {
                            ++longStartUnitigGoodStructure;
                        }
                    } else {
                        ++longStartUnitigBadStructure;
                    }
                }
            }
            logInfo("Long start unitig bad structure: " + to_string(longStartUnitigBadStructure));
            logInfo("Long start unitig good structure: " + to_string(longStartUnitigGoodStructure));
        }

        /**
         * \brief Gets the reference to UnitigsGraph object.
         *
         * \return returns reference to UnitigsGraph object
         */
        UnitigsToContigsExtension::UnitigsGraph& UnitigsToContigsExtension::getUnitigsGraph()
        {
            return unitigsGraph_;
        }

        std::vector< std::vector<UnitigsToContigsExtension::UnitigsGraphVertex> >& UnitigsToContigsExtension::getExtendedSequences() {
            return extendedSequences_;
        }

        // zakomentaować wywołanie funkcji estimateDistancesBetweenContigs w tym pliku
        // zakomentować addPairedReads w assembly.cpp
        /*void UnitigsToContigsExtension::buildUnitigsGraph()
        {
            logInfo("Building contigs graph...");
            unitigsFile_.clear();
            unitigsFile_.seekg(ios::beg);
            vector<string> unitigs;
            size_t i = 0U;
            while (true) {
                string id = "";
                string sequence = "";
                unitigsFile_ >> id >> sequence;
                if (id == "" || sequence == "") {
                    break;
                }
                unitigs.push_back(sequence);
                UnitigsGraphVertex v = add_vertex(unitigsGraph_);
                unitigsGraph_[v].sequenceSize_ = sequence.size() - K1_ + 1;
                unitigsGraph_[v].sequence_ = sequence;
                ++i;
                if (i % 1000000 == 0) {
                    logInfo("processing unitigs number: " + to_string(i));
                }
            }
            // s: 0 t: 391 1 s: 56 t: 39 0 0 est distance: 65535 org s: 1 org t: 0 c: 11
            ifstream edgesDescFile(CALC_TMP_DIR + "edgesDescOgorekTrimm""edgesDesc_ERR089806""edgesDescDrozdze""edgesDesc_SRR800765");
            while (true) {
                string tmpStr = "";
                unsigned long source = 0UL;
                unsigned long target = 0UL;
                bool isForConnectedContigs = false;
                bool isForPairedReads = false;
                unsigned short estimatedDistance = 0U;
                bool sourceOrg = false;
                bool targetOrg = false;
                unsigned short counter = 0U;
                edgesDescFile >> tmpStr >> source >> tmpStr >> target >> isForConnectedContigs >> tmpStr >> tmpStr >> tmpStr >> tmpStr >> isForPairedReads >> tmpStr >> tmpStr >> tmpStr >> estimatedDistance >> tmpStr >> tmpStr >> sourceOrg >> tmpStr >> tmpStr >> targetOrg >> tmpStr >> counter;
                if (tmpStr == "") {
                    break;
                }
                unitigsGraph_[source].isOriginal_ = sourceOrg;
                unitigsGraph_[target].isOriginal_ = targetOrg;
                add_edge(source, target, unitigsGraph_);
                unitigsGraph_[edge(source, target, unitigsGraph_).first].isForConnectedSequences_ = isForConnectedContigs;
                unitigsGraph_[edge(source, target, unitigsGraph_).first].isForPairedReads_ = isForPairedReads;
                unitigsGraph_[edge(source, target, unitigsGraph_).first].estimatedDistance_ = estimatedDistance;
                unitigsGraph_[edge(source, target, unitigsGraph_).first].counter_ = counter;
                ++i;
                if (i % 1000000 == 0) {
                    logInfo("processing edge number: " + to_string(i));
                }
            }
            std::cout << num_vertices(unitigsGraph_) << " " << num_edges(unitigsGraph_) << endl;
        }*/

        void UnitigsToContigsExtension::buildUnitigsGraph()
        {
            logInfo("Building contigs graph...");
            unitigsFile_.clear();
            unitigsFile_.seekg(ios::beg);
            vector<string> unitigs;
            size_t i = 0U;
            while (true) {
                string id = "";
                string sequence = "";
                unitigsFile_ >> id >> sequence;
                if (id == "" || sequence == "") {
                    break;
                }
                unitigs.push_back(sequence);
                UnitigsGraphVertex v = add_vertex(unitigsGraph_);
                unitigsGraph_[v].sequenceSize_ = sequence.size() - K1_ + 1;
                unitigsGraph_[v].sequence_ = sequence;
                ++i;
                if (i % 1000000 == 0) {
                    logInfo("processing unitigs number: " + to_string(i));
                }
            }
            for (auto& unitig : unitigs) {
                UnitigsGraphVertex consideredVertexId = &unitig- &unitigs[0];
                vector<pair<UnitigsGraphVertex, unsigned short>> suspectedVertices = hashTableMultipleValue_.find(unitig.data());
                for (auto& suspectedVertex : suspectedVertices) {
                    if (suspectedVertex.first == consideredVertexId) {
                        continue;
                    }
                    if (unitigs[suspectedVertex.first].substr(unitigs[suspectedVertex.first].size() - K1_, K1_) == unitigs[consideredVertexId].substr(0, K1_)) {
                        UnitigsGraphEdge edge = add_edge(suspectedVertex.first, consideredVertexId, unitigsGraph_).first;
                        unitigsGraph_[edge].isForConnectedSequences_ = true;
                    }
                }
            }
            typename boost::graph_traits<UnitigsGraph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end)= vertices(unitigsGraph_); vi != vi_end; ++vi)
            {
                unitigsGraph_[*vi].isOriginal_ = isOriginal_[*vi];
            }
            //std::cout << num_vertices(unitigsGraph_) << " " << num_edges(unitigsGraph_) << endl;
        }

        vector<pair<UnitigsToContigsExtension::UnitigsGraphVertex, unsigned short>> UnitigsToContigsExtension::findUnitigsGraphVertices(const char* k1Mer, bitset<2*MAX_KMER_LENGTH>& bitsetK1Mer, bool isWholeReadValid)
        {
            vector<pair<UnitigsGraphVertex, unsigned short>> vertices;
            if (isWholeReadValid || hashTableMultipleValue_.isValid(k1Mer, K1_))
            {
                vector<pair<UnitigsGraphVertex, unsigned short>> suspectedVerticesVector = hashTableMultipleValue_.find(bitsetK1Mer);
                for (auto it = suspectedVerticesVector.begin(); it != suspectedVerticesVector.end(); ++it) {
                    if (unitigsGraph_[it->first].sequence_.size() - K1_ + 1 > 2 && (strncmp(k1Mer, unitigsGraph_[it->first].sequence_.data(), K1_) == 0 ||
                        strncmp(k1Mer, unitigsGraph_[it->first].sequence_.data() + unitigsGraph_[it->first].sequence_.size() - K1_, K1_) == 0))   //dodane!!!!!!!!!!!!!!!!!!!!!
                    {
                        continue;
                    }

                    if (unitigsGraph_[it->first].sequence_.size() - K1_ + 1 == 2 && strncmp(k1Mer, unitigsGraph_[it->first].sequence_.data(), K1_) == 0)
                    //kontigi o wielkości dwa parowane tylko wg 2. wierzchołka, do poprawy!!!!!
                    {
                        continue;
                    }
                    vertices.push_back(*it);
                }
            }
            return vertices;
        }

        /**
         * \brief Marks long contigs (with size greater than maximum value of insert size).
         *
         * \return returns void
         */
        void UnitigsToContigsExtension::markLongContigs()
        {
            typename boost::graph_traits<UnitigsGraph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end)= vertices(unitigsGraph_); vi != vi_end; ++vi)
            {
                if (static_cast<float>(unitigsGraph_[*vi].sequence_.size() - K1_ + 1) > insertSizeMean_ - readLength_)
                {
                    unitigsGraph_[*vi].isLongNode_ = true;
                }
            }
        }

        void UnitigsToContigsExtension::initMaxInsertSize()
        {
            CalcMaxGapSize calcMaxGapSize(insertSizeMean_, insertSizeStdDev_);
            maxInsertSize_ = calcMaxGapSize.calcMaxGapSize();
        }

        void UnitigsToContigsExtension::correctOriginality()
        {
            typename boost::graph_traits<UnitigsGraph>::vertex_iterator vi2, vi2_end;
            for (boost::tie(vi2, vi2_end) = vertices(unitigsGraph_); vi2 != vi2_end; ++vi2)
            {
                if (unitigsGraph_[*vi2].sequence_.size() - K1_ + 1 == 2U)
                {
                    unitigsGraph_[*vi2].isOriginal_ = false;
                }
                if (unitigsGraph_[*vi2].sequence_.size() - K1_ + 1 > 5000U)    // this value should be added as application parameter - unitigs longer than 5000 bp are always original (there is no repetitive DNA fragment in investigated genome longer than 5000 bp)
                {
                    unitigsGraph_[*vi2].isOriginal_ = true;
                }
            }

            vector<unsigned int> in_degree(num_vertices(unitigsGraph_), 0U);
            vector<unsigned int> out_degree(num_vertices(unitigsGraph_), 0U);
            typename boost::graph_traits<UnitigsGraph>::edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = edges(unitigsGraph_); ei != ei_end; ++ei)
            {
                if (unitigsGraph_[*ei].isForConnectedSequences_)
                {
                    ++out_degree[source(*ei, unitigsGraph_)];
                    ++in_degree[target(*ei, unitigsGraph_)];
                }
            }
            typename boost::graph_traits<UnitigsGraph>::vertex_iterator vi, vi_end;
            unsigned int numOfOriginalVertices = 0U;
            for (boost::tie(vi, vi_end) = vertices(unitigsGraph_); vi != vi_end; ++vi)
            {
                if (unitigsGraph_[*vi].isOriginal_)
                {
                    ++numOfOriginalVertices;
                }
            }
            logInfo("Num of original vertices in contigs graph: " + to_string(numOfOriginalVertices));
            logInfo("Num of not original vertices in contigs graph: " + to_string(num_vertices(unitigsGraph_)-numOfOriginalVertices));
        }

        /**
         * \brief Generates set of extended contigs (using information, which contigs should be merged).
         *
         * \return returns void
         */
        void UnitigsToContigsExtension::generateOutContigs()
        {
            vector<bool> isContainedInAnother(extendedSequences_.size(), false);
            vector<bool> isInOutContigs(num_vertices(unitigsGraph_), false);
            for (typename vector< vector<UnitigsGraphVertex> >:: iterator it = extendedSequences_.begin(); it != extendedSequences_.end(); ++it)
            {
                if (isContainedInAnother[it - extendedSequences_.begin()])
                    continue;
                for (typename vector< vector<UnitigsGraphVertex> >:: iterator it2 = extendedSequences_.begin(); it2 != extendedSequences_.end(); ++it2)
                {
                    if (it == it2)
                        continue;
                    if (contains(*it, *it2))
                        isContainedInAnother[it2 - extendedSequences_.begin()] = true;
                }
            }

            for (typename vector< vector<UnitigsGraphVertex> >:: iterator it = extendedSequences_.begin(); it != extendedSequences_.end(); ++it)
            {
                if (isContainedInAnother[it - extendedSequences_.begin()])
                    continue;
                Contig tmpContig;
                unsigned int totalSize = 0U;
                for (typename vector<UnitigsGraphVertex>:: iterator it2 = it->begin(); it2 != it->end(); ++it2)
                {
                    if (*it2 == std::numeric_limits<std::size_t>::max()) {
                        tmpContig.push_back(std::numeric_limits<std::size_t>::max());
                        ++it2;
                        tmpContig.push_back(*it2);
                    } else {
                        UnitigsGraphVertex v = *it2;
                        totalSize += unitigsGraph_[v].sequence_.size() - K1_ + 1;
                        tmpContig.push_back(v);
                        isInOutContigs[v] = true;
                    }
                }
                outContigs_.push_back(tmpContig);
            }
            typename boost::graph_traits<UnitigsGraph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end)= vertices(unitigsGraph_); vi != vi_end; ++vi)
            {
                UnitigsGraphVertex v = *vi;
                if (isInOutContigs[v] == false)
                {
                    isInOutContigs[v] = true;
                    outContigs_.push_back(Contig());
                    outContigs_.back().push_back(v);
                }
            }
            typename boost::graph_traits<UnitigsGraph>::edge_iterator ei, ei_end;
            string name = CALC_TMP_DIR + string("edgesDescPET");
            ofstream ofile;
            ofile.open (name, ofstream::out | ofstream::trunc);
            for (tie(ei, ei_end)= edges(unitigsGraph_); ei != ei_end; ++ei)
            {
                ofile << "s: "
                      + to_string(source(*ei, unitigsGraph_))
                      + " t: "
                      + to_string(target(*ei, unitigsGraph_))
                      + " " + to_string(unitigsGraph_[*ei].isForConnectedSequences_)
                      + " " + "s: " + to_string(unitigsGraph_[source(*ei, unitigsGraph_)].sequence_.size() - K1_ + 1)
                      + " t: " + to_string(unitigsGraph_[target(*ei, unitigsGraph_)].sequence_.size() - K1_ + 1)
                      + " " + to_string(unitigsGraph_[*ei].isForPairedReads_)
                      + " " + to_string(unitigsGraph_[*ei].insertSizeOffsetVector_.size())
                      << " est distance: "
                      << to_string(unitigsGraph_[*ei].estimatedDistance_)
                      << " org s: " << unitigsGraph_[source(*ei, unitigsGraph_)].isOriginal_
                      << " org t: " << unitigsGraph_[target(*ei, unitigsGraph_)].isOriginal_
                      << " c: " << unitigsGraph_[*ei].counter_ << endl;
            }
        }

        void UnitigsToContigsExtension::buildHashTable() {
            logInfo("Hash table building...");
            DnaSequenceRepresentationConverter dnaSequenceRepresentationConverter(K1_);
            size_t i = 0U;
            while (true) {
                string id = "";
                string sequence = "";
                unitigsFile_ >> id >> sequence;
                if (id == "" || sequence == "") {
                    logInfo("Hash table is built, number of elements: "
                            + to_string(hashTableMultipleValue_.size())
                            + " - (" + to_string(hashTableMultipleValue_.getHashTableSingle().size())
                            + " + " + to_string(hashTableMultipleValue_.getHashTableMultiple().size()) + ")");
                    return;
                }
                if (sequence.size() <= 2U * maxInsertSize_) {    // k1-mers from whole unitig should be added to hash table
                    const char* seqPtr = sequence.data();
                    const char* lastSeqPtr = seqPtr + sequence.size() - K1_ + 1;
                    for (;seqPtr < lastSeqPtr; ++seqPtr) {
                        hashTableMultipleValue_.insert(seqPtr, i, static_cast<unsigned short>(seqPtr-sequence.data()));
                    }
                } else {
                    const char* frontSeqPtr = sequence.data();
                    const char* lastFrontSeqPtr = sequence.data() + maxInsertSize_;
                    const char* backSeqPtr = sequence.data() + sequence.size() - K1_ - maxInsertSize_;
                    const char* lastBackSeqPtr = sequence.data() + sequence.size() - K1_ + 1;
                    for (;frontSeqPtr < lastFrontSeqPtr; ++frontSeqPtr) {
                        hashTableMultipleValue_.insert(frontSeqPtr, i, static_cast<unsigned short>(frontSeqPtr-sequence.data()));
                    }
                    for (;backSeqPtr < lastBackSeqPtr; ++backSeqPtr) {
                        hashTableMultipleValue_.insert(backSeqPtr, i, static_cast<unsigned short>(lastBackSeqPtr-backSeqPtr));
                    }
                }
                ++i;
                if (i % 1000 == 0) {
                    logInfo("processing unitigs line number: " + to_string(i));
                }
            }
        }

}}
