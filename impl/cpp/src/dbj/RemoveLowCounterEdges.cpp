/**
 * \file RemoveLowCounterEdges.cpp
 * \brief the C++ file with implementation of specialized template class for removing edges with low counter (size of insertSizeOffsetVector_ vector)
 *
 */

#include "RemoveLowCounterEdges.hpp"

using namespace std;

namespace dnaasm { namespace dbj {

    template<>
    void RemoveLowCounterEdges<UnitigsToContigsExtension::UnitigsGraph>::operator()() {
        if (edgeCounterThreshold_ == 0) {
            return;
        }

        std::vector<Edge> edgesToDelete;
        unsigned int numOfDeletedEdges = 0U;
        typename boost::graph_traits<UnitigsToContigsExtension::UnitigsGraph>::edge_iterator ei, ei_end;

        for (boost::tie(ei, ei_end) = edges(g_); ei != ei_end;) {
            if (g_[*ei].isForPairedReads_ == true && g_[*ei].counter_ < edgeCounterThreshold_) {
                edgesToDelete.push_back(*ei);
                ++numOfDeletedEdges;
            }

            ++ei;
            if (edgesToDelete.size() == 100000 || ei == ei_end) {
                unsigned int i = 0U;

                for (unsigned int edgesToDeleteSize = static_cast<unsigned int>(edgesToDelete.size());
                     i != edgesToDeleteSize;
                     ++i, edgesToDelete.pop_back()) {

                    if (g_[edgesToDelete.back()].isForConnectedSequences_ == false) {
                        remove_edge(edgesToDelete.back(), g_);
                    } else {
                        g_[edgesToDelete.back()].isForPairedReads_ = false;
                        g_[edgesToDelete.back()].insertSizeOffsetVector_.clear();
                    }
                }

                std::vector<Edge>().swap(edgesToDelete);   // free memory allocated by vector
                if (ei == ei_end) {
                    break;
                }

                boost::tie(ei, ei_end) = edges(g_); // without it segmentation fault
            }
        }
        logInfo("Deleting edges below threshold deletes " + std::to_string(numOfDeletedEdges) + " paired edges from contigs graph.");

        return;
    }

}}
