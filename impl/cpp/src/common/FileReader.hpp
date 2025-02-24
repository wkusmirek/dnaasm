/**
 * \file FileReader.hpp
 * \brief the C++ file with declaration of class for reading single read or paired reads from files with checking, if reads are paired
 *
 */

#ifndef FILEREADER_HPP
#define FILEREADER_HPP

#include "InputFile.hpp"

namespace dnaasm {
    /**
     * \brief Class to read single read or paired reads from files with checking, if reads are paired.
     */
    class FileReader {
    public:

        /**
        * \brief FileReader constructor.
        */
        CALC_DLL(FileReader();)

        /**
        * \brief Sets input file pointer to first InputFile object.
        *
        * \param inputFile1 pointer to first InputFile object
        * \return returns void
        */
        CALC_DLL(void setInputFile1(InputFile* inputFile1);)

        /**
        * \brief Sets input file pointer to second InputFile object.
        *
        * \param inputFile2 pointer to second InputFile object
        * \return returns void
        */
        CALC_DLL(void setInputFile2(InputFile* inputFile2);)

        /**
        * \brief Reads single read from InputFile object.
        *
        * \param read reference to a Read object, where data (read + quality + description)from InputFile object will be stored
        * \return returns void
        */
        CALC_DLL(void readData(Read& read);)

        /**
        * \brief Reads paired reads from InputFile object.
        *
        * \param read reference to a Read object, where data for first read (read + quality + description)from InputFile object will be stored
        * \param pairedRead reference to a Read object, where data for second read (read + quality + description)from InputFile object will be stored
        * \return returns void
        */
        CALC_DLL(void readData(Read& read, Read& pairedRead);)

        /**
         * \brief Resets all variables in FileReader object - except inputFile1_ and inputFile2_.
         *
         * \return returns void
         */
        CALC_DLL(void reset();)

        /**
         * \brief Gets number of reads in file.
         *
         * \return returns number of reads in file
         */
        CALC_DLL(unsigned int getNumOfReads();)

        /**
         * \brief Gets number of unpaired reads in file.
         *
         * \return returns number of unpaired reads in file
         */
        CALC_DLL(unsigned int getNumOfUnpairedReads() const;)

        /**
         * \brief Gets number of paired reads in file.
         *
         * \return returns number of paired reads in file
         */
        CALC_DLL(unsigned int getNumOfPairedReads() const;)

        /**
         * \brief Gets information about next data existence in file.
         *
         * \return returns information about next data existence in file
         */
        CALC_DLL(bool getIsMoreSequences() const;)

        /**
         * \brief Gets information about file format.
         *
         * \return returns information about file format
         */
        CALC_DLL(InputFile::FileFormat getFileFormat() const;)

    private:
        InputFile* inputFile1_;
        InputFile* inputFile2_;
        bool isMoreSequences_;
        unsigned int numOfPairedReads_;
        //FileReader& operator=(const FileReader&)= delete;

        /**
        * \brief Checks if read from FASTQ ILLUMINA format file is first or second in a pair.
        *
        * \param read reference to a Read object, where data for read (read + quality + description)from InputFile object are stored
        * \return returns '1' - for first read or '2' - for second read in a pair
        */
        CALC_DLL(static char checkIndexFastqIllumina(Read& read);)

        /**
        * \brief Checks if two reads from FASTQ ILLUMINA format file are paired.
        *
        * \param read reference to a Read object, where data for first read (read + quality + description)from InputFile object are stored
        * \param pairedRead reference to a Read object, where data for second read (read + quality + description)from InputFile object are stored
        * \return returns true if reads are paired, false - if reads are unpaired
        */
        CALC_DLL(static bool arePairedFastqIllumina(Read& read, Read& pairedRead);)

    };

}

#endif    //FILEREADER
