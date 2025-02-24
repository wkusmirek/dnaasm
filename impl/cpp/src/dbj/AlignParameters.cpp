/**
 * \file AlignParameters.cpp
 * \brief the C++ file with implementation of class for representing dbj align parameters
 *
 */

#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "AlignParameters.hpp"

using namespace std;
using namespace boost;

namespace dnaasm { namespace dbj {
    AlignParameters::AlignParameters(Parameters::ParametersMap& parameters)
        : Parameters(parameters)
    { initParameters(); parametersService(parameters); }

    void AlignParameters::initParameters() {
        sequence_ = "";
        reference_ = "";
        isHirschbergAlgorithm_ = true;
        circular_ = false;
        gap_penalty_ = -1;
        initSubstitutionMatrix();
        Parameters::initParameters();
    }

    void AlignParameters::printHelpForModule() {
        cout << "-align\talign genome" << endl;
        cout << "\te.g." << endl;
        cout << "\t./dnaasm -align -align_algorithm nw -circular 0 -gap_penalty -1 -AA 1 -AC -1 -AG -1 -AT -1 -CA -1 -CC 1 -CG -1 -CT -1 -GA -1 -GC -1 -GG 1 -GT -1 -TA -1 -TC -1 -TG -1 -TT 1 -sequence seq.fasta -reference ref.fasta" << endl;
        cout << "\tdnaasm.exe -align -align_algorithm nw -circular 0 -gap_penalty -1 -AA 1 -AC -1 -AG -1 -AT -1 -CA -1 -CC 1 -CG -1 -CT -1 -GA -1 -GC -1 -GG 1 -GT -1 -TA -1 -TC -1 -TG -1 -TT 1 -sequence seq.fasta -reference ref.fasta" << endl << endl;
        cout << "Parameters:" << endl << endl;
        cout << "  -align_algorithm <string>\tset to 'h' if Hirschberg's algorithm should be used, 'nw' for Needleman-Wunsch algorithm. Default: 'h'"<< endl << endl;
        cout << "  -circular <int>\tset to '1' if genome is circular, otherwise '0'. Default: 0"<< endl << endl;
        cout << "  -gap_penalty <int>\tgap penalty. Default: -1" << endl << endl;
        cout << "  -AA <int>\tvalue of cell 'AA' in similarity matrix. Default: 1"<< endl << endl;
        cout << "  -AC <int>\tvalue of cell 'AC' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -AG <int>\tvalue of cell 'AG' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -AT <int>\tvalue of cell 'AT' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -CA <int>\tvalue of cell 'CA' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -CC <int>\tvalue of cell 'CC' in similarity matrix. Default: 1"<< endl << endl;
        cout << "  -CG <int>\tvalue of cell 'CG' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -CT <int>\tvalue of cell 'CT' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -GA <int>\tvalue of cell 'GA' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -GC <int>\tvalue of cell 'GC' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -GG <int>\tvalue of cell 'GG' in similarity matrix. Default: 1"<< endl << endl;
        cout << "  -GT <int>\tvalue of cell 'GT' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -TA <int>\tvalue of cell 'TA' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -TC <int>\tvalue of cell 'TC' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -TG <int>\tvalue of cell 'TG' in similarity matrix. Default: -1"<< endl << endl;
        cout << "  -TT <int>\tvalue of cell 'TT' in similarity matrix. Default: 1"<< endl << endl;
        cout << "  -sequence <file_name>\tfile with sequence in FASTA format"<< endl << endl;
        cout << "  -reference <file_name>\tfile with reference in FASTA format"<< endl << endl;
        cout << "  -output_file_name <file_name>\toutput file name. Default: out"<< endl << endl;

        cout << "Similarity matrix:" << endl << endl;
        cout << " \tA\tC\tG\tT" << endl << endl;
        cout << "A\tAA\tAC\tAG\tAT" << endl << endl;
        cout << "C\tCA\tCC\tCG\tCT" << endl << endl;
        cout << "G\tGA\tGC\tGG\tGT" << endl << endl;
        cout << "T\tTA\tTC\tTG\tTT" << endl << endl << endl;
    }

    string AlignParameters::getSequence() const {
        return sequence_;
    }

    string AlignParameters::getReference() const {
        return reference_;
    }

    bool AlignParameters::getCircular() const {
        return circular_;
    }

    bool AlignParameters::getIsHirschbergAlgorithm() const {
        return isHirschbergAlgorithm_;
    }

    short int AlignParameters::getGapPenalty() const {
        return gap_penalty_;
    }

    vector<vector<short int>> AlignParameters::getSubstitutionMatrix() const {
        return substitutionMatrix_;
    }

