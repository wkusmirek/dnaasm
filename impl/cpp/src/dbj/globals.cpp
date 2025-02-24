/**
 * \file globals.cpp
 * \brief the C++ file with implementation of some global things
 *
 */

#include "globals.hpp"

namespace dnaasm { namespace dbj {
    DeBruijnGraphVertexProperties::DeBruijnGraphVertexProperties() {}

    DeBruijnGraphEdgeProperties::DeBruijnGraphEdgeProperties(): counter_(1U) {}

    CompressedDeBruijnGraphVertexProperties::CompressedDeBruijnGraphVertexProperties() {}

    CompressedDeBruijnGraphEdgeProperties::CompressedDeBruijnGraphEdgeProperties(): counter_(1U), bridge_(false) {}
}}
