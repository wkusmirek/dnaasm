/**
 * \file TestCommon.cpp
 * \brief the C++ file with implementation of tests for methods in common file
 *
 */

#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../../../src/scfr/common.hpp"

using namespace dnaasm::scfr;

BOOST_AUTO_TEST_SUITE(TestCommon)

    BOOST_AUTO_TEST_CASE(get_reverse_complementary)
    {
        BOOST_CHECK_EQUAL(getReverseComplementary(""), "");
        BOOST_CHECK_EQUAL(getReverseComplementary("T"), "A");
        BOOST_CHECK_EQUAL(getReverseComplementary("c"), "g");
        BOOST_CHECK_EQUAL(getReverseComplementary("ACTGGTCAGT"), "ACTGACCAGT");
        BOOST_CHECK_EQUAL(getReverseComplementary("tgcaagctc"), "gagcttgca");
    }

    BOOST_AUTO_TEST_CASE(get_contig_id_and_orientation_from_str)
    {
        std::pair<unsigned int, bool> test1 = getContigIdAndOrientationFromStr("");
        BOOST_CHECK_EQUAL(test1.first, 0U);
        BOOST_CHECK_EQUAL(test1.second, false);

        std::pair<unsigned int, bool> test2 = getContigIdAndOrientationFromStr("f");
        BOOST_CHECK_EQUAL(test2.first, 0U);
        BOOST_CHECK_EQUAL(test2.second, false);

        std::pair<unsigned int, bool> test3 = getContigIdAndOrientationFromStr("abc");
        BOOST_CHECK_EQUAL(test3.first, 0U);
        BOOST_CHECK_EQUAL(test3.second, false);

        std::pair<unsigned int, bool> test4 = getContigIdAndOrientationFromStr("f56");
        BOOST_CHECK_EQUAL(test4.first, 56);
        BOOST_CHECK_EQUAL(test4.second, false);

        std::pair<unsigned int, bool> test5 = getContigIdAndOrientationFromStr("r3");
        BOOST_CHECK_EQUAL(test5.first, 3);
        BOOST_CHECK_EQUAL(test5.second, true);

        std::pair<unsigned int, bool> test6 = getContigIdAndOrientationFromStr("r-3.0");
        BOOST_CHECK_EQUAL(test6.first, 0U);
        BOOST_CHECK_EQUAL(test6.second, false);
    }

BOOST_AUTO_TEST_SUITE_END()
