/**
 * \file OlcAssembly.hpp
 * \brief the C++ calculation library interface for olc module
 */

#ifndef OLCASSEMBLY_HPP
#define OLCASSEMBLY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1800)
#pragma warning(disable:4512)
#endif

#include <mt4cpp/Scheduler.hpp>
#include <mt4cpp/CommandHistory.hpp>

#include "../common/common.hpp"

namespace dnaasm {
    namespace olc {
        CALC_DLL(std::string olcAssembly(std::istream &longReadsFileName,
                                         unsigned short int kMerLength,
                                         unsigned short int sketchNum,
                                         float minJaccardSim,
                                         short int matchScore,
                                         short int mismatchScore,
                                         short int gapPenalty,
                                         unsigned short int minEdge,
                                         unsigned short int minContigLength,
                                         unsigned short int pathWidth,
                                         mt4cpp::Progress *progress);
        )
    }
} //namespace dnaasm::olc

#endif  //OLCASSEMBLY_HPP
