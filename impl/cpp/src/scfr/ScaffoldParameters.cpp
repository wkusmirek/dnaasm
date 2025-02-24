/**
 * \file ScaffoldParameters.cpp
 * \brief the C++ file with implementation of class for representing scaffolder parameters
 *
 */

#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "ScaffoldParameters.hpp"

using namespace std;
using namespace boost;

namespace dnaasm { namespace scfr {
    ScaffoldParameters::ScaffoldParameters(map<string, string>& parameters)
        : Parameters(parameters)
    { initParameters(); parametersService(parameters); }

    void ScaffoldParameters::initParameters() {
        contigsFilePath_ = "";
        readsFilePath_ = "";
        kmerSize_ = 15U;
        distance_ = 4000U;
        step_ = 2U;
        minLinks_ = 5U;
        minReads_ = 1U;
        minLinksPerRead_ = 1U;
        maxRatio_ = 0.3;
        minContigLength_ = 500U;
        gapFilling_ = true;
        Parameters::initParameters();
    }

    void ScaffoldParameters::printHelpForModule() {
        cout << "-scaffold\tbuild scaffolds from contigs and long reads" << endl;
        cout << "\te.g." << endl;
        cout << "\t./dnaasm -scaffold -contigs_file_path contigs.fa -long_reads_file_path reads.fa -kmer_size 15 -distance 4000 -step 2 -min_links 5 -max_ratio 0.3 -min_contig_length 500 -output_file_name scaffolds.fa" << endl;
        cout << "\tdnaasm.exe -scaffold -contigs_file_path contigs.fa -long_reads_file_path reads.fa -kmer_size 15 -distance 4000 -step 2 -min_links 5 -max_ratio 0.3 -min_contig_length 500 -output_file_name scaffolds.fa" << endl << endl;
        cout << "Parameters:" << endl << endl;
        cout << "  -contigs_file_path <file_name>\tcontigs file in FASTA format" << endl << endl;
        cout << "  -long_reads_file_path <file_name>\treads file in FASTA format" << endl << endl;
        cout << "  -kmer_size <int>\tlength of k-mers extracted from reads and mapped into contigs. Default: 15" << endl << endl;
        cout << "  -distance <int>\tdistance between the 5’-end of each extracted k-mer pair. Default: 4000" << endl << endl;
        cout << "  -step <int>\tdefault step of sliding window during k-mer extraction. Default: 2" << endl << endl;
        cout << "  -min_links <int>\tminimum number of links (k-mer pairs) between two contigs to compute scaffold. Default: 5" << endl << endl;
        cout << "  -min_lpr <int>\tminimum number of links (between two contigs) coming from a single read to compute scaffold. Default: 1" << endl << endl;
        cout << "  -min_reads <int>\tminimum number of reads for which min_lpr threshold must be satisfied to compute scaffold. Default: 1" << endl << endl;
        cout << "  -max_ratio <float>\tmaximum link ratio between two best contigs to be paired. Default: 0.3"<< endl << endl;
        cout << "  -min_contig_length <int>\tminimum contig length to consider for scaffolding. Default: 500"<< endl << endl;
        cout << "  -gapfilling <int>\tenable gap filling on scaffolds. Default: 1"<< endl << endl;
        cout << "  -output_file_name <file_name>\toutput file name. Default: out"<< endl << endl;
    }

    std::string ScaffoldParameters::getContigsFilePath() const {
        return contigsFilePath_;
    }

    std::string ScaffoldParameters::getReadsFilePath() const {
        return readsFilePath_;
    }

    unsigned short int ScaffoldParameters::getKmerSize() const {
        return kmerSize_;
    }

    unsigned short int ScaffoldParameters::getDistance() const {
        return distance_;
    }

    unsigned short int ScaffoldParameters::getStep() const {
        return step_;
    }

    unsigned short int ScaffoldParameters::getMinLinks() const {
        return minLinks_;
    }

    unsigned short int ScaffoldParameters::getMinReads() const {
        return minReads_;
    }

    unsigned short int ScaffoldParameters::getMinLinksPerRead() const {
        return minLinksPerRead_;
    }

    float ScaffoldParameters::getMaxRatio() const {
        return maxRatio_;
    }

