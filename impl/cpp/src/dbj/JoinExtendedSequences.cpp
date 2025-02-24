/**
 * \file JoinExtendedSequences.cpp
 * \brief the C++ file with implementation of specialized template class for joining extended sequences in vertex representation
 *
 */

#include "JoinExtendedSequences.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    template<>
    unsigned int JoinExtendedSequences<ContigsToScaffoldsExtension::ContigsGraph>::joinVertexRepresentationSequences() {
        unsigned int sumOfJoins = 0U;

        for (typename VertexRepresentationSequences::iterator it = vertexRepresentationSequences_.begin(); it != vertexRepresentationSequences_.end(); ++it) {
            if(canBeExtended_[it - vertexRepresentationSequences_.begin()]) {
                unsigned int numOfJoinsForVertexRepresentationSequence = 0U;

                for (typename VertexRepresentationSequences::iterator it2 = vertexRepresentationSequences_.begin(); it2 != vertexRepresentationSequences_.end(); ++it2) {
                    if (it == it2 || it -> size() == 0 || it2 -> size() == 0)
                        continue;

                    if (it -> back() == it2 -> front() && g_[it -> back()].isLongNode_) {
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
}}
