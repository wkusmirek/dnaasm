#ifndef SEQUENCESKETCHSTREAMER_HPP
#define SEQUENCESKETCHSTREAMER_HPP

#include "../common.hpp"
#include "FrequencyCounts.hpp"
#include "SequenceSketch.hpp"
#include "FastaData.hpp"
#include "../../common/FileReader.hpp"
#include "../../common/InputFile.hpp"
#include <deque>
#include <string>

namespace dnaasm {
    namespace olc {
        namespace mhap {

            class SequenceSketchStreamer {
            public:
                //SequenceSketchStreamer() {}
                SequenceSketchStreamer(std::istream &longReadsFile, int32_t minOlapLength, int32_t kmerSize, int32_t numHashes,
                                       int32_t orderedKmerSize, int32_t orderedSketchSize,
                                       FreqCountPtr &kmerFilter, bool doReverseCompliment, double repeatWeight,
                                       int32_t offset);
                void enqueueFullFile(bool fwdOnly);
                int32_t getNumberProcessed() const { return numberProcessed_; }
                bool canDequeue() const {return !sequenceHashList_.empty(); };
            private:
                int32_t minOlapLength_;
                int32_t kmerSize_;
                int32_t numHashes_;
                int32_t orderedKmerSize_;
                int32_t orderedSketchSize_;
                int32_t numberProcessed_;
                FreqCountPtr &kmerFilter_;
                bool doReverseCompliment_;
                double repeatWeight_;
                //ReadVector reads;
                FastaData fastaData_;
                std::deque<SequenceSketch> sequenceHashList_;

                bool enqueue(bool fwdOnly);
                bool enqueueUntilFound(bool fwdOnly);

            protected:
                SequenceSketch getSketch(const Sequence &seq);

            public:
                static std::string getReverseCompliment(const std::string &read);
                SequenceSketch dequeue(bool fwdOnly);
            };
        }
    }
}

#endif /* SEQUENCESKETCHSTREAMER_HPP */
