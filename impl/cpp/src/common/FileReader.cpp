/**
 * \file FileReader.cpp
 * \brief the C++ file with implementation of class for reading single read or paired reads from files with checking, if reads are paired
 *
 */

#include "FileReader.hpp"
#include "log.hpp"

using namespace std;

namespace dnaasm {
    FileReader::FileReader(): inputFile1_(NULL), inputFile2_(NULL), isMoreSequences_(true), numOfPairedReads_(0U) {}

    void FileReader::setInputFile1(InputFile* inputFile1) {
        if (inputFile1 -> getFileFormat() != InputFile::FileFormat::NONE) {
            inputFile1_ = inputFile1;
        }
    }

    void FileReader::setInputFile2(InputFile* inputFile2) {
        if (inputFile2 -> getFileFormat() != InputFile::FileFormat::NONE) {
            inputFile2_ = inputFile2;
        }
    }

    void FileReader::readData(Read& read) {
        read.setDescription("");
        read.setRead("");
        read.setQuality("");
        if (inputFile1_ == NULL && inputFile2_ == NULL) {
            isMoreSequences_ = false;
            return;
        }

        if (inputFile1_ != NULL && inputFile1_ -> getIsMoreSequences()) {
            inputFile1_ -> readSingleRead(read);
            return;
        }

        if (inputFile2_ != NULL && inputFile2_ -> getIsMoreSequences()) {
            inputFile2_ -> readSingleRead(read);
            return;
        }

        isMoreSequences_ = false;
        return;
    }

    void FileReader::readData(Read& read, Read& pairedRead) {
        read.setDescription("");
        read.setRead("");
        read.setQuality("");
        pairedRead.setDescription("");
        pairedRead.setRead("");
        pairedRead.setQuality("");
        if (inputFile1_ == NULL && inputFile2_ == NULL) {
            isMoreSequences_ = false;
            return;
        } else if (inputFile1_ != NULL && inputFile2_ != NULL) {  //two files
            if (inputFile1_ -> getFileFormat() != inputFile2_ -> getFileFormat()) {
                logError("Error, files have different format.");
                isMoreSequences_ = false;
                return;
            }
            if (inputFile1_ -> getFileFormat() == InputFile::FileFormat::FASTQ_ILLUMINA) {   //for FASTQ_ILLUMINA
                inputFile1_ -> readSingleRead(read);
                /*while (checkIndexFastqIllumina(read) != '1' && inputFile1_ -> getIsMoreSequences()) {
                    logInfo(read.getDescription()+ " - unpaired");
                    inputFile1_ -> readSingleRead(read);
                }*/
                inputFile2_ -> readSingleRead(pairedRead);
                /*while (checkIndexFastqIllumina(pairedRead) != '2' && inputFile2_ -> getIsMoreSequences()) {
                    logInfo(pairedRead.getDescription()+ " - unpaired");
                    inputFile2_ -> readSingleRead(pairedRead);
                }*/
                if (!arePairedFastqIllumina(read, pairedRead)) {
                    logInfo(read.getDescription()+ " - unpaired");
                    logInfo(pairedRead.getDescription()+ " - unpaired");
                    read.setRead("");
                    read.setQuality("");
                    read.setDescription("");
                    pairedRead.setRead("");
                    pairedRead.setQuality("");
                    pairedRead.setDescription("");
                } else {
                    numOfPairedReads_ += 2;
                }
                isMoreSequences_ = (inputFile1_ -> getIsMoreSequences()&& inputFile2_ -> getIsMoreSequences());
                return;
            } else {
                inputFile1_ -> readSingleRead(read);
                inputFile2_ -> readSingleRead(pairedRead);
                isMoreSequences_ = (inputFile1_ -> getIsMoreSequences()&& inputFile2_ -> getIsMoreSequences());
            }
            return;
        } else {    //everything in one file
            if (inputFile1_ == NULL) {
                inputFile1_ = inputFile2_;
                inputFile2_ = NULL;
            }
            if (inputFile1_ -> getFileFormat() == InputFile::FileFormat::FASTQ_ILLUMINA) {   //for FASTQ_ILLUMINA
                inputFile1_ -> readSingleRead(read);
                while (checkIndexFastqIllumina(read) != '1' && inputFile1_ -> getIsMoreSequences()) {
                    logInfo(read.getDescription()+ " - unpaired");
                    inputFile1_ -> readSingleRead(read);
                }
                inputFile1_ -> readSingleRead(pairedRead);
                while (checkIndexFastqIllumina(pairedRead) == '1' && inputFile1_ -> getIsMoreSequences()) {
                    logInfo(pairedRead.getDescription()+ " - unpaired");
                    read = pairedRead;
                    inputFile1_ -> readSingleRead(pairedRead);
                }
                if (!arePairedFastqIllumina(read, pairedRead)) {
                    logInfo(read.getDescription()+ " - unpaired");
                    logInfo(pairedRead.getDescription()+ " - unpaired");
                    read.setRead("");
                    read.setQuality("");
                    read.setDescription("");
                    pairedRead.setRead("");
                    pairedRead.setQuality("");
                    pairedRead.setDescription("");
                } else {
                    numOfPairedReads_ += 2;
                }
                isMoreSequences_ = inputFile1_ -> getIsMoreSequences();
                return;
            } else {
                inputFile1_ -> readSingleRead(read);
                inputFile1_ -> readSingleRead(pairedRead);
                isMoreSequences_ = inputFile1_ -> getIsMoreSequences();
            }
            return;
        }
    }

