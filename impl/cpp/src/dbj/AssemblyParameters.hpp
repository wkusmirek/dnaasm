#ifndef ASSEMBLYPARAMETERS_HPP
#define ASSEMBLYPARAMETERS_HPP

#include "../common/Parameters.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    class AssemblyParameters : public dnaasm::common::Parameters {
    public:
        enum /*class*/ PairedReadsAlgorithm {NONE, VELVET_PAIRED_READS_ALGORITHM};

        /**
         * \brief AssemblyParameters constructor.
         *
         * \param parameters map of parameters
         */
        CALC_DLL(AssemblyParameters(std::map<std::string, std::string>& parameters);)

        /**
         * \brief Gets graph dimension.
         *
         * \return returns graph dimension
         */
        CALC_DLL(unsigned short getK() const;)

        /**
         * \brief Gets genome length.
         *
         * \return returns genome length
         */
        CALC_DLL(unsigned long long int getGenomeLength() const;)

        /**
         * \brief Gets insert size mean value of paired-end tags.
         *
         * \return returns insert size mean value of paired-end tags
         */
        CALC_DLL(float getInsertSizeMeanInward() const;)

        /**
         * \brief Gets insert size standard deviation value of paired-end tags.
         *
         * \return returns insert size standard deviation value of paired-end tags
         */
        CALC_DLL(float getInsertSizeStdDevInward() const;)

        /**
         * \brief Gets insert size mean value of mate pairs.
         *
         * \return returns insert size mean value of mate pairs
         */
        CALC_DLL(float getInsertSizeMeanOutward() const;)

        /**
         * \brief Gets insert size standard deviation value of mate pairs.
         *
         * \return returns insert size standard deviation value of mate pairs
         */
        CALC_DLL(float getInsertSizeStdDevOutward() const;)

        /**
         * \brief Gets quality threshold value.
         *
         * \return returns quality threshold value
         */
        CALC_DLL(unsigned short int getQualityThreshold() const;)

        /**
         * \brief Gets single k-mer counter threshold.
         *
         * \return returns single k-mer counter threshold
         */
        CALC_DLL(unsigned short int getBfcounterThreshold() const;)

        /**
         * \brief Gets single edge counter threshold.
         *
         * \return returns single edge counter threshold
         */
        CALC_DLL(unsigned short int getSingleEdgeCounterThreshold() const;)

        /**
         * \brief Gets paired reads threshold for paired-end tags (begin value).
         *
         * \return returns paired reads threshold for paired-end tags (begin value)
         */
        CALC_DLL(unsigned short int getPairedReadsPetThresholdFrom() const;)

        /**
         * \brief Gets paired reads threshold for paired-end tags (end value).
         *
         * \return returns paired reads threshold for paired-end tags (end value)
         */
        CALC_DLL(unsigned short int getPairedReadsPetThresholdTo() const;)

        /**
         * \brief Gets paired reads threshold for mate-pairs (begin value).
         *
         * \return returns paired reads threshold for mate-pairs (begin value)
         */
        CALC_DLL(unsigned short int getPairedReadsMpThresholdFrom() const;)

        /**
         * \brief Gets paired reads threshold for mate-pairs (end value).
         *
         * \return returns paired reads threshold for mate-pairs (end value)
         */
        CALC_DLL(unsigned short int getPairedReadsMpThresholdTo() const;)

        /**
         * \brief Gets type of paired reads algorithm.
         *
         * \return returns type of paired reads algorithm
         */
        CALC_DLL(unsigned short getPairedReadsAlgorithm() const;)

        /**
         * \brief Gets if graph will be correcting.
         *
         * \return returns if graph will be correcting
         */
        CALC_DLL(bool getCorrect() const;)

        /**
         * \brief Gets first input from first pair of inward reads.
         *
         * \return returns first input from first pair of inward reads
         */
        CALC_DLL(std::string getI1_1() const;)

        /**
         * \brief Gets second input from first pair of inward reads.
         *
         * \return returns second input from first pair of inward reads
         */
        CALC_DLL(std::string getI1_2() const;)

        /**
         * \brief Gets first input from first pair of outward reads.
         *
         * \return returns first input from first pair of outward reads
         */
        CALC_DLL(std::string getO1_1() const;)

        /**
         * \brief Gets second input from first pair of outward reads.
         *
         * \return returns second input from first pair of outward reads
         */
        CALC_DLL(std::string getO1_2() const;)

        /**
         * \brief Gets output file from BFCounter application.
         *
         * \return returns output file from BFCounter application
         */
        CALC_DLL(std::string getBfcFile() const;)


        /**
         * \brief Prints detailed help instruction of dbj assembly mode for user.
         *
         * \return returns void
         */
        CALC_DLL(static void printHelpForModule();)

    private:
        unsigned short k_;
        unsigned long long int genome_length_;
        float insert_size_mean_inward_;
        float insert_size_std_dev_inward_;
        float insert_size_mean_outward_;
        float insert_size_std_dev_outward_;
        unsigned short int quality_threshold_;
        unsigned short int bfcounter_threshold_;
        unsigned short int single_edge_counter_threshold_;
        unsigned short int paired_reads_pet_threshold_from_;
        unsigned short int paired_reads_pet_threshold_to_;
        unsigned short int paired_reads_mp_threshold_from_;
        unsigned short int paired_reads_mp_threshold_to_;
        PairedReadsAlgorithm paired_reads_algorithm_;
        bool correct_;
        std::string i1_1_;
        std::string i1_2_;
        std::string o1_1_;
        std::string o1_2_;
        std::string bfc_file_;

        /**
         * \brief Services parameters specifed by the user.
         *
         * \return returns void
         */
        void parametersService(
                std::map<std::string, std::string>& parameters);

        /**
         * \brief Initializes parameters to default values.
         *
         * \return returns void
         */
        void initParameters();
    };
}}

#endif //ASSEMBLYPARAMETERS_HPP
