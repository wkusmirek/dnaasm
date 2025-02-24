/**
 * \file assembly.cpp
 * \brief the C++ file with implementation of several main functions
 */

#include "assembly.hpp"
#include "SequenceAlignment.hpp"
#include "OutputVCF.hpp"
#include "EdgeNormalization.hpp"
#include "Output.hpp"
#include "InwardPairedReadsAdding.hpp"
#include "OutwardPairedReadsAdding.hpp"
#include "SingleGraphBuilder.hpp"
#include "../common/FileReader.hpp"
#include "Statistics.hpp"
#include "CorrectEdgeCounter.hpp"
#include "KMerCounter.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#include "GraphCompressor.hpp"
#include "UnitigsUncompressor.hpp"
#include "UnitigsGenerator.hpp"
#include "RemoveTips.hpp"
#include "RemoveBubbles.hpp"
#include "UnitigsToContigsExtension.hpp"
#include "ContigsToScaffoldsExtension.hpp"
#include "RemoveLowCounterEdges.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

#include <iostream>

using namespace dnaasm::dbj;
using namespace std;

typedef boost::graph_traits<CompressedDeBruijnGraph>::vertex_descriptor CompressedDeBruijnGraphVertex;
typedef std::vector<CompressedDeBruijnGraphVertex> CompressedUnitig;
typedef std::vector<CompressedUnitig> CompressedUnitigs;

typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;
typedef std::vector<DeBruijnGraphVertex> UncompressedUnitig;
typedef std::vector<UncompressedUnitig> UncompressedUnitigs;

namespace dnaasm { namespace dbj {
    string assemblyMode(unsigned short K1,
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
                        istream& i1_1,
                        istream& i1_2,
                        istream& o1_1,
                        istream& o1_2,
                        istream& bfcounterFile,
                        unsigned short pairedReadsAlgorithm,
                        bool correct,
                        string idPrefix,
                        mt4cpp::Progress* progress) {

        FileReader fileReader;
        InputFile inputFile1(i1_1);
        fileReader.setInputFile1(&inputFile1);
        InputFile inputFile2(i1_2);
        fileReader.setInputFile2(&inputFile2);

        DeBruijnGraph deBruijnGraph;
        string result;
        boost::tuple<CompressedUnitigs, vector<bool>, unsigned long> unitigsGeneratorResult;
        
        vector<char> firstChars;
        vector<uint48> compressedTargets;
        bool isBfcounterFileGood = bfcounterFile.good();
        string kmerOccurrenceTableSalt = to_string(rand());
        string kmerOccurrenceTableFilename = CALC_TMP_DIR+string("kmerOccurrenceTable_"+kmerOccurrenceTableSalt);

        Statistics statistics;
        if (K1 < 2 || genomeLength < 2) {
            logError("invalid K or genome length value");
            return "";
        }

        if (!isBfcounterFileGood) {
            KMerCounter kMerCounter(fileReader, K1, qualityThreshold, kmerOccurrenceTableFilename, progress);
            kMerCounter.calcKMersOccurrenceTable();
            ifstream bfcounterFile(kmerOccurrenceTableFilename);
            SingleGraph singleGraph(deBruijnGraph, bfcounterFile, K1, bfcounterThreshold);
            SingleGraphBuilder singleGraphBuilder(singleGraph, statistics, progress);
            singleGraphBuilder.build(firstChars, compressedTargets);
        } else {
            SingleGraph singleGraph(deBruijnGraph, bfcounterFile, K1, bfcounterThreshold);
            SingleGraphBuilder singleGraphBuilder(singleGraph, statistics, progress);
            singleGraphBuilder.build(firstChars, compressedTargets);
        }

        UncompressedUnitigs uncompressedUnitigs;

        if (correct) {
            RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, K1+1);
            removeTips();
        }

        CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounterBeforeRemovingLowCounterEdges(deBruijnGraph);
        correctEdgeCounterBeforeRemovingLowCounterEdges();
        RemoveLowCounterEdges<DeBruijnGraph> removeLowCounterEdges(deBruijnGraph, singleEdgeCounterThreshold);
        removeLowCounterEdges();
        CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounterAfterRemovingLowCounterEdges(deBruijnGraph);
        correctEdgeCounterAfterRemovingLowCounterEdges();
        EdgeNormalization<DeBruijnGraph> edgeNormalization(deBruijnGraph, K1+1, genomeLength,
                                                         singleEdgeCounterThreshold);
        RemoveBubbles<DeBruijnGraph> removeBubbles(deBruijnGraph, K1+1, edgeNormalization.getNormalizationRate());

        if (correct) {
            RemoveTips<DeBruijnGraph> removeTips(deBruijnGraph, K1+1);
            removeTips();
            removeBubbles();
            CorrectEdgeCounter<DeBruijnGraph> correctEdgeCounterAfterRemovingBubbles(deBruijnGraph);
            correctEdgeCounterAfterRemovingBubbles();
        }

        edgeNormalization.normalizeEdges();

        GraphCompressor<DeBruijnGraph, CompressedDeBruijnGraph> graphCompressor(deBruijnGraph);
        graphCompressor.compressGraph();

        UnitigsGenerator<CompressedDeBruijnGraph> generate(graphCompressor.getCompressedGraph(), progress, 2.0);
        unitigsGeneratorResult = generate();

        unsigned long long numVertices = num_vertices(deBruijnGraph);
        deBruijnGraph = DeBruijnGraph();

        vector<bitset<2*MAX_KMER_LENGTH>> sequences(numVertices);
        if (!isBfcounterFileGood) {
            ifstream bfcounterFile(kmerOccurrenceTableFilename);
            SingleGraph singleGraph(deBruijnGraph, bfcounterFile, K1, bfcounterThreshold);
            singleGraph.buildSequencesVector(sequences, compressedTargets);
        } else {
            SingleGraph singleGraph(deBruijnGraph, bfcounterFile, K1, bfcounterThreshold);
            singleGraph.buildSequencesVector(sequences, compressedTargets);
        }

        UnitigsUncompressor<DeBruijnGraph, CompressedDeBruijnGraph> unitigsUncompressor(graphCompressor.getCompressedGraph());
        unitigsUncompressor.uncompressUnitigs(uncompressedUnitigs, unitigsGeneratorResult.get<0>());

        removeBubbles.logBubbles(firstChars, sequences);

        ResultantSequencesGenerator<DeBruijnGraph> resultantSequencesGenerator(uncompressedUnitigs, firstChars, sequences, K1, statistics);

        Output<DeBruijnGraph> output(result, statistics, resultantSequencesGenerator, idPrefix);
        output.generateApplicationOutput();

