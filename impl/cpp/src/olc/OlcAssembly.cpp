/**
 * \file OlcAssembly.cpp
 * \brief the C++ file with interface for olc module
 */

#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

#include "../common/log.hpp"
#include "../common/FileReader.hpp"
#include "../common/InputFile.hpp"
#include "OlcAssembly.hpp"

#include "OvlpGraphBuilder.hpp"
#include "LayoutFormer.hpp"
#include "NWConsensusMaker.hpp"
#include "mhap/SequenceSketchStreamer.hpp"
#include "mhap/FrequencyCounts.hpp"
#include "mhap/MinHashSearch.hpp"

using namespace dnaasm::olc;
using namespace dnaasm::olc::mhap;

namespace dnaasm {
    namespace olc {

        std::string olcAssembly(std::istream &longReadsFile,
                                unsigned short int kMerLength,
                                unsigned short int sketchNum,
                                float minJaccardSim,
                                short int matchScore,
                                short int mismatchScore,
                                short int gapPenalty,
                                unsigned short int minEdge,
                                unsigned short int minContigLength,
                                unsigned short int pathWidth,
                                mt4cpp::Progress *progress) {
            logInfo("Beginning OLC assembly process");
            logInfo("Setting up file data structures");

            int32_t MinOlapLength = 116;
            int32_t KmerSize = 16;
            int32_t NumHashes = 512;
            int32_t OrderedKmerSize = 12;
            int32_t OrderedSketchSize = 1536;
            FreqCountPtr kmerFilter(nullptr);
            int32_t NumMinMatches = 3;
            int32_t NumThreads = std::thread::hardware_concurrency();
            int32_t MinStoreLength = 0;
            double MaxShift = 0.2;
            double AcceptScore = 0.78;

            SequenceSketchStreamer seqStreamer(longReadsFile,
                                               MinOlapLength,
                                               KmerSize,
                                               NumHashes,
                                               OrderedKmerSize,
                                               OrderedSketchSize,
                                               kmerFilter,
                                               true,
                                               0.9,
                                               0);
            MinHashSearch hashSearch(seqStreamer,
                                     NumHashes,
                                     NumMinMatches,
                                     NumThreads,
                                     false,
                                     MinStoreLength,
                                     MaxShift,
                                     AcceptScore,
                                     true);

            auto results = hashSearch.findMatches();
            std::string res;

            for (const auto& result : results) {
                std::cout << result.toString() << '\n';
                res += result.toString() + '\n';
            }
//            FileReader fileReader;
//            InputFile inputFile(longReadsFile);
//            fileReader.setInputFile1(&inputFile);
//            HashObj hashObj;

//            std::unique_ptr<Aligner<LocalAlignment>>
//                    aligner = std::make_unique<SmithWatermanAligner>(matchScore, mismatchScore,
//                                                                     gapPenalty);
//            ReadVector readVector(fileReader.getNumOfReads());
//            Read readWrapper(0U);
//
//            for (auto &read : readVector) {
//                inputFile.readSingleRead(readWrapper);
//                read = std::move(readWrapper.getRead());
//            }
//
//            OvlpGraphBuilder ovlpGraphBuilder(hashObj, readVector, aligner);
//
//            logInfo("O phase - building overlap graph");
//            if (progress != nullptr) { progress->setProgress(0.33); }
//
//            auto ovlpGraph = ovlpGraphBuilder.buildGraph(kMerLength, sketchNum, minJaccardSim,
//                                                         minEdge, progress);
//
//            logInfo("L phase - Forming layouts");
//            if (progress != nullptr) { progress->setProgress(0.66); }
//
//            LayoutFormer layoutFormer(ovlpGraph);
//            layoutFormer.removeCycles();
//            layoutFormer.removeTransInfEdges();
//            auto layoutVector = layoutFormer.findLayoutsInOvlpGraph();
//
//            //overlap graph is not needed anymore
//            ovlpGraph.clear();
//
//
//            logInfo("C phase - Creating consensuses (contigs)");
//            if (progress != nullptr) { progress->setProgress(0.80); }
//            NWConsensusMaker nwConsensusMaker(pathWidth);
//            auto result = nwConsensusMaker(layoutVector, readVector);
//            std::stringstream resultStream;
//            nwConsensusMaker.convertContigsToFasta(result, resultStream);
//
//            if (progress != nullptr) { progress->setProgress(1.0); }

//            return resultStream.str();
            return res;
        }

    }
} //namespace dnaasm::olc
