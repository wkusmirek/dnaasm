/**
 * \file OlcParameters.cpp
 * \brief the C++ file with implementation of class for representing olc parameters
 *
 */

#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "OlcParameters.hpp"

using namespace std;
using namespace boost;

namespace dnaasm {
    namespace olc {
        OlcParameters::OlcParameters(map<string, string> &parameters)
                : Parameters(parameters) {
            initParameters();
            parametersService(parameters);
        }

        void OlcParameters::initParameters() {
            kmerLength_ = 15U;
            sketchNum_ = 256;
            minJaccardSim_ = 0.5f;
            matchScore_ = 1;
            mismatchScore_ = -1;
            gapPenalty_ = -1;
            minEdge_ = 0U;
            minContigLength_ = 0U;
            pathWidth_ = 10000U;
            Parameters::initParameters();
        }

        void OlcParameters::printHelpForModule() {
            std::cout
                    << "-olc\tmake graph for input file (set of long reads) and write contigs to the file\n";
            std::cout << "\te.g.\n";
            std::cout
                    << "\t./dnaasm -olc -reads_input_file reads.fa -min_jaccard_sim 0.4 -kmer_length 16 -output_file_name result\n";
            std::cout
                    << "\tdnaasm.exe -olc -reads_input_file reads.fa -min_jaccard_sim 0.4 -kmer_length 16 -output_file_name result\n\n";
            std::cout << "Parameters:\n\n";
            std::cout
                    << "  -input_file_name <string>\t Path to input file containing long reads (FASTA format)\n\n";
            std::cout
                    << "  -kmer_length <int>\tLength of kmer which will be created from reads. Default: 15\n\n";
            std::cout
                    << "  -sketch_num <int>\tNumber of sketches representing one sequence in MinHash. Default: 256\n\n";
            std::cout
                    << "  -min_jaccard_sim <int>\tMinimum Jaccard Similarity Estimate. Default: 0.5\n\n";
            std::cout
                    << "  -match_score <int>\tMatch score in Smith-Waterman algorithm. Default: 1\n\n";
            std::cout
                    << "  -mismatch_score <int>\tMismatch score in Smith-Waterman algorithm. Default: 1\n\n";
            std::cout
                    << "  -gap_penalty <int>\tGap penalty in Smith-Waterman algorithm. Default: 1\n\n";
            std::cout
                    << "  -min_edge <int>\tMinimum total alignment score needed to create an edge in Overlap Graph. Default: 1000\n\n";
            std::cout
                    << "  -min_contig_length <int>\tMinimum length of an output contig. Default: 0\n\n";
            std::cout
                    << "  -path_width <int>\tWidth of the path in Needleman-Wunsch score matrix. Default: 10000\n\n";
            std::cout << "  -output_file_name <file_name>\toutput file name. Default: out\n\n";
        }

        std::string OlcParameters::getReadsFilePath() const { return readsFilePath_; }

        unsigned short int OlcParameters::getKmerLength() const { return kmerLength_; }

        unsigned short int OlcParameters::getSketchNum() const { return sketchNum_; }

        float OlcParameters::getMinJaccardSim() const { return minJaccardSim_; }

        short int OlcParameters::getMatchScore() const { return matchScore_; }

        short int OlcParameters::getMismatchScore() const { return mismatchScore_; }

        short int OlcParameters::getGapPenalty() const { return gapPenalty_; }

        unsigned short int OlcParameters::getMinEdge() const { return minEdge_; }

        unsigned short int OlcParameters::getMinContigLength() const { return minContigLength_; }

        unsigned short int OlcParameters::getPathWidth() const { return pathWidth_; }

