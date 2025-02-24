#include "Chainer.hpp"

namespace dnaasm {
namespace bst {

    Chainer::Chainer()
        :weight_(100)
    {}

    int Chainer::gapScore(S s0, S s1)
    {
        return abs(s1.x - s0.x - s1.y + s0.y);
    }

    std::vector<Chainer::S>& Chainer::genericChaining(std::vector<S> &s)
    {
        int best = 0;
        int score;
        std::vector<int> M, T;

        for(unsigned j=0; j < s.size(); j++)
        {
            M.push_back(0);
            T.push_back(-1);

            for(unsigned k=0; k < j; k++)
            {
                if(s[k] < s[j])
                {
                    score = M[k] + weight_ - gapScore(s[k], s[j]);
                    if(score > M[j])
                    {
                        M[j] = score;
                        T[j] = k;
                        if(score > M[best])
                        {
                            best = j;
                        }
                    }
                }
            }
        }
        result_.clear();

        int j = best;
        while(j != -1)
        {
            result_.push_back(s[j]);
            j = T[j];
        }

        return result_;
    }
}}
