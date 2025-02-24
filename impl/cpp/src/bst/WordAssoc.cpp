#include "WordAssoc.hpp"

namespace dnaasm {
namespace bst {

    WordAssoc::WordAssoc(Word word, short selfIndex)
        :Word(word), selfIndex_(selfIndex)
    {}

    short WordAssoc::selfIndex() const
    {
        return selfIndex_;
    }
}}
