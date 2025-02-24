#ifndef SMITHWATERMANALIGNER_HPP
#define SMITHWATERMANALIGNER_HPP

#include <cstdint>
#include <string>
#include <limits>
#include <utility>
#include <unordered_map>
#include <functional>

#include "../common/common.hpp"

#include "common.hpp"
#include "Aligner.hpp"

namespace dnaasm {
    namespace olc {

        enum Orientation : int8_t {
            LR = 1, //left align function arg is on the left
            EQ = 0,  //both reads start on same character
            RL = -1   //left align function arg is on the right
        };

        struct LocalAlignment {
            LocalAlignment() {}

            LocalAlignment(Orientation ori, uint32_t scoreVal)
                    : orient(ori), score(scoreVal) {}

            Orientation orient;
            uint32_t score;
        };

        class SmithWatermanAligner : public Aligner<LocalAlignment> {
        public:
            enum /*class*/ Directions : int8_t {
                LEFT,
                UP,
                LEFTUP,
                NONE
            };

            using ScoreRow = std::vector<int32_t>;
            using DirRow = std::vector<Directions>;

            CALC_DLL(SmithWatermanAligner(int32_t
                             matchScore, int32_t
                             mismatchScore, int32_t
                             gapScore);)

            SmithWatermanAligner() : SmithWatermanAligner(1, -1, -1) {}

            CALC_DLL(LocalAlignment operator()(const LongRead &lhs, const LongRead &rhs)
                             override;)

            void setMatchScore(int32_t matchScore) { matchScore_ = matchScore; }

            void setMismatchScore(int32_t mismatchScore) { mismatchScore_ = mismatchScore; }

            void setGapScore(int32_t gapScore) { gapScore_ = gapScore; }

        private:
            const size_t MatrixSize_;
            int32_t matchScore_;
            int32_t mismatchScore_;
            int32_t gapScore_;
            /*
             * Workaround for use of enum as unordered map key
             * (couldn't achieve same behaviour for enum class)
             */
            using EnumHash = std::hash<std::underlying_type<Directions>::type>;
            std::unordered_map<Directions, int32_t, EnumHash> cache_;

            std::vector<ScoreRow> scoreMatrix_;
            std::vector<DirRow> dirMatrix_;

            int32_t similarityScore(Base a, Base b) const;

            Orientation getOrientation(uint32_t ind1, uint32_t ind2) const;
        };

    }
} //namespace dnaasm::olc
#endif /* SMITHWATERMANALIGNER_HPP */
