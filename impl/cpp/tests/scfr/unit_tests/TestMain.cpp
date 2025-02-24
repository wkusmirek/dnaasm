/**
 * \file TestMain.cpp
 * \brief the C++ file with definition of 'main' for cpp unit test
 *
 */
#include <gmock/gmock.h>

#define BOOST_TEST_MODULE "scfr"
#include <boost/test/included/unit_test.hpp>

struct InitGMock {
    InitGMock() {
        ::testing::GTEST_FLAG(throw_on_failure) = true;
        //::testing::GMOCK_FLAG(verbose) = "info";
        ::testing::InitGoogleMock(&boost::unit_test::framework::master_test_suite().argc,
                                  boost::unit_test::framework::master_test_suite().argv);
    }
    ~InitGMock() { }
};

BOOST_GLOBAL_FIXTURE(InitGMock);