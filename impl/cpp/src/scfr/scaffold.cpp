/**
 * \file scaffold.cpp
 * \brief the C++ file with interface for scaffolder module
 */

#include "scaffold.hpp"
#include "BloomFilterFiller.hpp"
#include "MatepairGraphBuilder.hpp"
#include "KmerPositionFinder.hpp"
#include "ContigPairMaker.hpp"
#include "ContigLoader.hpp"
#include "Scaffolder.hpp"
#include "FileLogger.hpp"

#include <fstream>
#include "../common/log.hpp"

#include <thread>

using namespace dnaasm::scfr;
using namespace std;

int getFileSize(string file) {
    ifstream is (file.c_str(), ifstream::ate | ifstream::binary);
    return is.tellg();
}

namespace dnaasm { namespace scfr {

    string scaffold(const string &contigsFilePath,
                    const string &readsFilePath,
                    unsigned short int kmerSize,
                    unsigned short int distance,
                    unsigned short int step,
                    unsigned short int minLinks,
                    unsigned short int minReads,
                    unsigned short int minLinksPerRead,
                    float maxRatio,
                    unsigned int minContigLength,
                    bool gapFilling,
                    mt4cpp::Progress* progress) {

        // 0. Open input files
        if (progress != nullptr) { progress->setProgress(0.0); }

        if (contigsFilePath == "" || readsFilePath == "") {
            string type = contigsFilePath == "" ? "contigs" : "reads";
            logInfo("Empty input file with " + type);
            if (progress != nullptr) { progress->setProgress(1.0); }
            return "";
        }

        ifstream contigsFile(contigsFilePath.c_str());
        ifstream readsFile(readsFilePath.c_str());
        InputFile contigsInputFile(contigsFile);
        InputFile readsInputFile(readsFile);
        unsigned int contigsFileSize = (unsigned int)getFileSize(contigsFilePath);
        unsigned int readsFileSize = (unsigned int)getFileSize(readsFilePath);

        if (contigsFileSize == 0 || readsFileSize == 0) {
            auto fileName = contigsFileSize == 0 ? contigsFilePath : readsFilePath;
            logInfo("Empty file: " + fileName);
            if (progress != nullptr) { progress->setProgress(1.0); }
            return "";
        }

        // 1. Read contig sequences into memory
        if (progress != nullptr) { progress->setProgress(0.15); }
        logInfo("Loading whole contig sequences from contig file...");
        ContigSeqHashMap contigs =
            ContigLoader::loadContigsIntoMemory(contigsInputFile,
                                                "contig_correspondence.log");
        logInfo("Done loading contigs into memory.");

        // 2. Create Bloom Filter and fill it with k-mers extracted from contigs
        common::BloomFilter<std::string> bloomFilter(contigsFileSize, kmerSize);
        logInfo("Saving " + to_string(kmerSize)
                + "-mers from contigs in Bloom filter..");
        BloomFilterFiller::fillBloomFilter(contigs, bloomFilter);

        // 3. Extract k-mer pairs from long reads and build graph from them
        //    All reads are saved into memory during this step as well.
        if (progress != nullptr) { progress->setProgress(0.25); }
        logInfo("Extracting pairs of " + std::to_string(kmerSize)
            + "-mers from long reads which exist in Bloom filter...");
        MatepairGraph matepairs(kmerSize);
        MatepairGraphBuilder matepairGraphBuilder(matepairs, bloomFilter,
                                                  readsInputFile, kmerSize,
                                                  distance, step);
        unsigned int totalReadsNum = matepairGraphBuilder.buildGraph();
        logInfo("Extracted " + to_string(boost::num_edges(matepairs.graph()))
                + " pairs of " + to_string(kmerSize)
                + "-mers from " + to_string(totalReadsNum) + " long reads.");
        logInfo("Matepairs has " + to_string(boost::num_vertices(matepairs.graph())) + " vertices.");

        /*
        FileLogger::logImportantRegionsOnReads(
            "important_regions.log", matepairs, matepairGraphBuilder);
        */

        // 4. Find positions of k-mers on contig for all k-mers in graph
        if (progress != nullptr) { progress->setProgress(0.50); }
        logInfo("Gathering info about " + to_string(kmerSize)
                + "-mers which exist both on contigs and reads...");
        KmerPositionFinder kmerPositionFinder(matepairs, contigs,
                                              kmerSize, minContigLength);
        unsigned int filteredContigsNum = kmerPositionFinder.findKmerPositionOnContigs();
        logInfo("Considering " + to_string(filteredContigsNum) + " contigs"
                + " (>=" + to_string(minContigLength) + " bp)");

        // 5. Pair contigs
        if (progress != nullptr) { progress->setProgress(0.75); }
        logInfo("Contig pairing...");
        ContigPairGraph contigPairs;
        ContigPairMaker contigPairMaker(matepairs, contigs,
                                        contigPairs, distance);
        contigPairMaker.pairContigs();
        logInfo("Done contig pairing. " + to_string(num_edges(contigPairs))
                + " putative contig pairs found.");

        // save info about all possible contig pairs into file
        FileLogger::logContigPairs("contig_pairs.log", contigPairs, matepairs);

        // 6. Build scaffolds
        if (progress != nullptr) { progress->setProgress(0.80); }
        logInfo("Building scaffolds...");
        stringstream scaffoldCSV;
        Scaffolder scaffolder(minLinks, minReads,
                              minLinksPerRead, maxRatio, matepairs);
        scaffolder.buildScaffolds(contigPairs, contigs, scaffoldCSV);
        logInfo("Done building scaffolds.");

        // 7. Save scaffolds to files in CSV and FASTA formats
        if (progress != nullptr) { progress->setProgress(0.90); }
        ofstream csv("scaffolds.csv");
        csv << scaffoldCSV.str();
        csv.close();
        stringstream scaffoldFASTA;
        ReadSeqHashMap readSequences = matepairGraphBuilder.getReadSeqHashMap();
        logInfo("Saving created scaffolds into FASTA file...");
        scaffolder.saveScaffoldsToFasta(contigs, readSequences,
                                        scaffoldCSV, scaffoldFASTA, gapFilling);
        //logInfo("Scaffolds saved to FASTA file.");
        string result = scaffoldFASTA.str();

        // save all possible gap sequences for scaffolds in files
        const ContigPathHashMap &contigPaths = scaffolder.getContigPaths();
        FileLogger::logGapSequences("./gap_sequences", contigPaths,
                                    contigPairs, matepairs, readSequences);

        // save gap length histograms in files
        FileLogger::logGapLengthHistogram("./gap_sequences", contigPaths,
                                          contigPairs);

        if (progress != nullptr) { progress->setProgress(1.0); }
        contigsFile.close();
        readsFile.close();

        return result;
    }

}} //namespace dnaasm::scfr
