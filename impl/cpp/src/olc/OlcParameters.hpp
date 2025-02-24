#ifndef OLCPARAMETERS_HPP
#define OLCPARAMETERS_HPP

#include "../common/Parameters.hpp"

using namespace std;

namespace dnaasm {
    namespace olc {
        class OlcParameters : public dnaasm::common::Parameters {
        public:
            /**
             * \brief OlcParameters constructor.
             *
             * \param parameters map of parameters
             */
            CALC_DLL(OlcParameters(Parameters::ParametersMap &parameters);)

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
            CALC_DLL(unsigned short int getKmerLength() const;)

            /**
             * \brief Gets number of sketches representing single sequence in minhash
             *
             * \return returns number of sketches representing single sequence in minhash
             */
            CALC_DLL(unsigned short int getSketchNum() const;)

            /**
             * \brief Gets minimum Jaccard Similarity Estimate.
             *
             * \return returns min jaccard sim est
             */
            CALC_DLL(float getMinJaccardSim() const;)

            /**
             * \brief Gets match score for Smith-Waterman algorithm
             *
             * \return returns match score for Smith-Waterman algorithm
             */
            CALC_DLL(short int getMatchScore() const;)

            /**
             * \brief Gets mismatch score for Smith-Waterman algorithm
             *
             * \return returns mismatch score for Smith-Waterman algorithm
             */
            CALC_DLL(short int getMismatchScore() const;)

            /**
             * \brief Gets penalty for gap extention in Smith-Waterman algorithm
             *
             * \return returns penalty for gap extention in Smith-Waterman algorithm
             */
            CALC_DLL(short int getGapPenalty() const;)

            /**
             * \brief Gets minimum similarity needed to create edge in Overlap Graph
             *
             * \return returns minimum similarity needed to create edge in Overlap Graph
             */
            CALC_DLL(unsigned short int getMinEdge() const;)

            /**
             * \brief Gets minimal output contig length
             *
             * \return returns minimal output contig length
             */
            CALC_DLL(unsigned short int getMinContigLength() const;)

            /**
             * \brief Gets path width for Needleman-Wunsch algorithm (optimization)
             *
             * \return returns Gets path width for Needleman-Wunsch algorithm (optimization)
             */
            CALC_DLL(unsigned short int getPathWidth() const;)

            /**
             * \brief Prints detailed help instruction of olc mode for user.
             *
             * \return returns void
             */
            CALC_DLL(static void printHelpForModule();)

        private:
            std::string readsFilePath_;
            unsigned short int kmerLength_;
            unsigned short int sketchNum_;
            float minJaccardSim_;
            short int matchScore_;
            short int mismatchScore_;
            short int gapPenalty_;
            unsigned short int minEdge_;
            unsigned short int minContigLength_;
            unsigned short int pathWidth_;

            /**
             * \brief Services parameters specifed by the user.
             *
             * \return returns void
             */
            void parametersService(Parameters::ParametersMap &parameters);

            /**
             * \brief Initializes parameters to default values.
             *
             * \return returns void
             */
            void initParameters();
        };
    }
}

#endif //OLCPARAMETERS_HPP
