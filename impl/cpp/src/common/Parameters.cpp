/**
 * \file Parameters.cpp
 * \brief the C++ file with implementation of class for representing parameters specified by user (only for desktop application)
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Parameters.hpp"

using namespace std;

namespace dnaasm { namespace common {

    const std::set<std::string> Parameters::modesAllowed = {
        "-assembly",
        "-align",
        "-scaffold",
        "-olc",
        "-bst"
    };

    Parameters::Parameters(ParametersMap &params) {
        initParameters(); parametersService(params);
    }

    const char * Parameters::getMode() const {
        return mode_;
    }

    string Parameters::getOutputFileName() const {
        return output_file_name_;
    }

    bool Parameters::getPrintHelp() const {
        return print_help_;
    }

    void Parameters::printHelpForModule() {
        cout << endl << "DnaAssembler - genome assembler for next generation sequencing, using de Bruijn graph" << endl;
        cout << "Authors: Robert Nowak, Wiktor Kuśmirek" << endl;
        cout << "Institute of Computer Science" << endl;
        cout << "Warsaw University of Technology" << endl << endl;

        cout << "Help:" << endl << endl;
        cout << "Modes supported: -assembly, -align, -olc, -scaffold, -bst" << endl << endl;
        cout << "e.g. ./dnaasm -assembly -help" << endl;
        cout << "\tprints detailed help about assembly mode" << endl << endl;

        cout << "For more information, problems, suggestions, etc. send an email:" << endl;
        cout << "\tR.M.Nowak@elka.pw.edu.pl" << endl << endl;
    }

    Parameters::ParametersMap Parameters::convertArgvToMap(int argc, const char* argv[]) {
        ParametersMap parameters;
        std::vector<string> validParams {
            "-help",
            "-output_file_name",
        // assembly
            "-k",
            "-genome_length",
            "-correct",
            "-paired_reads_algorithm",
            "-insert_size_mean_inward",
            "-insert_size_std_dev_inward",
            "-insert_size_mean_outward",
            "-insert_size_std_dev_outward",
            "-quality_threshold",
            "-bfcounter_threshold",
            "-single_edge_counter_threshold",
            "-paired_reads_pet_threshold_from",
            "-paired_reads_pet_threshold_to",
            "-i1_1", "-i1_2",
            "-paired_reads_mp_threshold_from",
            "-paired_reads_mp_threshold_to",
            "-o1_1", "-o1_2",
            "-bfc_file",
        // align
            "-gap_penalty",
            "-align_algorithm",
            "-circular",
            "-sequence",
            "-reference",
            "-AA", "-AC", "-AG", "-AT",
            "-CA", "-CC", "-CG", "-CT",
            "-GA", "-GC", "-GG", "-GT",
            "-TA", "-TC", "-TG", "-TT",
        // scaffold
            "-contigs_file_path",
            "-long_reads_file_path",
            "-kmer_size",
            "-distance",
            "-step",
            "-min_links",
            "-min_reads",
            "-min_lpr",
            "-max_ratio",
            "-min_contig_length",
            "-gapfilling",
        // olc
            "-input_file_name",
            "-kmer_length",
            "-sketch_num",
            "-min_jaccard_sim",
            "-match_score",
            "-mismatch_score",
            "-gap_penalty",
            "-min_edge",
            "-min_contig_length",
            "-path_width",
        // bst
            "-input_file_path",
            "-kmer_size",
            "-min_similarity"
        };

        // recognize mode
        if (argc < 2) {
            return ParametersMap();
        } else {
            string mode = string(argv[1]);

            if (mode != "-help" && !modesAllowed.count(mode)) {
                return ParametersMap();
            }

            parameters.emplace(mode, "");
        }

        for (int i = 2; i < argc; ++i) {
            string p = string(argv[i]);

            if (find(validParams.begin(),
                     validParams.end(),
                     p) == validParams.end()) {
                cout << p << " not recognized!" << endl;

                return ParametersMap();
            }

            string value = ++i < argc ? string(argv[i]) : "";
            parameters.emplace(p, value);
        }
        return parameters;
    }

    void Parameters::initParameters() {
        mode_ = NULL;
        output_file_name_ = "out";
        print_help_ = false;
    }

    void Parameters::parametersService(ParametersMap &parameters) {
        if (parameters.empty() || parameters.size() == 1) {
            printHelpForModule();
            initParameters();
            return;
        }

        for (const auto & parameter : parameters) {
            if (modesAllowed.count(parameter.first)) {
                mode_ = parameter.first.c_str();
            } else if (parameter.first == "-help") {
                print_help_ = true; // help for specific module
            } else if (parameter.first == "output_file_name" ||
                parameter.first == "-output_file_name") {
                output_file_name_ = string(parameter.second);
            }
        }
    }
}}
