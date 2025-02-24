/**
 * \file KMerCounter.hpp
 * \brief the C++ file with declaration of class for calculating number of occurrence of each k-mer in input set of reads
 *
 */

#ifndef KMER_COUNTER_HPP
#define KMER_COUNTER_HPP

#include <mt4cpp/Scheduler.hpp>
#include "../common/FileReader.hpp"
#include "globals.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to calculate number of occurrence of each k-mer in input set of reads.
     */
    class KMerCounter {
    public:

        /**
        * \brief KMerCounter constructor.
        */
        CALC_DLL(KMerCounter(FileReader& fileReader, unsigned short K1, unsigned short qualityThreshold, std::string kmerOccurrenceTableFilename, mt4cpp::Progress* progress);)

        CALC_DLL(void calcKMersOccurrenceTable();)

    private:
        FileReader& fileReader_;
        unsigned short K1_;
        unsigned short qualityThreshold_;
        DnaSequenceRepresentationConverter dnaSequenceRepresentationConverter_;
        std::string kmerOccurrenceTableFilename_;
        mt4cpp::Progress* progress_;

        CALC_DLL(void addKMersFromReadToOccurrenceTable(HashTable& hashTable, const std::string& read, const std::string& complementaryRead);)

    };

}}

#endif    //KMER_COUNTER_HPP
