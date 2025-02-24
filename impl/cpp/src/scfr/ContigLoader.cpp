/**
 * \file ContigLoader.cpp
 * \brief the C++ file with implementation of class responsible for
 * loading contig sequences into hash map
 *
 */

#include "ContigLoader.hpp"

#include <fstream>
#include <iomanip>
#include <ios>

namespace dnaasm { namespace scfr {

    ContigSeqHashMap ContigLoader::loadContigsIntoMemory(
        InputFile &contigsFile,
        const std::string &idCorrespondenceFilePath)
    {
        ContigSeqHashMap sequences;
        Read contig(0U);
        std::string contigStr;
        unsigned int contigCount = 0U;
        std::ofstream correspondenceFile;

        if (idCorrespondenceFilePath != "") {
            correspondenceFile.open(idCorrespondenceFilePath);

            correspondenceFile << std::setw(20) << std::left
                               << "scfr_contig_id"
                               << "original_name"
                               << std::endl;
        }

        while (true) {
            contigsFile.readSingleRead(contig);
            contigStr = contig.getRead();

            if (contigStr == "")
                break;

            ++contigCount;

            sequences.insert(make_pair(contigCount, contigStr));

            if (idCorrespondenceFilePath != "") {
                auto origId = contig.getDescription();
                if (origId != "") origId = origId.substr(1); // skip '>'

                correspondenceFile << std::setw(10) << std::left
                                   << std::to_string(contigCount)
                                   << origId
                                   << std::endl;
            }
        }

        if (idCorrespondenceFilePath != "") {
            correspondenceFile.close();
        }

        return sequences;
    }

}} //namespace dnaasm::scfr