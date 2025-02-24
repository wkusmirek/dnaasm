/**
 * \file Mismatch.cpp
 * \brief the C++ file with implementation of class for representing single mismatch sequence with index in reference genome
 *
 */

#include "Mismatch.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    Mismatch::Mismatch(): sequenceMismatch_(""), referenceMismatch_(""), originalRefIdx_(0U), sequenceId_(".") {}

    Mismatch::Mismatch(string& sequenceMismatch,
                       string& referenceMismatch,
                       unsigned int originalRefIdx,
                       string& sequenceId)
        : sequenceMismatch_(sequenceMismatch)
        , referenceMismatch_(referenceMismatch)
        , originalRefIdx_(originalRefIdx)
        , sequenceId_(sequenceId)
    {}

    void Mismatch::appointCircular(unsigned int & originalRefIdx,
                                   unsigned int & actualSeqIdx,
                                   unsigned int & actualRefIdx,
                                   string sequence,
                                   string reference,
                                   unsigned int orgRefSize,
                                   string sequenceId) {
        sequenceId_ = sequenceId;

        if (sequence[actualSeqIdx] == reference[actualRefIdx]) {
            return;
        } else if (sequence[actualSeqIdx] != '-' && reference[actualRefIdx] != '-') {
            sequenceMismatch_ = sequence[actualSeqIdx];
            referenceMismatch_ = reference[actualRefIdx];
            originalRefIdx_ = (originalRefIdx % orgRefSize);
            ++originalRefIdx;
            ++actualSeqIdx;
            ++actualRefIdx;
            return;
        } else if (sequence[actualSeqIdx] == '-') {
            originalRefIdx_ = ((originalRefIdx - 1)% orgRefSize);
            if (originalRefIdx_ == 0U)
                originalRefIdx_ = 1U;
            if (sequence[actualSeqIdx+1] != '-' && reference[actualRefIdx+1] == '-') {
                referenceMismatch_ = reference[actualRefIdx];
                sequenceMismatch_ = sequence[actualSeqIdx+1];
                actualRefIdx += 2;
                actualSeqIdx += 2;
                ++originalRefIdx;
                while (sequence[actualSeqIdx+1] == '-') {
                    ++originalRefIdx;
                    ++actualSeqIdx;
                    ++actualRefIdx;
                    referenceMismatch_ += reference[actualRefIdx+1];
                }
                return;
            }

            if (actualSeqIdx == 0)
                sequenceMismatch_ = sequence[actualSeqIdx];
            else
                sequenceMismatch_ = sequence[actualSeqIdx-1];

            if (actualRefIdx == 0)
                referenceMismatch_ = reference[actualRefIdx];
            else
                referenceMismatch_ = reference[actualRefIdx-1];

            while (sequence[actualSeqIdx] == '-') {
                referenceMismatch_ += reference[actualRefIdx];
                ++originalRefIdx;
                ++actualSeqIdx;
                ++actualRefIdx;
            }
            return;
        } else if (reference[actualRefIdx] == '-') {
            originalRefIdx_ = ((originalRefIdx - 1)% orgRefSize);
            if (originalRefIdx_ == 0U)
                originalRefIdx_ = 1U;
            if (reference[actualRefIdx+1] != '-' && sequence[actualSeqIdx+1] == '-') {
                referenceMismatch_ = reference[actualRefIdx+1];
                sequenceMismatch_ = sequence[actualSeqIdx];
                actualRefIdx += 2;
                actualSeqIdx += 2;
                ++originalRefIdx;
                while (reference[actualRefIdx+1] == '-') {
                    ++originalRefIdx;
                    ++actualSeqIdx;
                    ++actualRefIdx;
                    sequenceMismatch_ += sequence[actualSeqIdx+1];
                }
                return;
            }

            if (actualSeqIdx == 0)
                sequenceMismatch_ = sequence[actualSeqIdx];
            else
                sequenceMismatch_ = sequence[actualSeqIdx-1];

            if (actualRefIdx == 0)
                referenceMismatch_ = reference[actualRefIdx];
            else
                referenceMismatch_ = reference[actualRefIdx-1];

            while (reference[actualRefIdx] == '-') {
                sequenceMismatch_ += sequence[actualSeqIdx];
                ++actualSeqIdx;
                ++actualRefIdx;
            }
            return;
        }
        return;
    }

    void Mismatch::appointLinear(unsigned int & originalRefIdx,
                                 unsigned int & actualSeqIdx,
                                 unsigned int & actualRefIdx,
                                 string sequence,
                                 string reference,
                                 string sequenceId) {
        sequenceId_ = sequenceId;

        if (sequence[actualSeqIdx] == reference[actualRefIdx]) {
            return;

        } else if (sequence[actualSeqIdx] != '-' && reference[actualRefIdx] != '-') {
            sequenceMismatch_ = sequence[actualSeqIdx];
            referenceMismatch_ = reference[actualRefIdx];
            originalRefIdx_ = originalRefIdx;
            ++originalRefIdx;
            ++actualSeqIdx;
            ++actualRefIdx;
            return;
        } else if (sequence[actualSeqIdx] == '-') {
            originalRefIdx_ = originalRefIdx - 1U;
            if (originalRefIdx_ == 0U)
                originalRefIdx_ = 1U;
            if (sequence[actualSeqIdx+1] != '-' && reference[actualRefIdx+1] == '-') {
                referenceMismatch_ = reference[actualRefIdx];
                sequenceMismatch_ = sequence[actualSeqIdx+1];
                actualRefIdx += 2;
                actualSeqIdx += 2;
                ++originalRefIdx;
                while (sequence[actualSeqIdx+1] == '-') {
                    ++originalRefIdx;
                    ++actualSeqIdx;
                    ++actualRefIdx;
                    referenceMismatch_ += reference[actualRefIdx+1];
                }
                return;
            }

            if (actualSeqIdx == 0) {
                unsigned int tmp = actualSeqIdx;
                while (tmp < sequence.length()&& sequence[tmp] == '-') {
                    ++tmp;
                }
                sequenceMismatch_ = sequence[tmp];
            } else {
                sequenceMismatch_ = sequence[actualSeqIdx-1];
            }

            if (actualRefIdx == 0) {
                referenceMismatch_ = reference[actualRefIdx];

                while (sequence[actualSeqIdx] == '-') {
                    referenceMismatch_ += reference[actualRefIdx+1];
                    ++originalRefIdx;
                    ++actualSeqIdx;
                    ++actualRefIdx;
                }
            } else {
                referenceMismatch_ = reference[actualRefIdx-1];

                while (sequence[actualSeqIdx] == '-') {
                    referenceMismatch_ += reference[actualRefIdx];
                    ++originalRefIdx;
                    ++actualSeqIdx;
                    ++actualRefIdx;
                }
            }
            return;
        } else if (reference[actualRefIdx] == '-') {
            originalRefIdx_ = originalRefIdx - 1U;

            if (originalRefIdx_ == 0U)
                originalRefIdx_ = 1U;

            if (reference[actualRefIdx+1] != '-' && sequence[actualSeqIdx+1] == '-') {
                referenceMismatch_ = reference[actualRefIdx+1];
                sequenceMismatch_ = sequence[actualSeqIdx];
                actualRefIdx += 2;
                actualSeqIdx += 2;
                ++originalRefIdx;

                while (reference[actualRefIdx+1] == '-') {
                    ++originalRefIdx;
                    ++actualSeqIdx;
                    ++actualRefIdx;
                    sequenceMismatch_ += sequence[actualSeqIdx+1];
                }
                return;
            }

            if (actualRefIdx == 0) {
                unsigned int tmp = actualRefIdx;
                while (tmp < reference.length()&& reference[tmp] == '-') {
                    ++tmp;
                }
                referenceMismatch_ = reference[tmp];
            } else {
                referenceMismatch_ = reference[actualRefIdx-1];
            }

            if (actualSeqIdx == 0) {
                sequenceMismatch_ = sequence[actualSeqIdx];

                while (reference[actualRefIdx] == '-') {
                    sequenceMismatch_ += sequence[actualSeqIdx+1];
                    ++actualRefIdx;
                    ++actualSeqIdx;
                }
            } else {
                sequenceMismatch_ = sequence[actualSeqIdx-1];
                while (reference[actualRefIdx] == '-') {
                    sequenceMismatch_ += sequence[actualSeqIdx];
                    ++actualRefIdx;
                    ++actualSeqIdx;
                }
            }
            return;
        }
        return;
    }

    string Mismatch::getSequenceMismatch() const {
        return sequenceMismatch_;
    }

    string Mismatch::getReferenceMismatch() const {
        return  referenceMismatch_;
    }

    unsigned int Mismatch::getOriginalRefIdx() const {
        return originalRefIdx_;
    }

    string Mismatch::getSequenceId() const {
        return sequenceId_;
    }
}}

