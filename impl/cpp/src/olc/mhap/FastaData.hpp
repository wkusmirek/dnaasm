#ifndef FASTADATA_HPP
#define FASTADATA_HPP

#include "../../common/FileReader.hpp"
#include "../../common/InputFile.hpp"
#include "Sequence.hpp"
#include <deque>

namespace dnaasm {
    namespace olc {
        namespace mhap {
            class FastaData {
            public:
                FastaData(std::istream &file);

                Sequence dequeue();

                bool enqueueNextSequenceInFile();

                int64_t getNumberProcessed() const { return numberProcessed_; }

                bool isEmpty() const { return sequenceList_.empty() && !inputFile_.getIsMoreSequences(); }

            private:
                std::deque<Sequence> sequenceList_;
                FileReader fileReader_;
                int32_t offset_;
                InputFile inputFile_;
                int64_t numberProcessed_;
                bool readFullFile_;

            };
        }
    }
}

#endif //FASTADATA_HPP