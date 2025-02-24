/**
 * \file HashObj.hpp
 * \brief the C++ file with declaration of functor struct (interface) used to
 * perform hash calculation
 *
 */

#ifndef HASHOBJ_HPP
#define HASHOBJ_HPP

#include <cstdint>

#include "../common/common.hpp"

namespace dnaasm {
    namespace olc {

        struct HashObj {
            uint64_t operator()(const std::string &kmer);
        };

    }
} //namespace dnaasm::olc

#endif //HASHOBJ_HPP
