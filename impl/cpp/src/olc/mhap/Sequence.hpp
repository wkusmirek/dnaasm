#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include "SequenceId.hpp"
#include <algorithm>
#include <string>

namespace dnaasm {
    namespace olc {
        namespace mhap {
            class Sequence {
            public:
                Sequence() {}
                Sequence(const std::string &seq, const SequenceId &id) : sequence_(seq), id_(id) {}
                ~Sequence() = default;

                std::string getSequenceString() const { return sequence_; }

                SequenceId getSequenceId() const { return id_; }

                Sequence getReverseCompliment() {
                    return Sequence(getReverseComplimentSeq(sequence_), id_.complimentId());
                }

                std::string getKmer(int32_t index, int32_t kmerSize) const {
                    return sequence_.substr(index, kmerSize);
                }

                int32_t numKmers(int32_t kmerSize) const { return sequence_.length() -kmerSize + 1; }
                size_t length() const { return sequence_.length(); }

            private:
                std::string sequence_;
                SequenceId id_;

                std::string getReverseComplimentSeq(const std::string &read) {
                    std::string reverseCompliment{read};
                    std::reverse(reverseCompliment.begin(), reverseCompliment.end());

                    for (auto &l : reverseCompliment) {
                        switch (l) {
                            case 'A':
                                l = 'T';
                                break;
                            case 'T':
                                l = 'A';
                                break;
                            case 'C':
                                l = 'G';
                                break;
                            case 'G':
                                l = 'C';
                                break;
                        }
                    }

                    return reverseCompliment;
                }
            };
        }
    }
}

#endif //SEQUENCE_HPP