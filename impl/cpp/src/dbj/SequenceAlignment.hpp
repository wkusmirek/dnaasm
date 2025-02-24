/**
 * \file SequenceAlignment.hpp
 * \brief the C++ file with declaration of class for aligning DNA sequence to reference genome
 *
 */

#ifndef SEQUENCEALIGNMENT_HPP
#define SEQUENCEALIGNMENT_HPP

#include <mt4cpp/Scheduler.hpp>
#include <mt4cpp/CommandHistory.hpp>

#include "Mismatch.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to align DNA sequence to reference genome.
     */
    class SequenceAlignment {
    public:

        /**
         * \brief SequenceAlignment constructor.
         *
         * \param sequence DNA sequence which will be aligment to reference genome
         * \param reference DNA genome reference
         * \param sequenceId actual sequence id
         * \param d gap penalty
         * \param substitutionMatrixValues vaues for similarity matrix (ACGT x ACGT)
         * \param progress actual task's progress
         * \param numOfAlignedSequences number of sequences, which was aligned, needed to count actual task progress
         * \param numOfSequences number of sequences in sequence input file, needed to count actual task progress
         */
        CALC_DLL(SequenceAlignment(std::string& sequence,
                                   std::string& reference,
                                   std::string& sequenceId,
                                   short int d,
                                   short int substitutionMatrixValues[16],
                                   mt4cpp::Progress* progress,
                                   unsigned int numOfAlignedSequences,
                                   unsigned int numOfSequences);
                )

        /**
         * \brief Aligns sequences using Hirschberg algorithm.
         *
         * \param isCircular true - genome is circular, false - genome is linear
         * \return returns vector of mismatches
         */
        CALC_DLL(std::vector<Mismatch>& alignSeqHirAlg(bool isCircular);)

        /**
         * \brief Aligns sequences using Needleman-Wunsch algorithm.
         *
         * \param isCircular true - genome is circular, false - genome is linear
         * \return returns vector of mismatches
         */
        CALC_DLL(std::vector<Mismatch>& alignSeqNeeWunAlg(bool isCircular);)

        /**
         * \brief Gets alignment result for sequence.
         *
         * \return returns output sequence - result for sequence
         */
        CALC_DLL(std::string getOutputSequence() const;)

        /**
         * \brief Gets alignment result for reference.
         *
         * \return returns output reference - result for reference
         */
        CALC_DLL(std::string getOutputReference() const;)

    private:
        std::string& sequence_;
        std::string reference_;
        std::string& sequenceId_;
        short int d_;
        short int substitutionMatrix_[4][4];    //ACGT x ACGT
        std::string outputSequence_;
        std::string outputReference_;
        std::vector<Mismatch> mismatches_;
        mt4cpp::Progress* progress_;
        unsigned int numOfAlignedSequences_;
        unsigned int numOfSequences_;
        SequenceAlignment& operator=(const SequenceAlignment&)= delete;

        /**
         * \brief Builds substitution matrix from set of values.
         *
         * \param substitutionMatrixValues values which will be inserted in substitution matrix
         * \return returns void
         */
        CALC_DLL(void buildSubstitutionMatrix(short int substitutionMatrixValues[16]);)

        /**
         * \brief Generates set of mismatches for circular genome.
         *
         * \return returns void
         */
        CALC_DLL(void generateMismatchesForCircularSeq();)

        /**
         * \brief Generates set of mismatches for linear genome.
         *
         * \return returns void
         */
        CALC_DLL(void generateMismatchesForLinearSeq();)

    };

}}

#endif    //SEQUENCEALIGNMENT_HPP
