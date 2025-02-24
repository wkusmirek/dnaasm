/**
 * \file assembly.hpp
 * \brief the C++ calculation library interface and declaration of several main functions
 */

#ifndef ASSEMBLY_HPP
#define ASSEMBLY_HPP

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
#pragma warning(disable:4512)
#endif

#include <mt4cpp/Scheduler.hpp>
#include <mt4cpp/CommandHistory.hpp>
#include <iostream>
#include "globals.hpp"

namespace dnaasm { namespace dbj {
    /**
    * \brief Main function for assembling mode (with counting progress of task).
    *
    * \param K1 length of strings stored in graph vertices (K1 + 1 = k form k-spectrum)
    * \param genomeLength length of original genome
    * \param insertSizeMeanInward value associated with paired-end reads - mean of insert size
    * \param insertSizeStdDevInward value associated with paired-end reads - insert size standard deviation
    * \param insertSizeMeanOutward value associated with mate pairs - mean of insert size
    * \param insertSizeStdDevOutward value associated with mate pairs - insert size standard deviation
    * \param qualityThreshold quality threshold value (0-93)
    * \param singleEdgeCounterThreshold edges from single graph with counters less than this value will be removed from graph
    * \param bfcounterThreshold k-mers with counters less than this value will not be considered
    * \param pairedReadsPetThresholdFrom threshold for number of connections between unitigs (each paired-end tag adds or increment counter for connection between unitigs), begin value
    * \param pairedReadsPetThresholdTo threshold for number of connections between unitigs (each paired-end tag adds or increment counter for connection between unitigs), end value
    * \param pairedReadsMpThresholdFrom threshold for number of connections between contigs (each mate-pair adds or increment counter for connection between contigs), begin value
    * \param pairedReadsMpThresholdTo threshold for number of connections between contigs (each mate-pair adds or increment counter for connection between contigs), end value
    * \param i1_1 first input from first pair of inward reads
    * \param i1_2 second input from first pair of inward reads
    * \param o1_1 first input from first pair of outward reads
    * \param o1_2 second input from first pair of outward reads
    * \param bfcounterFile reference to an input stream object with output data form BFCounter program (optional, to save memory for large genomes)
    * \param pairedReadsAlgorithm 0 - single reads, 1 - paired graph algorithm
    * \param correct true - correcting errors, false - not correcting errors
    * \param idPrefix prefix to output FASTA format id line
    * \param progress actual task's progress
    * \return returns output which should be stored in output file
    */
    CALC_DLL(std::string assemblyMode(unsigned short K1,
                                      unsigned long long int genomeLength,
                                      float insertSizeMeanInward,
                                      float insertSizeStdDevInward,
                                      float insertSizeMeanOutward,
                                      float insertSizeStdDevOutward,
                                      unsigned short int qualityThreshold,
                                      unsigned short int bfcounterThreshold,
                                      unsigned short int singleEdgeCounterThreshold,
                                      unsigned short int pairedReadsPetThresholdFrom,
                                      unsigned short int pairedReadsPetThresholdTo,
                                      unsigned short int pairedReadsMpThresholdFrom,
                                      unsigned short int pairedReadsMpThresholdTo,
                                      std::istream& i1_1,
                                      std::istream& i1_2,
                                      std::istream& o1_1,
                                      std::istream& o1_2,
                                      std::istream& bfcounterFile,
                                      unsigned short pairedReadsAlgorithm,
                                      bool correct,
                                      std::string idPrefix,
                                      mt4cpp::Progress* progress);
            )

    /**
    * \brief Main function for mode which will align two sequences - sequence and reference.
    *
    * \param sequence DNA sequence which will be aligned to reference genome
    * \param reference DNA genome reference
    * \param isHirschbergAlgorithm true - Hirschberg algorithm, false - Needleman-Wunsch algorithm
    * \param isCircular true if genome is circular, false - genome is linear
    * \param d gap penalty
    * \param substitutionMatrixValues values for similarity matrix (ACGT x ACGT)
    * \param progress actual task's progress
    * \return returns output - set of mismatches - which should be stored in output file
    */
    CALC_DLL(std::string alignMode(std::istream& sequence, 
                                   std::istream& reference, 
                                   bool isHirschbergAlgorithm, 
                                   bool isCircular, 
                                   short int d, 
                                   short int substitutionMatrix[16], 
                                   mt4cpp::Progress* progress);
            )

}}

#endif     //ASSEMBLY_HPP
