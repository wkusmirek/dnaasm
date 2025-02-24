#ifndef WORD_H_
#define WORD_H_

#include <vector>
#include "../common/common.hpp"
namespace dnaasm {
namespace bst {

// representation of k-mer
class Word
{
public:
    CALC_DLL(Word(short sequence, short index);)

    CALC_DLL(short sequence() const);
    CALC_DLL(short index() const);

protected:
    short sequence_;
    short index_;
};

}}

#endif
