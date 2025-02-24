/**
 * \file TestMain.cpp
 * \brief the C++ file with definition of 'main' for cpp unit test
 *
 */
#define BOOST_TEST_MODULE "dbj"
#include <boost/test/included/unit_test.hpp>

//supressing logger info in unit tests
#define BOOST_LOG_DYN_LINK
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>

#include <boost/filesystem.hpp>
#include "../../../src/common/common.hpp"

struct F {
    F() {
        boost::log::core::get()->set_filter(
            boost::log::trivial::severity >= boost::log::trivial::warning);

        // create tmp dir required by some objects from dbj module
        if (!boost::filesystem::exists(CALC_TMP_DIR)) {
            boost::filesystem::create_directory(CALC_TMP_DIR);
        }
    }
};

BOOST_GLOBAL_FIXTURE( F );