        if (pairedReadsAlgorithm == 1U) {  // using paired-end tags
            ofstream ofile(CALC_TMP_DIR+string("unitigs.fa"));
            ofile << result;
            ofile.close();
            ifstream unitigsFile(CALC_TMP_DIR+string("unitigs.fa"));
            result = "";
            Statistics contigsStatistics;

            UnitigsToContigsExtension unitigsToContigsExtension(K1, insertSizeMeanInward, insertSizeStdDevInward, 100, pairedReadsPetThresholdFrom, pairedReadsPetThresholdTo, unitigsFile, unitigsGeneratorResult.get<1>(), progress);
            InwardPairedReadsAdding<UnitigsToContigsExtension> addInwardPairedReads(fileReader, unitigsToContigsExtension, qualityThreshold, progress);
            addInwardPairedReads();
            logInfo("contigs graph: vertices: "
                    + to_string(num_vertices(unitigsToContigsExtension.getUnitigsGraph()))
                    + ", edges: " + to_string(num_edges(unitigsToContigsExtension.getUnitigsGraph())));
            UnitigsToContigsExtension::Contigs contigs = unitigsToContigsExtension.extendContigs();
            ResultantSequencesGenerator<UnitigsToContigsExtension::UnitigsGraph> resultantSequencesGenerator(contigs, unitigsFile, K1, contigsStatistics);
            unitigsFile.close();
            Output<UnitigsToContigsExtension::UnitigsGraph> output(result, contigsStatistics, resultantSequencesGenerator, idPrefix);
            output.generateApplicationOutput();
        }
        if (o1_1.good() || o1_2.good()) {   // using mate-pairs
            ofstream ofile(CALC_TMP_DIR+string("contigs.fa"));
            ofile << result;
            ofile.close();
            ifstream unitigsFile(CALC_TMP_DIR+string("unitigs.fa"));
            ifstream contigsFile(CALC_TMP_DIR+string("contigs.fa"));
            result = "";
            Statistics scaffoldsStatistics;

            FileReader fileReaderMP;
            InputFile inputFile1(o1_1);
            fileReaderMP.setInputFile1(&inputFile1);
            InputFile inputFile2(o1_2);
            fileReaderMP.setInputFile2(&inputFile2);

            ContigsToScaffoldsExtension contigsToScaffoldsExtension(K1, insertSizeMeanOutward, insertSizeStdDevOutward, 100, pairedReadsMpThresholdFrom, pairedReadsMpThresholdTo, unitigsFile, contigsFile, unitigsGeneratorResult.get<1>(), progress);
            OutwardPairedReadsAdding<ContigsToScaffoldsExtension> addOutwardPairedReads(fileReaderMP, contigsToScaffoldsExtension, qualityThreshold, progress);
            addOutwardPairedReads();
            logInfo("contigs graph: vertices: "
                    + to_string(num_vertices(contigsToScaffoldsExtension.getContigsGraph()))
                    + ", edges: " + to_string(num_edges(contigsToScaffoldsExtension.getContigsGraph())));
            ContigsToScaffoldsExtension::Contigs scaffolds = contigsToScaffoldsExtension.extendContigs();
            ResultantSequencesGenerator<ContigsToScaffoldsExtension::ContigsGraph> resultantSequencesGenerator(scaffolds, contigsFile, K1, scaffoldsStatistics);
            contigsFile.close();
            Output<ContigsToScaffoldsExtension::ContigsGraph> output(result, scaffoldsStatistics, resultantSequencesGenerator, idPrefix);
            output.generateApplicationOutput();
        }
        if (progress != NULL)
            progress->setProgress(1.0);
        return result;
    }

    string alignMode(istream& sequenceInput,
           istream& referenceInput,
           bool isHirschbergAlgorithm,
           bool isCircular,
           short int d,
           short int substitutionMatrix[16],
           mt4cpp::Progress* progress) {

        logInfo("start align sequences...");
        vector<Mismatch> mismatches;
        InputFile seqInputFile(sequenceInput);
        FileReader seqFileReader;
        seqFileReader.setInputFile1(&seqInputFile);
        unsigned int numOfSequences = seqFileReader.getNumOfReads();
        unsigned int numOfAlignedSequence = 0U;
        InputFile refInputFile(referenceInput);
        Read readSeq(0U), readRef(0U);
        refInputFile.readSingleRead(readRef);
        string sequence = "";
        string sequenceId = "";
        string reference = readRef.getRead();

        if (progress != NULL)
            progress->setProgress(0.1);

        while (true) {
            seqInputFile.readSingleRead(readSeq);
            sequence = readSeq.getRead();

            if (readSeq.getDescription().length() > 1) {
                sequenceId = (readSeq.getDescription()).substr(1);    // without begining '>' sign
            } else {
                sequenceId = "";
            }

            if (sequence == "" || reference == "")
                break;
            SequenceAlignment sequenceAlignment(sequence, reference, sequenceId, d,
                    substitutionMatrix, progress, numOfAlignedSequence++, numOfSequences);
            vector<Mismatch> singleSeqMismatches;

            if (isHirschbergAlgorithm) {
                singleSeqMismatches = sequenceAlignment.alignSeqHirAlg(isCircular);
            } else {
                singleSeqMismatches = sequenceAlignment.alignSeqNeeWunAlg(isCircular);
            }
            mismatches.insert(mismatches.end(), singleSeqMismatches.begin(), singleSeqMismatches.end());
        }

        if (progress != NULL)
            progress->setProgress(1.0);

        OutputVCF outputVCF(mismatches);
        return outputVCF.generateVCFOutput();
    }

}}
