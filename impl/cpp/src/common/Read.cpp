/**
 * \file Read.cpp
 * \brief the C++ file with implementation of class for representing single read with quality
 *
 */

#include "Read.hpp"

using namespace std;

namespace dnaasm {
    Read::Read() {}

    Read::Read(unsigned short int threshold)
        : read_("")
          , quality_("")
          , description_("")
          , threshold_(threshold)
    {}

    int Read::makeComplementaryStrand() {
        string complementaryStrand;
        unsigned int size = static_cast<unsigned int>(read_.size());

        for (unsigned int i = 0; i < size; ++i) {
            if (read_[size-i-1] == 'A') {
                complementaryStrand += 'T';
            } else if (read_[size-i-1] == 'a') {
                complementaryStrand += 't';
            } else if (read_[size-i-1] == 'T') {
                complementaryStrand += 'A';
            } else if (read_[size-i-1] == 't') {
                complementaryStrand += 'a';
            } else if (read_[size-i-1] == 'G') {
                complementaryStrand += 'C';
            } else if (read_[size-i-1] == 'g') {
                complementaryStrand += 'c';
            } else if (read_[size-i-1] == 'C') {
                complementaryStrand += 'G';
            } else if (read_[size-i-1] == 'c') {
                complementaryStrand += 'g';
            } else {
                complementaryStrand += read_[size-i-1];
            }
        }

        reverse(quality_.begin(), quality_.end());
        read_ = complementaryStrand;
        return 0;
    }

    void Read::filterReadBasedOnQuality() {
        if (quality_.size() == 0 || threshold_ == 0)   //fasta format
            return;

        unsigned int readSize = static_cast<unsigned int>(read_.size());

        if (readSize != quality_.size()) {
            read_ = "";
            return;
        }

        unsigned int last;

        for (last = 0; last < readSize; ++last) {
            if (quality_[last] - LOWEST_QUALITY_ASCII < threshold_)
                break;
        }

        read_.erase(last, readSize-last);
        return;
    }

    string Read::getRead() const {
        return read_;
    }

    void Read::setRead(string read) {
        this -> read_ = read;
    }

    string Read::getQuality() const {
        return quality_;
    }

    void Read::setQuality(string quality) {
        this -> quality_ = quality;
    }

    string Read::getDescription() const {
        return description_;
    }

    void Read::setDescription(string description) {
        this -> description_ = description;
    }
}

