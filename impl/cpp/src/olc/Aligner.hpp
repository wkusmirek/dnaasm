#ifndef ALIGNER_HPP
#define ALIGNER_HPP

#include <cstdint>
#include <string>
#include <limits>
#include <utility>

#include "common.hpp"

namespace dnaasm {
    namespace olc {

        template<typename T>
        struct Aligner {
            virtual T operator()(const LongRead &lhs, const LongRead &rhs) = 0;
        };

    }
} //namespace dnaasm::olc
#endif /* ALIGNER_HPP */
