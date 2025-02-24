/**
 * \file SequenceAlignment.cpp
 * \brief the C++ file with implementation of class for aligning DNA sequence to reference genome
 *
 */

#include "SequenceAlignment.hpp"
#include "HirschbergAlgorithm.hpp"
#include "NeedlemanWunschAlgorithm.hpp"
#include "../common/log.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    SequenceAlignment::SequenceAlignment(string& sequence,
                                         string& reference,
                                         string& sequenceId,
                                         short int d,
                                         short int substitutionMatrixValues[16],
                                         mt4cpp::Progress* progress,
                                         unsigned int numOfAlignedSequences,
                                         unsigned int numOfSequences)
        : sequence_(sequence)
        , reference_(reference)
        , sequenceId_(sequenceId)
        , d_(d)
        , progress_(progress)
        , numOfAlignedSequences_(numOfAlignedSequences)
        , numOfSequences_(numOfSequences)
    { buildSubstitutionMatrix(substitutionMatrixValues); }

    void SequenceAlignment::buildSubstitutionMatrix(short int * substitutionMatrixValues) {
        int k = 0;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                substitutionMatrix_[i][j] = substitutionMatrixValues[k++];
            }
        }
        return;
    }

    vector<Mismatch>& SequenceAlignment::alignSeqNeeWunAlg(bool isCircular) {
        if (sequence_.length() == 0 || reference_.length() == 0) {
            return mismatches_;
        }

        if (isCircular) {
            reference_ += reference_;
        }

        NeedlemanWunschAlgorithm needlemanWunschAlgorithm(sequence_,
                                                          reference_,
                                                          d_,
                                                          substitutionMatrix_,
                                                          progress_,
                                                          numOfAlignedSequences_,
                                                          numOfSequences_);
        needlemanWunschAlgorithm.align(!isCircular);    //if isCircular = true, then without ends penalties
        outputSequence_ = needlemanWunschAlgorithm.getXStrOut();
        outputReference_ = needlemanWunschAlgorithm.getYStrOut();

        if (isCircular) {
            generateMismatchesForCircularSeq();
        } else {
            generateMismatchesForLinearSeq();
        }
        return mismatches_;
    }

    vector<Mismatch>& SequenceAlignment::alignSeqHirAlg(bool isCircular) {
        if (sequence_.length() == 0 || reference_.length() == 0) {
            return mismatches_;
        }

        if (isCircular) {
            reference_ += reference_;
        }

        HirschbergAlgorithm hirschbergAlgorithm(d_,
                                                substitutionMatrix_,
                                                progress_,
                                                numOfAlignedSequences_,
                                                numOfSequences_);
        HirschbergAlgorithm::OutStrings resultHirschbergAlgorithm = hirschbergAlgorithm.align(sequence_, reference_, !isCircular);
        //if isCircular = true, then without ends penalties
        outputSequence_ = resultHirschbergAlgorithm.xStrOut;
        outputReference_ = resultHirschbergAlgorithm.yStrOut;

        if (isCircular) {
            generateMismatchesForCircularSeq();
        } else {
            generateMismatchesForLinearSeq();
        }
        return mismatches_;
    }

    void SequenceAlignment::generateMismatchesForCircularSeq() {
        //trimming sequence - removing start and end '-' sequences
        reverse(outputSequence_.begin(), outputSequence_.end());
        size_t lastNuc = outputSequence_.find_first_of("ACGTN");
        lastNuc = outputSequence_.length()- lastNuc;
        reverse(outputSequence_.begin(), outputSequence_.end());
        size_t firstNuc = outputSequence_.find_first_of("ACGTN");
        unsigned int actualNucRefIdx = static_cast<unsigned int>(firstNuc);
        unsigned int actualNucSeqIdx = static_cast<unsigned int>(firstNuc);
        unsigned int orgRefPos = static_cast<unsigned int>(firstNuc + 1);    //orgRefPos begin in '1' (not 0)

        while (true) {
            if (actualNucSeqIdx == static_cast<unsigned int>(lastNuc) || actualNucRefIdx == reference_.length()) {
                break;
            }

            if (outputReference_[actualNucRefIdx] != outputSequence_[actualNucSeqIdx]) {
                Mismatch mismatch;
                mismatch.appointCircular(orgRefPos,
                                         actualNucSeqIdx,
                                         actualNucRefIdx,
                                         outputSequence_,
                                         outputReference_,
                                         static_cast<unsigned int>((reference_.size())/2), sequenceId_);
                mismatches_.push_back(mismatch);
            } else {
                ++actualNucSeqIdx;
                ++actualNucRefIdx;
                ++orgRefPos;
            }
        }
    }

    void SequenceAlignment::generateMismatchesForLinearSeq() {
        unsigned int actualNucRefIdx = 0U;
        unsigned int actualNucSeqIdx = 0U;
        unsigned int orgRefPos = 1U;
        while (true) {

            if (actualNucRefIdx >= outputReference_.length()&& actualNucRefIdx >= outputSequence_.length()) {
                break;
            }

            if (outputReference_[actualNucRefIdx] != outputSequence_[actualNucSeqIdx]) {
                Mismatch mismatch;
                mismatch.appointLinear(orgRefPos, actualNucSeqIdx, actualNucRefIdx, outputSequence_, outputReference_, sequenceId_);
                mismatches_.push_back(mismatch);
            } else {
                ++actualNucSeqIdx;
                ++actualNucRefIdx;
                ++orgRefPos;
            }
        }
    }

    string SequenceAlignment::getOutputSequence() const {
        return outputSequence_;
    }

    string SequenceAlignment::getOutputReference() const {
        return outputReference_;
    }

}}

