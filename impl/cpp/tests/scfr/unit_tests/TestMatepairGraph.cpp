/**
 * \file TestMatepair.cpp
 * \brief the C++ file with implementation of tests for MatepairGraph class
 *
 */

#include <boost/test/unit_test.hpp>
#include <sstream>
#include "../../../src/common/InputFile.hpp"
#include "../../../src/scfr/MatepairGraph.hpp"

using namespace dnaasm::scfr;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestMatepairGraph)

BOOST_AUTO_TEST_CASE(add_vertex)
{
    MatepairGraph mpg(3);

    auto v_desc1 = mpg.add_vertex("CAT");
    auto v_desc2 = mpg.add_vertex("CAT");
    auto v_desc3 = mpg.add_vertex("GCA");
    BOOST_REQUIRE(v_desc1 != mpg.graph().null_vertex());
    BOOST_REQUIRE(v_desc2 != mpg.graph().null_vertex());
    BOOST_REQUIRE(v_desc3 != mpg.graph().null_vertex());
    BOOST_CHECK_EQUAL(v_desc1, v_desc2);
    BOOST_CHECK(v_desc1 != v_desc3);
    BOOST_CHECK_EQUAL(2, num_vertices(mpg.graph()));
    BOOST_CHECK_EQUAL(0, num_edges(mpg.graph()));
}

BOOST_AUTO_TEST_CASE(add_vertex_with_properties)
{
    MatepairGraph mpg(3);
    MatepairGraphVertexProperties prop1;
    MatepairGraphVertexProperties prop2(2, 4, 10);

    auto v_desc1 = mpg.add_vertex("CAT", prop1);
    auto v_desc2 = mpg.add_vertex("CAT", prop1);
    auto v_desc3 = mpg.add_vertex("GCA", prop2);
    BOOST_REQUIRE(v_desc1 != mpg.graph().null_vertex());
    BOOST_REQUIRE(v_desc2 != mpg.graph().null_vertex());
    BOOST_REQUIRE(v_desc3 != mpg.graph().null_vertex());
    BOOST_CHECK_EQUAL(v_desc1, v_desc2);
    BOOST_CHECK(v_desc1 != v_desc3);
    BOOST_CHECK_EQUAL(2, num_vertices(mpg.graph()));
    BOOST_CHECK_EQUAL(0, num_edges(mpg.graph()));
    BOOST_CHECK_EQUAL(0, mpg.graph()[v_desc1].contigId_);
    BOOST_CHECK_EQUAL(0, mpg.graph()[v_desc1].start_);
    BOOST_CHECK_EQUAL(0, mpg.graph()[v_desc1].end_);
    BOOST_CHECK_EQUAL(2, mpg.graph()[v_desc3].contigId_);
    BOOST_CHECK_EQUAL(4, mpg.graph()[v_desc3].start_);
    BOOST_CHECK_EQUAL(10, mpg.graph()[v_desc3].end_);

    // test MatepairGraphInternal const &MatepairGraph::graph() const
    BOOST_CHECK_EQUAL(10,
        (const_cast<const MatepairGraph&>(mpg)).graph()[v_desc3].end_);
}

BOOST_AUTO_TEST_CASE(vertex)
{
    MatepairGraph mpg(3);

    auto v_desc1 = mpg.add_vertex("CAT");
    auto v_desc2 = mpg.add_vertex("GCA");

    BOOST_CHECK_EQUAL(v_desc1, mpg.vertex("CAT"));
    BOOST_CHECK_EQUAL(v_desc2, mpg.vertex("GCA"));
}

BOOST_AUTO_TEST_SUITE_END()