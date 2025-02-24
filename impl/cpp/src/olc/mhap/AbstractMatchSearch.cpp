#include "AbstractMatchSearch.hpp"
#include "SequenceSketch.hpp"


namespace dnaasm {
    namespace olc {
        namespace mhap {
            void AbstractMatchSearch::addData(SequenceSketchStreamer &data, bool doReverseCompliment) {
                //SequenceSketch seqHashes = data.dequeue(!doReverseCompliment,)
                auto seqHashes = data.dequeue(!doReverseCompliment);

                while (data.canDequeue()) {
                    addSequence(seqHashes);
                    seqHashes = data.dequeue(false);
                }
            }

            std::vector<MatchResult> AbstractMatchSearch::findMatches() {
                std::vector<MatchResult> combinedList;
                std::deque<SequenceId> seqList(getStoredForwardSequenceIds());

                std::vector<MatchResult> localMatches;

                SequenceId nextSequence = std::move(seqList.front());
                seqList.pop_front();

                while (!seqList.empty()) {
                    auto sequenceHashes = getStoredSequenceHash(nextSequence);

                    auto matches = findMatches(sequenceHashes, true);
                    //localMatches.emplace_back()
                    std::move(matches.begin(), matches.end(), std::back_inserter(localMatches));

                    nextSequence = std::move(seqList.front());
                    seqList.pop_front();

                    //std::move(matches.begin(), matches.end(), std::back_inserter(localMatches));
                }

                //return combinedList;
                return localMatches;
            }
        }
    }
}
