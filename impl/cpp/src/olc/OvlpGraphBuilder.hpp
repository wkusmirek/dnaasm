/**
 * \file OvlpGraphBuilder.hpp
 * \brief the C++ file with declaration of class for Overlap Graph Builder
 *
 */

#ifndef OVLPGRAPHBUILDER_HPP
#define OVLPGRAPHBUILDER_HPP

#include <iostream>
#include <utility>

#include <mt4cpp/Scheduler.hpp>
#include <mt4cpp/CommandHistory.hpp>

#include "SmithWatermanAligner.hpp"
#include "common.hpp"
#include "OverlapGraph.hpp"
#include <unordered_map>
#include <memory>

namespace dnaasm {
    namespace olc {
        using AlignerPtr = std::unique_ptr<Aligner<LocalAlignment>>;

        class OvlpGraphBuilder {
        public:
            OvlpGraphBuilder(HashObj &hashObj, ReadVector &readVec, AlignerPtr &alignPtr)
                    : hashObj_(hashObj), reads_(readVec)
                    //Pass aligner ownership to graph builder
                    , aligner_(std::move(alignPtr)) {}

            CALC_DLL(~OvlpGraphBuilder();)

            OverlapGraph
            CALC_DLL(buildGraph(unsigned short, unsigned short, float, unsigned short minJaccardSim,
                       mt4cpp::Progress *progress);)

        private:
            HashObj &hashObj_;
            ReadVector &reads_;
            AlignerPtr aligner_;

            void loadKmersToMinHash(MinHash &,
                                    const LongRead &,
                                    const size_t,
                                    const PermutationVector &);
        };

    }
} //namespace dnaasm::olc

#endif // OVLPGRAPHBUILDER_HPP
