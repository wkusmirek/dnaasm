/**
 * \file MatepairGraph.hpp
 * \brief the C++ file with declaration of Matepair Graph
 */

#ifndef MATEPAIRGRAPH_HPP
#define MATEPAIRGRAPH_HPP

#include <boost/graph/adjacency_list.hpp>
#include <cstdint>

#include "../common/HashTable.hpp"

namespace dnaasm { namespace scfr {

    /**
     * Struct representing properties of MatepairGraph vertex.
     */
    struct MatepairGraphVertexProperties {
        /**
         * MatepairGraphVertexProperties c-tor.
         *
         * Initializes all struct members with 0.
         */
        CALC_DLL(MatepairGraphVertexProperties());

        /**
         * MatepairGraphVertexProperties c-tor.
         *
         * @param contigId identifier of contig on which k-mer was found
         * @param start position of first symbol of k-mer on contig
         * @param end position following the position of last symbol
         *        of k-mer on contig
         */
        CALC_DLL(MatepairGraphVertexProperties(uint32_t contigId,
                                               uint32_t start,
                                               uint32_t end);)

        uint32_t contigId_; /**< identifier of contig on which k-mer was found */
        uint32_t start_;    /**< position of first symbol of k-mer on contig */
        uint32_t end_;      /**< position following the position of last symbol
                             *   of k-mer on contig */
    };

    /**
     * Struct representing properties of MatepairGraph edge.
     */
    struct MatepairGraphEdgeProperties {

        /**
         * MatepairGraphEdgeProperties c-tor.
         *
         * Initializes all struct members with 0.
         */
        CALC_DLL(MatepairGraphEdgeProperties();)

        /**
         * MatepairGraphEdgeProperties c-tor.
         *
         * @param readId identifier of long read from which k-mer pair was extracted
         * @param offset offset used for k-mer pair extraction, i.e. position
         *               of first letter of first k-mer from pair
         */
        CALC_DLL(MatepairGraphEdgeProperties(uint32_t readId,
                                             uint32_t offset);)

        uint32_t readId_; /**< identifier of long read from which k-mer pair
                           *   was extracted */
        uint32_t offset_; /**< offset used for k-mer pair extraction */

    };

    /**
     * Type alias for Boost::adjacency_list representing matepair graph.
     */
    using MatepairGraphInternal =
            boost::adjacency_list<boost::vecS,
                boost::vecS,
                boost::directedS,
                MatepairGraphVertexProperties,
                MatepairGraphEdgeProperties,
                boost::no_property,
                boost::vecS>;

    /**
     * Type alias for MatepairGraph vertex descriptor.
     */
    using Vertex =
        boost::graph_traits<MatepairGraphInternal>::vertex_descriptor;

    /**
     * Type alias for MatepairGraph edge descriptor.
     */
    using Edge =
        boost::graph_traits<MatepairGraphInternal>::edge_descriptor;

    /**
     * Type alias for SparseHashTable with Vertex as value
     */
    using HashTable =
        dnaasm::SparseHashTable<Vertex>;

    /**
     * Class being a wrapper for MatepairGraphInternal.
     *
     * Mapping between k-mer string (vertex label) and vertex descriptor
     * is realized via HashTable.
     */
    class MatepairGraph {
    public:
        /**
         * MatepairGraph c-tor.
         *
         * @param K1 k-mer length
         */
        CALC_DLL(MatepairGraph(unsigned short K1);)

        /**
         * Returns internal graph representation.
         *
         * @return reference to internal graph representation
         */
        CALC_DLL(MatepairGraphInternal& graph();)

        /**
         * Returns internal graph representation.
         *
         * @return reference to const internal graph representation
         */
        CALC_DLL(MatepairGraphInternal const& graph() const;)

        /**
         * Returns descriptor of vertex specified by label.
         *
         * @param kmer reference to k-mer string (vertex label)
         * @return descriptor of vertex
         */
        CALC_DLL(Vertex vertex(const std::string &kmer);)

        /**
         * Adds k-mer to graph.
         *
         * Vertex is not added if it already exists in graph.
         *
         * @param kmer reference to k-mer to be inserted
         * @return descriptor of new or existing vertex
         */
        CALC_DLL(Vertex add_vertex(const std::string &kmer);)

        /**
         * Adds k-mer to graph with given vertex properties.
         *
         * Vertex is not added if it already exists in graph.
         *
         * @param kmer reference to k-mer to be inserted
         * @param vp reference to struct with properties of new vertex
         * @return descriptor of new or existing vertex
         */
        CALC_DLL(Vertex add_vertex(const std::string &kmer,
                                   const MatepairGraphVertexProperties& vp);)

        static const uint32_t CONTIG_ID_FOR_NOT_UNIQUE_KMER = UINT32_MAX;

    private:
        HashTable hashTable_;
        MatepairGraphInternal graph_;

        MatepairGraph& operator=(const MatepairGraph&) = delete;
    };

}} //namespace dnaasm::scfr

#endif //MATEPAIRGRAPH_HPP
