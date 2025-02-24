/**
 * \file JoinExtendedSequences.hpp
 * \brief the C++ file with implementation of template class for joining extended sequences in vertex representation
 */


#ifndef JOIN_EXTENDED_SEQUENCES_HPP
#define JOIN_EXTENDED_SEQUENCES_HPP

#include <iostream>
#include "../common/log.hpp"
#include "ContigsToScaffoldsExtension.hpp"

namespace dnaasm { namespace dbj {

    template<class Vertex>
    std::vector<Vertex>& operator+=(std::vector<Vertex>& con1, const std::vector<Vertex>& con2) {
        if (con1.size() == 0) {
            con1.insert(con1.end(), con2.begin(), con2.end());
        } else {
            con1.insert(con1.end(), con2.begin()+1, con2.end());
        }

        return con1;
    }

    /**
     * \brief Class to join extended sequences in vertex representation
    */
    template<class Graph> class JoinExtendedSequences {
    public:
        typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
        typedef typename boost::graph_traits<Graph>::edge_descriptor Edge;
        typedef std::vector<Vertex> VertexRepresentationSequence;
        typedef std::vector<VertexRepresentationSequence> VertexRepresentationSequences;

        /**
         * \brief AllPathsFinder constructor.
         *
         * \param g reference to Graph object
         */
        JoinExtendedSequences(Graph& g, VertexRepresentationSequences& vertexRepresentationSequences)
            : g_(g)
            , vertexRepresentationSequences_(vertexRepresentationSequences)
            , numOfOccurrence_(num_vertices(g_), 0U)
            , canBeExtended_(num_vertices(g_), true)
        {countNumOfOccurrence();}

        /**
         * \brief Joins all extended sequences in vertex representation, if start and end vertex are the same vertex and this vertex is original.
         *
         * \return returns void
         */
        void operator()() {
            logInfo("Joining extended sequences in vertex representation...");
            logInfo("Num of sequences in vertex representations before joining: " + std::to_string(vertexRepresentationSequences_.size()));
            removeVertexRepresentationSequencesContainedInAnotherVertexRepresentationSequence();
            unsigned int sumOfJoinsIterations = 0U;

            while (joinVertexRepresentationSequences() != 0U) {
                ++sumOfJoinsIterations;

                if (sumOfJoinsIterations == 10U) {
                    break;
                }
            }

            removeVertexRepresentationSequencesContainedInAnotherVertexRepresentationSequence();
            logInfo("Num of sequences in vertex representations after joining: " + std::to_string(vertexRepresentationSequences_.size()));
        }

    private:
        JoinExtendedSequences& operator=(const JoinExtendedSequences&)= delete;
        Graph& g_;
        VertexRepresentationSequences& vertexRepresentationSequences_;
        std::vector<unsigned short> numOfOccurrence_;
        std::vector<bool> canBeExtended_;

        template <typename T1, typename T2>
        static bool contains(std::vector<T1> const& a, std::vector<T2> const& b) {

            for (typename std::vector<T1>::const_iterator i = a.begin(), y = a.end(); i != y; ++i) {
                bool match = true;
                typename std::vector<T1>::const_iterator ii = i;

                for (typename std::vector<T2>::const_iterator j = b.begin(), z = b.end(); j != z; ++j) {
                    if (ii == a.end()|| *j != *ii) {
                        match = false;
                        break;
                    }
                    ii++;
                }

                if (match)
                    return true;
            }
            return false;
        }

        void countNumOfOccurrence() {
            for (typename VertexRepresentationSequences::iterator it = vertexRepresentationSequences_.begin(); it != vertexRepresentationSequences_.end(); ++it) {
                for (typename VertexRepresentationSequence::iterator it2 = it->begin(); it2 != it->end(); ++it2) {

                    if (*it2 == std::numeric_limits<unsigned long>::max()) {
                        continue;
                    }
                    ++numOfOccurrence_[*it2];
                }
            }
        }

        void removeVertexRepresentationSequencesContainedInAnotherVertexRepresentationSequence() {
            VertexRepresentationSequences tmpVertexRepresentationSequences;
            std::vector<bool> isContainedInAnother(vertexRepresentationSequences_.size(), false);

            for (typename VertexRepresentationSequences::iterator it = vertexRepresentationSequences_.begin(); it != vertexRepresentationSequences_.end(); ++it) {
                if (isContainedInAnother[it - vertexRepresentationSequences_.begin()])
                    continue;

                for (typename VertexRepresentationSequences::iterator it2 = vertexRepresentationSequences_.begin(); it2 != vertexRepresentationSequences_.end(); ++it2) {
                    if (it == it2)
                        continue;

                    if (contains(*it, *it2))
                        isContainedInAnother[it2 - vertexRepresentationSequences_.begin()] = true;
                }
            }
            for (typename VertexRepresentationSequences::iterator it = vertexRepresentationSequences_.begin(); it != vertexRepresentationSequences_.end(); ++it) {
                if (isContainedInAnother[it - vertexRepresentationSequences_.begin()])
                    continue;

                tmpVertexRepresentationSequences.push_back(*it);
            }
            vertexRepresentationSequences_ = tmpVertexRepresentationSequences;
        }

        unsigned int joinVertexRepresentationSequences() {
            unsigned int sumOfJoins = 0U;

            for (typename VertexRepresentationSequences::iterator it = vertexRepresentationSequences_.begin(); it != vertexRepresentationSequences_.end(); ++it) {
                if(canBeExtended_[it - vertexRepresentationSequences_.begin()]) {
                    unsigned int numOfJoinsForVertexRepresentationSequence = 0U;

                    for (typename VertexRepresentationSequences::iterator it2 = vertexRepresentationSequences_.begin(); it2 != vertexRepresentationSequences_.end(); ++it2) {
                        if (it == it2 || it -> size() == 0 || it2 -> size() == 0)
                            continue;

                        if (it -> back() == it2 -> front() && g_[it -> back()].isOriginal_) {
                            *it += *it2;
                            ++numOfJoinsForVertexRepresentationSequence;
                            ++sumOfJoins;
                        }
                    }

                    if(numOfJoinsForVertexRepresentationSequence == 0U) {
                        canBeExtended_[it - vertexRepresentationSequences_.begin()] = false;
                    }
                }
            }
            logInfo("Sum of joins for actual iteration: " + std::to_string(sumOfJoins));
            return sumOfJoins;
        }
    };

    template<>
    CALC_DLL(unsigned int JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::joinVertexRepresentationSequences();)

}}

#endif    //JOIN_EXTENDED_SEQUENCES_HPP
