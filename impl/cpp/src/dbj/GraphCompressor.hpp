/**
 * \file GraphCompressor.hpp
 * \brief the C++ file with implementation of template class for compressing de Bruijn graph before generating set of resultant unitigs (to save time in searching return paths, loops etc.)
 */


#ifndef GRAPH_COMPRESSOR_HPP
#define GRAPH_COMPRESSOR_HPP

#include "../common/log.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to compress graph
     */
    template<class UncompressedGraph, class CompressedGraph> class GraphCompressor {
    public:
        typedef typename boost::graph_traits<CompressedGraph>::vertex_descriptor CompressedVertex;
        typedef typename boost::graph_traits<CompressedGraph>::edge_descriptor CompressedEdge;
        typedef typename boost::graph_traits<UncompressedGraph>::vertex_descriptor UncompressedVertex;
        typedef typename boost::graph_traits<UncompressedGraph>::edge_descriptor UncompressedEdge;
        typedef std::vector<UncompressedVertex> UncompressedPath;

        /**
         * \brief GraphCompressor constructor.
         *
         * \param uncompGraph reference to UncompressedGraph object
         */
        GraphCompressor(UncompressedGraph& uncompGraph) : uncompGraph_(uncompGraph), compGraph_(), numOfDisconnectedVertices_(0U) {}

        /**
         * \brief Compresses de Bruijn graph.
         *
         * \return returns void
         */
        void compressGraph() {

            /* for simulating large number of unitigs in unitigs graph for E. coli */
            /*typename boost::graph_traits<UncompressedGraph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end)= vertices(uncompGraph_); vi != vi_end; ++vi) {
                if(*vi%5==0) {
                    clear_out_edges(*vi, uncompGraph_);
                }
            }*/

            logInfo("compressing reads graph...");
            std::vector<unsigned short int> in_degree_all(num_vertices(uncompGraph_), 0U);
            std::vector<unsigned short int> out_degree_all(num_vertices(uncompGraph_), 0U);
            std::vector<bool> wasCompressed(num_vertices(uncompGraph_), false);
            countDegrees(in_degree_all, out_degree_all);
            compressSingleDisconnectedPaths(in_degree_all, out_degree_all, wasCompressed);
            findUncompPaths(in_degree_all, out_degree_all, wasCompressed);
            addEdgesToCompGraph();
            logInfo("uncompressed reads graph: disconnected vertices: " + std::to_string(numOfDisconnectedVertices_));
            logInfo("compressed reads graph: vertices: " + std::to_string(num_vertices(compGraph_))
                    + " edges: " + std::to_string(num_edges(compGraph_)));
            return;
        }

        /**
         * \brief Gets reference to CompressedGraph object.
         *
         * \return returns reference to CompressedGraph object
         */
        CompressedGraph& getCompressedGraph() {
            return compGraph_;
        }

    private:
        GraphCompressor& operator=(const GraphCompressor&)= delete;
        UncompressedGraph& uncompGraph_;
        CompressedGraph compGraph_;
        unsigned int numOfDisconnectedVertices_;    // only for statistics

        /**
         * \brief Counts degrees (in and out) of each vertex of uncompressed de Bruijn graph.
         *
         * \param in_degree_all vector of information about number of in-edges for each vertex
         * \param out_degree_all vector of information about number of out-edges for each vertex
         * \return returns void
         */
        void countDegrees(std::vector<unsigned short int>& in_degree_all, std::vector<unsigned short int>& out_degree_all) {
            typename boost::graph_traits<UncompressedGraph>::edge_iterator ei, ei_end;
            for (boost::tie(ei, ei_end) = edges(uncompGraph_); ei != ei_end; ++ei) {
                if (uncompGraph_[*ei].counter_ != 0U) {
                    ++in_degree_all[target(*ei, uncompGraph_)];
                    ++out_degree_all[source(*ei, uncompGraph_)];
                }
            }
        }

        void compressSingleDisconnectedPaths(std::vector<unsigned short int>& in_degree_all,
                                             std::vector<unsigned short int>& out_degree_all,
                                             std::vector<bool>& wasCompressed) {

            typename boost::graph_traits<UncompressedGraph>::vertex_iterator vi, vi_end;
            for (boost::tie(vi, vi_end) = vertices(uncompGraph_); vi != vi_end; ++vi) {
                UncompressedVertex actualVertex = *vi;
                if (in_degree_all[actualVertex] == 0U && out_degree_all[actualVertex] == 1U && wasCompressed[actualVertex] == false) {
                    if (isSingleDisconnectedPath(actualVertex, in_degree_all, out_degree_all)) {
                        compressSingleVertex(actualVertex, wasCompressed);
                        UncompressedVertex nextVertex = getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(actualVertex);
                        compressSinglePath(nextVertex, in_degree_all, out_degree_all, wasCompressed);
                    }
                }
            }
        }

        bool isSingleDisconnectedPath(UncompressedVertex& actualVertex,
                                      std::vector<unsigned short int>& in_degree_all,
                                      std::vector<unsigned short int>& out_degree_all) {

            UncompressedVertex tmpVertex = actualVertex;
            while (true) {
                if (tmpVertex == (UncompressedVertex)(-1)) {
                    return false;
                }
                if (in_degree_all[tmpVertex] == 1U && out_degree_all[tmpVertex] == 0U) {
                    return true;
                }
                if (in_degree_all[tmpVertex] > 1U || out_degree_all[tmpVertex] > 1U) {
                    return false;
                }
                UncompressedVertex nextVertex = getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(tmpVertex);
                tmpVertex = nextVertex;
            }
        }

        /**
         * \brief Finds all paths in uncompressed de Bruijn graph, which can be compressed - each path in single, compressed vertex.
         *
         * \param in_degree_all vector of information about number of in-edges for each vertex
         * \param out_degree_all vector of information about number of out-edges for each vertex
         * \param wasCompressed vector with information, if specified vertex was compressed or not
         * \return returns void
         */
        void findUncompPaths(std::vector<unsigned short int>& in_degree_all,
                             std::vector<unsigned short int>& out_degree_all,
                             std::vector<bool>& wasCompressed) {
            typename boost::graph_traits<UncompressedGraph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end) = vertices(uncompGraph_); vi != vi_end; ++vi) {
                UncompressedVertex actualVertex = *vi;
                if (in_degree_all[actualVertex] == 0U && out_degree_all[actualVertex] == 1U && wasCompressed[actualVertex] == true) {   // single disconnected paths
                    continue;
                }
                if (in_degree_all[actualVertex] != 1U || out_degree_all[actualVertex] != 1U) {
                    findUncompPaths(actualVertex, in_degree_all, out_degree_all, wasCompressed);
                }
                if (in_degree_all[actualVertex] == 0U && out_degree_all[actualVertex] == 0U) { // only for statistics
                    ++numOfDisconnectedVertices_;
                }
            }

            // below loop for situations like a->b->c->d->a
            for (boost::tie(vi, vi_end) = vertices(uncompGraph_); vi != vi_end; ++vi) {
                UncompressedVertex actualVertex = *vi;
                if (wasCompressed[actualVertex] == false) {
                    findUncompPaths(actualVertex, in_degree_all, out_degree_all, wasCompressed);
                }
            }
        }

        /**
         * \brief Adds edges to compressed de Bruijn graph.
         *
         * \return returns void
         */
        void addEdgesToCompGraph() {
            std::multimap<UncompressedVertex, CompressedVertex> startOfUncompPath;
            typename boost::graph_traits<CompressedGraph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end) = vertices(compGraph_); vi != vi_end; ++vi) {
                startOfUncompPath.insert(std::pair<UncompressedVertex, CompressedVertex>(compGraph_[*vi].uncompressedVertices_.front(), *vi));
            }

            for (boost::tie(vi, vi_end) = vertices(compGraph_); vi != vi_end; ++vi) {
                CompressedVertex compSource = *vi;
                UncompressedVertex uncompSource = compGraph_[compSource].uncompressedVertices_.back();
                typename boost::graph_traits<UncompressedGraph>::out_edge_iterator ei, ei_end;

                for (boost::tie(ei, ei_end) = out_edges(uncompSource, uncompGraph_); ei != ei_end; ++ei) {
                    UncompressedVertex uncompTarget = target(*ei, uncompGraph_);
                    std::pair <typename std::multimap<UncompressedVertex, CompressedVertex>::iterator,
                               typename std::multimap<UncompressedVertex, CompressedVertex>::iterator> equalRangeResult = startOfUncompPath.equal_range(uncompTarget);

                    for (typename std::multimap<UncompressedVertex, CompressedVertex>::iterator equalRangeResultIt = equalRangeResult.first;
                         equalRangeResultIt != equalRangeResult.second; ++equalRangeResultIt) {
                        CompressedVertex compTarget = equalRangeResultIt->second;

                        if (!edge(compSource, compTarget, compGraph_).second) {
                            CompressedEdge compEdge = add_edge(compSource, compTarget, compGraph_).first;
                            compGraph_[compEdge].counter_ = uncompGraph_[*ei].counter_;
                        }
                    }
                }

            }
        }

        /**
         * \brief Finds all paths in uncompressed de Bruijn graph starts in startVertex, which can be compressed.
         *
         * \param startVertex first vertex, which can start new paths to compress
         * \param in_degree_all vector of information about number of in-edges for each vertex
         * \param out_degree_all vector of information about number of out-edges for each vertex
         * \param wasCompressed vector with information, if specified vertex was compressed or not
         * \return returns void
         */
        void findUncompPaths(UncompressedVertex& startVertex,
                             std::vector<unsigned short int>& in_degree_all,
                             std::vector<unsigned short int>& out_degree_all,
                             std::vector<bool>& wasCompressed) {

            if (in_degree_all[startVertex] == 0U && out_degree_all[startVertex] == 0U) {    // disconnected vertex
                return;
            }

            typename boost::graph_traits<UncompressedGraph>::out_edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = out_edges(startVertex, uncompGraph_); ei != ei_end; ++ei) {
                if (uncompGraph_[*ei].counter_ != 0U) {
                    UncompressedVertex secondVertex = target(*ei, uncompGraph_);
                    compressSinglePath(startVertex, secondVertex, in_degree_all, out_degree_all, wasCompressed);
                }
            }
        }

        /**
         * \brief Finds one path in uncompressed de Bruijn graph starts in startVertex with second vertex equal to secondVertex, which can be compressed.
         *
         * \param startVertex first vertex, which can start new path to compress
         * \param secondVertex second vertex, which can be second vertex in path to compress
         * \param in_degree_all vector of information about number of in-edges for each vertex
         * \param out_degree_all vector of information about number of out-edges for each vertex
         * \param wasCompressed vector with information, if specified vertex was compressed or not
         * \return returns void
         */
        void compressSinglePath(UncompressedVertex& startVertex,
                                UncompressedVertex& secondVertex,
                                std::vector<unsigned short int>& in_degree_all,
                                std::vector<unsigned short int>& out_degree_all,
                                std::vector<bool>& wasCompressed) {
            UncompressedPath uncompPath;

            if (in_degree_all[startVertex] == 0U) { // uncompressed graph entry
                addVertexToUncompPath(startVertex, uncompPath, wasCompressed);
            }

            UncompressedVertex actualVertex = secondVertex;

            while (true) {
                if (in_degree_all[actualVertex] != 1U || out_degree_all[actualVertex] != 1U || wasCompressed[actualVertex]) {
                    break;
                }

                addVertexToUncompPath(actualVertex, uncompPath, wasCompressed);
                actualVertex = getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(actualVertex);

                if (actualVertex == (UncompressedVertex)(-1)) {
                    break;
                }
            }

            if (in_degree_all[actualVertex] == 1U && out_degree_all[actualVertex] == 0U) { // uncompressed graph exit
                addVertexToUncompPath(actualVertex, uncompPath, wasCompressed);
                CompressedVertex compVertex = add_vertex(compGraph_);
                compGraph_[compVertex].uncompressedVertices_ = uncompPath;

            } else {
                if (uncompPath.size() > 0) {
                    CompressedVertex compVertex = add_vertex(compGraph_);
                    compGraph_[compVertex].uncompressedVertices_ = uncompPath;
                }

                compressSingleVertex(actualVertex, wasCompressed);
            }
        }

        void compressSinglePath(UncompressedVertex& startVertex,
                                std::vector<unsigned short int>& in_degree_all,
                                std::vector<unsigned short int>& out_degree_all,
                                std::vector<bool>& wasCompressed) {
            UncompressedPath uncompPath;
            UncompressedVertex actualVertex = startVertex;

            while (true) {
                if (in_degree_all[actualVertex] != 1U || out_degree_all[actualVertex] != 1U || wasCompressed[actualVertex]) {
                    break;
                }

                addVertexToUncompPath(actualVertex, uncompPath, wasCompressed);
                actualVertex = getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(actualVertex);

                if (actualVertex == (UncompressedVertex)(-1)) {
                    break;
                }
            }

            if (in_degree_all[actualVertex] == 1U && out_degree_all[actualVertex] == 0U) { // uncompressed graph exit
                addVertexToUncompPath(actualVertex, uncompPath, wasCompressed);
                CompressedVertex compVertex = add_vertex(compGraph_);
                compGraph_[compVertex].uncompressedVertices_ = uncompPath;

            } else {
                if (uncompPath.size() > 0) {
                    CompressedVertex compVertex = add_vertex(compGraph_);
                    compGraph_[compVertex].uncompressedVertices_ = uncompPath;
                }

                compressSingleVertex(actualVertex, wasCompressed);
            }
        }

        /**
         * \brief Compresses single, disconnected vertex from uncompressed de Bruijn graph.
         *
         * \param vertex uncompressed vertex, which will be compressed
         * \param wasCompressed vector with information, if specified vertex was compressed or not
         * \return returns void
         */
        void compressSingleVertex(UncompressedVertex& vertex, std::vector<bool>& wasCompressed) {
            if (wasCompressed[vertex] == false) {
                CompressedVertex compVertex = add_vertex(compGraph_);
                compGraph_[compVertex].uncompressedVertices_.push_back(vertex);
                wasCompressed[vertex] = true;
            }
        }

        /**
         * \brief Adds uncompressed vertex to uncompressed path, which will be compressed.
         *
         * \param vertex uncompressed vertex, which will be added to uncompressed path
         * \param uncompPath path with uncompressed vertices, which will be compressed into one compressed vertex
         * \param wasCompressed vector with information, if specified vertex was compressed or not
         * \return returns void
         */
        void addVertexToUncompPath(UncompressedVertex& vertex,
                                   UncompressedPath& uncompPath,
                                   std::vector<bool>& wasCompressed) {
            uncompPath.push_back(vertex);
            wasCompressed[vertex] = true;
        }

        UncompressedVertex getNextVertexConnectedWithEdgeWithCounterGreaterThanZero(UncompressedVertex& vertex) {
            typename boost::graph_traits<UncompressedGraph>::out_edge_iterator ei, ei_end;

            for (boost::tie(ei, ei_end) = out_edges(vertex, uncompGraph_); ei != ei_end; ++ei) {
                if (uncompGraph_[*ei].counter_ != 0U) {
                    return target(*ei, uncompGraph_);
                }
            }
            return (UncompressedVertex)(-1);
        }

    };
}}

#endif    // GRAPH_COMPRESSOR_HPP
