#ifndef ABSTRACTMATCHSEARCH_HPP
#define ABSTRACTMATCHSEARCH_HPP

#include "MatchResult.hpp"
#include "SequenceSketchStreamer.hpp"
#include <initializer_list>

namespace dnaasm {
    namespace olc {
        namespace mhap {
            class AbstractMatchSearch {
            public:
                AbstractMatchSearch() {}
                virtual bool addSequence(SequenceSketch &currHash) = 0;
                virtual std::deque<SequenceId> getStoredForwardSequenceIds() = 0;
                virtual SequenceSketch getStoredSequenceHash(SequenceId &id) = 0;
                virtual std::vector<MatchResult> findMatches();
            protected:
                void addData(SequenceSketchStreamer &data, bool doReverseCompliment);
                virtual std::vector<MatchResult> findMatches(SequenceSketch &hashes, bool toSelf) = 0;
            };
        }
    }
}

#endif //ABSTRACTMATCHSEARCH_HPP