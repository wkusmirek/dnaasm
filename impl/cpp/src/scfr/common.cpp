/**
 * \file common.hpp
 * \brief the C++ file with implementation of common utilities
 * for scfr module
 *
 */

#include "common.hpp"

#include "../common/Read.hpp"
#include "../common/log.hpp"

namespace dnaasm { namespace scfr {

    std::string getReverseComplementary(const std::string &sequence)
    {
        Read r(0U);
        r.setRead(sequence);
        r.makeComplementaryStrand();
        return r.getRead();
    }


    std::pair<unsigned int, bool> getContigIdAndOrientationFromStr(const std::string& s)
    {
        // s must follow regex: ^[fr]\d+
        try {
            bool reversed = s[0] == 'r';
            int id = std::stoi(s.substr(1, s.size()));

            if (id < 1) {
                logWarning("Error while reading contig id: "
                           + s + ". Id must be a positive number >1");
                return std::make_pair(0U, false);
            }

            return std::make_pair((unsigned int)id, reversed);
        } catch (...) {
            logWarning("Exception while reading contig id: " + s);
            return std::make_pair(0U, false);
        }
    }

}} //namespace dnaasm::scfr