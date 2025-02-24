/**
 * \file ContigPairGraph.cpp
 * \brief the C++ file with definition of Contig Pair Graph
 */

#include "ContigPairGraph.hpp"
#include "../common/log.hpp"

namespace dnaasm { namespace scfr {

    ContigPairGraphVertexProperties::ContigPairGraphVertexProperties(std::string contig)
        : contig_(contig)
    {}

    GapInfo::GapInfo(dnaasm::scfr::MatepairGraphEdge mpEdge,
                     uint32_t offset,
                     int32_t length)
        : mpEdge_(mpEdge), offset_(offset), length_(length), reversed_(false)
    {}

    ContigPairGraphEdgeProperties::ContigPairGraphEdgeProperties()
        : distance_(0)
    {}

    ContigPairGraphEdgeProperties::ContigPairGraphEdgeProperties(int16_t distance)
        : distance_(distance)
    {}

    int32_t ContigPairGraphEdgeProperties::gapSum() const {
        int32_t gapSum = 0;

        for (const auto &b: bridges_) {
            gapSum += b.length_;
        }

        return gapSum;
    }

    std::vector<ContigPairGraphEdge> getAllParallelEdges(
        ContigPairGraphVertex v1,
        ContigPairGraphVertex v2,
        const ContigPairGraph& g)
    {
        boost::graph_traits<ContigPairGraph>::out_edge_iterator ei, ei_end;
        boost::tie(ei, ei_end) = boost::out_edges(v1, g);
        std::vector<ContigPairGraphEdge> parallelEdges;

        std::copy_if(ei, ei_end, std::back_inserter(parallelEdges), [&v2, &g](auto e) {
            return boost::target(e, g) == v2;
        });

        return parallelEdges;
    }

    LinksPerReadVec createLinksPerReadVec(
        const ContigPairGraphEdgeProperties &pair,
        const MatepairGraph& matepairs)
    {
        LinksPerReadVec lprVec;
        lprVec.reserve(pair.bridges_.size());

        std::unordered_map<uint32_t, size_t> lprMap;

        for (auto b : pair.bridges_) {
            auto readId = matepairs.graph()[b.mpEdge_].readId_;

            if (!lprMap.count(readId)) {
                lprMap[readId] = 1;
            } else {
                lprMap[readId] += 1;
            }
        }

        lprVec.insert(lprVec.begin(), lprMap.begin(), lprMap.end());

        // sort descending by the counter value
        std::sort(lprVec.begin(), lprVec.end(),
                  [](const auto &a, const auto &b) { return a.second > b.second; }
        );

        return lprVec;
    }

}} //namespace dnaasm::scfr