/**
 * \file ContigsToScaffoldsExtension.cpp
 * \brief the C++ file with implementation of template class for extension contigs using mate pairs
 *
 */

#include "ContigsToScaffoldsExtension.hpp"
#include "CalcMaxGapSize.hpp"
#include "JoinExtendedSequences.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include "DistanceEstimator.hpp"
#include "../common/HashTable.hpp"
#include "FilterGraph.hpp"
#include "LowCounterEdgesCoverUncover.hpp"
#include "GraphInOutFinder.hpp"

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

    ContigsToScaffoldsExtension::ContigsToScaffoldsExtension(unsigned short K1,
                                       float insertSizeMean,
                                       float insertSizeStdDev,
                                       unsigned short readLength,
                                       unsigned short pairedReadsThrFrom,
                                       unsigned short pairedReadsThrTo,
                                       istream& unitigsFile,
                                       istream& contigsFile,
                                       vector<bool>& isOriginalUnitig,
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
        , contigsFile_(contigsFile)
        , isOriginalUnitig_(isOriginalUnitig)
        , dnaSequenceRepresentationConverter_(MAX_KMER_LENGTH)
        , progress_(progress)
    {initMaxInsertSize(); buildHashTable(); buildContigsGraph(); markLongContigs();}


        void ContigsToScaffoldsExtension::addPairedReads(const string& read, const string& pairedRead)
        {
            if (read.size() < K1_ || pairedRead.size() < K1_ || read.size() != pairedRead.size())
                return;
            vector<ContigsGraphEdge> consideredEdges;
            const char* readPtr = read.data();
            const char* lastReadPtr = readPtr + read.size()- K1_;
            bitset<2*MAX_KMER_LENGTH> lastReadBitset = dnaSequenceRepresentationConverter_.convertToBitset(lastReadPtr);
            const char* pairedReadPtr = pairedRead.data();
            const char* lastPairedReadPtr = pairedReadPtr + pairedRead.size() - K1_;
            bitset<2*MAX_KMER_LENGTH> lastPairedReadBitset = dnaSequenceRepresentationConverter_.convertToBitset(lastPairedReadPtr);
            bool isWholeReadValid = hashTableMultipleValue_.isValid(readPtr, read.size());
            bool isWholePairedReadValid = hashTableMultipleValue_.isValid(pairedReadPtr, pairedRead.size());
            vector<pair<ContigsGraphVertex, unsigned short>> lastReadPtrVertices = findContigsGraphVertices(lastReadPtr, lastReadBitset, isWholeReadValid);
            vector<pair<ContigsGraphVertex, unsigned short>> lastPairedReadPtrVertices = findContigsGraphVertices(lastPairedReadPtr, lastPairedReadBitset, isWholePairedReadValid);
            vector<pair<ContigsGraphVertex, unsigned short>> prevFromVertices;
            vector<pair<ContigsGraphVertex, unsigned short>> prevToVertices;
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
                vector<pair<ContigsGraphVertex, unsigned short>> fromVertices = findContigsGraphVertices(readPtr, readBitset, isWholeReadValid);
                readBitset = readBitset >> 2;
                readBitsetOffset += 1U;
                if (fromVertices == prevFromVertices || fromVertices.size() != 1 || contigsGraph_[fromVertices[0].first].isLongNode_ == false) {
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
                    vector<pair<ContigsGraphVertex, unsigned short>> toVertices = findContigsGraphVertices(pairedReadPtr, pairedReadBitset, isWholeReadValid);
                    pairedReadBitset = pairedReadBitset >> 2;
                    pairedReadBitsetOffset += 1U;
                    if (toVertices == prevToVertices || toVertices.size() != 1 || contigsGraph_[toVertices[0].first].isLongNode_ == false) {
                        continue;
                    }

                    prevToVertices = toVertices;
                    for (typename vector<pair<ContigsGraphVertex, unsigned short>>::iterator fromIt = fromVertices.begin(); fromIt != fromVertices.end(); ++fromIt)
                    {
                        if (contigsGraph_[fromIt->first].isLongNode_ == true) {
                            for (typename vector<pair<ContigsGraphVertex, unsigned short>>::iterator toIt = toVertices.begin(); toIt != toVertices.end(); ++toIt)
                            {
                                if (fromIt->first == toIt->first)   //without self-loops
                                {
                                    continue;
                                }
                                else
                                {
                                    pair<ContigsGraphEdge,bool> contigsGraphEdge = edge(fromIt->first, toIt->first, contigsGraph_);
                                    if (contigsGraphEdge.second && contigsGraph_[contigsGraphEdge.first].estimatedDistance_ == 1U)   // edge was considered
                                    {
                                        continue;
                                    }
                                    if (contigsGraphEdge.second && contigsGraph_[contigsGraphEdge.first].insertSizeOffsetVector_.size() > 10)
                                        continue;
                                    unsigned short fromOffset = fromIt->second;
                                    if (contigsGraph_[fromIt->first].sequenceSize_ + K1_ - 1 <= 2U * maxInsertSize_)
                                        fromOffset = contigsGraph_[fromIt->first].sequenceSize_  + K1_ - 1 - fromIt->second;
                                    unsigned short totalOffset
                                        = fromOffset+toIt->second
                                        + static_cast<unsigned short>(readPtr-read.data()
                                                                      + readLength_
                                                                      - pairedRead.size()
                                                                      + lastPairedReadPtr
                                                                      - pairedReadPtr+K1_);
                                    if (!contigsGraphEdge.second)   // if edge does not exist
                                    {
                                        contigsGraphEdge = add_edge(fromIt->first, toIt->first, contigsGraph_);
                                    }
                                    contigsGraph_[contigsGraphEdge.first].isForPairedReads_ = true;
                                    contigsGraph_[contigsGraphEdge.first].insertSizeOffsetVector_.push_back(totalOffset);
                                    consideredEdges.push_back(contigsGraphEdge.first);
                                    contigsGraph_[contigsGraphEdge.first].estimatedDistance_ = 1U;
                                    ++contigsGraph_[contigsGraphEdge.first].counter_;
                                }

                            }
                        }
                    }
                    if (toVertices == lastPairedReadPtrVertices) {
                        break;
                    }
                }
                if (fromVertices == lastReadPtrVertices && fromVertices.size() == 1 &&
                    contigsGraph_[fromVertices[0].first].isLongNode_)
                {
                    break;
                }
            }
            for(auto it = consideredEdges.begin(); it != consideredEdges.end(); ++it) {
                contigsGraph_[*it].estimatedDistance_ = 0U;
            }
        }

        void ContigsToScaffoldsExtension::estimateDistancesBetweenContigs()
        {
            DistanceEstimator distanceEstimator(insertSizeMean_, insertSizeStdDev_, maxInsertSize_);
            typename boost::graph_traits<ContigsGraph>::edge_iterator ei, ei_end;
            std::size_t i = 1;
            for (boost::tie(ei, ei_end)= edges(contigsGraph_); ei != ei_end; ++ei, ++i)
            {
                if (i % 10000 == 0)
                {
                    logInfo("processing edge number: " + to_string(i));
                }
                contigsGraph_[*ei].estimatedDistance_ = distanceEstimator.estimateDistanceBetweenSequences(contigsGraph_[*ei].insertSizeOffsetVector_);
                vector<unsigned short>().swap(contigsGraph_[*ei].insertSizeOffsetVector_);   // free memory allocated by vector
            }
        }

        /**
         * \brief Extends contigs using paired-end tags.
         *
         * \return returns set of extended contigs
         */
        ContigsToScaffoldsExtension::Contigs& ContigsToScaffoldsExtension::extendContigs()
        {
            logInfo("Distances between unitigs estimation...");
            estimateDistancesBetweenContigs();

            extend();

            JoinExtendedSequences<ContigsGraph> joinExtendedSequences(contigsGraph_, extendedSequences_);
            joinExtendedSequences();

            generateOutContigs();
            return outContigs_;
        }

        void ContigsToScaffoldsExtension::extend()
        {
            LowCounterEdgesCoverUncover<ContigsGraph> lowCounterEdgesCoverUncover(contigsGraph_);
            logInfo("Extending contigs to scaffolds using mate pairs...");
            for (unsigned short pairedReadsThr = pairedReadsThrFrom_; pairedReadsThr <= pairedReadsThrTo_; ++pairedReadsThr) {
                lowCounterEdgesCoverUncover.cover(pairedReadsThr);
                extendLongUnitigsToScaffolds();
            }
            lowCounterEdgesCoverUncover.uncover();
        }

        void ContigsToScaffoldsExtension::extendLongUnitigsToScaffolds()
        {
            unsigned int longStartUnitigBadStructure = 0U;
            unsigned int longStartUnitigGoodStructure = 0U;
            unsigned int progress = 0U;
            FilterGraph<ContigsGraph> filterGraph(contigsGraph_);
            typename boost::graph_traits<ContigsGraph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end)= vertices(contigsGraph_); vi != vi_end; ++vi)
            {
                ++progress;
                if (progress % 1000000 == 0)
                {
                    logInfo("Processing vertex number: " + to_string(progress));
                    if (progress_ != NULL)
                        progress_->setProgress(0.875+static_cast<float>(progress)/static_cast<float>(num_vertices(contigsGraph_))/8.0);
                }

                if (contigsGraph_[*vi].isLongNode_ && !contigsGraph_[*vi].isExtended_)
                {
                    ContigsGraphVertex sourceVertex = *vi;
                    vector<bool> isConnected(num_vertices(contigsGraph_), false);

                    isConnected[sourceVertex] = true;
                    typename boost::graph_traits<ContigsGraph>::out_edge_iterator ei, ei_end;
                    for (boost::tie(ei, ei_end) = out_edges(sourceVertex, contigsGraph_); ei != ei_end; ++ei) {
                        if (contigsGraph_[*ei].isForPairedReads_) {
                            isConnected[target(*ei, contigsGraph_)] = true;
                        }
                    }

                    ContigsGraph copyContigsGraph;
                    vector<ContigsToScaffoldsExtension::ContigsGraphVertex> connectedVerticesId = filterGraph(copyContigsGraph, isConnected);

                    GraphInOutFinder<ContigsGraph> graphInOutFinder(copyContigsGraph);

                    unsigned short numOfLongNodes = 0U;
                    typename boost::graph_traits<ContigsGraph>::vertex_iterator vi_copy, vi_end_copy;
                    for (boost::tie(vi_copy, vi_end_copy)= vertices(copyContigsGraph); vi_copy != vi_end_copy; ++vi_copy)
                    {
                        if (copyContigsGraph[*vi_copy].isLongNode_) {
                            ++numOfLongNodes;
                        }
                    }
                    if (numOfLongNodes == 2U) {
                        contigsGraph_[*vi].isExtended_ = true;
                        unsigned short distance = 0U;
                        extendedSequences_.push_back(vector<ContigsGraphVertex>());
                        extendedSequences_.back().push_back(*vi); // actual vertex
                        for (boost::tie(vi_copy, vi_end_copy)= vertices(copyContigsGraph); vi_copy != vi_end_copy; ++vi_copy) {
                            if (connectedVerticesId[*vi_copy] == *vi) {
                                //source = *vi_copy;
                            }
                        }
                        for (boost::tie(vi_copy, vi_end_copy)= vertices(copyContigsGraph); vi_copy != vi_end_copy; ++vi_copy) {
                            if (connectedVerticesId[*vi_copy] != *vi && copyContigsGraph[*vi_copy].isLongNode_) {
                                distance = contigsGraph_[edge(*vi, connectedVerticesId[*vi_copy], contigsGraph_).first].estimatedDistance_;
                                extendedSequences_.back().push_back(std::numeric_limits<std::size_t>::max());
                                extendedSequences_.back().push_back(distance);
                                extendedSequences_.back().push_back(connectedVerticesId[*vi_copy]);
                                break;
                            }
                        }
                        if (distance == 0U || distance > 2*maxInsertSize_) {
                            extendedSequences_.pop_back();
                            contigsGraph_[*vi].isExtended_ = false;
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
         * \brief Gets the reference to ContigsGraph object.
         *
         * \return returns reference to ContigsGraph object
         */
        ContigsToScaffoldsExtension::ContigsGraph& ContigsToScaffoldsExtension::getContigsGraph()
        {
            return contigsGraph_;
        }

        std::vector< std::vector<ContigsToScaffoldsExtension::ContigsGraphVertex> >& ContigsToScaffoldsExtension::getExtendedSequences() {
            return extendedSequences_;
        }

        void ContigsToScaffoldsExtension::buildContigsGraph()
        {
            logInfo("Building contigs graph...");
            contigsFile_.clear();
            contigsFile_.seekg(ios::beg);
            vector<string> unitigs;
            HashTableMultipleValue hashTableMultipleValue(K1_);
            size_t i = 0U;
            while (true) {
                string id = "";
                string sequence = "";
                contigsFile_ >> id >> sequence;
                if (id == "" || sequence == "") {
                    break;
                }
                unitigs.push_back(sequence);
                ContigsGraphVertex v = add_vertex(contigsGraph_);
                contigsGraph_[v].sequenceSize_ = sequence.size() - K1_ + 1;
                hashTableMultipleValue.insert(sequence.data(), i, 0U);
                hashTableMultipleValue.insert(sequence.data() + sequence.size() - K1_, i, 0U);
                ++i;
                if (i % 1000000 == 0) {
                    logInfo("processing unitigs number: " + to_string(i));
                }
            }
            for (auto& unitig : unitigs) {
                ContigsGraphVertex consideredVertexId = &unitig- &unitigs[0];
                vector<pair<ContigsGraphVertex, unsigned short>> suspectedVertices = hashTableMultipleValue.find(unitig.data());
                for (auto& suspectedVertex : suspectedVertices) {
                    if (suspectedVertex.first == consideredVertexId) {
                        continue;
                    }
                    if (unitigs[suspectedVertex.first].substr(unitigs[suspectedVertex.first].size() - K1_, K1_) == unitigs[consideredVertexId].substr(0, K1_)) {
                        ContigsGraphEdge edge = add_edge(suspectedVertex.first, consideredVertexId, contigsGraph_).first;
                        contigsGraph_[edge].isForConnectedSequences_ = true;
                    }
                }
            }
        }

        vector<pair<ContigsToScaffoldsExtension::ContigsGraphVertex, unsigned short>> ContigsToScaffoldsExtension::findContigsGraphVertices(const char* k1Mer, bitset<2*MAX_KMER_LENGTH>& bitsetK1Mer, bool isWholeReadValid)
        {
            vector<pair<ContigsGraphVertex, unsigned short>> vertices;
            if (isWholeReadValid || hashTableMultipleValue_.isValid(k1Mer, K1_))
            {
                vector<pair<ContigsGraphVertex, unsigned short>> suspectedVerticesVector = hashTableMultipleValue_.find(bitsetK1Mer);
                for (auto it = suspectedVerticesVector.begin(); it != suspectedVerticesVector.end(); ++it) {
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
        void ContigsToScaffoldsExtension::markLongContigs()
        {
            typename boost::graph_traits<ContigsGraph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end)= vertices(contigsGraph_); vi != vi_end; ++vi)
            {
                if (static_cast<float>(contigsGraph_[*vi].sequenceSize_) > insertSizeMean_ - readLength_)
                {
                    contigsGraph_[*vi].isLongNode_ = true;
                }
            }
        }

        void ContigsToScaffoldsExtension::initMaxInsertSize()
        {
            CalcMaxGapSize calcMaxGapSize(insertSizeMean_, insertSizeStdDev_);
            maxInsertSize_ = calcMaxGapSize.calcMaxGapSize();
        }

        /**
         * \brief Generates set of extended contigs (using information, which contigs should be merged).
         *
         * \return returns void
         */
        void ContigsToScaffoldsExtension::generateOutContigs()
        {
            vector<bool> isContainedInAnother(extendedSequences_.size(), false);
            vector<bool> isInOutContigs(num_vertices(contigsGraph_), false);
            for (typename vector< vector<ContigsGraphVertex> >:: iterator it = extendedSequences_.begin(); it != extendedSequences_.end(); ++it)
            {
                if (isContainedInAnother[it - extendedSequences_.begin()])
                    continue;
                for (typename vector< vector<ContigsGraphVertex> >:: iterator it2 = extendedSequences_.begin(); it2 != extendedSequences_.end(); ++it2)
                {
                    if (it == it2)
                        continue;
                    if (contains(*it, *it2))
                        isContainedInAnother[it2 - extendedSequences_.begin()] = true;
                }
            }

            for (typename vector< vector<ContigsGraphVertex> >:: iterator it = extendedSequences_.begin(); it != extendedSequences_.end(); ++it)
            {
                if (isContainedInAnother[it - extendedSequences_.begin()])
                    continue;
                Contig tmpContig;
                cout << "Glue ";
                for (typename vector<ContigsGraphVertex>:: iterator it2 = it->begin(); it2 != it->end(); ++it2)
                {
                    if (*it2 == std::numeric_limits<std::size_t>::max()) {
                        tmpContig.push_back(std::numeric_limits<std::size_t>::max());
                        ++it2;
                        tmpContig.push_back(*it2);
                    } else {
                        ContigsGraphVertex v = *it2;
                        tmpContig.push_back(v);
                        isInOutContigs[v] = true;
                        cout << v << " " << contigsGraph_[v].sequenceSize_ << " and ";
                    }
                }
                cout << endl;
                outContigs_.push_back(tmpContig);
            }
            typename boost::graph_traits<ContigsGraph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end)= vertices(contigsGraph_); vi != vi_end; ++vi)
            {
                ContigsGraphVertex v = *vi;
                if (isInOutContigs[v] == false)
                {
                    isInOutContigs[v] = true;
                    outContigs_.push_back(Contig());
                    outContigs_.back().push_back(v);
                }
            }
            typename boost::graph_traits<ContigsGraph>::edge_iterator ei, ei_end;
            string name = CALC_TMP_DIR + string("edgesDescMP");
            ofstream ofile;
            ofile.open (name, ofstream::out | ofstream::trunc);
            for (tie(ei, ei_end)= edges(contigsGraph_); ei != ei_end; ++ei)
            {
                ofile << "s: "
                      + to_string(source(*ei, contigsGraph_))
                      + " t: "
                      + to_string(target(*ei, contigsGraph_))
                      + " " + to_string(contigsGraph_[*ei].isForConnectedSequences_)
                      + " " + "s: " + to_string(contigsGraph_[source(*ei, contigsGraph_)].sequenceSize_)
                      + " t: " + to_string(contigsGraph_[target(*ei, contigsGraph_)].sequenceSize_)
                      + " " + to_string(contigsGraph_[*ei].isForPairedReads_)
                      + " " + to_string(contigsGraph_[*ei].insertSizeOffsetVector_.size())
                      << " est distance: "
                      << to_string(contigsGraph_[*ei].estimatedDistance_)
                      << " long s: " << contigsGraph_[source(*ei, contigsGraph_)].isLongNode_
                      << " long t: " << contigsGraph_[target(*ei, contigsGraph_)].isLongNode_
                      << " c: " << contigsGraph_[*ei].counter_ << endl;
            }
        }

        void ContigsToScaffoldsExtension::buildHashTable() {
            logInfo("Hash table building...");
            HashTable originalElements(K1_);
            size_t i = 0U;
            while (true) {
                string id = "";
                string sequence = "";
                unitigsFile_ >> id >> sequence;
                if (id == "" || sequence == "") {
                    logInfo("Number of original k-mers in contigs: "
                            + to_string(originalElements.size()));
                    break;
                }
                if (isOriginalUnitig_[i] && sequence.size() > 100) {
                    const char* seqPtr = sequence.data() + 1;  // +1 (without first vertex of contig)
                    const char* lastSeqPtr = sequence.data() + sequence.size() - K1_ + 1 - 1;    // -1 (without last vertex of contig)
                    for (;seqPtr < lastSeqPtr; ++seqPtr) {
                        originalElements.insert(seqPtr, i);
                    }
                }
                ++i;
                if (i % 1000 == 0) {
                    logInfo("processing unitigs number: " + to_string(i));
                }
            }
            i = 0U;
            while (true) {
                string id = "";
                string sequence = "";
                contigsFile_ >> id >> sequence;
                if (id == "" || sequence == "") {
                    logInfo("Hash table is built, number of elements: "
                            + to_string(hashTableMultipleValue_.size())
                            + " - (" + to_string(hashTableMultipleValue_.getHashTableSingle().size())
                            + " + " + to_string(hashTableMultipleValue_.getHashTableMultiple().size()) + ")");
                    break;
                }
                if (sequence.size() <= 2U * maxInsertSize_) {    // k1-mers from whole contig should be added to hash table
                    const char* seqPtr = sequence.data();
                    const char* lastSeqPtr = seqPtr + sequence.size() - K1_ + 1;
                    for (;seqPtr < lastSeqPtr; ++seqPtr) {
                        HashTable::iterator vertexIt = originalElements.find(seqPtr);
                        if (vertexIt != originalElements.end()) {
                            hashTableMultipleValue_.insert(seqPtr, i, static_cast<unsigned short>(seqPtr-sequence.data()));
                        }
                    }
                } else {
                    const char* frontSeqPtr = sequence.data();
                    const char* lastFrontSeqPtr = sequence.data() + maxInsertSize_;
                    const char* backSeqPtr = sequence.data() + sequence.size() - K1_ - maxInsertSize_;
                    const char* lastBackSeqPtr = sequence.data() + sequence.size() - K1_ + 1;
                    for (;frontSeqPtr < lastFrontSeqPtr; ++frontSeqPtr) {
                        HashTable::iterator vertexIt = originalElements.find(frontSeqPtr);
                        if (vertexIt != originalElements.end()) {
                            hashTableMultipleValue_.insert(frontSeqPtr, i, static_cast<unsigned short>(frontSeqPtr-sequence.data()));
                        }
                    }
                    for (;backSeqPtr < lastBackSeqPtr; ++backSeqPtr) {
                        HashTable::iterator vertexIt = originalElements.find(backSeqPtr);
                        if (vertexIt != originalElements.end()) {
                            hashTableMultipleValue_.insert(backSeqPtr, i, static_cast<unsigned short>(lastBackSeqPtr-backSeqPtr));
                        }
                    }
                }
                ++i;
                if (i % 1000 == 0) {
                    logInfo("processing contigs number: " + to_string(i));
                }
            }
        }

}}
