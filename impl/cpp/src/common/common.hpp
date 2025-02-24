/**
 * \file common.hpp
 * \brief the C++ file with declaration of some macros
 */

#ifndef COMMON_HPP
#define COMMON_HPP


#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
//msvc13.0 warnings for boost.Graph
#pragma warning(disable:4512)
#pragma warning(disable:4100)
#pragma warning(disable:4510)
#pragma warning(disable:4610)
//4127 - conditional expression is constant
#pragma warning(disable:4127)
//4068 - unknown pragma
#pragma warning(disable:4068)
#pragma warning(disable:4456)
#define __attribute__(x)
#endif

#define CALC_TMP_DIR "/tmp/dnaasm/"

#ifdef CALC_EXPORTS
/** Workaround for Windows DLL library exports */
#define CALC_DLL(X)__declspec(dllexport)X
#else
/** Workaround for Unix Shared Library exports */
#define CALC_DLL(X)X
#endif


#endif //COMMON_HPP
