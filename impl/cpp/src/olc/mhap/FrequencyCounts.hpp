#ifndef FREQUENCYCOUNTS_HPP
#define FREQUENCYCOUNTS_HPP

#include "../common.hpp"
#include "../../common/MurmurHash3.hpp"
#include "../../common/BloomFilter.hpp"

#include <cstdint>
#include <array>
#include <memory>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace dnaasm {
    namespace olc {
        namespace mhap {

            class FrequencyCounts;
            using FreqCountPtr = std::unique_ptr<FrequencyCounts>;
            //removeUnique = 0: do nothing extra to k-mers not specified in the file
            //removeUnique = 1: remove k-mers not specified in the file from the sketch
            //removeUnique = 2: supress k-mers not specified in the file the same as max supression
            enum class RemoveUnique {
                NOTHING, REMOVE, SUPRESS
            };

            class FrequencyCounts {
                //TODO: replace std containters with google sparsehash
            public:
                FrequencyCounts(const std::vector<LongRead> &bf, double filterCutoff, double offset, int32_t removeUnique,
                                bool noTf, int numThreads, double range, bool doReverseCompliment)
                    : range_(range)
                    , removeUnique_(removeUnique)
                    , noTf_(noTf) {

                }

                //FIXME:
                bool keepKmer(const int64_t &str) { return true; }
                bool isPopular(const int64_t &str) { return true; }
                double tfWeight(int a) { return 0; }
                double scaledIdf(const int64_t &str) { return 0; }

            private:
                double filterCutoff;
                std::unordered_map<long, double> fractionCounts;
                std::unordered_set<int32_t> kmerSizes;
                double maxIdfValue;
                double maxValue;
                double minIdfValue;
                double minValue;
                double offset;
                double range_;
                int32_t removeUnique_;
                bool noTf_;
                //common::BloomFilter<long> validMers;
            };
        }
    }
}

#endif //FREQUENCYCOUNTS_HPP