    void AlignParameters::initSubstitutionMatrix() {
        vector<short int> tempV(4, 0);
        substitutionMatrix_ = vector<vector<short int> >(4,tempV);

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                substitutionMatrix_[i][j] = -1;
            }
        }

        substitutionMatrix_[0][0] = 1;
        substitutionMatrix_[1][1] = 1;
        substitutionMatrix_[2][2] = 1;
        substitutionMatrix_[3][3] = 1;
        return;
    }

    void AlignParameters::parametersService(Parameters::ParametersMap& parameters) {
        if (parameters.size() == 1) {
            printHelpForModule();
            initParameters();
            return;
        }

        mode_ = "-align";

        for (const auto & parameter : parameters) {
            try {
                if (parameter.first == "output_file_name" || parameter.first == "-output_file_name") {
                    output_file_name_ = string(parameter.second);
                    continue;
                } else if (parameter.first == "circular" || parameter.first == "-circular") {
                    int tmp = lexical_cast<int>(parameter.second);
                    if (tmp == 0) {
                        circular_ = false;
                    } else if (tmp == 1) {
                        circular_ = true;
                    } else {
                        cout << "Invalid '-circular' value, it must be '0' or '1'" << endl;
                        initParameters();
                        return;
                    }
                    continue;
                } else if (parameter.first == "gap_penalty" || parameter.first == "-gap_penalty") {
                    gap_penalty_ = lexical_cast<short>(parameter.second);
                    continue;
                } else if (parameter.first == "AA" || parameter.first == "-AA") {
                    substitutionMatrix_[0][0] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "AC" || parameter.first == "-AC") {
                    substitutionMatrix_[0][1] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "AG" || parameter.first == "-AG") {
                    substitutionMatrix_[0][2] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "AT" || parameter.first == "-AT") {
                    substitutionMatrix_[0][3] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "CA" || parameter.first == "-CA") {
                    substitutionMatrix_[1][0] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "CC" || parameter.first == "-CC") {
                    substitutionMatrix_[1][1] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "CG" || parameter.first == "-CG") {
                    substitutionMatrix_[1][2] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "CT" || parameter.first == "-CT") {
                    substitutionMatrix_[1][3] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "GA" || parameter.first == "-GA") {
                    substitutionMatrix_[2][0] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "GC" || parameter.first == "-GC") {
                    substitutionMatrix_[2][1] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "GG" || parameter.first == "-GG") {
                    substitutionMatrix_[2][2] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "GT" || parameter.first == "-GT") {
                    substitutionMatrix_[2][3] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "TA" || parameter.first == "-TA") {
                    substitutionMatrix_[3][0] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "TC" || parameter.first == "-TC") {
                    substitutionMatrix_[3][1] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "TG" || parameter.first == "-TG") {
                    substitutionMatrix_[3][2] = lexical_cast<short int>(parameter.second);
                    continue;
                } else if (parameter.first == "TT" || parameter.first == "-TT") {
                    substitutionMatrix_[3][3] = lexical_cast<short int>(parameter.second);
                    continue;
                }
            }
            catch(bad_lexical_cast&) { }
            if (parameter.first == "align_algorithm" || parameter.first == "-align_algorithm") {
                if (parameter.second == "h") {
                    isHirschbergAlgorithm_ = true;
                } else if (parameter.second == "nw") {
                    isHirschbergAlgorithm_ = false;
                } else {
                    cout << "Invalid '-align_algorithm' value, it must be 'h' for Hirschberg's algorithm or 'nw' for Needleman-Wunsch algorithm" << endl;
                    initParameters();
                    return;
                }
                continue;
            }
            if (parameter.first == "sequence" || parameter.first == "-sequence") {
                sequence_ = parameter.second;
                if (parameter.second[0] != '>' && parameter.second[0] != '@' && parameter.second.size() != 0) { // only for testing process, where istringstream are required
                    ifstream fileCheck(parameter.second.c_str());
                    if (!fileCheck) {   //check if file exists
                        cout << parameter.second << ": no such file" << endl;
                        initParameters();
                        return;
                    }
                    fileCheck.close();
                }
                continue;
            }
            if (parameter.first == "reference" || parameter.first == "-reference") {
                reference_ = parameter.second;
                if (parameter.second[0] != '>' && parameter.second[0] != '@' && parameter.second.size() != 0) { // only for testing process, where istringstream are required
                    ifstream fileCheck(parameter.second.c_str());
                    if (!fileCheck) {   //check if file exists
                        cout << parameter.second << ": no such file" << endl;
                        initParameters();
                        return;
                    }
                    fileCheck.close();
                }
                continue;
            }
        }
        if (sequence_ == "" || reference_ == "") {
            initParameters();
        }
    }
}}
