#ifndef MINHASHSKETCH_HPP
#define MINHASHSKETCH_HPP

#include "../common.hpp"
#include <cmath>
#include <vector>
#include <limits>
#include <unordered_map>


//#include "KMerCounter.hpp"
#include "HitCounter.hpp"
#include "FrequencyCounts.hpp"
#include "Sequence.hpp"

namespace dnaasm {
    namespace olc {
        namespace mhap {

            class MinHashSketch {
            public:
                MinHashSketch(LongRead seq, int32_t nGramSize, int32_t numHashes,
                              FreqCountPtr &freqFilter, bool doReverseCompliment,
                              double repeatWeight)
                        : minHashes_(MinHashSketch::computeNgramMinHashesWeighted(seq, nGramSize, numHashes, freqFilter,
                                                                                 doReverseCompliment, repeatWeight)) {}


                std::vector<int32_t> &getMinHashArray() {
                    return minHashes_;
                }


            private:
                std::vector<int32_t> minHashes_;

                static std::vector<int32_t>
                computeNgramMinHashesWeighted(LongRead &seq, int32_t nGramSize,
                                              int32_t numHashes, FreqCountPtr &kmerFilter,
                                              bool doReverseCompliment, double repeatWeight);
            };

        }
    }
}

#endif /* MINHASHSKETCH_HPP */
