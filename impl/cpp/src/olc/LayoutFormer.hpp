/**
 * \file LayoutFormer.hpp
 * \brief the C++ file with definition of class responsible for forming
 * layouts (maximal simple paths)
 *
 */

#ifndef LAYOUTFORMER_HPP
#define LAYOUTFORMER_HPP

#include <boost/graph/depth_first_search.hpp>
#include <boost/range/irange.hpp>
#include <boost/pending/indirect_cmp.hpp>

#include "OverlapGraph.hpp"
#include "OvlpGraphBuilder.hpp"
#include "common.hpp"

namespace dnaasm { namespace olc {
    class LayoutFormer {
    public:
        LayoutFormer(OverlapGraph &overlapGraph) : ovlpGraph_(overlapGraph) {}

        CALC_DLL(void removeCycles();)
        void removeTransInfEdges();
        LayoutVec findLayoutsInOvlpGraph();
    private:
        OverlapGraph &ovlpGraph_;
    };
}} //namespace dnaasm::olc

#endif //LAYOUTFORMER_HPP
