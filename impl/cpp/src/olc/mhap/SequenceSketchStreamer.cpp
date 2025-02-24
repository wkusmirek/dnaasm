#include "SequenceSketchStreamer.hpp"
#include <algorithm>
#include <iostream>

namespace dnaasm {
    namespace olc {
        namespace mhap {
            SequenceSketchStreamer::SequenceSketchStreamer(std::istream &longReadsFile, int32_t minOlapLength, int32_t kmerSize, int32_t numHashes,
                                   int32_t orderedKmerSize, int32_t orderedSketchSize, FreqCountPtr &kmerFilter,
                                   bool doReverseCompliment, double repeatWeight, int32_t offset)
                    : minOlapLength_(minOlapLength)
                    , kmerSize_(kmerSize)
                    , numHashes_(numHashes)
                    , orderedKmerSize_(orderedKmerSize)
                    , orderedSketchSize_(orderedSketchSize)
                    , kmerFilter_(kmerFilter)
                    , doReverseCompliment_(doReverseCompliment)
                    , repeatWeight_(repeatWeight)
                    , fastaData_(longReadsFile)
                    {}

            SequenceSketch SequenceSketchStreamer::dequeue(bool fwdOnly) {
                //ensure not empty (enqueue unfil found?)
                //FIXME: fast workaround to hold all sequences and
                // sketches in program memory
                // load only some part in order to optimize memory
                // usage
                //enqueueUntilFound(fwdOnly);
                auto seqSketch = std::move(sequenceHashList_.front());
                sequenceHashList_.pop_front();

                return seqSketch;
            }

            bool SequenceSketchStreamer::enqueue(bool fwdOnly) {
                Sequence seq;
                do {
                    seq = fastaData_.dequeue();
                } while (!seq.getSequenceString().empty() && seq.length() < minOlapLength_);

                if (!seq.getSequenceString().empty()) {
                    sequenceHashList_.emplace_back(getSketch(seq));
                } else {
                    return false;
                }

                ++numberProcessed_;

                if (!fwdOnly) {
                    sequenceHashList_.emplace_back(getSketch(seq.getReverseCompliment()));
                    ++numberProcessed_;
                }

                return true;
            }

            void SequenceSketchStreamer::enqueueFullFile(bool fwdOnly) {
                while (enqueueUntilFound(fwdOnly)) {}
            }

            bool SequenceSketchStreamer::enqueueUntilFound(bool fwdOnly) {
                bool getNext = true;
                bool returnValue = false;

                while (getNext) {
                    returnValue = enqueue(fwdOnly);
                    getNext = false;
                }

                return returnValue;
            }

            SequenceSketch SequenceSketchStreamer::getSketch(const Sequence &seq) {
                return SequenceSketch(seq, kmerSize_, numHashes_, orderedKmerSize_, orderedSketchSize_, kmerFilter_,
                                      doReverseCompliment_, repeatWeight_);
            }

            std::string SequenceSketchStreamer::getReverseCompliment(const std::string &read) {
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
        }
    }
}

