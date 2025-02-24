/**
 * \file Scaffolder.cpp
 * \brief the C++ file with implementation of Scaffolder class
 */

#include <sstream>
#include <iomanip>
#include <regex>

#include "../common/log.hpp"
#include "Scaffolder.hpp"

//#if defined(_MSC_VER) && (_MSC_VER >= 1800)
//#include "common.hpp"
//#endif


namespace dnaasm { namespace scfr {

    Scaffolder::Scaffolder(unsigned short int minLinks,
                           unsigned short int minReads,
                           unsigned short int minLinksPerRead,
                           float maxRatio,
                           const MatepairGraph& matepairGraph)
        : minLinks_(minLinks)
        , minReads_(minReads)
        , minLinksPerRead_(minLinksPerRead)
        , maxRatio_(maxRatio)
        , matepairGraph_(matepairGraph)
    {}

    void Scaffolder::buildScaffolds(
        ContigPairGraph &pairs,
        const ContigSeqHashMap &contigsSeqs,
        std::stringstream &scaffolds)
    {
        // sort contigs from longest to shortest,
        // then from lowest id to highest
        std::vector<unsigned int> sortedContigIds;
        sortedContigIds.reserve(contigsSeqs.size());
        for (auto &it : contigsSeqs) {
            sortedContigIds.push_back(it.first);
        }
        std::sort(sortedContigIds.begin(), sortedContigIds.end(),
            [&contigsSeqs](unsigned int a, unsigned int b) {
                auto size_a = contigsSeqs.at(a).size();
                auto size_b = contigsSeqs.at(b).size();

                if (size_a != size_b) {
                    return size_b < size_a; // longer first
                } else {
                    return a < b; // lower id first
                }
        });

        unsigned int scaffoldId = 0;
        VisitedHashMap visited;

        for (auto &contigId : sortedContigIds) {
            auto fContig = "f" + std::to_string(contigId);
            auto rContig = "r" + std::to_string(contigId);

            if (visited.find(contigId) == visited.end()) {
                ++scaffoldId;
                auto seedLength = (unsigned int) contigsSeqs.at(contigId).size();
                std::string chainLeft = "";
                std::string chainRight = fContig + "Z" + std::to_string(seedLength);
                auto scaffoldLength = seedLength;

                //logInfo("Building scaffold " + std::to_string(scaffoldId));

                std::string scaffoldIdStr = "scaffold" + std::to_string(scaffoldId);

                computeLayout(scaffoldIdStr, Right, chainRight,
                              fContig, contigId, pairs,
                              contigsSeqs, scaffoldLength, visited);
                computeLayout(scaffoldIdStr, Left, chainLeft,
                              rContig, contigId, pairs,
                              contigsSeqs, scaffoldLength, visited);

                visited.emplace(contigId, true);

                auto scaffold = chainLeft + chainRight;
                scaffolds << scaffoldIdStr << ","
                          << scaffoldLength << "," << scaffold << std::endl;
            }
        }
    }

    const ContigPathHashMap& Scaffolder::getContigPaths() const
    {
        return contigPathsForScaffolds_;
    }

