/**
 * \file KMerCounter.hpp
 * \brief the C++ file with implementation of class for calculating number of occurrence of each k-mer in input set of reads
 *
 */

#include "KMerCounter.hpp"
#include "../common/log.hpp"
#include <fstream>

using namespace std;

namespace dnaasm { namespace dbj {
    KMerCounter::KMerCounter(FileReader& fileReader, unsigned short K1, unsigned short qualityThreshold, string kmerOccurrenceTableFilename, mt4cpp::Progress* progress)
        : fileReader_(fileReader)
        , K1_(K1)
        , qualityThreshold_(qualityThreshold)
        , dnaSequenceRepresentationConverter_(K1_ + 1)
        , kmerOccurrenceTableFilename_(kmerOccurrenceTableFilename)
        , progress_(progress)
    {}

    void KMerCounter::calcKMersOccurrenceTable() {
        logInfo("counting k-mers in input set of reads...");
        Read read(qualityThreshold_);
        HashTable hashTable(K1_+1); // counting k-mers (not k1-mers)
        unsigned int k = 0U;
        fileReader_.reset();

        while (true) {
            fileReader_.readData(read);

            read.filterReadBasedOnQuality();
            string readStr = read.getRead();
            read.makeComplementaryStrand();

            addKMersFromReadToOccurrenceTable(hashTable, readStr, read.getRead());
            k += 1;

            if (k % 100000 == 0) {
                logInfo("processing read number: " + std::to_string(k));
            }

            if (!fileReader_.getIsMoreSequences()) {
                logInfo("k-mer occurrence table is built, number of elements: " + to_string(hashTable.size()));
                logInfo("storing k-mer occurrence table to file...");
                ofstream ofile(kmerOccurrenceTableFilename_);
                for (auto kmerIt : hashTable) {
                    ofile << dnaSequenceRepresentationConverter_.convertToString(kmerIt.first) << " " << kmerIt.second << std::endl;
                }
                ofile.close();
                logInfo("k-mer occurrence table stored to file");
                return;
            }
        }
        return;
    }

    // [TODO] 'N' !!!???
    void KMerCounter::addKMersFromReadToOccurrenceTable(HashTable& hashTable, const string& read, const string& complementaryRead) {
        if (read.size() <= K1_)
            return;
        const char* readPtr = read.data();
        const char* lastReadPtr = readPtr + read.size() - K1_;
        const char* complementaryReadPtr = complementaryRead.data();
        const char* lastComplementaryReadPtr = complementaryReadPtr + complementaryRead.size() - K1_;
        for (;readPtr < lastReadPtr; ++readPtr) {
            bitset<2*MAX_KMER_LENGTH> bitsetKMer = dnaSequenceRepresentationConverter_.convertToBitset(readPtr);
            HashTable::iterator it = hashTable.find(bitsetKMer);
            if (it == hashTable.end()) {
                bitset<2*MAX_KMER_LENGTH> bitsetKMer = dnaSequenceRepresentationConverter_.convertToBitset(lastComplementaryReadPtr - (readPtr - read.data()) - 1);
                HashTable::iterator it = hashTable.find(bitsetKMer);
                if (it == hashTable.end()) {
                    hashTable.insert(bitsetKMer, 1U);
                } else {
                    it->second += 1U;
                }
            } else {
                it->second += 1U;
            }
        }
    }

}}

