/**
 * \file scaffold.hpp
 * \brief the C++ calculation library interface for scaffolder module
 */

#ifndef SCAFFOLD_HPP
#define SCAFFOLD_HPP

#include <mt4cpp/Scheduler.hpp>
#include "../common/common.hpp"

namespace dnaasm { namespace scfr {

    /**
     * Builds scaffolds from contigs and long reads
     *
     * @param contigsFilePath path to file with contigs
     * @param readsFilePath path to file with long reads
     * @param kmerSize k-mer length
     * @param distance distance that will be used for k-mer pairs extraction
     * @param step length of sliding window two subsequent between k-mer pairs
     * @param minLinks minimum number of linkages between contigs to consired them
     *        in scaffolding
     * @param maxRatio maximum link ratio between two best contig pairs
     * @param minContigLength minimum contig length to consider for scaffolding
     * @param progress pointer to Progress object
     * @return string with scaffolds in FASTA format
     */
    CALC_DLL(std::string scaffold(const std::string &contigsFilePath,
                                  const std::string &readsFilePath,
                                  unsigned short int kmerSize,
                                  unsigned short int distance,
                                  unsigned short int step,
                                  unsigned short int minLinks,
                                  unsigned short int minReads,
                                  unsigned short int minLinksPerRead,
                                  float maxRatio,
                                  unsigned int minContigLength,
                                  bool gapFilling,
                                  mt4cpp::Progress *progress);
    )

}} //namespace dnaasm::scfr

#endif  //SCAFFOLD_HPP
