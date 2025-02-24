/**
 * \file TestContigLoader.cpp
 * \brief the C++ file with implementation of tests for TestContigLoader class
 *
 */

#include <boost/test/unit_test.hpp>
#include <sstream>
#include "../../../src/common/InputFile.hpp"
#include "../../../src/scfr/ContigLoader.hpp"

using namespace dnaasm::scfr;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestContigLoader)

BOOST_AUTO_TEST_CASE(loadContigsIntoMemory)
{
    string contigsStr = ">1\nACC\n>2\nTAG\n";
    istringstream contigs(contigsStr);
    dnaasm::InputFile contigsFile(contigs);

    ContigSeqHashMap sequences = ContigLoader::loadContigsIntoMemory(contigsFile);

    BOOST_CHECK_EQUAL(sequences[1], "ACC");
    BOOST_CHECK_EQUAL(sequences[2], "TAG");
}

BOOST_AUTO_TEST_SUITE_END()
