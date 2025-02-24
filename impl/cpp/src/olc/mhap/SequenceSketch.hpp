#ifndef SEQUENCESKETCH_HPP
#define SEQUENCESKETCH_HPP

#include <memory>
#include "MinHashSketch.hpp"
#include "BottomOverlapSketch.hpp"
#include "FrequencyCounts.hpp"
#include "Sequence.hpp"
#include "SequenceId.hpp"

namespace dnaasm {
    namespace olc {
        namespace mhap {

            class SequenceSketch {
            public:
                SequenceSketch(Sequence seq, int32_t kmerSize, int32_t numHashes, int32_t orderedKmerSize,
                               int32_t orderedSketchSize, FreqCountPtr &kmerFilter,
                               bool doReverseCompliment, double repeatWeight)
                        : sequenceLength_(seq.length())
                        , id_(seq.getSequenceId())
                        //UNUSED: doReverseCompliment
                        , mainHashes_(seq.getSequenceString(), kmerSize, numHashes, kmerFilter, false, repeatWeight)
                        , orderedHashes_(seq.getSequenceString(), orderedKmerSize, orderedSketchSize, false) {}

                 const SequenceId &getSequenceId() const { return id_; }
                 MinHashSketch &getMinHashes() { return mainHashes_; }
                 int32_t getSequenceLength() const { return sequenceLength_; }
                 BottomOverlapSketch &getOrderedHashes() { return orderedHashes_; }
            private:
                int32_t sequenceLength_;
                SequenceId id_;
                MinHashSketch mainHashes_;
                BottomOverlapSketch orderedHashes_;
            };
            using SequenceSketchPtr = std::unique_ptr<SequenceSketch>;
        }
    }
}

#endif /* SEQUENCESKETCH_HPP */
