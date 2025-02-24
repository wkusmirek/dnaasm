/**
 * \file common.hpp
 * \brief the C++ file with some common utilities
 *
 */
#ifndef OLCCOMMON_HPP
#define OLCCOMMON_HPP

#include <string>
#include <vector>

#if defined(_MSC_VER) && (_MSC_VER >= 1800)
/*
* Need to define these macros,
* because Visual Studio Compiler,
* does not support keyword alternative logical operators,
* when language extensions are enabled,
* which causes compilation fail
*/
#define and &&
#define or ||
#define not !
#define not_eq !=

#endif

namespace dnaasm {
    namespace olc {
        using LongRead = std::string;
        using ReadVector = std::vector<LongRead>;

        using HashVector = std::vector<uint64_t>;
        using PermutationVector = std::vector<HashVector>;

        using Layout = std::vector<uint32_t>;
        using LayoutVec = std::vector<Layout>;
        using Base = char;

    }
} //namespace dnaasm::olc

#endif //OLCCOMMON_HPP
