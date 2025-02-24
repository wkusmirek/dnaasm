/**
 * \file InputFile.hpp
 * \brief the C++ file with declaration of class for reading single reads with qualities from input file
 *
 */

#ifndef INPUTFILE_HPP
#define INPUTFILE_HPP

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/regex.hpp>
#include "Read.hpp"

namespace dnaasm {
    /**
     * \brief Class to read single reads with qualities from input file.
     */
    class InputFile {
    public:

        /**
         * \brief Input file format.
         */
        enum /*class*/ FileFormat { NONE, FASTA, FASTQ, FASTQ_ILLUMINA };

        /**
         * \brief Input file compression type.
         */
        enum /*class*/ FileCompressionType { TEXT, GZ };

        /**
         * \brief InputFile constructor.
         *
         * \param input reference to an input stream object with data
         */
        CALC_DLL(explicit InputFile(std::istream& input);)

        /**
         * \brief InputFile destructor.
         */
        CALC_DLL(virtual ~InputFile();)

        /**
        * \brief Reads data (read + quality + description)from a input stream object.
        *
        * \param read reference to a Read object, where data (read + quality + description)from file will be stored
        * \return returns void
        */
        CALC_DLL(void readSingleRead(Read& read);)

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
        CALC_DLL(FileFormat getFileFormat() const;)

        /**
         * \brief Gets information about file compression type.
         *
         * \return returns information about file compression type
         */
        CALC_DLL(FileCompressionType getFileCompressionType() const;)

        /**
         * \brief Rewinds the position of a file pointer.
         *
         * \return returns void
         */
        CALC_DLL(void reset();)

        /**
         * \brief Gets number of lines in a input file.
         *
         * \return number of lines in a input file
         */
        CALC_DLL(unsigned int getNumOfLinesInFile() const;)

    protected:
        std::istream& input_;
        FileFormat fileFormat_;
        FileCompressionType fileCompressionType_;
        bool isMoreSequences_;
        unsigned int numOfLinesInFile_;
        boost::regex fastaPattern_;
        boost::regex fastqPattern_;
        boost::regex fastqIlluminaPattern_;
        boost::iostreams::filtering_istream in_;
        InputFile& operator=(const InputFile&)= delete;

        /**
         * \brief Checks input file format (fasta or fastq).
         *
         * \return returns void
         */
        CALC_DLL(void checkFileFormat();)

        /**
         * \brief Checks input file compression type (text or gz).
         *
         * \return returns void
         */
        CALC_DLL(void checkFileCompressionType();)

        /**
         * \brief Reads single read and quality information from a not compressed fastq file.
         *
         * \param read reference to a Read object, where data (read + quality) from file will be stored
         * \return returns void
         */
        CALC_DLL(void readFromTextFastq(Read& read);)

        /**
         * \brief Reads single read and quality information from a not compressed fasta file.
         *
         * \param read reference to a Read object, where data (read) from file will be stored
         * \return returns void
         */
        CALC_DLL(void readFromTextFasta(Read& read);)

        /**
         * \brief Reads single read and quality information from a compressed (gz) fastq file.
         *
         * \param read reference to a Read object, where data (read + quality) from file will be stored
         * \return returns void
         */
        CALC_DLL(void readFromGzFastq(Read& read);)

        /**
         * \brief Reads single read and quality information from a compressed (gz) fasta file.
         *
         * \param read reference to a Read object, where data (read) from file will be stored
         * \return returns void
         */
        CALC_DLL(void readFromGzFasta(Read& read);)

        /**
         * \brief Counts number of lines in a input file.
         *
         * \return returns void
         */
        CALC_DLL(void countLinesInFile();)

        /**
         * \brief Checks if file is compressed (gz).
         *
         * \return returns true if file is compressed (gz), otherwise - function returns false
         */
        CALC_DLL(bool isGz();)

    };
}

#endif    //INPUTFILE_HPP
