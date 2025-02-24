/**
 * \file FileLogger.hpp
 * \brief the C++ file with declaration of file logger methods
 *
 */

#ifndef SCFR_FILELOGGER_HPP
#define SCFR_FILELOGGER_HPP


#include "ContigPairGraph.hpp"
#include "MatepairGraph.hpp"
#include "MatepairGraphBuilder.hpp"
#include "Scaffolder.hpp"

namespace dnaasm { namespace scfr {

    namespace FileLogger {

        void logContigPairs(
            const std::string &filePath,
            const ContigPairGraph &contigGraph,
            const MatepairGraph &matepairGraph
        );

        void logImportantRegionsOnReads(
            const std::string &filePath,
            const MatepairGraph &matepairGraph,
            const MatepairGraphBuilder& matepairGraphBuilder
        );

        void logGapSequences(
            const std::string &dirPath,
            const ContigPathHashMap &contigPaths,
            const ContigPairGraph &contigGraph,
            const MatepairGraph &matepairGraph,
            const ReadSeqHashMap &reads
        );

        void logGapLengthHistogram(
            const std::string &dirPath,
            const ContigPathHashMap &contigPaths,
            const ContigPairGraph &contigGraph
        );
    }

}} //namespace dnaasm::scfr

#endif //SCFR_FILELOGGER_HPP
