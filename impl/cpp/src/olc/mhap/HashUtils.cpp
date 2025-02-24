#include "HashUtils.hpp"
#include <algorithm>
#include "SequenceSketchStreamer.hpp"
#include "../../common/MurmurHash3.hpp"

namespace dnaasm {
    namespace olc {
        namespace mhap {
            std::array<uint64_t, 2> HashUtils::hash128(const LongRead &kmer, int32_t nGramSize, int32_t seed) {
                std::array<uint64_t, 2> hashValue;
                MurmurHash3_x64_128(kmer.data(), kmer.size(), 0, hashValue.data());
                return hashValue;
            }

            int32_t HashUtils::hash32(const LongRead &kmer, int32_t nGramSize, int32_t seed) {
                int32_t hashValue;
                MurmurHash3_x86_32(kmer.data(), kmer.size(), 0, &hashValue);
                return hashValue;
            }

            std::vector<int64_t>
            HashUtils::computeSequenceHashesLong(const LongRead &seq, int32_t nGramSize, int32_t seed,
                                                 bool doReverseCompliment) {
                std::vector<int64_t> hashes(seq.length() - nGramSize + 1);

                for (size_t i = 0; i < hashes.size(); ++i) {
                    //TODO: consider use of std::string_view or boost::string view instead of copying string
                    auto kmer = seq.substr(i, nGramSize);

                    if (doReverseCompliment) {

                        std::string kmerReverse(SequenceSketchStreamer::getReverseCompliment(kmer));

                        if (kmerReverse.compare(kmer) < 0) {
                            kmer = kmerReverse;
                        }

                    }

                    hashes[i] = hash128(kmer, nGramSize, seed)[0];
                    //hashes[i] = static_cast<int64_t>(std::hash<std::string>{}(kmer));
                }

                return hashes;
            }

            std::vector<int32_t>
            HashUtils::computeSequenceHashes(const LongRead &seq, int32_t nGramSize, bool doReverseCompliment) {
                std::vector<int32_t> hashes(seq.length() - nGramSize + 1);

                for (size_t i = 0; i < hashes.size(); ++i) {
                    //TODO: consider use of std::string_view or boost::string view instead of copying string
                    auto kmer = seq.substr(i, nGramSize);

                    if (doReverseCompliment) {
                        std::string kmerReverse(SequenceSketchStreamer::getReverseCompliment(kmer));

                        if (kmerReverse.compare(kmer) < 0) {
                            kmer = kmerReverse;
                        }

                    }

                    hashes[i] = hash32(kmer, nGramSize, 0);
                }

                return hashes;
            }
        }
    }
}

