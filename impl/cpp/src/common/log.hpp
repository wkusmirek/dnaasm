/**
 * \file log.hpp
 * \brief the C++ logger declaraion
 *
 */

#ifndef LOG_HPP
#define LOG_HPP

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4714)
#endif

#ifndef STR
#define STR(s) stringify(s)
#define stringify(s) #s
#endif

#include <string>
#include "common.hpp"

namespace dnaasm {
    /** log info message */
    CALC_DLL(void logInfo(const std::string& msg));

    /** log warning message */
    CALC_DLL(void logWarning(const std::string& msg));

    /** log error message */
    CALC_DLL(void logError(const std::string& msg));

    /** init logging library - set logger file path */
    CALC_DLL(void initCalcModule());
}

#endif    //LOG_HPP
