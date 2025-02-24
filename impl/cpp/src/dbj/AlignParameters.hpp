#ifndef ALIGNPARAMETERS_HPP
#define ALIGNPARAMETERS_HPP

#include <vector>
#include "../common/Parameters.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    class AlignParameters : public dnaasm::common::Parameters {
    public:
        /**
         * \brief AlignParameters constructor.
         *
         * \param parameters map of parameters
         */
        CALC_DLL(AlignParameters(std::map<std::string, std::string>& parameters);)

        /**
         * \brief Gets sequence input.
         *
         * \return returns sequence input
         */
        CALC_DLL(std::string getSequence() const;)

        /**
         * \brief Gets reference input.
         *
         * \return returns reference input
         */
        CALC_DLL(std::string getReference() const;)

        /**
         * \brief Gets if genome is circular.
         *
         * \return returns true for circular genome, false for linear genome
         */
        CALC_DLL(bool getCircular() const;)

        /**
         * \brief Gets if align algorithm is equal to Hirschberg's algorithm.
         *
         * \return returns true for Hirschberg's algorithm, false for Needleman-Wunsch algorithm
         */
        CALC_DLL(bool getIsHirschbergAlgorithm() const;)

        /**
         * \brief Gets gap penalty.
         *
         * \return returns gap penalty
         */
        CALC_DLL(short int getGapPenalty() const;)

        /**
         * \brief Gets substitution matrix.
         *
         * \return returns substitution matrix
         */
        CALC_DLL(std::vector<std::vector<short int>> getSubstitutionMatrix() const;)

        /**
         * \brief Prints detailed help instruction of align mode for user.
         *
         * \return returns void
         */
        CALC_DLL(static void printHelpForModule();)

    private:
        std::string sequence_;
        std::string reference_;
        bool isHirschbergAlgorithm_;
        bool circular_;
        short int gap_penalty_;
        std::vector<std::vector<short int>> substitutionMatrix_;

        /**
         * \brief Initializes substitution matrix with default values.
         *
         * \return returns void
         */
        CALC_DLL(void initSubstitutionMatrix();)

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

#endif //ALIGNPARAMETERS_HPP
