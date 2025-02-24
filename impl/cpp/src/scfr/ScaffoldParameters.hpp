#ifndef SCAFFOLDPARAMETERS_HPP
#define SCAFFOLDPARAMETERS_HPP

#include "../common/Parameters.hpp"

using namespace std;

namespace dnaasm { namespace scfr {

    class ScaffoldParameters : public dnaasm::common::Parameters {
    public:
        /**
         * \brief ScaffoldParameters constructor.
         *
         * \param parameters map of parameters
         */
        CALC_DLL(ScaffoldParameters(std::map<std::string, std::string>& parameters);)

        /**
         * \brief Gets path of input file with contigs.
         *
         * \return returns path of input file with contigs
         */
        CALC_DLL(std::string getContigsFilePath() const;)

        /**
         * \brief Gets path of input file with long reads.
         *
         * \return returns path of input file with long reads
         */
        CALC_DLL(std::string getReadsFilePath() const;)

        /**
         * \brief Gets k-mer length.
         *
         * \return returns k-mer length
         */
        CALC_DLL(unsigned short int getKmerSize() const;)

        /**
         * \brief Gets distance between the 5’-end of each k-mer pair.
         *
         * \return returns distance between the 5’-end of each k-mer pair
         */
        CALC_DLL(unsigned short int getDistance() const;)

        /**
         * \brief Gets step of sliding window.
         *
         * \return returns step of sliding window
         */
        CALC_DLL(unsigned short int getStep() const;)

        /**
         * \brief Gets minimum number of links between contigs to compute scaffold.
         *
         * \return returns minimum number of links between contigs to compute scaffold
         */
        CALC_DLL(unsigned short int getMinLinks() const;)

        /**
         * \brief Gets minimum number of reads linking two contigs to compute scaffold.
         *
         * \return returns minimum number of reads linking two contigs to compute scaffold
         */
        CALC_DLL(unsigned short int getMinReads() const;)

        /**
         * \brief Gets minimum number of links between contigs extracted from single read
         * to compute scaffold.
         *
         * \return returns minimum number of reads linking two contigs to compute scaffold
         */
        CALC_DLL(unsigned short int getMinLinksPerRead() const;)

        /**
         * \brief Gets maximum link ratio between two best contig pairs.
         *
         * \return returns maximum link ratio between two best contig pairs
         */
        CALC_DLL(float getMaxRatio() const;)

        /**
         * \brief Gets minimum contig length to consider for scaffolding.
         *
         * \return returns minimum contig length to consider for scaffolding
         */
        CALC_DLL(unsigned int getMinContigLength() const;)

        CALC_DLL(bool getGapFilling() const;)

        /**
         * \brief Prints detailed help instruction of selected module for user.
         *
         * \return returns void
         */
        CALC_DLL(static void printHelpForModule();)

    private:
        std::string contigsFilePath_;
        std::string readsFilePath_;
        unsigned short int kmerSize_;
        unsigned short int distance_;
        unsigned short int step_;
        unsigned short int minLinks_;
        unsigned short int minReads_;
        unsigned short int minLinksPerRead_;
        float maxRatio_;
        unsigned int minContigLength_;
        bool gapFilling_;

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

}} //namespace dnaasm::scfr

#endif //SCAFFOLDPARAMETERS_HPP
