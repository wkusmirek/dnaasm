#include "Word.hpp"

namespace dnaasm {
namespace bst {

    Word::Word(short sequence, short index)
        :sequence_(sequence), index_(index)
    {}

    short Word::index() const
    {
        return index_;
    }

    short Word::sequence() const
    {
        return sequence_;
    }

}}
