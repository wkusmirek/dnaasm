#ifndef MINHASHSEARCH_HPP
#define MINHASHSEARCH_HPP

#include "SequenceSketchStreamer.hpp"
#include "AbstractMatchSearch.hpp"
#include <unordered_map>
#include "SequenceId.hpp"
#include <deque>

namespace dnaasm {
    namespace olc {
        namespace mhap {

            class MinHashSearch : public AbstractMatchSearch {

            public:
                MinHashSearch(SequenceSketchStreamer &data, int32_t numHashes, int32_t numMinMatches,
                              int32_t numThreads, bool storeResults, int32_t minStoreLength,
                              double maxShift, double acceptScore, bool doReverseCompliment);

                virtual bool addSequence(SequenceSketch &currHash) override;
                virtual std::deque<SequenceId> getStoredForwardSequenceIds() override;
                virtual SequenceSketch getStoredSequenceHash(SequenceId &id) override;
                std::vector<MatchResult> findMatches() { return AbstractMatchSearch::findMatches(); }
            protected:
                virtual std::vector<MatchResult> findMatches(SequenceSketch &hashes, bool toSelf) override;

            private:
                int32_t numMinMatches_;
                double maxShift;
                int32_t minStoreLength_;
                double acceptScore_;

                using Int2ObjectOpenHashMap = std::unordered_map<int32_t, std::vector<SequenceId>>;
                std::vector<Int2ObjectOpenHashMap> hashes_;
                std::unordered_map<SequenceId, SequenceSketch, SequenceIdHash> sequenceVectorsHash_;
            };
        }
    }
}
#endif /* MINHASHSEARCH_HPP */