        void OlcParameters::parametersService(std::map<std::string, std::string> &parameters) {
            if (parameters.size() == 0) {
                printHelpForModule();
                initParameters();
                return;
            }

            mode_ = "-olc";

            for (const auto &parameter : parameters) {
                try {
                    if (parameter.first == "output_file_name" ||
                        parameter.first == "-output_file_name") {
                        output_file_name_ = string(parameter.second);
                        continue;
                    } else if (parameter.first == "kmer_length" ||
                               parameter.first == "-kmer_length") {
                        kmerLength_ = lexical_cast<unsigned short int>(parameter.second);
                        if (kmerLength_ < 1) {
                            cout << "K-mer_len is to small, have to be greater than 0\n";
                            initParameters();
                            return;
                        }
                        continue;
                    } else if (parameter.first == "sketch_num" ||
                               parameter.first == "-sketch_num") {
                        sketchNum_ = lexical_cast<unsigned short int>(parameter.second);
                        if (sketchNum_ < 128) {
                            cout
                                    << "Number of sketches is to small, have to be greater than or equal 128\n";
                            initParameters();
                            return;
                        }
                        continue;
                    } else if (parameter.first == "min_jaccard_sim" ||
                               parameter.first == "-min_jaccard_sim") {
                        minJaccardSim_ = lexical_cast<float>(parameter.second);
                        if (minJaccardSim_ < 0 || minJaccardSim_ > 1) {
                            cout << "Minimal Jaccard similarity estimate should be from [0;1]\n";
                            initParameters();
                            return;
                        }
                        continue;
                    } else if (parameter.first == "match_score" ||
                               parameter.first == "-match_score") {
                        matchScore_ = lexical_cast<short int>(parameter.second);
//                        if (matchScore_ < 0 || matchScore_ > 1) {
//                            cout << "Minimal Jaccard similarity estimate should be from [0;1]\n";
//                            initParameters();
//                            return;
//                        }
                        continue;
                    } else if (parameter.first == "mismatch_score" ||
                               parameter.first == "-mismatch_score") {
                        mismatchScore_ = lexical_cast<short int>(parameter.second);
//                        if (matchScore_ < 0 || matchScore_ > 1) {
//                            cout << "Minimal Jaccard similarity estimate should be from [0;1]\n";
//                            initParameters();
//                            return;
//                        }
                        continue;

                    } else if (parameter.first == "gap_penalty" ||
                               parameter.first == "-gap_penalty") {
                        gapPenalty_ = lexical_cast<short int>(parameter.second);
//                        if (matchScore_ < 0 || matchScore_ > 1) {
//                            cout << "Minimal Jaccard similarity estimate should be from [0;1]\n";
//                            initParameters();
//                            return;
//                        }
                        continue;
                    } else if (parameter.first == "min_edge" ||
                               parameter.first == "-min_edge") {
                        minEdge_ = lexical_cast<unsigned short int>(parameter.second);
//                        if (matchScore_ < 0 || matchScore_ > 1) {
//                            cout << "Minimal Jaccard similarity estimate should be from [0;1]\n";
//                            initParameters();
//                            return;
//                        }
                        continue;
                    } else if (parameter.first == "min_contig_length" ||
                               parameter.first == "-min_contig_length") {
                        minContigLength_ = lexical_cast<unsigned short int>(parameter.second);
//                        if (matchScore_ < 0 || matchScore_ > 1) {
//                            cout << "Minimal Jaccard similarity estimate should be from [0;1]\n";
//                            initParameters();
//                            return;
//                        }
                        continue;
                    } else if (parameter.first == "path_width" ||
                               parameter.first == "-path_width") {
                        pathWidth_ = lexical_cast<unsigned short int>(parameter.second);
//                        if (matchScore_ < 0 || matchScore_ > 1) {
//                            cout << "Minimal Jaccard similarity estimate should be from [0;1]\n";
//                            initParameters();
//                            return;
//                        }
                        continue;
                    }
                } catch (bad_lexical_cast &) {}

                if (parameter.first == "input_file_name" ||
                    parameter.first == "-input_file_name") {
                    readsFilePath_ = parameter.second;
                    ifstream fileCheck(parameter.second.c_str());
                    if (!fileCheck) {   //check if file exists
                        cout << parameter.second << ": no such file" << endl;
                        initParameters();
                        return;
                    }
                    fileCheck.close();
                    continue;
                }
            }

            if (readsFilePath_ == "") {
                cout << "-input_file_name parameter is obligatory!" << endl;
                initParameters();
            }
        }
    }
} //namespace dnaasm::olc
