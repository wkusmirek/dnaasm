/**
 * \file OutputVCF.hpp
 * \brief the C++ file with declaration of class for generating output string in VCF format from set of mismatches
 *
 */

#ifndef OUTPUTVCF_HPP
#define OUTPUTVCF_HPP

#include "Mismatch.hpp"

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to generate output string in VCF format from set of mismatches.
     */
    class OutputVCF {
    public:

        /**
         * \brief OutputVCF constructor.
         *
         * \param mismatches set of mismatches between sequence and reference
         */
        CALC_DLL(explicit OutputVCF(std::vector<Mismatch>& mismatches);)

        /**
         * \brief Generates output in VCF format from set of mismatches.
         *
         * \return returns string wih mismatches in VCF format
         */
        CALC_DLL(std::string generateVCFOutput();)

    private:
        std::vector<Mismatch>& mismatches_;
        std::string outputString_;
        OutputVCF& operator=(const OutputVCF&)= delete;
    };

}}

#endif    //OUTPUTVCF_HPP
