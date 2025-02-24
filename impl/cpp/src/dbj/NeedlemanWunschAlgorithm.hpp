/**
 * \file NeedlemanWunschAlgorithm.hpp
 * \brief the C++ file with declaration of class for Needleman-Wunsch algorithm (to align two sequences)
 *
 */

#ifndef NEEDLEMANWUNSCHALGORITHM_HPP
#define NEEDLEMANWUNSCHALGORITHM_HPP

#include <mt4cpp/Scheduler.hpp>
#include <mt4cpp/CommandHistory.hpp>

#include "globals.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class for Needleman-Wunsch algorithm (to align two sequences).
     */
    class NeedlemanWunschAlgorithm {
    public:

        /**
         * \brief NeedlemanWunschAlgorithm constructor.
         *
         * \param xStr first sequence, which will be aligned
         * \param yStr second sequence, which will be aligned
         * \param d gap penalty
         * \param substitutionMatrixValues vaues for similarity matrix (ACGT x ACGT)
         * \param progress actual task's progress
         * \param numOfAlignedSequences number of sequences, which was aligned, needed to count actual task progress
         * \param numOfSequences number of sequences in sequence input file, needed to count actual task progress
         */
        CALC_DLL(NeedlemanWunschAlgorithm(std::string& xStr,
                                          std::string& yStr,
                                          short int d,
                                          short int (&substitutionMatrix)[4][4],
                                          mt4cpp::Progress* progress,
                                          unsigned int numOfAlignedSequences,
                                          unsigned int numOfSequences);
                )

        /**
         * \brief Aligns sequences using Needleman–Wunsch algorithm.
         *
         * \param withEndsPenalty parameter, which indicates if panalties should be used for both ends
         * \return returns void
         */
        CALC_DLL(void align(bool withEndsPenalty);)

        /**
         * \brief Gets alignment result for first sequence.
         *
         * \return returns first output sequence - result for first sequence
         */
        CALC_DLL(std::string getXStrOut() const;)

        /**
         * \brief Gets alignment result for second sequence.
         *
         * \return returns second output sequence - result for second sequence
         */
        CALC_DLL(std::string getYStrOut() const;)

    private:
        std::string& xStr_;
        std::string& yStr_;
        short int d_;
        short int (&substitutionMatrix_)[4][4];    //ACGT x ACGT
        std::string xStrOut_;
        std::string yStrOut_;
        mt4cpp::Progress* progress_;
        unsigned int numOfAlignedSequences_;
        unsigned int numOfSequences_;
        NeedlemanWunschAlgorithm& operator=(const NeedlemanWunschAlgorithm&)= delete;


        /**
         * \brief Initializes matrixes for dynamic programming and traceback.
         *
         * \param dynamicM matrix for dynamic programming
         * \param tracebackM matrix for traceback
         * \param endsPenalty value of penalty for both ends - should be equal to 0 for no penalty for both ends or equal to d_
         * \return returns void
         */
        CALC_DLL(void matrixInit(int ** dynamicM, char ** tracebackM, short int endsPenalty) const;)

        /**
         * \brief Chooses max value from set of values and stores her direction in ptr.
         *
         * \param f1 first value (for '|' direction)
         * \param f2 second value (for '\' direction)
         * \param f3 third value (for '-' direction)
         * \param ptr direction for max value ('-', '|' or '\')
         * \return returns max value for set of reads
         */
        CALC_DLL(static int max(int f1, int f2, int f3, char * ptr);)

    };

}}

#endif    //NEEDLEMANWUNSCHALGORITHM
