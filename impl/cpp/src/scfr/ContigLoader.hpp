/**
 * \file ContigLoader.hpp
 * \brief the C++ file with declaration of class responsible for
 * loading contig sequences into hash map
 *
 */

#ifndef CONTIGLOADER_HPP
#define CONTIGLOADER_HPP

#include "../common/common.hpp"
#include "../common/FileReader.hpp"

#include "common.hpp"

namespace dnaasm { namespace scfr {

    namespace ContigLoader {

        /**
         * Creates and returns hash map with DNA sequences read from given file.
         *
         * Sequences will be stored as <id,seq> pairs, where id is
         * ordinal number of sequence in file.
         *
         * @param contigsFile reference to file with sequences
         * @param idCorrespondenceFilePath string with path to file where
         *        correspondence between new and original contigs' ids will be saved.
         *        File will be created only if given path is valid.
         *        Default: empty string
         *
         * @returns hash map with contig id as key and sequence as value.
         */
        CALC_DLL( ContigSeqHashMap loadContigsIntoMemory(
            InputFile &contigsFile,
            const std::string &idCorrespondenceFilePath = ""
        ); )
    } //namespace ContigLoader

}} //namespace dnaasm::scfr

#endif //CONTIGLOADER_HPP
