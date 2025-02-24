#ifndef BSTPARAMETERS_HPP
#define BSTPARAMETERS_HPP

#include "../common/Parameters.hpp"

namespace dnaasm {
namespace bst {

    class BstParameters : public dnaasm::common::Parameters {
    public:
        /**
         * \brief BstParameters constructor.
         *
         * \param parameters map of parameters
         */
        CALC_DLL(BstParameters(std::map<std::string, std::string>& parameters);)

        /**
         * \brief Gets path of input file with long reads.
         *
         * \return returns path of input file with long reads
         */
        CALC_DLL(std::string getInputFilePath() const;)

        /**
         * \brief Gets k-mer length.
         *
         * \return returns k-mer length
         */
        CALC_DLL(unsigned getWordLength() const;)

        /**
         * \brief Gets minimum Jaccard Similarity Estimate.
         *
         * \return returns min jaccard sim est
         */
        CALC_DLL(unsigned getMinimalWordCount() const;)

        /**
         * \brief Gets minimum Jaccard Similarity Estimate.
         *
         * \return returns min jaccard sim est
         */
        CALC_DLL(unsigned getMaximalWordCount() const;)

        /**
         * \brief Gets minimum Jaccard Similarity Estimate.
         *
         * \return returns min jaccard sim est
         */
        CALC_DLL(unsigned getMinimalAssociation() const;)

        /**
         * \brief Gets minimum Jaccard Similarity Estimate.
         *
         * \return returns min jaccard sim est
         */
        CALC_DLL(unsigned getPathWidth() const;)

        /**
         * \brief Prints detailed help instruction of bst mode for user.
         *
         * \return returns void
         */
        CALC_DLL(static void printHelpForModule();)

    private:
        std::string inputFilePath_;
        unsigned wordLength_;
        unsigned minimalWordCount_;
        unsigned maximalWordCount_;
        unsigned minimalAssociation_;
        unsigned pathWidth_;

        /**
         * \brief Services parameters specifed by the user.
         *
         * \return returns void
         */
        void parametersService(std::map<std::string, std::string>& parameters);

        /**
         * \brief Initializes parameters to default values.
         *
         * \return returns void
         */
        void initParameters();

        bool isParameterEqual(std::string param, std::string str);
    };

}
}

#endif //BSTPARAMETERS_HPP
