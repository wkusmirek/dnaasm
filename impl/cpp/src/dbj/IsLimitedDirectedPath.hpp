/**
 * \file IsLimitedDirectedPath.hpp
 * \brief the C++ file with implementation of template class for checking if limited, directed path exists in graph
 *
 */

#ifndef IS_LIMITED_DIRECTED_PATH_HPP
#define IS_LIMITED_DIRECTED_PATH_HPP

#include "globals.hpp"

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to check if limited, directed path exists in graph.
    */
    template<class Graph> class IsLimitedDirectedPath {
    public:

        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef std::vector<Vertex> Block;  // block of vertices

        /**
         * \brief IsLimitedDirectedPath constructor.
         *
         * \param graph reference to specified graph object
         * \param limit max path length
         */
        IsLimitedDirectedPath(Graph& graph, unsigned short& limit): graph_(graph), limit_(limit) {}

        bool operator()(Vertex& sourceBlockId, Vertex& destinationBlockId, unsigned short overcomedDistance) {
            if (sourceBlockId == destinationBlockId)
                return true;

            std::vector<bool> wasUsed(num_vertices(graph_), false);

            if (overcomedDistance <= limit_ &&
                isLimitedDirectedPath(sourceBlockId, destinationBlockId, limit_ - overcomedDistance, wasUsed)) {  //jak to zakomentowane to działa dużo szybciej :)
                return true;
            }
            return false;
        }

        bool operator()(Vertex& sourceBlockId, Vertex& destinationBlockId) {
            if (sourceBlockId == destinationBlockId)
                return true;

            std::vector<bool> wasUsed(num_vertices(graph_), false);

            if (isLimitedDirectedPath(sourceBlockId, destinationBlockId, limit_, wasUsed)) {
                return true;
            }
            return false;
        }

    private:
        IsLimitedDirectedPath& operator=(const IsLimitedDirectedPath&)= delete;
        Graph& graph_;
        unsigned short& limit_;

        bool isLimitedDirectedPath(Vertex& source, Vertex& destination, unsigned short actualLimit, std::vector<bool>& wasUsed) {
            if(source == destination)
                return true;

            typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

            for(tie(ei, ei_end) = out_edges(source, graph_); ei != ei_end; ++ei) {
                if(graph_[*ei].isForConnectedSequences_ == false)
                    continue;

                auto targetVertex = target(*ei, graph_);

                if(targetVertex == destination)
                    return true;

                unsigned short targetSize = graph_[targetVertex].sequenceSize_;

                if(targetSize > actualLimit)
                    continue;

                if(isLimitedDirectedPath(targetVertex, destination, actualLimit-targetSize, wasUsed))
                    return true;
            }

            return false;
        }

        /**
         * \brief Counts distance from specified vertex to end of block.
         *
         * \param vertex specified vertex, for which distance to end of block will be calculated
         * \param block pointer to Block object
         * \return returns distance from specified vertex to end of block or maximum value of unsigned short
         */
        unsigned short countDistanceToEndOfBlock(Vertex& vertex, Block* block) {
            if (block->size() == 0) {
                return std::numeric_limits<unsigned short>::max();
            }

            typename Block::reverse_iterator vertexPositionIt;

            if (block->size() > limit_) {
                vertexPositionIt = find(block->rbegin(), block->rbegin()+limit_, vertex);
                if (vertexPositionIt == block->rbegin()+limit_) {
                    return std::numeric_limits<unsigned short>::max();
                }
            } else {
                vertexPositionIt = find(block->rbegin(), block->rend(), vertex);
                if (vertexPositionIt == block->rend()) {
                    return std::numeric_limits<unsigned short>::max();
                }
            }

            return static_cast<unsigned short>((vertexPositionIt - block->rbegin()));
        }

        /**
         * \brief Counts distance from start of block to specified vertex.
         *
         * \param vertex specified vertex, for which distance from start of block will be calculated
         * \param block pointer to Block object
         * \return returns distance from start of block to specified vertex or maximum value of unsigned short
         */
        unsigned short countDistanceFromStartOfBlock(Vertex& vertex, Block* block) {
            if (block->size() == 0) {
                return std::numeric_limits<unsigned short>::max();
            }

            typename Block::iterator vertexPositionIt;

            if (block->size() > limit_) {
                vertexPositionIt = find(block->begin(), block->begin()+limit_, vertex);
                if (vertexPositionIt == block->begin()+limit_) {
                    return std::numeric_limits<unsigned short>::max();
                }
            } else {
                vertexPositionIt = find(block->begin(), block->end(), vertex);
                if (vertexPositionIt == block->end()) {
                    return std::numeric_limits<unsigned short>::max();
                }
            }

            return static_cast<unsigned short>((vertexPositionIt - block->begin()));
        }

    };
}}
#endif    //IS_LIMITED_DIRECTED_PATH_HPP
