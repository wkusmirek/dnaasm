/**
 * \file Mismatch.hpp
 * \brief the C++ file with declaration of class for representing single mismatch sequence with index in reference genome
 *
 */

#ifndef MISMATCH_HPP
#define MISMATCH_HPP

#include "globals.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to represent single mismatch sequence with index in reference genome.
     */
    class Mismatch {
    public:

        /**
         * \brief Mismatch constructor.
         */
        CALC_DLL(Mismatch();)

        /**
         * \brief Mismatch constructor.
         *
         * \param sequenceMismatch mismatch (single nucleotide or many nucletides)in sequence
         * \param referenceMismatch mismatch (single nucleotide or many nucletides)in reference genome
         * \param originalRefIdx index of mismatch in original reference genome
         */
        CALC_DLL(Mismatch(std::string& sequenceMismatch,
                          std::string& referenceMismatch,
                          unsigned int originalRefIdx,
                          std::string& sequenceId);
                )

        /**
         * \brief Appoints mismatch in sequence and circular reference genome.
         *
         * \param originalRefIdx index of mismatch in original reference genome
         * \param actualSeqIdx index of actual nucleotide in sequence
         * \param actualRefIdx index of actual nucleotide in reference
         * \param sequence DNA sequence under investigation
         * \param reference DNA genome reference
         * \param orgRefSize original DNA genome reference size
         * \param sequenceId id of sequence
         * \return returns void
         */
        CALC_DLL(void appointCircular(unsigned int & originalRefIdx,
                                      unsigned int & actualSeqIdx,
                                      unsigned int & actualRefIdx,
                                      std::string sequence,
                                      std::string reference,
                                      unsigned int orgRefSize,
                                      std::string sequenceId);
                )

        /**
         * \brief Appoints mismatch in sequence and linearreference genome.
         *
         * \param originalRefIdx index of mismatch in original reference genome
         * \param actualSeqIdx index of actual nucleotide in sequence
         * \param actualRefIdx index of actual nucleotide in reference
         * \param sequence DNA sequence under investigation
         * \param reference DNA genome reference
         * \param sequenceId id of sequence
         * \return returns void
         */
        CALC_DLL(void appointLinear(unsigned int & originalRefIdx,
                                    unsigned int & actualSeqIdx,
                                    unsigned int & actualRefIdx,
                                    std::string sequence,
                                    std::string reference,
                                    std::string sequenceId);
                )

        /**
         * \brief Gets mismatch in sequence genome.
         *
         * \return returns mismatch in sequence genome
         */
        CALC_DLL(std::string getSequenceMismatch() const;)

        /**
         * \brief Gets mismatch in reference genome.
         *
         * \return returns mismatch in reference genome
         */
        CALC_DLL(std::string getReferenceMismatch() const;)

        /**
         * \brief Gets index of mismatch in reference genome.
         *
         * \return returns index of mismatch in reference genome
         */
        CALC_DLL(unsigned int getOriginalRefIdx() const;)

        /**
         * \brief Gets sequence id for mismatch.
         *
         * \return returns sequence id for mismatch
         */
        CALC_DLL(std::string getSequenceId() const;)

    private:
        std::string sequenceMismatch_;
        std::string referenceMismatch_;
        unsigned int originalRefIdx_;
        std::string sequenceId_;
    };

}}

#endif    //MISMATCH
