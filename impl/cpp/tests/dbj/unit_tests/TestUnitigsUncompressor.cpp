/**
 * \file TestUnitigsUncompressor.cpp
 * \brief the C++ file with implementation of tests for UnitigsUncompressor class
 *
 */

#include <boost/test/unit_test.hpp>

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
//#pragma warning(disable:4068)
//#pragma warning(disable:4512)
#endif

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

#include "../../../src/dbj/globals.hpp"
#include "../../../src/dbj/UnitigsUncompressor.hpp"

#if defined __GNUC__ && !defined __clang__
#pragma GCC diagnostic pop
#endif

using namespace dnaasm::dbj;
using namespace std;

typedef boost::graph_traits<CompressedDeBruijnGraph>::vertex_descriptor CompressedDeBruijnGraphVertex;
typedef std::vector<CompressedDeBruijnGraphVertex> CompressedUnitig;
typedef std::vector<CompressedUnitig> CompressedUnitigs;
typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;
typedef boost::graph_traits<DeBruijnGraph>::vertex_descriptor DeBruijnGraphVertex;
typedef std::vector<DeBruijnGraphVertex> UncompressedUnitig;
typedef std::vector<UncompressedUnitig> UncompressedUnitigs;

BOOST_AUTO_TEST_SUITE(TestUnitigsUncompressor)

BOOST_AUTO_TEST_CASE(uncompressUnitigsTest_empty_unitigs)
{
    CompressedDeBruijnGraph compGraph;
    CompressedUnitigs compUnitigs;
    UncompressedUnitigs uncompUnitigs;
    UnitigsUncompressor<DeBruijnGraph, CompressedDeBruijnGraph> unitigsUncompressor(compGraph);
    unitigsUncompressor.uncompressUnitigs(uncompUnitigs, compUnitigs);
    BOOST_CHECK_EQUAL(uncompUnitigs.size(), 0);
}

BOOST_AUTO_TEST_CASE(uncompressUnitigsTest_1_long_compressed_unitig)
{
    CompressedDeBruijnGraph compGraph;
    CompressedDeBruijnGraphVertex v0 = add_vertex(compGraph);
    CompressedDeBruijnGraphVertex v1 = add_vertex(compGraph);
    compGraph[v0].uncompressedVertices_.push_back(4UL);
    compGraph[v0].uncompressedVertices_.push_back(5UL);
    compGraph[v0].uncompressedVertices_.push_back(6UL);
    compGraph[v1].uncompressedVertices_.push_back(9UL);
    compGraph[v1].uncompressedVertices_.push_back(10UL);
    compGraph[v1].uncompressedVertices_.push_back(11UL);
    CompressedUnitig compUnitig0;
    compUnitig0.push_back(v0);
    compUnitig0.push_back(v1);
    CompressedUnitigs compUnitigs;
    compUnitigs.push_back(compUnitig0);
    UncompressedUnitigs uncompUnitigs;
    UnitigsUncompressor<DeBruijnGraph, CompressedDeBruijnGraph> unitigsUncompressor(compGraph);
    unitigsUncompressor.uncompressUnitigs(uncompUnitigs, compUnitigs);
    BOOST_CHECK_EQUAL(uncompUnitigs.size(), 1);
    BOOST_CHECK_EQUAL(uncompUnitigs[0].size(), 6);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][0], 4UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][1], 5UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][2], 6UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][3], 9UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][4], 10UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][5], 11UL);
}

BOOST_AUTO_TEST_CASE(uncompressUnitigsTest_2_long_compressed_unitigs)
{
    CompressedDeBruijnGraph compGraph;
    CompressedDeBruijnGraphVertex v0 = add_vertex(compGraph);
    CompressedDeBruijnGraphVertex v1 = add_vertex(compGraph);
    CompressedDeBruijnGraphVertex v2 = add_vertex(compGraph);
    compGraph[v0].uncompressedVertices_.push_back(4UL);
    compGraph[v0].uncompressedVertices_.push_back(5UL);
    compGraph[v0].uncompressedVertices_.push_back(6UL);
    compGraph[v1].uncompressedVertices_.push_back(9UL);
    compGraph[v1].uncompressedVertices_.push_back(10UL);
    compGraph[v1].uncompressedVertices_.push_back(11UL);
    compGraph[v2].uncompressedVertices_.push_back(7UL);
    CompressedUnitig compUnitig0;
    compUnitig0.push_back(v0);
    compUnitig0.push_back(v1);
    CompressedUnitig compUnitig1;
    compUnitig1.push_back(v0);
    compUnitig1.push_back(v1);
    compUnitig1.push_back(v2);
    CompressedUnitigs compUnitigs;
    compUnitigs.push_back(compUnitig0);
    compUnitigs.push_back(compUnitig1);
    UncompressedUnitigs uncompUnitigs;
    UnitigsUncompressor<DeBruijnGraph, CompressedDeBruijnGraph> unitigsUncompressor(compGraph);
    unitigsUncompressor.uncompressUnitigs(uncompUnitigs, compUnitigs);
    BOOST_CHECK_EQUAL(uncompUnitigs.size(), 2);
    BOOST_CHECK_EQUAL(uncompUnitigs[0].size(), 6);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][0], 4UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][1], 5UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][2], 6UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][3], 9UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][4], 10UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[0][5], 11UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[1].size(), 7);
    BOOST_CHECK_EQUAL(uncompUnitigs[1][0], 4UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[1][1], 5UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[1][2], 6UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[1][3], 9UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[1][4], 10UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[1][5], 11UL);
    BOOST_CHECK_EQUAL(uncompUnitigs[1][6], 7UL);
}

BOOST_AUTO_TEST_CASE(uncompressUnitigsTest_disconnected_single_vertex)
{
    CompressedDeBruijnGraph compGraph;
    CompressedDeBruijnGraphVertex v0 = add_vertex(compGraph);
    compGraph[v0].uncompressedVertices_.push_back(4UL);
    CompressedUnitig compUnitig0;
    compUnitig0.push_back(v0);
    CompressedUnitigs compUnitigs;
    compUnitigs.push_back(compUnitig0);
    UncompressedUnitigs uncompUnitigs;
    UnitigsUncompressor<DeBruijnGraph, CompressedDeBruijnGraph> unitigsUncompressor(compGraph);
    unitigsUncompressor.uncompressUnitigs(uncompUnitigs, compUnitigs);
    BOOST_CHECK_EQUAL(uncompUnitigs.size(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

