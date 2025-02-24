/**
 * \file TestMinHash.cpp
 * \brief the C++ file with implementation of tests for MinHash structure
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/olc/common.hpp"
#include "../../../src/olc/MinHash.hpp"

using namespace dnaasm::olc;

BOOST_AUTO_TEST_SUITE(TestMinHash)

BOOST_AUTO_TEST_CASE(initializeTest_01)
{
    PermutationVector vec = {
        {1, 2, 3},
        {4, 5, 6}
    };

    MinHash::initialize(1, 3, vec);

    BOOST_CHECK_EQUAL(vec.size(), 2);

    for (const auto &perm : vec) {
        BOOST_CHECK_EQUAL(perm.size(), 3);
    }
}

BOOST_AUTO_TEST_CASE(basicOverlapTest_01)
{
    std::string r1 = "CAC";
    std::string r2 = "CAC";
    size_t numPerm = 128;
    size_t seed = 1;
    HashObj hashObj;
    PermutationVector perms;
    MinHash::initialize(seed, numPerm, perms);

    MinHash m1(numPerm);
    MinHash m2(numPerm);
    m1.update(r1, 0U, hashObj, perms);
    m2.update(r2, 0U, hashObj, perms);
    BOOST_CHECK_EQUAL(m1.estJaccardSimilarity(m2), 1.0);
}

BOOST_AUTO_TEST_CASE(basicOverlapTest_02)
{
    std::string r1 = "CACTGACTGACCTGCC";
    std::string r2 = "CACTGACTGACCTGCC";
    size_t numPerm = 128;
    size_t seed = 1;
    HashObj hashObj;
    PermutationVector perms;
    MinHash::initialize(seed, numPerm, perms);

    MinHash m1(numPerm);
    MinHash m2(numPerm);
    m1.update(r1, 0U, hashObj, perms);
    m2.update(r2, 0U, hashObj, perms);
    BOOST_CHECK_EQUAL(m1.estJaccardSimilarity(m2), 1.0);
}

BOOST_AUTO_TEST_CASE(basicOverlapTest_03)
{
    std::string r1 = "AAAA";
    std::string r2 = "CCCC";
    size_t numPerm = 128;
    size_t seed = 1;
    HashObj hashObj;
    PermutationVector perms;
    MinHash::initialize(seed, numPerm, perms);

    MinHash m1(numPerm);
    MinHash m2(numPerm);
    m1.update(r1, 0U, hashObj, perms);
    m2.update(r2, 0U, hashObj, perms);
    BOOST_CHECK_EQUAL(m1.estJaccardSimilarity(m2), 0.0);
}

BOOST_AUTO_TEST_SUITE_END()