    unsigned int ScaffoldParameters::getMinContigLength() const {
        return minContigLength_;
    }

    bool ScaffoldParameters::getGapFilling() const {
        return gapFilling_;
    }

    void ScaffoldParameters::parametersService(std::map<std::string, std::string>& parameters) {
        if (parameters.size() <= 1) {
            printHelpForModule();
            initParameters();
            return;
        }

        mode_ = "-scaffold";

        for (const auto & parameter : parameters) {
            try {
                if (parameter.first == "output_file_name" || parameter.first == "-output_file_name") {
                    output_file_name_ = string(parameter.second);
                    continue;
                } else if (parameter.first == "kmer_size" || parameter.first == "-kmer_size") {
                    if (lexical_cast<int>(parameter.second) < 1) {
                        cout << "K-mer_size is too small, have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    kmerSize_ = lexical_cast<unsigned short int>(parameter.second);
                    continue;
                } else if (parameter.first == "distance" || parameter.first == "-distance") {
                    if (lexical_cast<int>(parameter.second) < 1) {
                        cout << "Distance is too small, have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    distance_ = lexical_cast<unsigned short int>(parameter.second);
                    continue;
                } else if (parameter.first == "step" || parameter.first == "-step") {
                    if (lexical_cast<int>(parameter.second) < 1) {
                        cout << "Step is too small, have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    step_ = lexical_cast<unsigned short int>(parameter.second);
                    continue;
                } else if (parameter.first == "min_links" || parameter.first == "-min_links") {
                    if (lexical_cast<int>(parameter.second) < 1) {
                        cout << "Minimum number of links is too small, have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    minLinks_ = lexical_cast<unsigned short int>(parameter.second);
                    continue;
                } else if (parameter.first == "min_reads" || parameter.first == "-min_reads") {
                    if (lexical_cast<int>(parameter.second) < 1) {
                        cout << "Minimum number of reads is too small, have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    minReads_ = lexical_cast<unsigned short int>(parameter.second);
                    continue;
                } else if (parameter.first == "min_lpr" || parameter.first == "-min_lpr") {
                    if (lexical_cast<int>(parameter.second) < 1) {
                        cout << "Minimum number of links per read (lpr) is too small, have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    minLinksPerRead_ = lexical_cast<unsigned short int>(parameter.second);
                    continue;
                } else if (parameter.first == "max_ratio" || parameter.first == "-max_ratio") {
                    maxRatio_ = lexical_cast<float>(parameter.second);
                    if (maxRatio_ <= 0.0 || maxRatio_ >= 1.0) {
                        cout << "Max ratio have to be float between 0 and 1" << endl;
                        initParameters();
                        return;
                    }
                    continue;
                } else if (parameter.first == "min_contig_length" || parameter.first == "-min_contig_length") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "Minimum contig length is too small, have to be greater or equal 0" << endl;
                        initParameters();
                        return;
                    }
                    minContigLength_ = lexical_cast<unsigned int>(parameter.second);
                    continue;
                } else if (parameter.first == "gapfilling" || parameter.first == "-gapfilling") {
                    if (lexical_cast<int>(parameter.second) != 0 && lexical_cast<int>(parameter.second) != 1) {
                        cout << "Gap filling switch must have value 0 or 1" << endl;
                        initParameters();
                        return;
                    }
                    gapFilling_ = lexical_cast<bool>(parameter.second);
                    continue;
                }
            }
            catch(bad_lexical_cast&) {}
            if (parameter.first == "contigs_file_path" || parameter.first == "-contigs_file_path") {
                contigsFilePath_ = parameter.second;
                ifstream fileCheck(parameter.second.c_str());
                if (!fileCheck) {   //check if file exists
                    cout << parameter.second << ": no such file" << endl;
                    initParameters();
                    return;
                }
                fileCheck.close();
                continue;
            }
            if (parameter.first == "long_reads_file_path" || parameter.first == "-long_reads_file_path") {
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
        if (contigsFilePath_ == "" || readsFilePath_ == "") {
            cout << "-contigs_file_path and -long_reads_file_path parameters are obligatory!" << endl;
            initParameters();
        }
    }
}}
