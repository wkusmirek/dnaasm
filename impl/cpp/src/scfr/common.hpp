/**
 * \file common.hpp
 * \brief the C++ file with declaration of common utilities for scfr module
 *
 */

#ifndef SCFR_COMMON_HPP
#define SCFR_COMMON_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <cstdint>

#include "../common/common.hpp"

namespace dnaasm { namespace scfr {

    using ContigSeqHashMap =
        std::unordered_map<unsigned int, std::string>;

    using VisitedHashMap =
        std::unordered_map<unsigned int, bool>;

    using ReadSeqHashMap =
        std::unordered_map<unsigned int, std::string>;

    using LinksPerReadVec =
        std::vector<std::pair<uint32_t, size_t>>;

    /**
     * Returns sequence reverse complement to given sequence.
     *
     * Input sequence will not be changed.
     *
     * @param sequence reference to sequence to be reversed
     * @return reverse complementary sequence
     */
	CALC_DLL(std::string getReverseComplementary(const std::string &sequence);)

   /**
    * Need to typedef return type,
    * because C/C++ preprocessor is not able to
    * correctly handle case when
    * function return tape has a comma inside of it.
    */
    typedef std::pair<unsigned int, bool> UintBool_t;
    CALC_DLL(UintBool_t	 getContigIdAndOrientationFromStr(const std::string& s);)

}} //namespace dnaasm::scfr

#endif //SCFR_COMMON_HPP
