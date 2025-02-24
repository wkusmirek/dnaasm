/**
 * \file HirschbergAlgorithm.hpp
 * \brief the C++ file with declaration of class for Hirschberg's algorithm (to align two sequences)
 *
 */

#ifndef HIRSCHBERGALGORITHM_HPP
#define HIRSCHBERGALGORITHM_HPP

#include <mt4cpp/Scheduler.hpp>
#include <mt4cpp/CommandHistory.hpp>

#include "globals.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class for Hirschberg's algorithm (to align two sequences).
     */
    class HirschbergAlgorithm {
    public:

        typedef struct {std::string xStrOut; std::string yStrOut;} OutStrings;

        /**
         * \brief HirschbergAlgorithm constructor.
         *
         * \param d gap penalty
         * \param substitutionMatrixValues vaues for similarity matrix (ACGT x ACGT)
         * \param progress actual task's progress
         * \param numOfAlignedSequences number of sequences, which was aligned, needed to count actual task progress
         * \param numOfSequences number of sequences in sequence input file, needed to count actual task progress
         */
        CALC_DLL(HirschbergAlgorithm(short int d, 
                                     short int (&substitutionMatrix)[4][4],
                                     mt4cpp::Progress* progress, 
                                     unsigned int numOfAlignedSequences, 
                                     unsigned int numOfSequences);
                )

        /**
         * \brief Aligns sequences using Hirschberg algorithm.
         *
         * \param xStr first sequence, which will be aligned
         * \param yStr second sequence, which will be aligned
         * \param withEndsPenalty parameter, which indicates if panalties should be used for both ends
         * \return returns two output sequences (one for each input sequence)
         */
        CALC_DLL(OutStrings align(std::string& xStr, std::string& yStr, bool withEndsPenalty);)


    private:
        short int d_;
        short int (&substitutionMatrix_)[4][4];    //ACGT x ACGT
        mt4cpp::Progress* progress_;
        unsigned int numOfAlignedSequences_;
        unsigned int numOfSequences_;
        unsigned int sumForCounter_;        //to estimate progress
        unsigned int counter_;    //to estimate progress
        HirschbergAlgorithm& operator=(const HirschbergAlgorithm&)= delete;

        /**
         * \brief Gets last column of Needleman-Wunsch score matrix.
         *
         * \param x first sequence, which will be aligned
         * \param y second sequence, which will be aligned
         * \param withEndsPenalty parameter, which indicates if panalties should be used for both ends
         * \return returns the last column of the Needleman-Wunsch score matrix
         */
        CALC_DLL(std::vector<int> lastAlignColumn(std::string& x, std::string& y, bool withEndsPenalty);)

        /**
         * \brief Finds the best y for two vector of scores (argument of the maximum).
         *
         * \param leftScore vector of first scores
         * \param rightScore vector of second scores
         * \return value of middle y
         */
        CALC_DLL(unsigned int partitionY(std::vector<int>& leftScore, std::vector<int>& rightScore);)

    };

}}

#endif    //HIRSCHBERGALGORITHM_HPP
