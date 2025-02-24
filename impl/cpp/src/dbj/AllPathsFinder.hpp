/**
 * \file AllPathsFinder.hpp
 * \brief the C++ file with implementation of template class for finding all possible paths from source vertex to target vertex
 */


#ifndef ALL_PATHS_FINDER_HPP
#define ALL_PATHS_FINDER_HPP

#include "globals.hpp"
#include "IsLimitedDirectedPath.hpp"

#include <iostream>

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to find all possible paths from source vertex to target vertex
    */
    template<class Graph> class AllPathsFinder {
    public:
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
        typedef std::vector<Vertex> Path;
        typedef std::vector<Path> Paths;

        /**
         * \brief AllPathsFinder constructor.
         *
         * \param g reference to Graph object
         */
        AllPathsFinder(Graph& g, Vertex& source, Vertex& target, unsigned short pathSizeLimit)
            : g_(g)
            , source_(source)
            , target_(target)
            , pathSizeLimit_(pathSizeLimit)
            , searchDepthLimit_(num_vertices(g_) < 40 ? 40U : static_cast<unsigned int>((2*num_vertices(g_))))
        {}

        AllPathsFinder(Graph& g, Vertex& source, Vertex& target)
            : g_(g)
            , source_(source)
            , target_(target)
            , pathSizeLimit_(std::numeric_limits<unsigned short>::max())
            , searchDepthLimit_(std::numeric_limits<unsigned int>::max())
        {}

        /**
         * \brief Generates all paths form source to target vertex.
         *
         * \return returns all paths
         */
        Paths findAllPaths() {
            initFirstPath();
            evaluateNewPathsForFindingAllPaths();

            while (checkPathsSize() && openedPaths_.size() != 0 && --searchDepthLimit_ != 0U) {
                expandOpenedPaths();
                evaluateNewPathsForFindingAllPaths();
            }

            sort(closedPaths_.begin(), closedPaths_.end());
            closedPaths_.erase(unique(closedPaths_.begin(), closedPaths_.end()), closedPaths_.end());

            return closedPaths_;
        }

        Paths findSpecifiedPaths() {
            initFirstPath();
            evaluateNewPathsForFindingSpecifiedPaths();

            while (checkPathsSize() && openedPaths_.size() != 0 && --searchDepthLimit_ != 0U) {
                expandOpenedPaths();
                evaluateNewPathsForFindingSpecifiedPaths();
            }

            sort(closedPaths_.begin(), closedPaths_.end());
            closedPaths_.erase(unique(closedPaths_.begin(), closedPaths_.end()), closedPaths_.end());

            return closedPaths_;
        }

    private:
        AllPathsFinder& operator=(const AllPathsFinder&)= delete;
        Graph& g_;
        Vertex& source_;
        Vertex& target_;
        unsigned short pathSizeLimit_;
        unsigned int searchDepthLimit_;
        Paths newPaths_;
        Paths openedPaths_;
        Paths closedPaths_;

        void initFirstPath() {
            Path firstNewPath;
            firstNewPath.push_back(source_);
            newPaths_.push_back(firstNewPath);
        }

        void expandOpenedPaths() {
            newPaths_.clear();

            for (typename Paths::iterator it = openedPaths_.begin(); it != openedPaths_.end(); ++it) {
                typename boost::graph_traits<Graph>::out_edge_iterator ei, ei_end;

                for (boost::tie(ei, ei_end)= out_edges(it->back(), g_); ei != ei_end; ++ei) {
                    if (g_[*ei].isForConnectedSequences_) {
                        Path newPath = *it;
                        newPath.push_back(target(*ei, g_));
                        newPaths_.push_back(newPath);
                    }
                }
            }
        }

        void evaluateNewPathsForFindingAllPaths() {
            sort(newPaths_.begin(), newPaths_.end());
            newPaths_.erase(unique(newPaths_.begin(), newPaths_.end()), newPaths_.end());
            openedPaths_.clear();

            for (typename Paths::iterator it = newPaths_.begin(); it != newPaths_.end(); ++it) {
                unsigned short overcomedDistance = countOvercomedDistance(*it);

                if (it->back() == target_) {
                    closedPaths_.push_back(*it);
                } else if (overcomedDistance < pathSizeLimit_) {
                    unsigned short remainingDistance = pathSizeLimit_ - overcomedDistance;
                    IsLimitedDirectedPath<Graph> isLimitedDirectedPath(g_, remainingDistance);

                    if (isLimitedDirectedPath(it->back(), target_)) {
                        openedPaths_.push_back(*it);
                    }
                }
            }
            newPaths_.clear();
        }

        void evaluateNewPathsForFindingSpecifiedPaths() {
            sort(newPaths_.begin(), newPaths_.end());
            newPaths_.erase(unique(newPaths_.begin(), newPaths_.end()), newPaths_.end());
            openedPaths_.clear();

            for (typename Paths::iterator it = newPaths_.begin(); it != newPaths_.end(); ++it) {
                if (isOriginalityConstraintKept(*it)) {
                    if (it->back() == target_) {
                        closedPaths_.push_back(*it);
                    } else if (countOvercomedDistance(*it) < pathSizeLimit_) {
                        openedPaths_.push_back(*it);
                    }
                }
            }
            newPaths_.clear();
        }

        bool checkPathsSize() {
            //jak 100 000 to jest dobrze, jak 1000 to nie jest dobrze dla 7 i 8 i k=55
            if (closedPaths_.size() + openedPaths_.size() > 2000000 || closedPaths_.size() > 1000) {   // to protect against out of memory in complicated graphs
                newPaths_.clear();
                openedPaths_.clear();
                closedPaths_.clear();
                return false;
            }
            return true;
        }

        unsigned short countOvercomedDistance(Path& path) {
            if (path.size() == 0 || path.size() == 1)
                return 0U;

            unsigned short overcomedDistance = 0U;
            for (typename Path::iterator it = path.begin() + 1; it != path.end(); ++it) {
                overcomedDistance += static_cast<unsigned short>(g_[*it].sequenceSize_);
            }
            return overcomedDistance;
        }

        bool isOriginalityConstraintKept(Path& path) {
            std::vector<bool> wasUsed(num_vertices(g_), false);

            for (typename Path::iterator it = path.begin(); it != path.end(); ++it) {
                if (wasUsed[*it] == true)
                    return false;
                if (g_[*it].isOriginal_ == true)
                    wasUsed[*it] = true;
            }
            return true;
        }
    };
}}

#endif    //ALL_PATHS_FINDER_HPP
