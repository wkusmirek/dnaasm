#ifndef EDGEDATA_HPP
#define EDGEDATA_HPP

#include <cstdint>

namespace dnaasm {
    namespace olc {
        namespace mhap {
            struct EdgeData {
                EdgeData(int32_t a1_, int32_t a2_, int32_t b1_, int32_t b2_, int32_t count_)
                        : a1(a1_), a2(a2_), b1(b1_), b2(b2_), count(count_) {}

                int32_t a1;
                int32_t a2;
                int32_t b1;
                int32_t b2;
                int32_t count;
            };
        }
    }
}
#endif //EDGEDATA_HPP