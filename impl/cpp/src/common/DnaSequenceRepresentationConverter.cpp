/**
 * \file DnaSequenceRepresentationConverter.hpp
 * \brief the C++ file with implementation of class for converting different representation of DNA sequence (string to bitset and bitset to string)
 *
 */

#include "DnaSequenceRepresentationConverter.hpp"

namespace dnaasm {

    DnaSequenceRepresentationConverter::DnaSequenceRepresentationConverter(unsigned short sequenceLength): sequenceLength_(sequenceLength) {}

    std::string DnaSequenceRepresentationConverter::convertToString(const std::bitset<2*MAX_KMER_LENGTH>& bitsetRepresentation) const {
        // 00 -> A   01 -> C   10 -> G   11 -> T
        char stringRepresentation[MAX_KMER_LENGTH];
        char * stringRepresentationPtr = stringRepresentation;

        for (unsigned short i = 0; i < sequenceLength_; ++i, ++stringRepresentationPtr) {
            if (bitsetRepresentation[2*i] == 0 && bitsetRepresentation[2*i+1] == 0) {
                *stringRepresentationPtr = 'A';
            } else if (bitsetRepresentation[2*i] == 1 && bitsetRepresentation[2*i+1] == 0) {
                *stringRepresentationPtr = 'C';
            } else if (bitsetRepresentation[2*i] == 0 && bitsetRepresentation[2*i+1] == 1) {
                *stringRepresentationPtr = 'G';
            } else if (bitsetRepresentation[2*i] == 1 && bitsetRepresentation[2*i+1] == 1) {
                *stringRepresentationPtr = 'T';
            }
        }

        *stringRepresentationPtr = '\0';
        return std::string(stringRepresentation);
    }

    std::bitset<2*MAX_KMER_LENGTH> DnaSequenceRepresentationConverter::convertToBitset(const char * stringRepresentation) const {
        // A -> 00   C -> 01   G -> 10   T -> 11
        std::bitset<2*MAX_KMER_LENGTH> bitsetRepresentation(sequenceLength_*2);

        for (unsigned short i = 0; i < sequenceLength_; ++i) {
            unsigned short firstBitPosition = 2*i;
            unsigned short secondBitPosition = 2*i+1;
            switch(stringRepresentation[i]) {
                case 'A': bitsetRepresentation[firstBitPosition] = 0; bitsetRepresentation[secondBitPosition] = 0; break;
                case 'C': bitsetRepresentation[firstBitPosition] = 1; bitsetRepresentation[secondBitPosition] = 0; break;
                case 'G': bitsetRepresentation[firstBitPosition] = 0; bitsetRepresentation[secondBitPosition] = 1; break;
                case 'T': bitsetRepresentation[firstBitPosition] = 1; bitsetRepresentation[secondBitPosition] = 1; break;
            }
        }
        return bitsetRepresentation;
    }
}
