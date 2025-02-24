/**
 * \file HashObj.cpp
 * \brief the C++ file with definition of functor structure (interface) used to
 * perform hash calculation
 *
 */

#include <string>

#include "HashObj.hpp"

namespace dnaasm {
    namespace olc {

        uint64_t HashObj::operator()(const std::string &kmer) {
            return std::hash<std::string>{}(kmer);
        }

    }
} //namespace dnaasm::olc
