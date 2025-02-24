/**
 * \file InputFile.cpp
 * \brief the C++ file with implementation of class for reading single reads with qualities from input_ file
 *
 */

#include "InputFile.hpp"
#include "log.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <boost/iostreams/filter/gzip.hpp>

using namespace std;

namespace dnaasm {
    InputFile::InputFile(istream &input)
        : input_(input)
        , fileFormat_(FileFormat::NONE)
        , fileCompressionType_(FileCompressionType::TEXT)
        , isMoreSequences_(true)
        , numOfLinesInFile_(0U)
        , fastaPattern_(">+.*")
        , fastqPattern_("@+.*")
        , fastqIlluminaPattern_("@+[^ :]*:[0-9]*:[^ :]*:[0-9]*:[0-9]*:[0-9]*:[0-9]* (1|2){1}:(N|Y){1}:[0-9]*:[ATCGN]+")
    {checkFileCompressionType(); checkFileFormat(); countLinesInFile();}

    InputFile::~InputFile() { }

    void InputFile::reset() {
        isMoreSequences_ = true;
        input_.clear();
        input_.seekg(ios::beg);
        checkFileFormat();
    }

    bool InputFile::isGz() {
        /*
         * Version that was using boost
         * exceoption throwing was
         * kind of undefined behaviour?
         * because boost filter object gz decompressor
         * is not designed to handle uncompressed file
         * so on Linux it was throwing exception
         * and unfortunately using MSVC 14.0 did not
         * function was changed to check first two bytes
         * from input stream according do gzip standard
         */
        bool result = false;
        const unsigned char FirstGzipByte = 0x1f;
        const unsigned char SecondGzipByte = 0x8b;
        unsigned char firstStreamByte, secondStreamByte;
        input_.seekg(ios::beg);

        input_ >> std::noskipws >> firstStreamByte >> secondStreamByte;

        if (!input_.fail()) {
            if (firstStreamByte == FirstGzipByte && secondStreamByte == SecondGzipByte) {
                result = true;
            }
        } else {
            //FIXME:
            //throw some exception?
            input_.seekg(ios::beg);
        }

        input_.seekg(ios::beg);

        return result;
    }

    void InputFile::checkFileFormat() {
        string description;

        if (fileCompressionType_ == FileCompressionType::TEXT) {
            getline(input_, description);
        } else if (fileCompressionType_ == FileCompressionType::GZ) {
            boost::iostreams::filtering_istream in;
            in.push(boost::iostreams::gzip_decompressor());
            in.push(input_);
            getline(in, description);
        }

        if (boost::regex_match(description.begin(), description.end(), fastaPattern_)) {
            fileFormat_ = FileFormat::FASTA;
        } else if (boost::regex_match(description.begin(), description.end(), fastqPattern_)) {  //fastq format
            if (boost::regex_match(description.begin(), description.end(), fastqIlluminaPattern_)) {
                fileFormat_ = FileFormat::FASTQ_ILLUMINA;
            } else {
                fileFormat_ = FileFormat::FASTQ;
            }
        } else {
            fileFormat_ = FileFormat::NONE;
            isMoreSequences_ = false;
        }
        input_.seekg(ios::beg);

        return;
    }

    void InputFile::checkFileCompressionType() {
        if (isGz()) {
            fileCompressionType_ = FileCompressionType::GZ;
            in_.push(boost::iostreams::gzip_decompressor());
            in_.push(input_);
        } else {
            fileCompressionType_ = FileCompressionType::TEXT;
        }
        return;
    }

    void InputFile::readFromTextFasta(Read& read) {
        string builtRead, description;

        if (input_.good()) {
            /*
             * Hotfix:
             * While reading from source 
             * that function should not rewind stream
             * but buffer already read data and change/save state
             * rewind on stream differ on Windows and Linux (lexer convention?)
             * as can be seen with unit tests
             *
             * So while loop below actually guarantees that
             * after rewind reader state always will be
             * on the beginning of FASTA header
             * TODO: rewrite reading from FASTA
             */
            while (getline(input_, description)) {
                if (description[0] == '>') {
                    break;
                }
            }

            read.setDescription(description);
            size_t positionInFile = 0U;

            for (std::string temp; getline(input_, temp);) {
                if (temp[0] == '>') {
                    input_.seekg(positionInFile, ios::beg);
                    isMoreSequences_ = true;
                    break;
                }

                builtRead += temp;
                positionInFile = static_cast<size_t>(input_.tellg());
            }

            if (input_.eof()) {
                isMoreSequences_ = false;
            }

            //TODO: convert sequence to upper case
            read.setRead(builtRead);

        } else {
            isMoreSequences_ = false;
        }
    }