    void Scaffolder::computeLayout(
        const std::string &scaffoldId,
        ExtensionType extType,
        std::string &chain,
        const std::string &origContig,
        unsigned int seedContigId,
        const ContigPairGraph &pairs,
        const ContigSeqHashMap &contigsSeqs,
        unsigned int &totalLength,
        VisitedHashMap &visited)
    {
        // start scaffold extension from origContig
        std::string currContig = origContig;
        unsigned int currContigId = seedContigId;
        bool extension = true;

        while(extension) {
            auto v_desc = pairs.vertex(currContig);
            if (v_desc == pairs.null_vertex()) {
                // currContig is not paired with any other contig
                return;
            }

            // 1. Main loop: iterate over pairs with current contig as source
            auto outEdges = out_edges(v_desc, pairs);

            if (outEdges.first != outEdges.second) {
                // sort ascending distances between contigs
                std::set<int> distances;
                for (auto it = outEdges.first; it != outEdges.second; ++it) {
                    distances.insert(pairs[*it].distance_);
                }
                // 2. Inner loop: iterate over distance categories
                for (auto dist : distances) {
                    // sort contigs by the number of links descending
                    std::vector<ContigPairGraphEdge> sortedEdges;

                    std::copy_if(outEdges.first, outEdges.second,
                                 std::back_inserter(sortedEdges),
                                 [&pairs, &dist](const auto& e) {
                        return pairs[e].distance_ == dist;
                    });
                    std::sort(sortedEdges.begin(), sortedEdges.end(),
                        [&pairs](const auto &a, const auto &b) {
                            return pairs[b].bridges_.size() < pairs[a].bridges_.size();
                    });

                    // consider only two best linked contigs

                    auto &bestEdgeDesc = sortedEdges.front();
                    auto &bestEdge = pairs[bestEdgeDesc];

                    ContigPairValidator cpv(bestEdge);
                    bool isBestEdgeValid = cpv.isValid(matepairGraph_,
                                                       minLinks_,
                                                       minReads_,
                                                       minLinksPerRead_);
                    unsigned int bestLinksNum = cpv.getNumLinks();
                    unsigned int secondBestLinksNum = 0;

                    if (sortedEdges.size() > 1) {
                        auto &sndBestEdgeDesc = sortedEdges[1];
                        secondBestLinksNum = (unsigned int) pairs[sndBestEdgeDesc].bridges_.size();
                    }

                    // compute ratio between two best matches
                    float ratio = bestLinksNum != 0
                        ? (float)secondBestLinksNum / (float)bestLinksNum
                        : (float)0.0;


                    std::string bestMatch = pairs.graph()[target(bestEdgeDesc, pairs)].contig_;
                    unsigned int newContigId = getContigIdAndOrientationFromStr(bestMatch).first;

                    // check if pair meets the requirements
                    if (visited.find(newContigId) != visited.end()
                        || !isBestEdgeValid
                        || ratio > maxRatio_
                        || newContigId == seedContigId) {
                        extension = false;
                        continue; // distance loop
                    }

                    auto newContigLength = (unsigned int) contigsSeqs.at(newContigId).size();
                    extendScaffold(extType, chain,
                                   bestMatch, newContigLength,
                                   cpv, ratio);

                    totalLength += newContigLength;

                    // save used contig pair in contig path for this scaffold
                    ContigPath& contigPath = contigPathsForScaffolds_[scaffoldId];
                    auto pos = extType == Left
                        ? contigPath.begin()
                        : contigPath.end();
                    contigPath.insert(pos, bestEdgeDesc);

                    // bestMatch becomes current contig
                    currContig = bestMatch;
                    extension = true;
                    visited.emplace(currContigId, true);
                    visited.emplace(newContigId, true);
                    currContigId = newContigId;
                    break; // distance loop
                }
            } else {
                // current contig does not pair with any other contig
                return;
            }
        }
    }

    void Scaffolder::extendScaffold(
        ExtensionType extType,
        std::string &scaffold,
        const std::string &newContig,
        unsigned int newContigLength,
        const ContigPairValidator& cpv,
        float ratio)
    {
        unsigned int newContigId = getContigIdAndOrientationFromStr(newContig).first;
        unsigned int numLinks = cpv.getNumLinks();
        unsigned int numReads = cpv.getNumReads();
        unsigned int readId = cpv.getGapReadId();
        unsigned int gapOffsetOnRead = cpv.getGapOffset();
        bool isGapReversed = cpv.getIsGapReversed();
        int meanDistance = cpv.getMeanDistance();
        std::string gapSign = isGapReversed ? "-" : "+";

        // some magic stuff to convert floats to strings with given precision
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << ratio;
        std::string ratioStr = ss.str();

        if (extType == ExtensionType::Right) {
            scaffold += "k" + std::to_string(numLinks)
                += "a" + ratioStr
                += "n" + std::to_string(numReads)
                += "i" + gapSign + std::to_string(readId)
                += "o" + std::to_string(gapOffsetOnRead)
                += "m" + std::to_string(meanDistance)
                += "_" + newContig
                += "z" + std::to_string(newContigLength);
        } else {
            // extend scaffold in LEFT direction
            // that means: PREpend current scaffold with reversed contig
            std::string revMatch = newContig.at(0) == 'f'
                ? "r" + std::to_string(newContigId)
                : "f" + std::to_string(newContigId);

            scaffold = revMatch + "z" + std::to_string(newContigLength)
                += "k" + std::to_string(numLinks)
                += "a" + ratioStr
                += "n" + std::to_string(numReads)
                += "i" + gapSign + std::to_string(readId)
                += "o" + std::to_string(gapOffsetOnRead)
                += "m" + std::to_string(meanDistance)
                += "_" + scaffold;
        }
    }

