/**
 * \file DnaSequenceRepresentationConverter.hpp
 * \brief the C++ file with declaration of class for converting different representation of DNA sequence (string to bitset and bitset to string)
 *
 */

#ifndef DNA_SEQUENCE_REPRESENTATION_CONVERTER_HPP
#define DNA_SEQUENCE_REPRESENTATION_CONVERTER_HPP

#include <string>
#include <bitset>

#include "common.hpp"

namespace dnaasm {

    /**
     * \brief Class to convert different representation of DNA sequence (string to bitset and bitset to string).
     */
    class DnaSequenceRepresentationConverter {

    public:

        /**
         * \brief DnaSequenceRepresentationConverter constructor.
         *
         * \param sequenceLength length of DNA sequence to convert [bp]
         */
        CALC_DLL(explicit DnaSequenceRepresentationConverter(unsigned short sequenceLength);)

        /**
         * \brief Converts DNA sequence from bitset to string.
         *
         * \param bitsetRepresentation DNA sequence in bitset representation
         * \return returns DNA sequence in string representation
         */
        CALC_DLL(std::string convertToString(const std::bitset<2*MAX_KMER_LENGTH>& bitsetRepresentation) const;)

        /**
         * \brief Converts DNA sequence from string to bitset.
         *
         * \param stringRepresentation DNA sequence in string representation
         * \return returns DNA sequence in bitset representation
         */
        CALC_DLL(std::bitset<2*MAX_KMER_LENGTH> convertToBitset(const char * stringRepresentation) const;)

    private:
        unsigned short sequenceLength_;
        DnaSequenceRepresentationConverter& operator=(const DnaSequenceRepresentationConverter&)= delete;
    };


}

#endif    //DNA_SEQUENCE_REPRESENTATION_CONVERTER_HPP
