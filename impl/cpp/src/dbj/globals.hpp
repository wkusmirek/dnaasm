/**
 * \file globals.hpp
 * \brief the C++ file with declaration of some global things
 *
 */

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <boost/graph/compressed_sparse_row_graph.hpp>
#include <boost/graph/adjacency_list.hpp>


#include "../common/common.hpp"
#include "../common/HashTable.hpp"

namespace dnaasm { namespace dbj {

    struct DeBruijnGraphVertexProperties {
        CALC_DLL(DeBruijnGraphVertexProperties();)
    };

    struct DeBruijnGraphEdgeProperties {
        CALC_DLL(DeBruijnGraphEdgeProperties();)
        unsigned short counter_ = 0U;
    };

    typedef boost::compressed_sparse_row_graph<boost::directedS,
                                               DeBruijnGraphVertexProperties,
                                               DeBruijnGraphEdgeProperties> DeBruijnGraph;

    struct CompressedDeBruijnGraphEdgeProperties {
        CALC_DLL(CompressedDeBruijnGraphEdgeProperties();)
        unsigned short counter_;
        bool bridge_;
    };

    struct CompressedDeBruijnGraphVertexProperties {
        CALC_DLL(CompressedDeBruijnGraphVertexProperties();)
        std::vector<std::size_t> uncompressedVertices_;
    };

    typedef boost::adjacency_list<boost::vecS,
                                  boost::vecS,
                                  boost::directedS,
                                  CompressedDeBruijnGraphVertexProperties,
                                  CompressedDeBruijnGraphEdgeProperties,
                                  boost::no_property,
                                  boost::vecS> CompressedDeBruijnGraph;

    struct uint48 {
        unsigned long long v:48;
    } __attribute__((packed));


    typedef SparseHashTable<boost::graph_traits<DeBruijnGraph>::vertex_descriptor> HashTable;
}}

#endif  // GLOBALS_HPP
