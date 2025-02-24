#include "MatepairGraph.hpp"
#include "../common/log.hpp"
namespace dnaasm { namespace scfr {

    MatepairGraphVertexProperties::MatepairGraphVertexProperties()
        : contigId_(0U), start_(0U), end_(0U)
    {}

    MatepairGraphVertexProperties::MatepairGraphVertexProperties(uint32_t contigId,
                                                                 uint32_t start,
                                                                 uint32_t end)
        : contigId_(contigId), start_(start), end_(end)
    {}

    MatepairGraphEdgeProperties::MatepairGraphEdgeProperties()
        : readId_(0U), offset_(0U)
    {}

    MatepairGraphEdgeProperties::MatepairGraphEdgeProperties(uint32_t readId,
                                                             uint32_t offset)
        : readId_(readId), offset_(offset)
    {}

    MatepairGraph::MatepairGraph(unsigned short K1)
        : hashTable_(K1)
    {}

    MatepairGraphInternal &MatepairGraph::graph() {
        return graph_;
    }

    MatepairGraphInternal const &MatepairGraph::graph() const {
        return graph_;
    }

    Vertex MatepairGraph::vertex(const std::string &kmer) {
        auto foundIt = hashTable_.find(kmer.data());
        if (foundIt == hashTable_.end()) {
            return boost::graph_traits<MatepairGraphInternal>::null_vertex();
        }
        return foundIt->second;
    }

    Vertex MatepairGraph::add_vertex(const std::string &kmer) {
        auto foundIt = hashTable_.find(kmer.data());
        if (foundIt == hashTable_.end()) {
            auto v_desc = boost::add_vertex(graph_);
            hashTable_.insert(kmer.data(), v_desc);
            return v_desc;
        }
        return foundIt->second;
    }

    Vertex MatepairGraph::add_vertex(const std::string &kmer,
                                     const MatepairGraphVertexProperties& vp) {
        auto foundIt = hashTable_.find(kmer.data());
        if (foundIt == hashTable_.end()) {
            auto v_desc = boost::add_vertex(vp, graph_);
            hashTable_.insert(kmer.data(), v_desc);
            return v_desc;
        }
        return foundIt->second;
    }
}}