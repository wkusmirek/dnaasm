/**
 * \file TestDnaSequenceRepresentationConverter.cpp
 * \brief the C++ file with implementation of tests for DnaSequenceRepresentationConverter structure
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/common/DnaSequenceRepresentationConverter.hpp"

using namespace dnaasm;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestDnaSequenceRepresentationConverter)

BOOST_AUTO_TEST_CASE(DnaSequenceRepresentationConverter_basic_test)
{
    unsigned short K1 = 3U;
    DnaSequenceRepresentationConverter dnaSequenceRepresentationConverter(K1);
    string stringRepresentation = "ACGT";
    bitset<2*MAX_KMER_LENGTH> bitsetRepresentation(string("11100100"));
    string trimmedStringRepresentation = "ACG";
    bitset<2*MAX_KMER_LENGTH> trimmedBitsetRepresentation(string("100100"));
    BOOST_CHECK_EQUAL(dnaSequenceRepresentationConverter.convertToString(bitsetRepresentation), trimmedStringRepresentation);
    BOOST_CHECK_EQUAL(dnaSequenceRepresentationConverter.convertToBitset(stringRepresentation.data()), trimmedBitsetRepresentation);
}

BOOST_AUTO_TEST_SUITE_END()

