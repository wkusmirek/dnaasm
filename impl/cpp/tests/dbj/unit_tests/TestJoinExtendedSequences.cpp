/**
 * \file TestJoinExtendedSequences.cpp
 * \brief the C++ file with implementation of tests for TestJoinExtendedSequences class
 *
 */


#include <boost/test/unit_test.hpp>
#include "../../../src/dbj/globals.hpp"

#include "../../../src/dbj/JoinExtendedSequences.hpp"
#include "../../../src/dbj/UnitigsToContigsExtension.hpp"

using namespace dnaasm::dbj;
using namespace std;

BOOST_AUTO_TEST_SUITE(TestJoinExtendedSequences)

/******************************** unitigs graph ********************************/

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_empty_unitig_graph)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph> joinExtendedSequences(unitigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 0);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_single_multiple_repetitive_unitigs)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph> joinExtendedSequences(unitigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 3);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 1);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv, v1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[1].size(), 1);
    iv = vertexRepresentationSequences[1].begin();
    BOOST_CHECK_EQUAL(*iv, v2);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[2].size(), 1);
    iv = vertexRepresentationSequences[2].begin();
    BOOST_CHECK_EQUAL(*iv, v0);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_one_unitig_contained_in_another_unitig)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v0);
    vertexRepresentationSequence1.push_back(v1);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    vertexRepresentationSequence2.push_back(v0);
    vertexRepresentationSequence2.push_back(v1);
    vertexRepresentationSequence2.push_back(v2);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph> joinExtendedSequences(unitigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 4);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv, v2);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_four_unitigs_all_vertices_not_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v3);
    vertexRepresentationSequence2.push_back(v1);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence3;
    vertexRepresentationSequence3.push_back(v1);
    vertexRepresentationSequence3.push_back(v4);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence3);
    unitigsGraph[v0].isOriginal_ = false;
    unitigsGraph[v1].isOriginal_ = false;
    unitigsGraph[v2].isOriginal_ = false;
    unitigsGraph[v3].isOriginal_ = false;
    unitigsGraph[v4].isOriginal_ = false;
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph> joinExtendedSequences(unitigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 5);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 4);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 2);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv, v1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[1].size(), 2);
    iv = vertexRepresentationSequences[1].begin();
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv, v2);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[2].size(), 2);
    iv = vertexRepresentationSequences[2].begin();
    BOOST_CHECK_EQUAL(*iv++, v3);
    BOOST_CHECK_EQUAL(*iv, v1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[3].size(), 2);
    iv = vertexRepresentationSequences[3].begin();
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv, v4);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_two_unitigs_all_vertices_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = true;
    unitigsGraph[v2].isOriginal_ = true;
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph> joinExtendedSequences(unitigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 3);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv, v2);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_three_unitigs_all_vertices_original)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    vertexRepresentationSequence2.push_back(v3);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = true;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v3].isOriginal_ = true;
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph> joinExtendedSequences(unitigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 4);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv, v3);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_three_unitigs_all_vertices_original_another_order)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    vertexRepresentationSequence2.push_back(v3);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = true;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v3].isOriginal_ = true;
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph> joinExtendedSequences(unitigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 4);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv, v3);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_three_unitigs_all_vertices_original_with_vertex_which_depicts_N_sign)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    vertexRepresentationSequence2.push_back(std::numeric_limits<unsigned long>::max());    // N sign
    vertexRepresentationSequence2.push_back(std::numeric_limits<unsigned long>::max());    // N sign
    vertexRepresentationSequence2.push_back(std::numeric_limits<unsigned long>::max());    // N sign
    vertexRepresentationSequence2.push_back(v3);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = true;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v3].isOriginal_ = true;
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph> joinExtendedSequences(unitigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 7);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv++, std::numeric_limits<unsigned long>::max());    // N sign
    BOOST_CHECK_EQUAL(*iv++, std::numeric_limits<unsigned long>::max());    // N sign
    BOOST_CHECK_EQUAL(*iv++, std::numeric_limits<unsigned long>::max());    // N sign
    BOOST_CHECK_EQUAL(*iv, v3);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_more_unitigs_all_vertices_original_another_order)
{
    UnitigsToContigsExtension::UnitigsGraph unitigsGraph;
    UnitigsToContigsExtension::UnitigsGraphVertex v0 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v1 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v2 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v3 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v4 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v5 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v6 = add_vertex(unitigsGraph);
    UnitigsToContigsExtension::UnitigsGraphVertex v7 = add_vertex(unitigsGraph);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    vertexRepresentationSequence2.push_back(v3);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence3;
    vertexRepresentationSequence3.push_back(v2);
    vertexRepresentationSequence3.push_back(v3);
    vertexRepresentationSequence3.push_back(v4);
    vertexRepresentationSequence3.push_back(v5);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence vertexRepresentationSequence4;
    vertexRepresentationSequence4.push_back(v5);
    vertexRepresentationSequence4.push_back(v6);
    vertexRepresentationSequence4.push_back(v7);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence3);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence4);
    unitigsGraph[v0].isOriginal_ = true;
    unitigsGraph[v1].isOriginal_ = true;
    unitigsGraph[v2].isOriginal_ = true;
    unitigsGraph[v3].isOriginal_ = true;
    unitigsGraph[v4].isOriginal_ = true;
    unitigsGraph[v5].isOriginal_ = true;
    unitigsGraph[v6].isOriginal_ = true;
    unitigsGraph[v7].isOriginal_ = true;
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph> joinExtendedSequences(unitigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(unitigsGraph), 8);
    BOOST_CHECK_EQUAL(num_edges(unitigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 8);
    JoinExtendedSequences<UnitigsToContigsExtension::UnitigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv++, v3);
    BOOST_CHECK_EQUAL(*iv++, v4);
    BOOST_CHECK_EQUAL(*iv++, v5);
    BOOST_CHECK_EQUAL(*iv++, v6);
    BOOST_CHECK_EQUAL(*iv, v7);
}

