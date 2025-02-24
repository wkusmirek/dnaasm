/**
 * \file ResultantSequencesGenerator.hpp
 * \brief the C++ file with implementation of template class for generating an output sequences
 */

#ifndef RESULTANT_SEQUENCES_GENERATOR_HPP
#define RESULTANT_SEQUENCES_GENERATOR_HPP

#include "Statistics.hpp"
#include "../common/DnaSequenceRepresentationConverter.hpp"

namespace dnaasm { namespace dbj {

    /**
     * \brief Class to generate an output set of sequences.
     */
    template<class Graph> class ResultantSequencesGenerator {
    public:

        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename std::vector<Vertex> VertexRepresentationSequence;
        typedef typename std::vector<VertexRepresentationSequence> VertexRepresentationSequences;

        /**
         * \brief ResultantSequencesGenerator constructor.
         *
         * \param vertexRepresentationSequences set of resultant sequences in vertex representation
         * \param firstChars information about first char represented by specified vertex
         * \param sequences information about whole DNA sequence represented by specified vertex
         * \param K1 length of strings stored in graph vertices (K1 + 1 = k from k-spectrum)
         * \param statistics reference to statistics object with set of statistics
         */
        ResultantSequencesGenerator(VertexRepresentationSequences& vertexRepresentationSequences,
                   std::vector<char>& firstChars,
                   std::vector<std::bitset<2*MAX_KMER_LENGTH>>& sequences,
                   unsigned short K1,
                   Statistics& statistics)
            : vertexRepresentationSequences_(vertexRepresentationSequences)
            , K1_(K1)
            , statistics_(statistics)
        { generateOutputAndStatistics(firstChars, sequences); }

        /**
         * \brief ResultantSequencesGenerator constructor.
         *
         * \param vertexRepresentationSequences set of resultant sequences in vertex representation
         * \param unitigsFile file with unitigs produced without using paired-end tags
         * \param K1 length of strings stored in graph vertices (K1 + 1 = k form k-spectrum)
         * \param statistics reference to statistics object with set of statistics
         */
        ResultantSequencesGenerator(VertexRepresentationSequences& vertexRepresentationSequences,
                   std::istream& unitigsFile,
                   unsigned short K1,
                   Statistics& statistics)
            : vertexRepresentationSequences_(vertexRepresentationSequences)
            , K1_(K1)
            , statistics_(statistics)
        { generateOutputAndStatistics(unitigsFile); }

        /**
        * \brief Gets string representation for specified resultant sequence.
         *
         * \param index vector index
         * \return returns string representation for specified resultant sequence
         */
        std::string getOut(unsigned int index) const {
            if (index >= stringRepresentationSequences_.size())
                return "";
            return stringRepresentationSequences_[index];
        }

    private:
        VertexRepresentationSequences& vertexRepresentationSequences_;
        unsigned short K1_;
        Statistics& statistics_;
        std::vector<std::string> stringRepresentationSequences_;
        ResultantSequencesGenerator& operator=(const ResultantSequencesGenerator&)= delete;

        /**
        * \brief Fills all fields and vectors for ResultantSequencesGenerator class.
        *
        * \param unitigsFile file with unitigs produced without using paired-end tags
        * \return returns void
        */
        void generateOutputAndStatistics(std::istream& unitigsFile) {
            convertVertexRepresentationToStringRepresentation(unitigsFile);
            buildSequencesHistogram();
            statistics_.collectStatisticsFromSequences();
        }

        /**
        * \brief Finds string representation from each sequence in vertex representation.
        *
        * \param unitigsFile file with unitigs produced without using paired-end tags
        * \return returns void
        */
        void convertVertexRepresentationToStringRepresentation(std::istream& unitigsFile) {
            if (vertexRepresentationSequences_.size() == 0)
                return;
            unitigsFile.clear();
            unitigsFile.seekg(std::ios::beg);
            std::vector<std::string> unitigs;
            size_t i = 0U;
            while (true) {
                std::string id = "";
                std::string sequence = "";
                unitigsFile >> id >> sequence;
                if (id == "" || sequence == "") {
                    break;
                }
                unitigs.push_back(sequence);
                ++i;
                if (i % 1000000 == 0) {
                }
            }
            for (const auto& vertexRepresentationSequence : vertexRepresentationSequences_) {
                if (vertexRepresentationSequence.size() == 0)
                    continue;
                std::string stringRepresentationSequence = "";
                for (auto it = std::begin(vertexRepresentationSequence); it != std::end(vertexRepresentationSequence); ++it) {
                    if (*it == std::numeric_limits<unsigned long>::max()) {  // vertex equal to std::numeric_limits<unsigned long>::max() depicts chain of 'N' signs
                        ++it;
                        for (unsigned long i = 0UL; i < *it; ++i) {
                            stringRepresentationSequence += 'N';
                        }
                    } else {
                        stringRepresentationSequence += std::string(unitigs[*it], 0, unitigs[*it].size()-K1_);
                    }
                }

                stringRepresentationSequence
                    += std::string(unitigs[vertexRepresentationSequence.back()],
                                   unitigs[vertexRepresentationSequence.back()].size()-K1_, K1_);
                stringRepresentationSequences_.push_back(stringRepresentationSequence);
            }
        }

        /**
        * \brief Fills all fields and vectors for ResultantSequencesGenerator class.
        *
        * \param firstChars information about first char represented by specified vertex
        * \param sequences information about whole DNA sequence represented by specified vertex
        * \return returns void
        */
        void generateOutputAndStatistics(std::vector<char>& firstChars,
                                         std::vector<std::bitset<2*MAX_KMER_LENGTH>>& sequences) {
            convertVertexRepresentationToStringRepresentation(firstChars, sequences);
            buildSequencesHistogram();
            statistics_.collectStatisticsFromSequences();
        }

        /**
        * \brief Finds string representation from each sequence in vertex representation.
        *
        * \param firstChars information about first char represented by specified vertex
        * \param sequences information about whole DNA sequence represented by specified vertex
        * \return returns void
        */
        void convertVertexRepresentationToStringRepresentation(std::vector<char>& firstChars,
                            std::vector<std::bitset<2*MAX_KMER_LENGTH>>& sequences) {
            if (vertexRepresentationSequences_.size() == 0) return;

            for (const auto& vertexRepresentationSequence : vertexRepresentationSequences_) {
                if (vertexRepresentationSequence.size() == 0)
                    continue;

                DnaSequenceRepresentationConverter dnaSequenceRepresentationConverter(K1_);
                std::string stringRepresentationSequence = "";

                for (auto it = std::begin(vertexRepresentationSequence); it != std::end(vertexRepresentationSequence); ++it) {
                    if (*it == std::numeric_limits<unsigned long>::max()) {  // vertex equal to std::numeric_limits<unsigned long>::max() depicts chain of 'N' signs
                        ++it;
                        for (unsigned long i = 0UL; i < *it; ++i) {
                            stringRepresentationSequence += 'N';
                        }
                    } else {
                        stringRepresentationSequence += firstChars[*it];
                    }
                }

                stringRepresentationSequence += std::string(dnaSequenceRepresentationConverter.convertToString(sequences[vertexRepresentationSequence.back()]), 1, K1_);
                stringRepresentationSequences_.push_back(stringRepresentationSequence);
            }
        }

        /**
        * \brief Builds histogram for size of resultant sequencess.
        *
        * \return returns void
        */
        void buildSequencesHistogram() {
            for (const auto& out : stringRepresentationSequences_) {
                statistics_.addSequenceLengthStat(static_cast<unsigned int>(out.size()));
            }
        }

    };

}}

#endif    // RESULTANT_SEQUENCES_GENERATOR_HPP
