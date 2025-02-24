/**
 * \file DistanceArrayBuilder.hpp
 * \brief the C++ file with template class for building distance array between sequences in graph
 *
 */

#ifndef DISTANCE_ARRAY_BUILDER_HPP
#define DISTANCE_ARRAY_BUILDER_HPP

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
#pragma warning(disable:4459)   // for boost/multi_array
#endif

#include "boost/multi_array.hpp"
#include "globals.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to build distance array between sequences in graph.
     */
    template<class Graph> class DistanceArrayBuilder {
    public:

        typedef boost::multi_array<unsigned short, 2> DistanceArray;
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;

        /**
        * \brief DistanceArrayBuilder constructor.
        *
        * \param graph reference to original (huge) graph with sequences
        */
        DistanceArrayBuilder(Graph& graph)
            : graph_(graph)
        {}

        /**
         * \brief Builds array with distances between sequences.
         *
         * \param subGraph reference to subgraph, for which distance array should be built
         * \param connectedVerticesId vector to map ids for graph_ and subGraph references
         * \return returns array with distances between sequences
         */
        DistanceArray buildDistanceArray(
                Graph& subGraph,
                std::vector<Vertex>& connectedVerticesId) {

            DistanceArray distanceArray(boost::extents[num_vertices(subGraph)][num_vertices(subGraph)]);
            typename boost::graph_traits<Graph>::vertex_iterator vi, vi_end;

            for (boost::tie(vi, vi_end)= vertices(subGraph); vi != vi_end; ++vi) {
                typename boost::graph_traits<Graph>::vertex_iterator vi2, vi2_end;
                for (boost::tie(vi2, vi2_end)= vertices(subGraph); vi2 != vi2_end; ++vi2) {
                    std::pair<Edge, bool> currentEdge = edge(connectedVerticesId[*vi], connectedVerticesId[*vi2], graph_);
                    if (currentEdge.second == false) {
                        distanceArray[*vi][*vi2] = std::numeric_limits<unsigned short>::max();
                    } else {
                        distanceArray[*vi][*vi2] = graph_[currentEdge.first].estimatedDistance_;
                    }
                }
            }

            correctDistanceAray(distanceArray, connectedVerticesId);

            /*for (size_t fromV = 0; fromV < distanceArray.shape()[0]; fromV++) {
                for (size_t toV = 0; toV < distanceArray.shape()[1]; toV++) {
                    std::cout << "From: " << fromV << " to: " << toV << " dist: " << distanceArray[fromV][toV] << std::endl;
                }
            }*/

            return distanceArray;
        }

    private:
        Graph& graph_;

        /**
         * \brief Corrects array with distances between sequences - if there is no direct connection between two sequences, it can be estimated by 'sub-connections'.
         *
         * \param distanceArray original array with distances between sequences
         * \param connectedVerticesId vector to map ids for graph_ and subGraph references
         * \return returns void
         */
        void correctDistanceAray(
                DistanceArray& distanceArray,
                std::vector<Vertex>& connectedVerticesId) {

            for (size_t fromV = 0; fromV < distanceArray.shape()[0]; fromV++) {
                for (size_t toV = 0; toV < distanceArray.shape()[1]; toV++) {
                    if (distanceArray[fromV][toV] == std::numeric_limits<unsigned short>::max()) {
                        unsigned short connectionCounter = 0U;
                        unsigned short distanceCounter = 0U;

                        for (size_t subV = 0; subV < distanceArray.shape()[1]; subV++) {
                            if (graph_[connectedVerticesId[subV]].isOriginal_ && 
                                distanceArray[fromV][subV] != 0U && 
                                distanceArray[fromV][subV] != std::numeric_limits<unsigned short>::max() && 
                                distanceArray[subV][toV] != 0U && distanceArray[subV][toV] != std::numeric_limits<unsigned short>::max()) {

                                ++connectionCounter;
                                distanceCounter += distanceArray[fromV][subV];
                                distanceCounter += static_cast<unsigned short>(graph_[connectedVerticesId[subV]].sequenceSize_);
                                distanceCounter += distanceArray[subV][toV];
                            }
                        }
                        connectionCounter != 0U ? distanceArray[fromV][toV] = distanceCounter/connectionCounter : distanceArray[fromV][toV] = std::numeric_limits<unsigned short>::max();
                    }
                }
            }
        }

    };

}}

#endif    //DISTANCE_ARRAY_BUILDER_HPP
