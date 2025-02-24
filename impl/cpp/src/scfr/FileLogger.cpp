/**
 * \file FileLogger.hpp
 * \brief the C++ file with implementation of file logger methods
 */

#include "FileLogger.hpp"
#include "../common/log.hpp"
#include "ContigPairGraph.hpp"

#include <fstream>
#include <iomanip>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace dnaasm { namespace scfr {

    void FileLogger::logContigPairs(
        const std::string &filePath,
        const ContigPairGraph& contigGraph,
        const MatepairGraph& matepairGraph)
    {
        ofstream logFile(filePath);

        auto edges = boost::edges(contigGraph);
        for (auto e = edges.first; e != edges.second; ++e) {
            auto pair = contigGraph[*e];

            // create links per read counters
            LinksPerReadVec lprVec =
                createLinksPerReadVec(pair, matepairGraph);

            auto eReadsNum = lprVec.size();

            logFile
                << contigGraph.graph()[source(*e, contigGraph)].contig_
                << " " << contigGraph.graph()[target(*e, contigGraph)].contig_
                << " " << std::to_string(pair.distance_)
                << " " << std::to_string(pair.bridges_.size())
                << " " << std::to_string(eReadsNum);


            logFile << " (";

            for (auto it = lprVec.begin(); it != lprVec.end(); ++it) {
                logFile << it->first << ": " << it->second;

                if (std::next(it) != lprVec.end()) {
                    logFile << ", ";
                }
            }

            logFile << ")" << std::endl;
        }
        logFile.close();
    }

    void FileLogger::logImportantRegionsOnReads(
        const std::string &filePath,
        const dnaasm::scfr::MatepairGraph &matepairGraph,
        const dnaasm::scfr::MatepairGraphBuilder& matepairGraphBuilder)
    {
        ofstream logFile(filePath);

        auto edges = boost::edges(matepairGraph.graph());
        std::unordered_map<unsigned int, unsigned int> readsCountersMap;

        for (auto e = edges.first; e != edges.second; ++e) {
            readsCountersMap[matepairGraph.graph()[*e].readId_] += 1;

        }
        logFile << "Number of reads with at least 1 important region: "
                << std::to_string(readsCountersMap.size()) << std::endl;

        MatepairGraphBuilder::ReadRegionsMap importantRegions =
                matepairGraphBuilder.getReadRegionsMap();

        logFile << "Size of importantRegionsMap: "
                << std::to_string(importantRegions.size()) << std::endl;

        for (const auto& readRegionsPair : importantRegions) {
            std::string regionStr;
            size_t importantRegionsSize = 0;

            for (auto it = readRegionsPair.second.begin(); it != readRegionsPair.second.end(); ++it) {
                regionStr += std::to_string(it->first)
                    + ":" + std::to_string(it->second);
                importantRegionsSize += it->second - it->first;

                if (std::next(it) != readRegionsPair.second.end()) {
                    regionStr += ", ";
                }
            }

            auto readSize = matepairGraphBuilder.getReadSeqHashMap().at(readRegionsPair.first).size();
            float importantPercent = (float)importantRegionsSize / (float)readSize;
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << importantPercent;
            std::string percentStr = ss.str();

            logFile << "id: " << std::to_string(readRegionsPair.first)
                    << ", size: " << std::to_string(readSize)
                    << ", (" << regionStr + ") " <<  percentStr << std::endl;
        }

        logFile.close();
    }

    void FileLogger::logGapSequences(
        const std::string &dirPath,
        const ContigPathHashMap &contigPaths,
        const dnaasm::scfr::ContigPairGraph &contigGraph,
        const MatepairGraph &matepairGraph,
        const dnaasm::scfr::ReadSeqHashMap &reads)
    {
        fs::path dir(dirPath);
        if (!contigPaths.empty() && !fs::exists(dir) && !fs::create_directory(dir)) {
            logWarning("Could not create directory: " + dirPath);
        }

        for (const auto& scaffoldPathPair: contigPaths) {
            for (const auto& edgeDesc: scaffoldPathPair.second) {
                const auto &edge = contigGraph.graph()[edgeDesc];

                // edge represents an overlap between contigs,
                // so there is no gap sequence here
                if (edge.distance_ == -1) {
                    continue;
                }

                // get ids of two contigs
                auto source = boost::source(edgeDesc, contigGraph);
                std::string sourceContigStr = contigGraph.graph()[source].contig_;
                auto target = boost::target(edgeDesc, contigGraph);
                std::string targetContigStr = contigGraph.graph()[target].contig_;

                // create log file
                std::string logFileName = scaffoldPathPair.first +
                    + "_" + sourceContigStr + "_" + targetContigStr + ".fa";
                fs::path logPath(logFileName);
                fs::path fullLogPath = dir / logPath;
                ofstream logFile(fullLogPath.string());

                // filter bridges with unique readIds and offsets
                using ReadsOffsetsMap =
                    std::unordered_map<
                        uint32_t,
                        std::vector<std::pair<uint32_t, int32_t>>>;

                // this is a help structure for counting
                // identical (readId, offset, length) tuples
                ReadsOffsetsMap offsetsMap;
                for (const auto &b: edge.bridges_) {
                    auto readId = matepairGraph.graph()[b.mpEdge_].readId_;
                    auto pair = std::make_pair(b.offset_, b.length_);
                    offsetsMap[readId].push_back(pair);
                }

                std::vector<GapInfo> uniqueBridges;
                std::unique_copy(
                    edge.bridges_.begin(),
                    edge.bridges_.end(),
                    std::back_inserter(uniqueBridges),
                    [&matepairGraph](const GapInfo &g1, const GapInfo &g2) {
                        auto g1ReadId = matepairGraph.graph()[g1.mpEdge_].readId_;
                        auto g2ReadId = matepairGraph.graph()[g2.mpEdge_].readId_;
                        return g1ReadId == g2ReadId &&
                               g1.offset_ == g2.offset_ &&
                               g1.length_ == g2.length_;
                });

                // write gap sequences to file
                for (const auto &b : uniqueBridges) {
                    const auto &mpEdgeProps = matepairGraph.graph()[b.mpEdge_];
                    auto counter = std::count(
                        offsetsMap[mpEdgeProps.readId_].begin(),
                        offsetsMap[mpEdgeProps.readId_].end(),
                        std::make_pair(b.offset_, b.length_)
                    );
                    std::string gapSequence =
                        reads.at(mpEdgeProps.readId_).substr(b.offset_, b.length_);

                    if (b.reversed_) {
                        gapSequence = getReverseComplementary(gapSequence);
                    }

                    logFile << ">" << scaffoldPathPair.first << "_gap_"
                        << sourceContigStr << "_" << targetContigStr
                        << ", read id: " << std::to_string(mpEdgeProps.readId_)
                        << ", offset: " << std::to_string(b.offset_)
                        << ", length: " << std::to_string(b.length_)
                        << ", repeated: " << std::to_string(counter)
                        << std::endl << gapSequence << std::endl;
                }

                logFile.close();
            }
        }
    }

    void FileLogger::logGapLengthHistogram(
        const std::string &dirPath,
        const dnaasm::scfr::ContigPathHashMap &contigPaths,
        const ContigPairGraph &contigGraph)
    {
        fs::path dir(dirPath);
        if (!contigPaths.empty() && !fs::exists(dir) && !fs::create_directory(dir)) {
            logWarning("Could not create directory: " + dirPath);
        }

        // for each scaffold
        for (const auto& scaffoldPathPair: contigPaths) {
            // for each gap
            for (const auto& edgeDesc: scaffoldPathPair.second) {
                const auto &edge = contigGraph.graph()[edgeDesc];

//                if (edge.distance_ == -1) {
//                    continue;
//                }

                // get ids of two contigs
                auto source = boost::source(edgeDesc, contigGraph);
                std::string sourceContigStr = contigGraph.graph()[source].contig_;
                auto target = boost::target(edgeDesc, contigGraph);
                std::string targetContigStr = contigGraph.graph()[target].contig_;

                // create log file
                std::string logFileName = scaffoldPathPair.first +
                                          + "_" + sourceContigStr
                                          + "_" + targetContigStr
                                          + "_histogram.txt";
                fs::path logPath(logFileName);
                fs::path fullLogPath = dir / logPath;
                ofstream logFile(fullLogPath.string());


                // create gap length histogram
                using GapLengthHistogram =
                    std::map<int32_t, uint32_t>;

                GapLengthHistogram histogram;
                int32_t lengthSum = 0;

                for (const auto &b: edge.bridges_) {
                    if (histogram.find(b.length_) == histogram.end()) {
                        histogram[b.length_] = 1;
                    } else {
                        histogram[b.length_] += 1;
                    }

                    lengthSum += b.length_;
                }

                // add mean distance as well
                int32_t meanLength =
                    std::floor((float)lengthSum / (float)edge.bridges_.size());

                if (histogram.find(meanLength) == histogram.end()) {
                    histogram[meanLength] = 0;
                }

                // write histogram to file
                for (const auto &lengthCount : histogram) {
                    auto infix = (lengthCount.first == meanLength)
                        ? " (mean): "
                        : ": ";

                    logFile << std::to_string(lengthCount.first)
                            << infix << std::to_string(lengthCount.second)
                            << std::endl;
                }

                logFile.close();
            }
        }
    }

}} //namespace dnaasm::scfr