/******************************** contigs graph ********************************/

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_empty_contig_graph)
{
    ContigsToScaffoldsExtension::ContigsGraph contigsGraph;
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph> joinExtendedSequences(contigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(contigsGraph), 0);
    BOOST_CHECK_EQUAL(num_edges(contigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 0);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_single_multiple_repetitive_contigs)
{
    ContigsToScaffoldsExtension::ContigsGraph contigsGraph;
    ContigsToScaffoldsExtension::ContigsGraphVertex v0 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v1 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v2 = add_vertex(contigsGraph);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    contigsGraph[v0].isLongNode_ = false;
    contigsGraph[v1].isLongNode_ = false;
    contigsGraph[v2].isLongNode_ = false;
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph> joinExtendedSequences(contigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(contigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(contigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 3);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 1);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv, v1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[1].size(), 1);
    iv = vertexRepresentationSequences[1].begin();
    BOOST_CHECK_EQUAL(*iv, v2);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[2].size(), 1);
    iv = vertexRepresentationSequences[2].begin();
    BOOST_CHECK_EQUAL(*iv, v0);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_one_contig_contained_in_another_contig)
{
    ContigsToScaffoldsExtension::ContigsGraph contigsGraph;
    ContigsToScaffoldsExtension::ContigsGraphVertex v0 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v1 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v2 = add_vertex(contigsGraph);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v0);
    vertexRepresentationSequence1.push_back(v1);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    vertexRepresentationSequence2.push_back(v0);
    vertexRepresentationSequence2.push_back(v1);
    vertexRepresentationSequence2.push_back(v2);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    contigsGraph[v0].isLongNode_ = false;
    contigsGraph[v1].isLongNode_ = false;
    contigsGraph[v2].isLongNode_ = false;
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph> joinExtendedSequences(contigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(contigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(contigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 4);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv, v2);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_four_contigs_all_vertices_not_long)
{
    ContigsToScaffoldsExtension::ContigsGraph contigsGraph;
    ContigsToScaffoldsExtension::ContigsGraphVertex v0 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v1 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v2 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v3 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v4 = add_vertex(contigsGraph);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v3);
    vertexRepresentationSequence2.push_back(v1);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence3;
    vertexRepresentationSequence3.push_back(v1);
    vertexRepresentationSequence3.push_back(v4);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence3);
    contigsGraph[v0].isLongNode_ = false;
    contigsGraph[v1].isLongNode_ = false;
    contigsGraph[v2].isLongNode_ = false;
    contigsGraph[v3].isLongNode_ = false;
    contigsGraph[v4].isLongNode_ = false;
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph> joinExtendedSequences(contigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(contigsGraph), 5);
    BOOST_CHECK_EQUAL(num_edges(contigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 4);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 2);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv, v1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[1].size(), 2);
    iv = vertexRepresentationSequences[1].begin();
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv, v2);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[2].size(), 2);
    iv = vertexRepresentationSequences[2].begin();
    BOOST_CHECK_EQUAL(*iv++, v3);
    BOOST_CHECK_EQUAL(*iv, v1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[3].size(), 2);
    iv = vertexRepresentationSequences[3].begin();
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv, v4);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_two_contigs_all_vertices_long)
{
    ContigsToScaffoldsExtension::ContigsGraph contigsGraph;
    ContigsToScaffoldsExtension::ContigsGraphVertex v0 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v1 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v2 = add_vertex(contigsGraph);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    contigsGraph[v0].isLongNode_ = true;
    contigsGraph[v1].isLongNode_ = true;
    contigsGraph[v2].isLongNode_ = true;
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph> joinExtendedSequences(contigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(contigsGraph), 3);
    BOOST_CHECK_EQUAL(num_edges(contigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 3);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv, v2);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_three_contigs_all_vertices_long)
{
    ContigsToScaffoldsExtension::ContigsGraph contigsGraph;
    ContigsToScaffoldsExtension::ContigsGraphVertex v0 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v1 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v2 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v3 = add_vertex(contigsGraph);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    vertexRepresentationSequence2.push_back(v3);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    contigsGraph[v0].isLongNode_ = true;
    contigsGraph[v1].isLongNode_ = true;
    contigsGraph[v2].isLongNode_ = true;
    contigsGraph[v3].isLongNode_ = true;
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph> joinExtendedSequences(contigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(contigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(contigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 4);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv, v3);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_three_contigs_all_vertices_long_another_order)
{
    ContigsToScaffoldsExtension::ContigsGraph contigsGraph;
    ContigsToScaffoldsExtension::ContigsGraphVertex v0 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v1 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v2 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v3 = add_vertex(contigsGraph);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    vertexRepresentationSequence2.push_back(v3);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    contigsGraph[v0].isLongNode_ = true;
    contigsGraph[v1].isLongNode_ = true;
    contigsGraph[v2].isLongNode_ = true;
    contigsGraph[v3].isLongNode_ = true;
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph> joinExtendedSequences(contigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(contigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(contigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 4);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv, v3);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_three_contigs_all_vertices_long_with_vertex_which_depicts_N_sign)
{
    ContigsToScaffoldsExtension::ContigsGraph contigsGraph;
    ContigsToScaffoldsExtension::ContigsGraphVertex v0 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v1 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v2 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v3 = add_vertex(contigsGraph);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    vertexRepresentationSequence2.push_back(std::numeric_limits<unsigned long>::max());    // N sign
    vertexRepresentationSequence2.push_back(std::numeric_limits<unsigned long>::max());    // N sign
    vertexRepresentationSequence2.push_back(std::numeric_limits<unsigned long>::max());    // N sign
    vertexRepresentationSequence2.push_back(v3);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    contigsGraph[v0].isLongNode_ = true;
    contigsGraph[v1].isLongNode_ = true;
    contigsGraph[v2].isLongNode_ = true;
    contigsGraph[v3].isLongNode_ = true;
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph> joinExtendedSequences(contigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(contigsGraph), 4);
    BOOST_CHECK_EQUAL(num_edges(contigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 7);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv++, std::numeric_limits<unsigned long>::max());    // N sign
    BOOST_CHECK_EQUAL(*iv++, std::numeric_limits<unsigned long>::max());    // N sign
    BOOST_CHECK_EQUAL(*iv++, std::numeric_limits<unsigned long>::max());    // N sign
    BOOST_CHECK_EQUAL(*iv, v3);
}

BOOST_AUTO_TEST_CASE(JoinExtendedSequences_more_contigs_all_vertices_long_another_order)
{
    ContigsToScaffoldsExtension::ContigsGraph contigsGraph;
    ContigsToScaffoldsExtension::ContigsGraphVertex v0 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v1 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v2 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v3 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v4 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v5 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v6 = add_vertex(contigsGraph);
    ContigsToScaffoldsExtension::ContigsGraphVertex v7 = add_vertex(contigsGraph);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence0;
    vertexRepresentationSequence0.push_back(v0);
    vertexRepresentationSequence0.push_back(v1);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence1;
    vertexRepresentationSequence1.push_back(v1);
    vertexRepresentationSequence1.push_back(v2);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence2;
    vertexRepresentationSequence2.push_back(v2);
    vertexRepresentationSequence2.push_back(v3);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence3;
    vertexRepresentationSequence3.push_back(v2);
    vertexRepresentationSequence3.push_back(v3);
    vertexRepresentationSequence3.push_back(v4);
    vertexRepresentationSequence3.push_back(v5);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence vertexRepresentationSequence4;
    vertexRepresentationSequence4.push_back(v5);
    vertexRepresentationSequence4.push_back(v6);
    vertexRepresentationSequence4.push_back(v7);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequences vertexRepresentationSequences;
    vertexRepresentationSequences.push_back(vertexRepresentationSequence0);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence1);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence2);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence3);
    vertexRepresentationSequences.push_back(vertexRepresentationSequence4);
    contigsGraph[v0].isLongNode_ = true;
    contigsGraph[v1].isLongNode_ = true;
    contigsGraph[v2].isLongNode_ = true;
    contigsGraph[v3].isLongNode_ = true;
    contigsGraph[v4].isLongNode_ = true;
    contigsGraph[v5].isLongNode_ = true;
    contigsGraph[v6].isLongNode_ = true;
    contigsGraph[v7].isLongNode_ = true;
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph> joinExtendedSequences(contigsGraph, vertexRepresentationSequences);
    joinExtendedSequences();
    BOOST_CHECK_EQUAL(num_vertices(contigsGraph), 8);
    BOOST_CHECK_EQUAL(num_edges(contigsGraph), 0);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences.size(), 1);
    BOOST_CHECK_EQUAL(vertexRepresentationSequences[0].size(), 8);
    JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::VertexRepresentationSequence::const_iterator iv = vertexRepresentationSequences[0].begin();
    BOOST_CHECK_EQUAL(*iv++, v0);
    BOOST_CHECK_EQUAL(*iv++, v1);
    BOOST_CHECK_EQUAL(*iv++, v2);
    BOOST_CHECK_EQUAL(*iv++, v3);
    BOOST_CHECK_EQUAL(*iv++, v4);
    BOOST_CHECK_EQUAL(*iv++, v5);
    BOOST_CHECK_EQUAL(*iv++, v6);
    BOOST_CHECK_EQUAL(*iv, v7);
}

BOOST_AUTO_TEST_SUITE_END()
