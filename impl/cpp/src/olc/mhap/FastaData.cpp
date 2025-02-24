#include "FastaData.hpp"

namespace dnaasm {
    namespace olc {
        namespace mhap {
            FastaData::FastaData(std::istream &file) : offset_(0), inputFile_(file), numberProcessed_(0U) {
                fileReader_.setInputFile1(&inputFile_);
            }

            Sequence FastaData::dequeue() {
                if (sequenceList_.empty()) {
                    if (!enqueueNextSequenceInFile()) {
                        return Sequence();
                    }
                }

                auto seq = std::move(sequenceList_.front());
                sequenceList_.pop_front();

                return seq;
            }

            bool FastaData::enqueueNextSequenceInFile() {
                if (!inputFile_.getIsMoreSequences()) {
                    return false;
                }

                Read readWrapper(0U);
                inputFile_.readSingleRead(readWrapper);

                auto index = numberProcessed_;
                ++numberProcessed_;

                SequenceId id(index);
                sequenceList_.emplace_back(readWrapper.getRead(), id);
                return true;
            }
        }
    }
}