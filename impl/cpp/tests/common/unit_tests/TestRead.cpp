/**
 * \file TestRead.cpp
 * \brief the C++ file with implementation of tests for Read class
 *
 */

#include <boost/test/unit_test.hpp>
#include "../../../src/common/Read.hpp"

using namespace dnaasm;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestRead)

BOOST_AUTO_TEST_CASE(makeComplementaryStrand_test)
{
    Read read(0);
    read.setRead("");
    read.setQuality("");
    read.setDescription("");
    read.makeComplementaryStrand();
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
    BOOST_CHECK_EQUAL(read.getDescription(), "");
    read.setRead("A");
    read.setQuality("A");
    read.setDescription("test");
    BOOST_CHECK_EQUAL(read.makeComplementaryStrand(), 0);
    BOOST_CHECK_EQUAL(read.getRead(), "T");
    BOOST_CHECK_EQUAL(read.getQuality(), "A");
    BOOST_CHECK_EQUAL(read.getDescription(), "test");
    read.setRead("ACTGGTCAGT");
    read.setQuality("ABCDEFGHIJ");
    read.makeComplementaryStrand();
    BOOST_CHECK_EQUAL(read.getRead(), "ACTGACCAGT");
    BOOST_CHECK_EQUAL(read.getQuality(), "JIHGFEDCBA");
    BOOST_CHECK_EQUAL(read.getDescription(), "test");
    read.setRead("APC");
    read.setQuality("ABC");
    read.makeComplementaryStrand();
    BOOST_CHECK_EQUAL(read.getRead(), "GPT");
    BOOST_CHECK_EQUAL(read.getQuality(), "CBA");
    BOOST_CHECK_EQUAL(read.getDescription(), "test");
}

BOOST_AUTO_TEST_CASE(filterReadBasedOnQuality1)
{
    Read read(40);
    read.setRead("");
    read.setQuality("");
    read.filterReadBasedOnQuality();
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
}

BOOST_AUTO_TEST_CASE(filterReadBasedOnQuality2)
{
    Read read(40);
    read.setRead("AC");
    read.setQuality("");
    read.filterReadBasedOnQuality();
    BOOST_CHECK_EQUAL(read.getRead(), "AC");
    BOOST_CHECK_EQUAL(read.getQuality(), "");
}

BOOST_AUTO_TEST_CASE(filterReadBasedOnQuality3)
{
    Read read(40);
    read.setRead("");
    read.setQuality("IJJ");
    read.filterReadBasedOnQuality();
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "IJJ");
}

BOOST_AUTO_TEST_CASE(filterReadBasedOnQuality4)
{
    Read read(35);
    read.setRead("TAT");
    read.setQuality("IJJ");
    read.filterReadBasedOnQuality();
    BOOST_CHECK_EQUAL(read.getRead(), "TAT");
    BOOST_CHECK_EQUAL(read.getQuality(), "IJJ");
}

BOOST_AUTO_TEST_CASE(filterReadBasedOnQuality5)
{
    Read read(40);
    read.setRead("TAT");
    read.setQuality("IJJ");
    read.filterReadBasedOnQuality();
    BOOST_CHECK_EQUAL(read.getRead(), "TAT");
    BOOST_CHECK_EQUAL(read.getQuality(), "IJJ");
}

BOOST_AUTO_TEST_CASE(filterReadBasedOnQuality6)
{
    Read read(41);
    read.setRead("TAT");
    read.setQuality("IJJ");
    read.filterReadBasedOnQuality();
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "IJJ");
}

BOOST_AUTO_TEST_CASE(filterReadBasedOnQuality7)
{
    Read read(41);
    read.setRead("TATCCA");
    read.setQuality("JJCCJJ");
    read.filterReadBasedOnQuality();
    BOOST_CHECK_EQUAL(read.getRead(), "TA");
    BOOST_CHECK_EQUAL(read.getQuality(), "JJCCJJ");
}

BOOST_AUTO_TEST_CASE(filterReadBasedOnQuality8)
{
    Read read(45);
    read.setRead("TATACC");
    read.setQuality("IJJIJJ");
    read.filterReadBasedOnQuality();
    BOOST_CHECK_EQUAL(read.getRead(), "");
    BOOST_CHECK_EQUAL(read.getQuality(), "IJJIJJ");
}

BOOST_AUTO_TEST_CASE(filterReadBasedOnQuality9)
{
    Read read(0);
    read.setRead("TATACC");
    read.setQuality("IJJIJJ");
    read.filterReadBasedOnQuality();
    BOOST_CHECK_EQUAL(read.getRead(), "TATACC");
    BOOST_CHECK_EQUAL(read.getQuality(), "IJJIJJ");
}

BOOST_AUTO_TEST_SUITE_END()
