/**
 * \file TestBloomFilterFiller.cpp
 * \brief the C++ file with implementation of tests for BloomFilterFiller class
 *
 */

#include <boost/test/unit_test.hpp>
#include <sstream>
#include "../../../src/common/InputFile.hpp"
#include "../../../src/scfr/BloomFilterFiller.hpp"
#include "../mocks/MockBloomFilter.hpp"

using namespace dnaasm::scfr;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestBloomFilterFiller)

BOOST_AUTO_TEST_CASE(fillBloomFilter)
{
    MockBloomFilter mbf;

    ContigSeqHashMap contigs;
    contigs.insert({1, "ACC"});
    contigs.insert({2, "TAG"});

//    EXPECT_CALL(mbf, insertKmersFromSeq(string("ACC"))).Times(1);
//    EXPECT_CALL(mbf, insertKmersFromSeq(string("GGT"))).Times(1);
//    EXPECT_CALL(mbf, insertKmersFromSeq(string("TAG"))).Times(1);
//    EXPECT_CALL(mbf, insertKmersFromSeq(string("CTA"))).Times(1);

    BloomFilterFiller::fillBloomFilter(contigs, mbf);
}

BOOST_AUTO_TEST_SUITE_END()
