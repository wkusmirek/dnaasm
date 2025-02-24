#ifndef CHAINER_H_
#define CHAINER_H_

#include <vector>
#include <cmath>
#include <iostream>
#include "../common/common.hpp"
namespace dnaasm {
namespace bst {

// representation of k-mer
class Chainer
{
public:
    struct S {
        S(int x_, int y_)
            :x(x_), y(y_)
        {}

        friend bool operator < (const S& s0, const S& s1)
        {
            return s0.x < s1.x && s0.y < s1.y;
        }

        friend std::ostream& operator<<(std::ostream& os, const S& s)
        {
            return os << s.x << " " << s.y;
        }

        friend bool operator!=(const S &s0, const S &s1)
        {
            return s0.x != s1.x || s0.y != s1.y;
        }

        int x,y;
    };

    CALC_DLL(Chainer();)

    CALC_DLL(std::vector<S>& genericChaining(std::vector<S> &s);)
protected:
    CALC_DLL(int gapScore(S s0, S s1));

    unsigned weight_;
    std::vector<S> result_;
};

}}

#endif
