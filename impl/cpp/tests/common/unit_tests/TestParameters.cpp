/**
 * \file TestParameters.cpp
 * \brief the C++ file with implementation of tests for Parameters class
 *
 */
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "../../../src/common/Parameters.hpp"
#include "../../../src/dbj/AlignParameters.hpp"
#include "../../../src/dbj/AssemblyParameters.hpp"
#include "../../../src/bst/BstParameters.hpp"
#include "../../../src/scfr/ScaffoldParameters.hpp"
using namespace dnaasm::dbj;
using namespace dnaasm::bst;
using namespace dnaasm::scfr;
using namespace std;

struct HideOutput {
    HideOutput()  { backup = std::cout.rdbuf(nullptr);
                    boost::unit_test::unit_test_log.set_stream(std::cerr); }
    ~HideOutput() { std::cout.rdbuf(backup); }

    std::streambuf *backup;
};

struct ScfrFixture {
    ScfrFixture() {}
    ~ScfrFixture() {}

    void checkScaffoldDefaultParameters(const ScaffoldParameters& params)
    {
        BOOST_CHECK_EQUAL(params.getMode(), (char*)NULL);
        BOOST_CHECK_EQUAL(params.getContigsFilePath(), "");
        BOOST_CHECK_EQUAL(params.getReadsFilePath(), "");
        BOOST_CHECK_EQUAL(params.getKmerSize(), 15);
        BOOST_CHECK_EQUAL(params.getDistance(), 4000);
        BOOST_CHECK_EQUAL(params.getStep(), 2);
        BOOST_CHECK_EQUAL(params.getMinLinks(), 5);
        BOOST_CHECK_CLOSE(params.getMaxRatio(), 0.3, 0.0001);
        BOOST_CHECK_EQUAL(params.getMinContigLength(), 500);
        BOOST_CHECK_EQUAL(params.getOutputFileName(), "out");
    }
};

BOOST_AUTO_TEST_SUITE(TestParameters/*, *boost::unit_test::fixture<HideOutput>()*/)

/********************** console application **********************/

