/**
 * \file AssemblyParameters.cpp
 * \brief the C++ file with implementation of class for representing dbj assembly parameters
 *
 */

#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "AssemblyParameters.hpp"

using namespace std;
using namespace boost;

namespace dnaasm { namespace dbj {
    AssemblyParameters::AssemblyParameters(map<string, string>& parameters)
        : Parameters(parameters)
    { initParameters(); parametersService(parameters); }

    void AssemblyParameters::initParameters() {
        k_ = 0U;
        genome_length_ = 0ULL;
        insert_size_mean_inward_ = 0.0;
        insert_size_std_dev_inward_ = 0.0;
        insert_size_mean_outward_ = 0.0;
        insert_size_std_dev_outward_ = 0.0;
        quality_threshold_ = 0U;
        bfcounter_threshold_ = 0U;
        single_edge_counter_threshold_ = 0U;
        paired_reads_pet_threshold_from_ = 0U;
        paired_reads_pet_threshold_to_ = 0U;
        paired_reads_mp_threshold_from_ = 0U;
        paired_reads_mp_threshold_to_ = 0U;
        paired_reads_algorithm_ = AssemblyParameters::PairedReadsAlgorithm::NONE;
        correct_ = true;
        i1_1_ = "";
        i1_2_ = "";
        o1_1_ = "";
        o1_2_ = "";
        bfc_file_ = "";
        Parameters::initParameters();
    }

    void AssemblyParameters::printHelpForModule() {
        cout << "-assembly\tmake graph for input file (set of reads) and write contigs to the file" << endl;
        cout << "\te.g." << endl;
        cout << "\t./dnaasm -assembly -k 5 -genome_length 40 -correct 1 -paired_reads_algorithm 1 -quality_threshold 6 -bfcounter_threshold 2 -single_edge_counter_threshold 8 -paired_reads_pet_threshold_from 0 -paired_reads_pet_threshold_to 3 -paired_reads_mp_threshold_from 0 -paired_reads_mp_threshold_to 3 -insert_size_mean_inward 200 -insert_size_std_dev_inward 20 -insert_size_mean_outward 2000 -insert_size_std_dev_outward 200 -i1_1 test_inward.R1.fq -i1_2 test_inward.R2.fq -o1_1 test_outward.R1.fq -o1_2 test_outward.R2.fq" << endl;
        cout << "\tdnaasm.exe -assembly -k 5 -genome_length 40 -correct 1 -paired_reads_algorithm 1 -quality_threshold 6 -bfcounter_threshold 2 -single_edge_counter_threshold 8 -paired_reads_pet_threshold_from 0 -paired_reads_pet_threshold_to 3 -paired_reads_mp_threshold_from 0 -paired_reads_mp_threshold_to 3 -i1_1 test_inward.R1.fq -i1_2 test_inward.R2.fq -o1_1 test_outward.R1.fq -o1_2 test_outward.R2.fq" << endl << endl;
        cout << "Parameters:" << endl << endl;
        cout << "  -k <int>\tthe de Bruijn graph dimension, it should be odd number smaller than or equal to " << MAX_KMER_LENGTH << endl << endl;
        cout << "  -genome_length <int>\tthe length of original genome"<< endl << endl;
        cout << "  -correct <int>\tset to '1' if errors should be corrected in graph, otherwise '0'. Default: 1"<< endl << endl;
        cout << "  -paired_reads_algorithm <int>\tset to '0' if reads are unpaired, '1' if reads are paired (forward-reverse)(-insert_size_mean_inward, -insert_size_std_dev_inward, -pairedReadsThrFrom and -pairedReadsThrTo required only in paired mode). Default: 0"<< endl << endl;
        cout << "  -insert_size_mean_inward <float>\tthe value associated with paired-end tags, required only when '-paired_reads_algorithm' is set to '1'. Default: 0.0"<< endl << endl;
        cout << "  -insert_size_std_dev_inward <float>\tthe value associated with paired-end tags, required only when '-paired_reads_algorithm' is set to '1'. Default: 0.0"<< endl << endl;
        cout << "  -insert_size_mean_outward <float>\tthe value associated with mate pairs, required only when mate-pair data is available. Default: 0.0"<< endl << endl;
        cout << "  -insert_size_std_dev_outward <float>\tthe value associated with mate pairs, required only when mate-pair data is available. Default: 0.0"<< endl << endl;
        cout << "  -quality_threshold <int>\tthe quality threshold value(0-93)for reads from FASTQ files. Default: 0"<< endl << endl;
        cout << "  -bfcounter_threshold <int>\tthe threshold of k-mer counter in k-mer occurrence table below which k-mer will not be considered.  Default: 0"<< endl << endl;
        cout << "  -single_edge_counter_threshold <int>\tthe threshold of edge counter in single graph below which edge will be deleted from single graph.  Default: 0"<< endl << endl;
        cout << "  -paired_reads_pet_threshold_from <int>\tthe threshold (begin value) of edge counter (each paired-end tag adds new edge or increment specified counter) for unitigs graph, required only when '-paired_reads_algorithm' is set to '1'. Default: 0"<< endl << endl;
        cout << "  -paired_reads_pet_threshold_to <int>\tthe threshold (end value) of edge counter (each paired-end tag adds new edge or increment specified counter) for unitigs graph, required only when '-paired_reads_algorithm' is set to '1'. Default: 0"<< endl << endl;
        cout << "  -paired_reads_mp_threshold_from <int>\tthe threshold (begin value) of edge counter (each mate-pair adds new edge or increment specified counter) for contigs graph, required only when mate-pair data is available. Default: 0"<< endl << endl;
        cout << "  -paired_reads_mp_threshold_to <int>\tthe threshold (end value) of edge counter (each mate-pair adds new edge or increment specified counter) for contigs graph, required only when mate-pair data is available. Default: 0"<< endl << endl;
        cout << "  -i1_1 <file_name>\treads file in FASTA or FASTQ format in inward orientation" << endl << endl;
        cout << "  -i1_2 <file_name>\treads file in FASTA or FASTQ format in inward orientation" << endl << endl;
        cout << "  -o1_1 <file_name>\treads file in FASTA or FASTQ format in outward orientation" << endl << endl;
        cout << "  -o1_2 <file_name>\treads file in FASTA or FASTQ format in outward orientation" << endl << endl;
        cout << "  -bfc_file <file_name>\toutput from BFCounter application, this file is optional, but recommended to assembling large genomes (to save memory)"<< endl << endl;
        cout << "  -output_file_name <file_name>\toutput file name. Default: out"<< endl << endl;
    }