    void InputFile::readFromTextFastq(Read& read) {
        string description;
        getline(input_, description);
        read.setDescription(description);
        string temp;
        getline(input_, temp);
        read.setRead(temp);
        getline(input_, temp);
        getline(input_, temp);
        read.setQuality(temp);

        if (description == "")
            isMoreSequences_ = false;
        return;
    }

    void InputFile::readFromGzFasta(Read& read) {
        try {
            char tmp;
            string builtRead, description;
            getline(in_, description);
            if (description.size() > 0 && description[0] != '>') {
                description = '>' + description;
            }
            read.setDescription(description);
            while (in_ >> tmp) {
                if (tmp == '>') {       //start a new sequence
                    isMoreSequences_ = true;
                    break;
                }
                builtRead += tmp;
            }

            if (description == "") {
                isMoreSequences_ = false;
            }
            read.setRead(builtRead);
        } catch(const boost::iostreams::gzip_error& e) {
            cout << e.what() << endl;
            return;
        }
        return;
    }

    void InputFile::readFromGzFastq(Read& read) {
        try {
            string description;
            getline(in_, description);
            read.setDescription(description);
            string temp;
            getline(in_, temp);
            read.setRead(temp);
            getline(in_, temp);
            getline(in_, temp);
            read.setQuality(temp);
            if (description == "") {
                isMoreSequences_ = false;
            }
        } catch(const boost::iostreams::gzip_error& e) {
            cout << e.what() << endl;
            return;
        }
        return;
    }

    void InputFile::readSingleRead(Read& read) {
        if (!isMoreSequences_) {
            read.setRead("");
            read.setQuality("");
            read.setDescription("");
            return;
        }

        if (fileCompressionType_ == FileCompressionType::TEXT) {
            if (fileFormat_ == FileFormat::FASTA) {   // fasta format
                readFromTextFasta(read);
            } else if (fileFormat_ == FileFormat::FASTQ || fileFormat_ == FileFormat::FASTQ_ILLUMINA) {   // fastq format
                readFromTextFastq(read);
            }
        } else if (fileCompressionType_ == FileCompressionType::GZ) {
            if (fileFormat_ == FileFormat::FASTA) {   // fasta format
                readFromGzFasta(read);
            } else if (fileFormat_ == FileFormat::FASTQ || fileFormat_ == FileFormat::FASTQ_ILLUMINA) {   // fastq format
                readFromGzFastq(read);
            }
        }

        return;
    }

    unsigned int InputFile::getNumOfLinesInFile() const {
        return numOfLinesInFile_;
    }

    void InputFile::countLinesInFile() {
        string line;
        if (fileCompressionType_ == FileCompressionType::TEXT) {
            while (getline(input_, line)) {
                ++numOfLinesInFile_;
            }
        } else if (fileCompressionType_ == FileCompressionType::GZ) {
            try {
                input_.seekg(ios::beg);
                boost::iostreams::filtering_istream in;
                in.push(boost::iostreams::gzip_decompressor());
                in.push(input_);
                while (getline(in, line)) {
                    ++numOfLinesInFile_;
                }
            } catch(const boost::iostreams::gzip_error& e) {
            }
        }
        input_.clear();
        input_.seekg(ios::beg);
        return;
    }

    bool InputFile::getIsMoreSequences() const {
        return isMoreSequences_;
    }

    InputFile::FileFormat InputFile::getFileFormat() const {
        return fileFormat_;
    }

    InputFile::FileCompressionType InputFile::getFileCompressionType() const {
        return fileCompressionType_;
    }
}
