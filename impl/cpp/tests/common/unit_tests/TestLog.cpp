/**
 * \file TestLog.cpp
 * \brief the C++ file with implementation of tests for C++ logger
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/common/log.hpp"

#include <fstream>

using namespace dnaasm;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestLog)

BOOST_AUTO_TEST_CASE(logInfoTest)
{
    string info1 = "info log test 1";
    string info2 = "info log test 2";
    initCalcModule();
    logInfo(info1);
    logInfo(info2);
    ifstream logFile(std::string(STR(LOG_CPP_LOC))+ std::string(STR(LOG_CPP_FILE_NAME)));
    if (logFile.is_open())
    {
        string line = "";
        getline(logFile, line);
        BOOST_CHECK_EQUAL(line.find("[info] - " + info1) != std::string::npos, true);
        BOOST_CHECK_EQUAL(line.find("[info] - " + info2), std::string::npos);
        getline(logFile, line);
        BOOST_CHECK_EQUAL(line.find("[info] - " + info1), std::string::npos);
        BOOST_CHECK_EQUAL(line.find("[info] - " + info2) != std::string::npos, true);
        logFile.close();
    }
}

BOOST_AUTO_TEST_CASE(logWarningTest)
{
    string warning1 = "warning log test 1";
    string warning2 = "warning log test 2";
    initCalcModule();
    logWarning(warning1);
    logWarning(warning2);
    ifstream logFile(std::string(STR(LOG_CPP_LOC))+ std::string(STR(LOG_CPP_FILE_NAME)));
    if (logFile.is_open())
    {
        string line = "";
        getline(logFile, line);
        BOOST_CHECK_EQUAL(line.find("[warning] - " + warning1) != std::string::npos, true);
        BOOST_CHECK_EQUAL(line.find("[warning] - " + warning2), std::string::npos);
        getline(logFile, line);
        BOOST_CHECK_EQUAL(line.find("[warning] - " + warning1), std::string::npos);
        BOOST_CHECK_EQUAL(line.find("[warning] - " + warning2) != std::string::npos, true);
        logFile.close();
    }
}

BOOST_AUTO_TEST_CASE(logErrorTest)
{
    string error1 = "error log test 1";
    string error2 = "error log test 2";
    initCalcModule();
    logError(error1);
    logError(error2);
    ifstream logFile(std::string(STR(LOG_CPP_LOC))+ std::string(STR(LOG_CPP_FILE_NAME)));
    if (logFile.is_open())
    {
        string line = "";
        getline(logFile, line);
        BOOST_CHECK_EQUAL(line.find("[error] - " + error1) != std::string::npos, true);
        BOOST_CHECK_EQUAL(line.find("[error] - " + error2), std::string::npos);
        getline(logFile, line);
        BOOST_CHECK_EQUAL(line.find("[error] - " + error1), std::string::npos);
        BOOST_CHECK_EQUAL(line.find("[error] - " + error2) != std::string::npos, true);
        logFile.close();
    }
}

BOOST_AUTO_TEST_SUITE_END()