    unsigned short AssemblyParameters::getK() const {
        return k_;
    }

    unsigned long long int AssemblyParameters::getGenomeLength() const {
        return genome_length_;
    }

    float AssemblyParameters::getInsertSizeMeanInward() const {
        return insert_size_mean_inward_;
    }

    float AssemblyParameters::getInsertSizeStdDevInward() const {
        return insert_size_std_dev_inward_;
    }

    float AssemblyParameters::getInsertSizeMeanOutward() const {
        return insert_size_mean_outward_;
    }

    float AssemblyParameters::getInsertSizeStdDevOutward() const {
        return insert_size_std_dev_outward_;
    }

    unsigned short int AssemblyParameters::getQualityThreshold() const {
        return quality_threshold_;
    }

    unsigned short int AssemblyParameters::getBfcounterThreshold() const {
        return bfcounter_threshold_;
    }

    unsigned short int AssemblyParameters::getSingleEdgeCounterThreshold() const {
        return single_edge_counter_threshold_;
    }

    unsigned short int AssemblyParameters::getPairedReadsPetThresholdFrom() const {
        return paired_reads_pet_threshold_from_;
    }

    unsigned short int AssemblyParameters::getPairedReadsPetThresholdTo() const {
        return paired_reads_pet_threshold_to_;
    }

    unsigned short int AssemblyParameters::getPairedReadsMpThresholdFrom() const {
        return paired_reads_mp_threshold_from_;
    }

