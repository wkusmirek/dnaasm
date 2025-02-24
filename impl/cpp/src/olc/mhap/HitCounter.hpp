#ifndef HITCOUNTER_HPP
#define HITCOUNTER_HPP

#include "../common.hpp"
//#include "../../common/MurmurHash3.hpp"

#include <cstdint>
#include <array>
#include <vector>


namespace dnaasm {
    namespace olc {
        namespace mhap {

            struct HitCounter {
                int32_t count;

                HitCounter() : count(0) {}

                HitCounter(int32_t cnt) : count(cnt) {}

                HitCounter &addHit() {
                    ++count;
                    return *this;
                }

                void addHits(int32_t counts) {
                    count += counts;
                }
            };
        }
    }
}
#endif /* HITCOUNTER_HPP */