BOOST_AUTO_TEST_CASE(parametersService0_argv)
{
    const char* argv [] = {"./dnaasm", "-h", NULL};
    int argc = 2;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService1_argv)
{
    const char* argv [] = {"./dnaasm", NULL};
    int argc = 1;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService2_argv)
{
    const char* argv [] = {"./dnaasm", "-assembly", NULL};
    int argc = 2;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService3_argv)
{
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", NULL};
    int argc = 4;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService4_argv)
{
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", NULL};
    int argc = 6;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService5_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", existFilePath.data(), NULL};
    int argc = 8;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService6_argv)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", notExistFilePath.data(), NULL};
    int argc = 8;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService7_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_2", existFilePath.data(), NULL};
    int argc = 8;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService8_argv)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_2", notExistFilePath.data(), NULL};
    int argc = 8;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService9_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", existFilePath.data(), "-bfc_file", existFilePath.data(), NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService10_argv)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-o1_1", notExistFilePath.data(), NULL};
    int argc = 8;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService11_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-o1_2", existFilePath.data(), NULL};
    int argc = 8;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService12_argv)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-o1_2", notExistFilePath.data(), NULL};
    int argc = 8;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService13_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-o1_1", existFilePath.data(), "-bfc_file", existFilePath.data(), NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService14_argv)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", existFilePath.data(), "-bfc_file", notExistFilePath.data(), NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService15_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-paired_reads_pet_threshold_from", "5", "-i1_1", existFilePath.data(), NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 5U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService16_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", existFilePath.data(), "-paired_reads_pet_threshold_from", "-1", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService17_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-paired_reads_pet_threshold_to", "5", "-i1_1", existFilePath.data(), NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 5U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService18_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", existFilePath.data(), "-paired_reads_pet_threshold_to", "-1", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService19_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-paired_reads_mp_threshold_from", "5", "-i1_1", existFilePath.data(), NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 5U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService20_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", existFilePath.data(), "-paired_reads_mp_threshold_from", "-1", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService21_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-paired_reads_mp_threshold_to", "5", "-i1_1", existFilePath.data(), NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 5U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService22_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", existFilePath.data(), "-paired_reads_mp_threshold_to", "-1", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService23_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-bfcounter_threshold", "5", "-i1_1", existFilePath.data(), NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 5U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService24_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", existFilePath.data(), "-bfcounter_threshold", "-1", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService25_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-single_edge_counter_threshold", "5", "-i1_1", existFilePath.data(), NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 5U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService26_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", existFilePath.data(), "-single_edge_counter_threshold", "-1", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService27_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-quality_threshold", "5", "-i1_1", existFilePath.data(), NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 5U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService28_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_1", existFilePath.data(), "-quality_threshold", "95", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService29_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-genome_length", "4000", "-i1_2", existFilePath.data(), "-k", "1", NULL};
    int argc = 8;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService30_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    string tooLargeK = to_string(MAX_KMER_LENGTH+1);
    const char* argv [] = {"./dnaasm", "-assembly", "-genome_length", "4000", "-i1_2", existFilePath.data(), "-k", tooLargeK.c_str(), NULL};
    int argc = 8;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService31_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "5", "-i1_2", existFilePath.data(), "-genome_length", "-1", NULL};
    int argc = 8;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService32_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_2", existFilePath.data(), "-correct", "2",  NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService33_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "3", "-genome_length", "4000", "-i1_2", existFilePath.data(), "-paired_reads_algorithm", "33",  NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService34_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "5", "-i1_2", existFilePath.data(), "-genome_length", "6", "-insert_size_mean_inward", "-1", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getInsertSizeMeanInward(), 0.0);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService35_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "5", "-i1_2", existFilePath.data(), "-genome_length", "6", "-insert_size_std_dev_inward", "-1", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getInsertSizeStdDevInward(), 0.0);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService36_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "5", "-i1_2", existFilePath.data(), "-genome_length", "6", "-insert_size_mean_outward", "-1", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getInsertSizeMeanOutward(), 0.0);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService37_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-assembly", "-k", "5", "-i1_2", existFilePath.data(), "-genome_length", "6", "-insert_size_std_dev_outward", "-1", NULL};
    int argc = 10;
    AssemblyParameters::ParametersMap paramMap = AssemblyParameters::convertArgvToMap(argc, argv);
    AssemblyParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getInsertSizeStdDevOutward(), 0.0);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService38_argv)
{
    const char* argv [] = {"./dnaasm", "-align", NULL};
    int argc = 2;
    AlignParameters::ParametersMap paramMap = AlignParameters::convertArgvToMap(argc, argv);
    AlignParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService39_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-align", "-gap_penalty", "-5", "-AA", "0", "-AC", "1", "-AG", "2", "-AT", "3", "-CA", "4", "-CC", "5", "-CG", "6", "-CT", "7", "-GA", "8", "-GC", "9", "-GG", "10", "-GT", "11", "-TA", "12", "-TC", "13", "-TG", "14", "-TT", "15", "-sequence", existFilePath.data(), NULL};
    int argc = 38;
    AlignParameters::ParametersMap paramMap = AlignParameters::convertArgvToMap(argc, argv);
    AlignParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService40_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-align", "-gap_penalty", "-5", "-AA", "0", "-AC", "1", "-AG", "2", "-AT", "3", "-CA", "4", "-CC", "5", "-CG", "6", "-CT", "7", "-GA", "8", "-GC", "9", "-GG", "10", "-GT", "11", "-TA", "12", "-TC", "13", "-TG", "14", "-TT", "15", "-reference", existFilePath.data(), NULL};
    int argc = 38;
    AlignParameters::ParametersMap paramMap = AlignParameters::convertArgvToMap(argc, argv);
    AlignParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService41_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-align", "-gap_penalty", "-5", "-AA", "0", "-AC", "1", "-AG", "2", "-AT", "3", "-CA", "4", "-CC", "5", "-CG", "6", "-CT", "7", "-GA", "8", "-GC", "9", "-GG", "10", "-GT", "11", "-TA", "12", "-TC", "13", "-TG", "14", "-TT", "15", "-circular", "1", "-align_algorithm", "h", "-sequence", existFilePath.data(), "-reference", existFilePath.data(), NULL};
    int argc = 44;
    AlignParameters::ParametersMap paramMap = AlignParameters::convertArgvToMap(argc, argv);
    AlignParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-align");
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -5);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 0);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], 2);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], 3);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], 4);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 5);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], 6);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], 7);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], 8);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], 9);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 10);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], 11);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], 12);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], 13);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], 14);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 15);
    BOOST_CHECK_EQUAL(parameters.getCircular(), true);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getReference(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService42_argv)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    const char* argv [] = {"./dnaasm", "-align", "-gap_penalty", "-5", "-AA", "0", "-AC", "1", "-AG", "2", "-AT", "3", "-CA", "4", "-CC", "5", "-CG", "6", "-CT", "7", "-GA", "8", "-GC", "9", "-GG", "10", "-GT", "11", "-TA", "12", "-TC", "13", "-TG", "14", "-TT", "15", "-circular", "0", "-align_algorithm", "nw", "-reference", notExistFilePath.data(), NULL};
    int argc = 42;
    AlignParameters::ParametersMap paramMap = AlignParameters::convertArgvToMap(argc, argv);
    AlignParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService43_argv)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    const char* argv [] = {"./dnaasm", "-align", "-gap_penalty", "-5", "-AA", "0", "-AC", "1", "-AG", "2", "-AT", "3", "-CA", "4", "-CC", "5", "-CG", "6", "-CT", "7", "-GA", "8", "-GC", "9", "-GG", "10", "-GT", "11", "-TA", "12", "-TC", "13", "-TG", "14", "-TT", "15", "-out", "outputFile", "-sequence", notExistFilePath.data(), NULL};
    int argc = 40;
    AlignParameters::ParametersMap paramMap = AlignParameters::convertArgvToMap(argc, argv);
    AlignParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService44_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-align", "-gap_penalty", "-5", "-AA", "0", "-AC", "1", "-AG", "2", "-AT", "3", "-CA", "4", "-CC", "5", "-CG", "6", "-CT", "7", "-GA", "8", "-GC", "9", "-GG", "10", "-GT", "11", "-TA", "12", "-TC", "13", "-TG", "14", "-TT", "15", "-circular", "1", "-sequence", existFilePath.data(), "-reference", existFilePath.data(), "-align_algorithm", "bad_value", NULL};
    int argc = 44;
    AlignParameters::ParametersMap paramMap = AlignParameters::convertArgvToMap(argc, argv);
    AlignParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService45_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"./dnaasm", "-align", "-gap_penalty", "-5", "-AA", "0", "-AC", "1", "-AG", "2", "-AT", "3", "-CA", "4", "-CC", "5", "-CG", "6", "-CT", "7", "-GA", "8", "-GC", "9", "-GG", "10", "-GT", "11", "-TA", "12", "-TC", "13", "-TG", "14", "-TT", "15", "-sequence", existFilePath.data(), "-reference", existFilePath.data(), "-align_algorithm", "h", "-circular", "2", NULL};
    int argc = 44;
    AlignParameters::ParametersMap paramMap = AlignParameters::convertArgvToMap(argc, argv);
    AlignParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService46_argv)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    const char* argv [] = {"dnaasm.exe", "-align", "-gap_penalty", "-5", "-AA", "0", "-AC", "1", "-AG", "2", "-AT", "3", "-CA", "4", "-CC", "5", "-CG", "6", "-CT", "7", "-GA", "8", "-GC", "9", "-GG", "10", "-GT", "11", "-TA", "12", "-TC", "13", "-TG", "14", "-TT", "15", "-circular", "1", "-align_algorithm", "h", "-sequence", existFilePath.data(), "-reference", existFilePath.data(), NULL};
    int argc = 44;
    AlignParameters::ParametersMap paramMap = AlignParameters::convertArgvToMap(argc, argv);
    AlignParameters parameters(paramMap);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-align");
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -5);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 0);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], 2);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], 3);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], 4);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 5);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], 6);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], 7);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], 8);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], 9);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 10);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], 11);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], 12);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], 13);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], 14);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 15);
    BOOST_CHECK_EQUAL(parameters.getCircular(), true);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getReference(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

//BOOST_AUTO_TEST_CASE(parametersService46_bst)
//{
//    const char* argv [] = {"./dnaasm", "-bst", "-input_file_path", "cpp/tests/bst/unit_tests/reads", "-kmer_size", "20", "-min_similarity", "2"};
//    int argc = 8;
//    BstParameters::ParametersMap paramMap = BstParameters::convertArgvToMap(argc, argv);
//    BstParameters parameters(paramMap);
//    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-bst");
//    BOOST_CHECK_EQUAL(parameters.getInputFilePath(), "cpp/tests/bst/unit_tests/reads");
//    BOOST_CHECK_EQUAL(parameters.getWordLength(), 20);
//    BOOST_CHECK_EQUAL(parameters.getMinimalWordCount(), 2);
//    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
//}

BOOST_FIXTURE_TEST_CASE(parametersService47_scfr_help, ScfrFixture)
{
    const char* argv [] = {"./dnaasm", "-scaffold", "-help", NULL};
    int argc = 3;
    ScaffoldParameters::ParametersMap paramMap = ScaffoldParameters::convertArgvToMap(argc, argv);
    ScaffoldParameters parameters(paramMap);
    checkScaffoldDefaultParameters(parameters);

    const char* argv2 [] = {"./dnaasm", "-scaffold", NULL};
    int argc2 = 2;
    ScaffoldParameters::ParametersMap paramMap2 = ScaffoldParameters::convertArgvToMap(argc2, argv2);
    ScaffoldParameters parameters2(paramMap2);
    checkScaffoldDefaultParameters(parameters2);
}

//BOOST_AUTO_TEST_CASE(parametersService48_scfr_good_params)
//{
//    const char* argv [] = {"./dnaasm", "-scaffold", "-contigs_file_path", "cpp/tests/scfr/unit_tests/test.fa", "-long_reads_file_path", "cpp/tests/scfr/unit_tests/test.fa", "-kmer_size", "20", "-distance", "1000", "-step", "10", "-min_links", "3", "-max_ratio", "0.4", "-min_contig_length", "100", "-output_file_name", "outfile", NULL};
//    int argc = 20;
//    ScaffoldParameters::ParametersMap paramMap = ScaffoldParameters::convertArgvToMap(argc, argv);
//    ScaffoldParameters parameters(paramMap);
//    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-scaffold");
//    BOOST_CHECK_EQUAL(parameters.getContigsFilePath(), "cpp/tests/scfr/unit_tests/test.fa");
//    BOOST_CHECK_EQUAL(parameters.getReadsFilePath(), "cpp/tests/scfr/unit_tests/test.fa");
//    BOOST_CHECK_EQUAL(parameters.getKmerSize(), 20);
//    BOOST_CHECK_EQUAL(parameters.getDistance(), 1000);
//    BOOST_CHECK_EQUAL(parameters.getStep(), 10);
//    BOOST_CHECK_EQUAL(parameters.getMinLinks(), 3);
//    BOOST_CHECK_CLOSE(parameters.getMaxRatio(), 0.4, 0.0001);
//    BOOST_CHECK_EQUAL(parameters.getMinContigLength(), 100);
//    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "outfile");
//}

BOOST_FIXTURE_TEST_CASE(parametersService49_scfr_wrong_kmer_size, ScfrFixture)
{
    const char* argv [] = {"./dnaasm", "-scaffold", "-kmer_size", "-1", NULL};
    int argc = 4;
    ScaffoldParameters::ParametersMap paramMap = ScaffoldParameters::convertArgvToMap(argc, argv);
    ScaffoldParameters parameters(paramMap);
    checkScaffoldDefaultParameters(parameters);

    // not integer
    const char* argv2 [] = {"./dnaasm", "-scaffold", "-kmer_size", "s", NULL};
    int argc2 = 4;
    ScaffoldParameters::ParametersMap paramMap2 = ScaffoldParameters::convertArgvToMap(argc2, argv2);
    ScaffoldParameters parameters2(paramMap);
    checkScaffoldDefaultParameters(parameters2);
}

BOOST_FIXTURE_TEST_CASE(parametersService50_scfr_wrong_distance, ScfrFixture)
{
    const char* argv [] = {"./dnaasm", "-scaffold", "-distance", "-1", NULL};
    int argc = 4;
    ScaffoldParameters::ParametersMap paramMap = ScaffoldParameters::convertArgvToMap(argc, argv);
    ScaffoldParameters parameters(paramMap);
    checkScaffoldDefaultParameters(parameters);

    // not integer
    const char* argv2 [] = {"./dnaasm", "-scaffold", "-distance", "s", NULL};
    int argc2 = 4;
    ScaffoldParameters::ParametersMap paramMap2 = ScaffoldParameters::convertArgvToMap(argc2, argv2);
    ScaffoldParameters parameters2(paramMap2);
    checkScaffoldDefaultParameters(parameters2);
}

BOOST_FIXTURE_TEST_CASE(parametersService51_scfr_wrong_step, ScfrFixture)
{
    const char* argv [] = {"./dnaasm", "-scaffold", "-step", "-1", NULL};
    int argc = 4;
    ScaffoldParameters::ParametersMap paramMap = ScaffoldParameters::convertArgvToMap(argc, argv);
    ScaffoldParameters parameters(paramMap);
    checkScaffoldDefaultParameters(parameters);

    // not integer
    const char* argv2 [] = {"./dnaasm", "-scaffold", "-step", "s", NULL};
    int argc2 = 4;
    ScaffoldParameters::ParametersMap paramMap2 = ScaffoldParameters::convertArgvToMap(argc2, argv2);
    ScaffoldParameters parameters2(paramMap2);
    checkScaffoldDefaultParameters(parameters2);
}

BOOST_FIXTURE_TEST_CASE(parametersService52_scfr_wrong_min_links, ScfrFixture)
{
    const char* argv [] = {"./dnaasm", "-scaffold", "-min_links", "-1", NULL};
    int argc = 4;
    ScaffoldParameters::ParametersMap paramMap = ScaffoldParameters::convertArgvToMap(argc, argv);
    ScaffoldParameters parameters(paramMap);
    checkScaffoldDefaultParameters(parameters);

    // not integer
    const char* argv2 [] = {"./dnaasm", "-scaffold", "-min_links", "s", NULL};
    int argc2 = 4;
    ScaffoldParameters::ParametersMap paramMap2 = ScaffoldParameters::convertArgvToMap(argc2, argv2);
    ScaffoldParameters parameters2(paramMap2);
    checkScaffoldDefaultParameters(parameters2);
}

BOOST_FIXTURE_TEST_CASE(parametersService53_scfr_wrong_max_ratio, ScfrFixture)
{
    const char* argv [] = {"./dnaasm", "-scaffold", "-max_ratio", "-1", NULL};
    int argc = 4;
    ScaffoldParameters::ParametersMap paramMap = ScaffoldParameters::convertArgvToMap(argc, argv);
    ScaffoldParameters parameters(paramMap);
    checkScaffoldDefaultParameters(parameters);

    const char* argv1 [] = {"./dnaasm", "-scaffold", "-max_ratio", "0.0", NULL};
    ScaffoldParameters::ParametersMap paramMap1 = ScaffoldParameters::convertArgvToMap(argc, argv1);
    ScaffoldParameters parameters1(paramMap1);
    checkScaffoldDefaultParameters(parameters1);

    const char* argv2 [] = {"./dnaasm", "-scaffold", "-max_ratio", "1.0", NULL};
    ScaffoldParameters::ParametersMap paramMap2 = ScaffoldParameters::convertArgvToMap(argc, argv2);
    ScaffoldParameters parameters2(paramMap2);
    checkScaffoldDefaultParameters(parameters2);

    // not float
    const char* argv3 [] = {"./dnaasm", "-scaffold", "-max_ratio", "s", NULL};
    ScaffoldParameters::ParametersMap paramMap3 = ScaffoldParameters::convertArgvToMap(argc, argv3);
    ScaffoldParameters parameters3(paramMap3);
    checkScaffoldDefaultParameters(parameters3);
}

BOOST_FIXTURE_TEST_CASE(parametersService54_scfr_wrong_min_contig_length, ScfrFixture)
{
    const char* argv [] = {"./dnaasm", "-scaffold", "-min_contig_length", "-1", NULL};
    int argc = 4;
    ScaffoldParameters::ParametersMap paramMap = ScaffoldParameters::convertArgvToMap(argc, argv);
    ScaffoldParameters parameters(paramMap);
    checkScaffoldDefaultParameters(parameters);

    // not integer
    const char* argv2 [] = {"./dnaasm", "-scaffold", "-min_contig_length", "s", NULL};
    int argc2 = 4;
    ScaffoldParameters::ParametersMap paramMap2 = ScaffoldParameters::convertArgvToMap(argc2, argv2);
    ScaffoldParameters parameters2(paramMap2);
    checkScaffoldDefaultParameters(parameters2);
}

BOOST_FIXTURE_TEST_CASE(parametersService55_scfr_file_does_not_exist, ScfrFixture)
{
    const char* argv [] = {"./dnaasm", "-scaffold", "-contigs_file_path", "file", NULL};
    int argc = 4;
    ScaffoldParameters::ParametersMap paramMap = ScaffoldParameters::convertArgvToMap(argc, argv);
    ScaffoldParameters parameters(paramMap);
    checkScaffoldDefaultParameters(parameters);

    const char* argv2 [] = {"./dnaasm", "-scaffold", "-long_reads_file_path", "file", NULL};
    int argc2 = 4;
    ScaffoldParameters::ParametersMap paramMap2 = ScaffoldParameters::convertArgvToMap(argc2, argv2);
    ScaffoldParameters parameters2(paramMap2);
    checkScaffoldDefaultParameters(parameters2);
}

/********************** web application **********************/

BOOST_AUTO_TEST_CASE(parametersService0_map)
{
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("h", ""));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService1_map)
{
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService2_map)
{
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService3_map)
{
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService4_map)
{
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService5_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService6_map)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("-i1_1", notExistFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService7_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("i1_2", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService8_map)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("i1_2", notExistFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService9_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    params.insert(pair<string, string>("bfc_file", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService10_map)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("o1_1", notExistFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService11_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("o1_2", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService12_map)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("o1_2", notExistFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService13_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("o1_1", existFilePath));
    params.insert(pair<string, string>("bfc_file", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService14_map)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    params.insert(pair<string, string>("bfc_file", notExistFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService15_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("-paired_reads_pet_threshold_from", "5"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 5U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService16_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("-paired_reads_pet_threshold_from", "-1"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService17_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("paired_reads_pet_threshold_to", "5"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 5U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService18_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("paired_reads_pet_threshold_to", "-1"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService19_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("paired_reads_mp_threshold_from", "5"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 5U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService20_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("paired_reads_mp_threshold_from", "-1"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService21_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("paired_reads_mp_threshold_to", "5"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 5U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService22_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("paired_reads_mp_threshold_to", "-1"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService23_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("bfcounter_threshold", "5"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 5U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService24_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("bfcounter_threshold", "-1"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService25_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("single_edge_counter_threshold", "5"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 5U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService26_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("single_edge_counter_threshold", "-1"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService27_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("quality_threshold", "5"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-assembly");
    BOOST_CHECK_EQUAL(parameters.getK(), 3U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 4000ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 5U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService28_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("quality_threshold", "95"));
    params.insert(pair<string, string>("-i1_1", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService29_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("k", "1"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("i1_2", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService30_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    string tooLargeK = to_string(MAX_KMER_LENGTH+1);
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("k", tooLargeK));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("i1_2", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService31_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("k", "5"));
    params.insert(pair<string, string>("genome_length", "-1"));
    params.insert(pair<string, string>("i1_2", existFilePath));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService32_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("i1_2", existFilePath));
    params.insert(pair<string, string>("correct", "2"));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService33_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("-k", "3"));
    params.insert(pair<string, string>("-genome_length", "4000"));
    params.insert(pair<string, string>("i1_2", existFilePath));
    params.insert(pair<string, string>("paired_reads_algorithm", "33"));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService34_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("k", "5"));
    params.insert(pair<string, string>("genome_length", "6"));
    params.insert(pair<string, string>("i1_2", existFilePath));
    params.insert(pair<string, string>("insert_size_mean_inward", "-1"));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getInsertSizeMeanInward(), 0.0);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService35_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("k", "5"));
    params.insert(pair<string, string>("genome_length", "6"));
    params.insert(pair<string, string>("i1_2", existFilePath));
    params.insert(pair<string, string>("insert_size_std_dev_inward", "-1"));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getInsertSizeStdDevInward(), 0.0);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService36_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("k", "5"));
    params.insert(pair<string, string>("genome_length", "6"));
    params.insert(pair<string, string>("i1_2", existFilePath));
    params.insert(pair<string, string>("insert_size_mean_outward", "-1"));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getInsertSizeMeanOutward(), 0.0);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService37_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("-assembly", ""));
    params.insert(pair<string, string>("k", "5"));
    params.insert(pair<string, string>("genome_length", "6"));
    params.insert(pair<string, string>("i1_2", existFilePath));
    params.insert(pair<string, string>("insert_size_std_dev_outward", "-1"));
    AssemblyParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getK(), 0U);
    BOOST_CHECK_EQUAL(parameters.getGenomeLength(), 0ULL);
    BOOST_CHECK_EQUAL(parameters.getInsertSizeStdDevOutward(), 0.0);
    BOOST_CHECK_EQUAL(parameters.getQualityThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getBfcounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getSingleEdgeCounterThreshold(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsPetThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdFrom(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsMpThresholdTo(), 0U);
    BOOST_CHECK_EQUAL(parameters.getPairedReadsAlgorithm(), AssemblyParameters::PairedReadsAlgorithm::NONE);
    BOOST_CHECK_EQUAL(parameters.getCorrect(), true);
    BOOST_CHECK_EQUAL(parameters.getI1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getI1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_1(), "");
    BOOST_CHECK_EQUAL(parameters.getO1_2(), "");
    BOOST_CHECK_EQUAL(parameters.getBfcFile(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService38_map)
{
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("align", ""));
    AlignParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService39_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("align", ""));
    params.insert(pair<string, string>("gap_penalty", "-5"));
    params.insert(pair<string, string>("AA", "0"));
    params.insert(pair<string, string>("AC", "1"));
    params.insert(pair<string, string>("AG", "2"));
    params.insert(pair<string, string>("AT", "3"));
    params.insert(pair<string, string>("CA", "4"));
    params.insert(pair<string, string>("CC", "5"));
    params.insert(pair<string, string>("CG", "6"));
    params.insert(pair<string, string>("CT", "7"));
    params.insert(pair<string, string>("GA", "8"));
    params.insert(pair<string, string>("GC", "9"));
    params.insert(pair<string, string>("GG", "10"));
    params.insert(pair<string, string>("GT", "11"));
    params.insert(pair<string, string>("TA", "12"));
    params.insert(pair<string, string>("TC", "13"));
    params.insert(pair<string, string>("TG", "14"));
    params.insert(pair<string, string>("TT", "15"));
    params.insert(pair<string, string>("sequence", existFilePath));
    AlignParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService40_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("align", ""));
    params.insert(pair<string, string>("gap_penalty", "-5"));
    params.insert(pair<string, string>("AA", "0"));
    params.insert(pair<string, string>("AC", "1"));
    params.insert(pair<string, string>("AG", "2"));
    params.insert(pair<string, string>("AT", "3"));
    params.insert(pair<string, string>("CA", "4"));
    params.insert(pair<string, string>("CC", "5"));
    params.insert(pair<string, string>("CG", "6"));
    params.insert(pair<string, string>("CT", "7"));
    params.insert(pair<string, string>("GA", "8"));
    params.insert(pair<string, string>("GC", "9"));
    params.insert(pair<string, string>("GG", "10"));
    params.insert(pair<string, string>("GT", "11"));
    params.insert(pair<string, string>("TA", "12"));
    params.insert(pair<string, string>("TC", "13"));
    params.insert(pair<string, string>("TG", "14"));
    params.insert(pair<string, string>("TT", "15"));
    params.insert(pair<string, string>("reference", existFilePath));
    AlignParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService41_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("./dnaasm", ""));
    params.insert(pair<string, string>("align", ""));
    params.insert(pair<string, string>("gap_penalty", "-5"));
    params.insert(pair<string, string>("AA", "0"));
    params.insert(pair<string, string>("AC", "1"));
    params.insert(pair<string, string>("AG", "2"));
    params.insert(pair<string, string>("AT", "3"));
    params.insert(pair<string, string>("CA", "4"));
    params.insert(pair<string, string>("CC", "5"));
    params.insert(pair<string, string>("CG", "6"));
    params.insert(pair<string, string>("CT", "7"));
    params.insert(pair<string, string>("GA", "8"));
    params.insert(pair<string, string>("GC", "9"));
    params.insert(pair<string, string>("GG", "10"));
    params.insert(pair<string, string>("GT", "11"));
    params.insert(pair<string, string>("TA", "12"));
    params.insert(pair<string, string>("TC", "13"));
    params.insert(pair<string, string>("TG", "14"));
    params.insert(pair<string, string>("TT", "15"));
    params.insert(pair<string, string>("circular", "1"));
    params.insert(pair<string, string>("align_algorithm", "h"));
    params.insert(pair<string, string>("sequence", existFilePath));
    params.insert(pair<string, string>("reference", existFilePath));
    AlignParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-align");
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -5);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 0);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], 2);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], 3);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], 4);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 5);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], 6);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], 7);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], 8);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], 9);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 10);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], 11);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], 12);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], 13);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], 14);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 15);
    BOOST_CHECK_EQUAL(parameters.getCircular(), true);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getReference(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService42_map)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    map<string, string> params;
    params.insert(pair<string, string>("dnaasm.exe", ""));
    params.insert(pair<string, string>("align", ""));
    params.insert(pair<string, string>("gap_penalty", "-5"));
    params.insert(pair<string, string>("AA", "0"));
    params.insert(pair<string, string>("AC", "1"));
    params.insert(pair<string, string>("AG", "2"));
    params.insert(pair<string, string>("AT", "3"));
    params.insert(pair<string, string>("CA", "4"));
    params.insert(pair<string, string>("CC", "5"));
    params.insert(pair<string, string>("CG", "6"));
    params.insert(pair<string, string>("CT", "7"));
    params.insert(pair<string, string>("GA", "8"));
    params.insert(pair<string, string>("GC", "9"));
    params.insert(pair<string, string>("GG", "10"));
    params.insert(pair<string, string>("GT", "11"));
    params.insert(pair<string, string>("TA", "12"));
    params.insert(pair<string, string>("TC", "13"));
    params.insert(pair<string, string>("TG", "14"));
    params.insert(pair<string, string>("TT", "15"));
    params.insert(pair<string, string>("circular", "1"));
    params.insert(pair<string, string>("align_algorithm", "h"));
    params.insert(pair<string, string>("reference", notExistFilePath));
    AlignParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService43_map)
{
    string notExistFilePath = boost::filesystem::exists("notExistFile") ? "notExistFilenotExistFile" : "notExistFile";
    map<string, string> params;
    params.insert(pair<string, string>("dnaasm.exe", ""));
    params.insert(pair<string, string>("align", ""));
    params.insert(pair<string, string>("gap_penalty", "-5"));
    params.insert(pair<string, string>("AA", "0"));
    params.insert(pair<string, string>("AC", "1"));
    params.insert(pair<string, string>("AG", "2"));
    params.insert(pair<string, string>("AT", "3"));
    params.insert(pair<string, string>("CA", "4"));
    params.insert(pair<string, string>("CC", "5"));
    params.insert(pair<string, string>("CG", "6"));
    params.insert(pair<string, string>("CT", "7"));
    params.insert(pair<string, string>("GA", "8"));
    params.insert(pair<string, string>("GC", "9"));
    params.insert(pair<string, string>("GG", "10"));
    params.insert(pair<string, string>("GT", "11"));
    params.insert(pair<string, string>("TA", "12"));
    params.insert(pair<string, string>("TC", "13"));
    params.insert(pair<string, string>("TG", "14"));
    params.insert(pair<string, string>("TT", "15"));
    params.insert(pair<string, string>("circular", "1"));
    params.insert(pair<string, string>("align_algorithm", "h"));
    params.insert(pair<string, string>("sequence", notExistFilePath));
    AlignParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService44_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("dnaasm.exe", ""));
    params.insert(pair<string, string>("align", ""));
    params.insert(pair<string, string>("gap_penalty", "-5"));
    params.insert(pair<string, string>("AA", "0"));
    params.insert(pair<string, string>("AC", "1"));
    params.insert(pair<string, string>("AG", "2"));
    params.insert(pair<string, string>("AT", "3"));
    params.insert(pair<string, string>("CA", "4"));
    params.insert(pair<string, string>("CC", "5"));
    params.insert(pair<string, string>("CG", "6"));
    params.insert(pair<string, string>("CT", "7"));
    params.insert(pair<string, string>("GA", "8"));
    params.insert(pair<string, string>("GC", "9"));
    params.insert(pair<string, string>("GG", "10"));
    params.insert(pair<string, string>("GT", "11"));
    params.insert(pair<string, string>("TA", "12"));
    params.insert(pair<string, string>("TC", "13"));
    params.insert(pair<string, string>("TG", "14"));
    params.insert(pair<string, string>("TT", "15"));
    params.insert(pair<string, string>("circular", "1"));
    params.insert(pair<string, string>("align_algorithm", "bad_value"));
    params.insert(pair<string, string>("sequence", existFilePath));
    params.insert(pair<string, string>("reference", existFilePath));
    AlignParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService45_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("dnaasm.exe", ""));
    params.insert(pair<string, string>("align", ""));
    params.insert(pair<string, string>("gap_penalty", "-5"));
    params.insert(pair<string, string>("AA", "0"));
    params.insert(pair<string, string>("AC", "1"));
    params.insert(pair<string, string>("AG", "2"));
    params.insert(pair<string, string>("AT", "3"));
    params.insert(pair<string, string>("CA", "4"));
    params.insert(pair<string, string>("CC", "5"));
    params.insert(pair<string, string>("CG", "6"));
    params.insert(pair<string, string>("CT", "7"));
    params.insert(pair<string, string>("GA", "8"));
    params.insert(pair<string, string>("GC", "9"));
    params.insert(pair<string, string>("GG", "10"));
    params.insert(pair<string, string>("GT", "11"));
    params.insert(pair<string, string>("TA", "12"));
    params.insert(pair<string, string>("TC", "13"));
    params.insert(pair<string, string>("TG", "14"));
    params.insert(pair<string, string>("TT", "15"));
    params.insert(pair<string, string>("circular", "2"));
    params.insert(pair<string, string>("align_algorithm", "h"));
    params.insert(pair<string, string>("sequence", existFilePath));
    params.insert(pair<string, string>("reference", existFilePath));
    AlignParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)NULL);
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -1);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], -1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 1);
    BOOST_CHECK_EQUAL(parameters.getCircular(), false);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), "");
    BOOST_CHECK_EQUAL(parameters.getReference(), "");
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_CASE(parametersService46_map)
{
    string existFilePath = boost::filesystem::exists("cpp/tests/dbj/unit_tests/test") ? "cpp/tests/dbj/unit_tests/test" : "tests/dbj/unit_tests/test";
    map<string, string> params;
    params.insert(pair<string, string>("dnaasm.exe", ""));
    params.insert(pair<string, string>("align", ""));
    params.insert(pair<string, string>("gap_penalty", "-5"));
    params.insert(pair<string, string>("AA", "0"));
    params.insert(pair<string, string>("AC", "1"));
    params.insert(pair<string, string>("AG", "2"));
    params.insert(pair<string, string>("AT", "3"));
    params.insert(pair<string, string>("CA", "4"));
    params.insert(pair<string, string>("CC", "5"));
    params.insert(pair<string, string>("CG", "6"));
    params.insert(pair<string, string>("CT", "7"));
    params.insert(pair<string, string>("GA", "8"));
    params.insert(pair<string, string>("GC", "9"));
    params.insert(pair<string, string>("GG", "10"));
    params.insert(pair<string, string>("GT", "11"));
    params.insert(pair<string, string>("TA", "12"));
    params.insert(pair<string, string>("TC", "13"));
    params.insert(pair<string, string>("TG", "14"));
    params.insert(pair<string, string>("TT", "15"));
    params.insert(pair<string, string>("circular", "1"));
    params.insert(pair<string, string>("align_algorithm", "h"));
    params.insert(pair<string, string>("sequence", existFilePath));
    params.insert(pair<string, string>("reference", existFilePath));
    AlignParameters parameters(params);
    BOOST_CHECK_EQUAL(parameters.getMode(), (char*)"-align");
    BOOST_CHECK_EQUAL(parameters.getGapPenalty(), -5);
    vector<vector<short int>> substitutionMatrix_ = parameters.getSubstitutionMatrix();
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][0], 0);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][1], 1);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][2], 2);
    BOOST_CHECK_EQUAL(substitutionMatrix_[0][3], 3);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][0], 4);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][1], 5);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][2], 6);
    BOOST_CHECK_EQUAL(substitutionMatrix_[1][3], 7);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][0], 8);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][1], 9);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][2], 10);
    BOOST_CHECK_EQUAL(substitutionMatrix_[2][3], 11);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][0], 12);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][1], 13);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][2], 14);
    BOOST_CHECK_EQUAL(substitutionMatrix_[3][3], 15);
    BOOST_CHECK_EQUAL(parameters.getCircular(), true);
    BOOST_CHECK_EQUAL(parameters.getIsHirschbergAlgorithm(), true);
    BOOST_CHECK_EQUAL(parameters.getSequence(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getReference(), existFilePath);
    BOOST_CHECK_EQUAL(parameters.getOutputFileName(), "out");
}

BOOST_AUTO_TEST_SUITE_END()