    unsigned short int AssemblyParameters::getPairedReadsMpThresholdTo() const {
        return paired_reads_mp_threshold_to_;
    }

    unsigned short AssemblyParameters::getPairedReadsAlgorithm() const {
        return static_cast<unsigned short>(paired_reads_algorithm_);
    }

    bool AssemblyParameters::getCorrect() const {
        return correct_;
    }

    string AssemblyParameters::getI1_1() const {
        return i1_1_;
    }

    string AssemblyParameters::getI1_2() const {
        return i1_2_;
    }

    string AssemblyParameters::getO1_1() const {
        return o1_1_;
    }

    string AssemblyParameters::getO1_2() const {
        return o1_2_;
    }

    string AssemblyParameters::getBfcFile() const {
        return bfc_file_;
    }

    void AssemblyParameters::parametersService(std::map<std::string, std::string>& parameters) {
        if (parameters.size() <= 1) {
            printHelpForModule();
            initParameters();
            return;
        }

        mode_ = "-assembly";

        for (const auto & parameter : parameters) {
            try {
                if (parameter.first == "k" || parameter.first == "-k") {
                    if (lexical_cast<unsigned short>(parameter.second) < 3) {
                        cout << "K is too small, it have to be greater than or equal to 3" << endl;
                        initParameters();
                        return;
                    }
                    if (lexical_cast<unsigned short>(parameter.second) > MAX_KMER_LENGTH) {
                        cout << "K is too large, it have to be smaller than or equal to " << MAX_KMER_LENGTH << endl;
                        initParameters();
                        return;
                    }
                    k_ = lexical_cast<unsigned short>(parameter.second);
                    continue;
                } else if (parameter.first == "insert_size_mean_inward" || parameter.first == "-insert_size_mean_inward") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "Insert size mean is too small, it have to be greater than or equal to 0" << endl;
                        initParameters();
                        return;
                    }
                    insert_size_mean_inward_ = lexical_cast<float>(parameter.second);
                    continue;
                } else if (parameter.first == "insert_size_std_dev_inward" || parameter.first == "-insert_size_std_dev_inward") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "Insert size standard deviation is too small, it have to be greater than or equal to 0" << endl;
                        initParameters();
                        return;
                    }
                    insert_size_std_dev_inward_ = lexical_cast<float>(parameter.second);
                    continue;
                } else if (parameter.first == "insert_size_mean_outward" || parameter.first == "-insert_size_mean_outward") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "Insert size mean is too small, it have to be greater than or equal to 0" << endl;
                        initParameters();
                        return;
                    }
                    insert_size_mean_outward_ = lexical_cast<float>(parameter.second);
                    continue;
                } else if (parameter.first == "insert_size_std_dev_outward" || parameter.first == "-insert_size_std_dev_outward") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "Insert size standard deviation is too small, it have to be greater than or equal to 0" << endl;
                        initParameters();
                        return;
                    }
                    insert_size_std_dev_outward_ = lexical_cast<float>(parameter.second);
                    continue;
                } else if (parameter.first == "genome_length" || parameter.first == "-genome_length") {
                    if (lexical_cast<long long int>(parameter.second) <= 0) {
                        cout << "Genome length is too small, it have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    genome_length_ = lexical_cast<unsigned long long int>(parameter.second);
                    continue;
                } else if (parameter.first == "correct" || parameter.first == "-correct") {
                    int tmp = lexical_cast<int>(parameter.second);
                    if (tmp == 0) {
                        correct_ = false;
                    } else if (tmp == 1) {
                        correct_ = true;
                    } else {
                        cout << "Invalid '-correct' value, it must be '0' or '1'" << endl;
                        initParameters();
                        return;
                    }
                    continue;
                } else if (parameter.first == "paired_reads_algorithm" || parameter.first == "-paired_reads_algorithm") {
                    int tmp = lexical_cast<int>(parameter.second);
                    if (tmp == 0) {
                        paired_reads_algorithm_ = AssemblyParameters::PairedReadsAlgorithm::NONE;
                    } else if (tmp == 1) {
                        paired_reads_algorithm_ = AssemblyParameters::PairedReadsAlgorithm::VELVET_PAIRED_READS_ALGORITHM;
                    } else {
                        cout << "Invalid '-paired_reads_algorithm' value, it must be '0', or '1'" << endl;
                        initParameters();
                        return;
                    }
                    continue;
                }
                else if (parameter.first == "quality_threshold" || parameter.first == "-quality_threshold") {
                    if (lexical_cast<int>(parameter.second) < 0 || lexical_cast<int>(parameter.second) > 93) {
                        cout << "Quality threshold value is incorrect, it should be greater than or equal to 0 and smaller than 94." << endl;
                        initParameters();
                        return;
                    }
                    quality_threshold_ = lexical_cast<unsigned short>(parameter.second);
                    continue;
                } else if (parameter.first == "bfcounter_threshold" || parameter.first == "-bfcounter_threshold") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "BFCounter threshold for single k-mer is too small, it have to be greater than or equal to 0" << endl;
                        initParameters();
                        return;
                    }
                    bfcounter_threshold_ = lexical_cast<unsigned short>(parameter.second);
                    continue;
                } else if (parameter.first == "single_edge_counter_threshold" || parameter.first == "-single_edge_counter_threshold") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "Edge counter threshold for single graph is too small, it have to be greater than or equal to 0" << endl;
                        initParameters();
                        return;
                    }
                    single_edge_counter_threshold_ = lexical_cast<unsigned short>(parameter.second);
                    continue;
                } else if (parameter.first == "paired_reads_pet_threshold_from" || parameter.first == "-paired_reads_pet_threshold_from") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "Paired reads threshold (begin value) for paired-end tags is too small, it have to be greater than or equal to 0" << endl;
                        initParameters();
                        return;
                    }
                    paired_reads_pet_threshold_from_ = lexical_cast<unsigned short>(parameter.second);
                    continue;
                } else if (parameter.first == "paired_reads_pet_threshold_to" || parameter.first == "-paired_reads_pet_threshold_to") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "Paired reads threshold (end value) for paired-end tags is too small, it have to be greater than or equal to 0" << endl;
                        initParameters();
                        return;
                    }
                    paired_reads_pet_threshold_to_ = lexical_cast<unsigned short>(parameter.second);
                    continue;
                } else if (parameter.first == "paired_reads_mp_threshold_from" || parameter.first == "-paired_reads_mp_threshold_from") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "Paired reads threshold (begin value) for mate-pairs is too small, it have to be greater than or equal to 0" << endl;
                        initParameters();
                        return;
                    }
                    paired_reads_mp_threshold_from_ = lexical_cast<unsigned short>(parameter.second);
                    continue;
                } else if (parameter.first == "paired_reads_mp_threshold_to" || parameter.first == "-paired_reads_mp_threshold_to") {
                    if (lexical_cast<int>(parameter.second) < 0) {
                        cout << "Paired reads threshold (end value) for mate-pairs is too small, it have to be greater than or equal to 0" << endl;
                        initParameters();
                        return;
                    }
                    paired_reads_mp_threshold_to_ = lexical_cast<unsigned short>(parameter.second);
                    continue;
                } else if (parameter.first == "output_file_name" || parameter.first == "-output_file_name") {
                    output_file_name_ = string(parameter.second);
                    continue;
                }
            }
            catch(bad_lexical_cast&) { }
            if (parameter.first == "i1_1" || parameter.first == "-i1_1") {
                i1_1_ = parameter.second;
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
            if (parameter.first == "i1_2" || parameter.first == "-i1_2") {
                i1_2_ = parameter.second;
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
            if (parameter.first == "o1_1" || parameter.first == "-o1_1") {
                o1_1_ = parameter.second;
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
            if (parameter.first == "o1_2" || parameter.first == "-o1_2") {
                o1_2_ = parameter.second;
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
            if (parameter.first == "bfc_file" || parameter.first == "-bfc_file") {
                bfc_file_ = parameter.second;
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
        if (i1_1_ == "" && i1_2_ == "" && o1_1_ == "" && o1_2_ == "") {
            initParameters();
        }
        
    }
}}