    void Scaffolder::saveScaffoldsToFasta(
        const ContigSeqHashMap &contigs,
        const ReadSeqHashMap &reads,
        std::stringstream &scaffoldsCSV,
        std::stringstream &outputFasta,
        bool gapFilling)
    {

        auto split = [](const std::string &s, char delimeter) ->
                        std::vector<std::string>
        {
            std::vector<std::string> result;
            std::stringstream ss;
            ss.str(s);
            std::string item;
            while (std::getline(ss, item, delimeter)) {
                *(std::back_inserter(result)++) = item;
            }
            return result;
        };

        std::string line;

        while (std::getline(scaffoldsCSV, line)) {
            // firstly split line on commas since input has CSV format
            std::vector<std::string> elems = split(line, ',');

            if (elems.size() != 3) {
                logWarning("Cannot create FASTA because input file is not valid CSV");
                return;
            }

            // secondly split scaffold string on '_' to get contigs with params
            std::vector<std::string> tigsWithParams = split(elems[2], '_');

            // if scaffold consists only of one contig
            if (tigsWithParams.empty()) {
                tigsWithParams.emplace_back(elems[2]);
            }

            // write scaffold string as id
            outputFasta << ">" << line << std::endl;

            // write scaffold sequence
            for (auto &tig : tigsWithParams) {
                std::regex tigRegex("([fr])(\\d+)[Zz]\\d+(\\S+)?");
                std::smatch matches;

                if (std::regex_match(tig, matches, tigRegex)) {
                    std::string orient = matches[1];
                    std::string tigNum = matches[2];
                    std::string rest = matches[3];

                    auto found = contigs.find((unsigned int) std::stoi(tigNum));

                    if (found == contigs.end()) {
                        logWarning("Not recognized contig ID in CSV: " + tigNum);
                        return;
                    }
                    std::string sequence = found->second;

                    if (orient == "r") {
                        sequence = getReverseComplementary(sequence);
                    }

                    // not last contig in scaffold
                    if (!rest.empty()) {
                        sequence += createGapSequenceFromLayout(rest, reads, gapFilling).first;
                    }

                    outputFasta << sequence;
                }
            }
            outputFasta << std::endl;
        }
    }

    std::pair<std::string, bool> Scaffolder::createGapSequenceFromLayout(
        const std::string &layout,
        const ReadSeqHashMap &reads,
        bool gapFilling)
    {
        // read gap info from layout string
        std::string gap, strReadId, strOffset;
        bool isGapReversed = false;
        std::regex gapsRegex("i(\\+|-)(\\d+)o(\\d+)m(\\-?\\d+)");
        std::smatch gapMatches;

        if (std::regex_search(layout, gapMatches, gapsRegex) && gapMatches.size() > 2) {
            isGapReversed = gapMatches[1] == "-";
            strReadId = gapMatches[2];
            strOffset = gapMatches[3];
            gap = gapMatches[4];
        } else {
            logWarning("Unexpected gap layout string in CSV: " + layout);
            return std::make_pair("", false);
        }

        long gapLength = 0;

        try {
            gapLength = std::stol(gap);
        } catch (...) {
            logWarning("Unexpected gap length string in CSV: " + gap);
            return std::make_pair("", false);
        }

        if (gapLength == 0) {
            return std::make_pair("", true);
        } else if (gapLength < 0) {
            return std::make_pair("n", true); // overlap
        } else { // concatenate gap/overlap symbol (or sequence) to contig seq
            if (gapFilling) {
                unsigned int readId;
                size_t gapOffsetOnRead;
                std::string gapSequence;
                bool fail = false;

                try {
                    readId = (unsigned int) std::stoul(strReadId);
                } catch (...) {
                    logWarning("Unexpected readId in CSV: " + strReadId);
                    fail = true;
                }
                try {
                    gapOffsetOnRead = (size_t) std::stoul(strOffset);
                } catch (...) {
                    logWarning("Unexpected gap offset in CSV: " + strOffset);
                    fail = true;
                }

                try {
                    gapSequence =
                        reads.at(readId).substr(gapOffsetOnRead, (size_t)gapLength);

                    if (isGapReversed) {
                        gapSequence = getReverseComplementary(gapSequence);
                    }

                    // transform gap seqence to lowercase;
                    // using tolower here is safe since seq has ASCII chars
                    std::transform(gapSequence.begin(), gapSequence.end(),
                                   gapSequence.begin(), ::tolower);
                } catch (const std::out_of_range& e) {
                    logWarning("Cannot find read with id " + strReadId);
                    fail = true;
                }

                if (fail) {
                    return std::make_pair(std::string((size_t)gapLength, 'N'), false);
                }

                return std::make_pair(gapSequence, true);
            } else {
                return std::make_pair(std::string((size_t)gapLength, 'N'), true);
            }
        }
    }

}} //namespace dnaasm::scfr