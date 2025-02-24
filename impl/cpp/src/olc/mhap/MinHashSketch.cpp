#include "MinHashSketch.hpp"
#include "HashUtils.hpp"

namespace dnaasm {
    namespace olc {
        namespace mhap {
            std::vector<int>
            MinHashSketch::computeNgramMinHashesWeighted(LongRead &seq, int32_t nGramSize,
                                                         int32_t numHashes, FreqCountPtr &kmerFilter,
                                                         bool doReverseCompliment, double repeatWeight) {
                //int numberNgrams = seq.length() - nGramSize + 1;
                //TODO: is check < 1 really necessary?
                std::vector<int64_t>
                        kmerHashes(HashUtils::computeSequenceHashesLong(seq, nGramSize, 0, doReverseCompliment));

                std::unordered_map<int64_t, HitCounter> hitMap;//(kmerHashes.size());

                for (const auto &kmer : kmerHashes) {

                    if (kmerFilter && !kmerFilter->keepKmer(kmer))
                        continue;

                    if (hitMap.find(kmer) == hitMap.end()) {
                        hitMap.emplace(kmer, HitCounter(1));
                    } else {
                        hitMap[kmer].addHit();
                    }
                }

                if (hitMap.empty()) {
                    throw std::runtime_error("Found zero unfiltered n-grams in the string.");
                }

                std::vector<int32_t> hashes(std::max(1, numHashes));
                std::vector<int64_t> best(numHashes, std::numeric_limits<int64_t>::max());

                int32_t numberValid{0};

                for (auto &kmer : hitMap) {
                    //copy on purpose
                    auto key = kmer.first;
                    auto weight = kmer.second.count;

                    if (repeatWeight < 0.0) {

                        weight = 1;

                        if (kmerFilter && kmerFilter->isPopular(kmer.first))
                            weight = 0;

                    } else if (kmerFilter) {
                        if (repeatWeight >= 0.0 && repeatWeight < 1.0) {
                            double tf = static_cast<double>(kmerFilter->tfWeight(weight));
                            double idf = kmerFilter->scaledIdf(key);

                            weight = static_cast<int32_t>(round(tf * idf));

                            if (weight < 1)
                                weight = 1;
                        }
                    }

                    if (weight <= 0)
                        continue;

                    ++numberValid;

                    int64_t x = key;

                    for (int32_t word = 0; word < numHashes; ++word) {
                        for (int32_t count = 0; count < weight; ++count) {
                            // XORShift Random Number Generators
                            x ^= (x << 21);
                            x ^= static_cast<uint32_t>(x >> 35);
                            x ^= (x << 4);

                            if (x < best[word]) {
                                best[word] = x;
                                if (word % 2 == 0) {
                                    hashes[word] = static_cast<int32_t>(key);
                                } else {
                                    hashes[word] = static_cast<int32_t>(static_cast<uint32_t>(key >> 32));
                                }
                            }
                        }
                    }
                }

                if (numberValid <= 0) {
                    throw std::runtime_error("Found zero unfiltered n-grams in the string.");
                }

                return hashes;
            }
        }
    }
}
