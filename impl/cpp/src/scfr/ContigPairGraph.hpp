/**
 * \file ContigPairGraph.hpp
 * \brief the C++ file with declaration of Contig Pair Graph
 */

#ifndef CONTIGPAIRGRAPH_HPP
#define CONTIGPAIRGRAPH_HPP

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/labeled_graph.hpp>

#include "../common/common.hpp"
#include "common.hpp"
#include "MatepairGraph.hpp"

#include <cstdint>

namespace dnaasm { namespace scfr {

    using MatepairGraphEdge = Edge;

    /**
     * Struct representing properties of ContigPairGraph vertex.
     */
    struct ContigPairGraphVertexProperties {
        CALC_DLL(ContigPairGraphVertexProperties(std::string contig = "");)

        std::string contig_; /**< contig identifier prepended with
                              *   its orientation, eg. f3, r12 */
    };

    struct GapInfo {
        CALC_DLL(GapInfo(MatepairGraphEdge mpEdge,
                uint32_t offset,
                int32_t length);)

        MatepairGraphEdge mpEdge_; //readId, pair offset
        uint32_t offset_; // offset of gap on read
        int32_t length_; // gap length
        bool reversed_;
    };


    /**
     * Struct representing properties of ContigPairGraph edge.
     */
    struct ContigPairGraphEdgeProperties {
        CALC_DLL(ContigPairGraphEdgeProperties(int16_t distance);)

        CALC_DLL(ContigPairGraphEdgeProperties();)

        int16_t distance_;  /**< category of distance (discretized distance)
                             *   between paired contigs */

//        int32_t gapSum_;    /**< sum of distances (gaps or overlaps length)
//                             *   between paired contigs calculated for all
//                             *   linkages within distance_ category */
//
//        uint32_t offset_;   /**< offset of gap sequence laying on read
//                             *   specified by readId_ identifier*/

        std::vector<GapInfo> bridges_; /**< descriptors of MatepairGraph
                             * edges which identify pairs of k-mers linking
                             * two contigs*/

        CALC_DLL(int32_t gapSum() const;)
    };



    /**
     * Type alias for Boost::labeled_graph.
     */
    using ContigPairGraph =
        boost::labeled_graph<
            boost::adjacency_list<boost::vecS,
                boost::vecS,
                boost::directedS,
                ContigPairGraphVertexProperties,
                ContigPairGraphEdgeProperties,
                boost::no_property,
                boost::vecS>,
            std::string>;

    /**
     * Type alias for ContigPairGraph vertex descriptor.
     */
    using ContigPairGraphVertex =
        boost::graph_traits<ContigPairGraph>::vertex_descriptor;

    /**
    * Type alias for ContigPairGraph edge descriptor.
    */
    using ContigPairGraphEdge =
        boost::graph_traits<ContigPairGraph>::edge_descriptor;

    CALC_DLL(std::vector<ContigPairGraphEdge> getAllParallelEdges(
        ContigPairGraphVertex v1,
        ContigPairGraphVertex v2,
        const ContigPairGraph& g
    );)

    CALC_DLL(LinksPerReadVec createLinksPerReadVec(
        const ContigPairGraphEdgeProperties &pair,
        const MatepairGraph& matepairs
    );)

}} //namespace dnaasm::scfr
#endif //CONTIGPAIRGRAPH_HPP