    bool FileReader::getIsMoreSequences() const {
        return isMoreSequences_;
    }

    char FileReader::checkIndexFastqIllumina(Read& read) {
        return read.getDescription()[read.getDescription().find(' ')+ 1];
    }

    bool FileReader::arePairedFastqIllumina(Read& read, Read& pairedRead) {
        if (read.getDescription().size() == 0 || pairedRead.getDescription().size() == 0 || checkIndexFastqIllumina(read) != '1' || checkIndexFastqIllumina(pairedRead) != '2')
            return false;
        unsigned int spaceIndex = (unsigned int)read.getDescription().find(' ');
        return (read.getDescription().compare(0, spaceIndex, pairedRead.getDescription().substr(0, spaceIndex)) == 0 &&
                read.getDescription().substr(spaceIndex + 2, read.getDescription().size()) ==
                pairedRead.getDescription().substr(spaceIndex + 2, pairedRead.getDescription().size()));
    }

    void FileReader::reset() {
        numOfPairedReads_ = 0U;
        isMoreSequences_ = true;

        if (inputFile1_ != NULL)
            inputFile1_ -> reset();

        if (inputFile2_ != NULL)
            inputFile2_ -> reset();

        return;
    }

    unsigned int FileReader::getNumOfUnpairedReads() const {
        unsigned int sumOfLine = 0U;

        if (inputFile1_ != NULL)
            sumOfLine += inputFile1_ -> getNumOfLinesInFile();

        if (inputFile2_ != NULL)
            sumOfLine += inputFile2_ -> getNumOfLinesInFile();

        if ((inputFile1_ != NULL && inputFile1_ -> getFileFormat() == InputFile::FileFormat::FASTQ_ILLUMINA) ||
            (inputFile2_ != NULL && inputFile2_ -> getFileFormat() == InputFile::FileFormat::FASTQ_ILLUMINA))
            return (sumOfLine / 4U)- numOfPairedReads_;
        else
            return 0U;
    }

    unsigned int FileReader::getNumOfPairedReads() const {
        return numOfPairedReads_;
    }

    unsigned int FileReader::getNumOfReads() {
        unsigned int sumOfReads = 0U;
        Read read(0U);
        reset();

        while (isMoreSequences_) {
            readData(read);
            if (read.getRead().size() != 0)
                ++sumOfReads;
        }

        reset();
        return sumOfReads;
    }

    InputFile::FileFormat FileReader::getFileFormat() const {
        if (inputFile1_ != NULL)
            return inputFile1_ -> getFileFormat();
        else if (inputFile2_ != NULL)
            return inputFile2_ -> getFileFormat();
        else
            return InputFile::FileFormat::NONE;
    }
}

