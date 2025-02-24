/**
 * \file UnitigsUncompressor.hpp
 * \brief the C++ file with implementation of template class for uncompressing unitigs (when unitigs were generated from compressed de Bruijn graph)
 */


#ifndef UNITIGS_UNCOMPRESSOR_HPP
#define UNITIGS_UNCOMPRESSOR_HPP

#include "../common/log.hpp"

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to uncompress unitigs
     */
    template<class UncompressedGraph, class CompressedGraph> class UnitigsUncompressor {
    public:
        typedef typename boost::graph_traits<UncompressedGraph>::vertex_descriptor UncompressedVertex;
        typedef std::vector<UncompressedVertex> UncompressedUnitig;
        typedef std::vector<UncompressedUnitig> UncompressedUnitigs;
        typedef typename boost::graph_traits<CompressedGraph>::vertex_descriptor CompressedVertex;
        typedef std::vector<CompressedVertex> CompressedUnitig;
        typedef std::vector<CompressedUnitig> CompressedUnitigs;

        /**
         * \brief UnitigsUncompressor constructor.
         *
         * \param compGraph reference to CompressedGraph object
         */
        UnitigsUncompressor(CompressedGraph& compGraph) : compGraph_(compGraph) {}

        /**
         * \brief Uncompresses set of compressed unitigs - unitigs generated from compressed de Bruijn graph.
         *
         * \param uncompUnitigs reference to UncompressedUnitigs object, where uncompressed (resultant) conrigs should be stored
         * \param compUnitigs reference to CompressedUnitigs object, where set of compressed unitigs is stored
         * \return returns void
         */
        void uncompressUnitigs(UncompressedUnitigs& uncompUnitigs, CompressedUnitigs& compUnitigs) {
            logInfo("uncompressing unitigs...");
            for (typename CompressedUnitigs::iterator compUnitigsIt = compUnitigs.begin(); compUnitigsIt != compUnitigs.end(); ++compUnitigsIt) {
                UncompressedUnitig actualUncompUnitig;

                for (typename CompressedUnitig::iterator compUnitigIt = compUnitigsIt->begin(); compUnitigIt != compUnitigsIt->end(); ++compUnitigIt) {
                    actualUncompUnitig.insert(actualUncompUnitig.end(),
                                              compGraph_[*compUnitigIt].uncompressedVertices_.begin(),
                                              compGraph_[*compUnitigIt].uncompressedVertices_.end());
                }

                if (actualUncompUnitig.size() > 1) {
                    uncompUnitigs.push_back(actualUncompUnitig);
                }
            }
            return;
        }

    private:
        UnitigsUncompressor& operator=(const UnitigsUncompressor&)= delete;
        CompressedGraph& compGraph_;
    };
}}

#endif    // UNITIGS_UNCOMPRESSOR_HPP
