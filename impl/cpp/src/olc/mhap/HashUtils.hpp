#ifndef HASHUTILS_HPP
#define HASHUTILS_HPP

#include "../common.hpp"


#include <cstdint>
#include <array>
#include <vector>


namespace dnaasm {
    namespace olc {
        namespace mhap {

            struct HashUtils {
                static std::array<uint64_t, 2> hash128(const LongRead &kmer, int32_t nGramSize, int32_t seed);

                static int32_t hash32(const LongRead &kmer, int32_t nGramSize, int32_t seed);

                static std::vector<int64_t>
                computeSequenceHashesLong(const LongRead &seq, int32_t nGramSize, int32_t seed, bool doReverseCompliment);

                static std::vector<int32_t>
                computeSequenceHashes(const LongRead &seq, int32_t nGramSize, bool doReverseCompliment);
            };
        }
    }
}

#endif //HASHUTILS_HPP
