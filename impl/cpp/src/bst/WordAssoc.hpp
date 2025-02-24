#ifndef WORDASSOC_H_
#define WORDASSOC_H_

#include "Word.hpp"

namespace dnaasm {
namespace bst {

class WordAssoc : public Word
{
public:
    CALC_DLL(WordAssoc(Word word, short selfIndex));

    CALC_DLL(short selfIndex() const;)

    friend bool operator < (const WordAssoc& w1, const WordAssoc& w2)
    {
        if(w1.sequence_ == w2.sequence_)
            return w1.selfIndex_ < w2.selfIndex_;
        else
            return w1.sequence_ < w2.sequence_;
    }
protected:
    short selfIndex_;
};

}}

#endif
