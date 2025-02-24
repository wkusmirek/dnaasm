/**
 * \file TestIsLimitedDirectedPath.cpp
 * \brief the C++ file with implementation of tests for IsLimitedDirectedPath class
 *
 */

#include <boost/test/unit_test.hpp>

#include "../../../src/dbj/IsLimitedDirectedPath.hpp"
#include "../../../src/dbj/UnitigsToContigsExtension.hpp"
#include "../../../src/dbj/SingleGraph.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestIsLimitedDirectedPath)
// TODO
// trzeba ogarnąć te testy, bo nie ma pola .contig_ w contigsGraph
/*
BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_equal_to_destination_limit_equal_to_0)
{
    unsigned short limit = 0U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0;
    contig0.push_back(v0);
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v0, cv0, cv0), true);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_not_equal_to_destination_limit_equal_to_0)
{
    unsigned short limit = 0U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0;
    contig0.push_back(v0);
    contig0.push_back(v1);
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v1, cv0, cv0), false);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v1, v0, cv0, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_not_connected_contig)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0;
    contig0.push_back(v0);
    ContigsExtension::Contig contig1;
    contig1.push_back(v1);
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v1, cv0, cv1), false);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v1, v0, cv1, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_connected_by_paired_read)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0;
    contig0.push_back(v0);
    ContigsExtension::Contig contig1;
    contig1.push_back(v1);
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = false;
    contigsGraph[e0].isForPairedReads_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v1, cv0, cv1), false);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v1, v0, cv1, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_connected_by_connected_contigs_edge_single_vertex_in_contigs)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0;
    contig0.push_back(v0);
    ContigsExtension::Contig contig1;
    contig1.push_back(v1);
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = true;
    contigsGraph[e0].isForPairedReads_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v1, cv0, cv1), true);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v1, v0, cv1, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_subcontig_size_less_than_limit)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    Vertex v2 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0;
    contig0.push_back(v0);
    ContigsExtension::Contig contig1(5, v1);
    ContigsExtension::Contig contig2;
    contig2.push_back(v2);
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv2 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    contigsGraph[cv2].contig_ = &contig2;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e1 = add_edge(cv1, cv2, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = true;
    contigsGraph[e1].isForConnectedContigs_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v2, cv0, cv2), true);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v2, v0, cv2, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_subcontig_size_greater_than_limit)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    Vertex v2 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0;
    contig0.push_back(v0);
    ContigsExtension::Contig contig1(15, v1);
    ContigsExtension::Contig contig2;
    contig2.push_back(v2);
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv2 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    contigsGraph[cv2].contig_ = &contig2;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e1 = add_edge(cv1, cv2, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = true;
    contigsGraph[e1].isForConnectedContigs_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v2, cv0, cv2), false);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v2, v0, cv2, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_subcontig_size_less_than_limit_fork_in_the_end)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    Vertex v2 = add_vertex(uncompGraph);
    Vertex v3 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0;
    contig0.push_back(v0);
    ContigsExtension::Contig contig1(7, v1);
    ContigsExtension::Contig contig2(7, v2);
    ContigsExtension::Contig contig3;
    contig3.push_back(v3);
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv2 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv3 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    contigsGraph[cv2].contig_ = &contig2;
    contigsGraph[cv3].contig_ = &contig3;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e1 = add_edge(cv1, cv2, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e2 = add_edge(cv1, cv3, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = true;
    contigsGraph[e1].isForConnectedContigs_ = true;
    contigsGraph[e2].isForConnectedContigs_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v3, cv0, cv3), true);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v3, v0, cv3, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_subcontig_size_greater_than_limit_fork_in_the_end)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    Vertex v2 = add_vertex(uncompGraph);
    Vertex v3 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0;
    contig0.push_back(v0);
    ContigsExtension::Contig contig1(15, v1);
    ContigsExtension::Contig contig2(15, v2);
    ContigsExtension::Contig contig3;
    contig2.push_back(v3);
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv2 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv3 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    contigsGraph[cv2].contig_ = &contig2;
    contigsGraph[cv3].contig_ = &contig3;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e1 = add_edge(cv1, cv2, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e2 = add_edge(cv1, cv3, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = true;
    contigsGraph[e1].isForConnectedContigs_ = true;
    contigsGraph[e2].isForConnectedContigs_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v3, cv0, cv3), false);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v3, v0, cv3, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_repetitive_vertices_in_end_contigs)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    Vertex v2 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0(20, v0);
    ContigsExtension::Contig contig1(5, v1);
    ContigsExtension::Contig contig2(20, v2);
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv2 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    contigsGraph[cv2].contig_ = &contig2;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e1 = add_edge(cv1, cv2, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = true;
    contigsGraph[e1].isForConnectedContigs_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v2, cv0, cv2), true);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v2, v0, cv2, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_repetitive_vertices_in_end_contigs_only_one_specified_vertex_source_close_to_end_dest_close_to_begin)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    Vertex v2 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0(20, v1);
    contig0[17] = v0;
    ContigsExtension::Contig contig1(5, v1);
    ContigsExtension::Contig contig2(20, v1);
    contig2[2] = v2;
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv2 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    contigsGraph[cv2].contig_ = &contig2;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e1 = add_edge(cv1, cv2, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = true;
    contigsGraph[e1].isForConnectedContigs_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v2, cv0, cv2), true);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v2, v0, cv2, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_repetitive_vertices_in_end_contigs_only_one_specified_vertex_source_far_from_end_dest_far_from_begin)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    Vertex v2 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0(20, v1);
    contig0[2] = v0;
    ContigsExtension::Contig contig1(5, v1);
    ContigsExtension::Contig contig2(20, v1);
    contig2[17] = v2;
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv2 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    contigsGraph[cv2].contig_ = &contig2;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e1 = add_edge(cv1, cv2, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = true;
    contigsGraph[e1].isForConnectedContigs_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v2, cv0, cv2), false);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v2, v0, cv2, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_repetitive_vertices_in_end_contigs_only_one_specified_vertex_source_close_to_end_dest_far_from_begin)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    Vertex v2 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0(20, v1);
    contig0[17] = v0;
    ContigsExtension::Contig contig1(5, v1);
    ContigsExtension::Contig contig2(20, v1);
    contig2[17] = v2;
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv2 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    contigsGraph[cv2].contig_ = &contig2;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e1 = add_edge(cv1, cv2, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = true;
    contigsGraph[e1].isForConnectedContigs_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v2, cv0, cv2), false);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v2, v0, cv2, cv0), false);
}

BOOST_AUTO_TEST_CASE(isLimitedDirectedPath_source_and_destination_in_another_contigs_repetitive_vertices_in_end_contigs_only_one_specified_vertex_source_far_from_end_dest_close_to_begin)
{
    unsigned short limit = 10U;
    UncompressedGraph uncompGraph;
    Vertex v0 = add_vertex(uncompGraph);
    Vertex v1 = add_vertex(uncompGraph);
    Vertex v2 = add_vertex(uncompGraph);
    ContigsExtension::Contig contig0(20, v1);
    contig0[2] = v0;
    ContigsExtension::Contig contig1(5, v1);
    ContigsExtension::Contig contig2(20, v1);
    contig2[2] = v2;
    ContigsExtension::ContigsGraph contigsGraph;
    ContigsExtension::ContigsGraphVertex cv0 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv1 = add_vertex(contigsGraph);
    ContigsExtension::ContigsGraphVertex cv2 = add_vertex(contigsGraph);
    contigsGraph[cv0].contig_ = &contig0;
    contigsGraph[cv1].contig_ = &contig1;
    contigsGraph[cv2].contig_ = &contig2;
    ContigsExtension::ContigsGraphEdge e0 = add_edge(cv0, cv1, contigsGraph).first;
    ContigsExtension::ContigsGraphEdge e1 = add_edge(cv1, cv2, contigsGraph).first;
    contigsGraph[e0].isForConnectedContigs_ = true;
    contigsGraph[e1].isForConnectedContigs_ = true;
    IsLimitedDirectedPath<ContigsExtension::ContigsGraph> isLimitedDirectedPath(contigsGraph, limit);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v0, v2, cv0, cv2), false);
    BOOST_CHECK_EQUAL(isLimitedDirectedPath(v2, v0, cv2, cv0), false);
}
*/
BOOST_AUTO_TEST_SUITE_END()

