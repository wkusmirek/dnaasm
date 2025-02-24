#ifndef GRAPHBUILDER_HPP
#define GRAPHBUILDER_HPP

#include <memory>
#include <vector>
#include <numeric>
#include <climits>

#include "WordAssoc.hpp"
#include "OverlapGraph.hpp"
#include "Chainer.hpp"

namespace dnaasm { namespace bst {

using Layout = std::vector<std::pair<unsigned, unsigned>>;

class GraphBuilder
{
public:
    CALC_DLL(GraphBuilder();)

    CALC_DLL(void buildOverlapGraph(
                unsigned minimalAssociation,
                unsigned wordLength,
                unsigned readsCount,
                std::unique_ptr<std::vector<WordAssoc> []> associationTable);)
    CALC_DLL(void deleteAssociationTable();)
    CALC_DLL(void removeTransitiveEdges();)

    CALC_DLL(std::vector<Layout> getLayouts());

protected:
    using S = Chainer::S;

    CALC_DLL(void removeCycles());
    Layout longestPath(unsigned vertex, Layout l);
    void addEdgeToGraph(unsigned i, unsigned j, std::vector<S>& ov);

    unsigned wordLength_;
    unsigned minimalAssociation_;
    unsigned readsCount_;
    unsigned iterations_;
    unsigned maxFound_;
    bool enough_;

    std::unique_ptr<std::vector<WordAssoc> []> associationTable_;
    std::unique_ptr<Chainer> chainer_;
    std::unique_ptr<OverlapGraph> graph_;
};

}} //namespace dnaasm::bst

#endif  //GRAPHBUILDER_HPP
