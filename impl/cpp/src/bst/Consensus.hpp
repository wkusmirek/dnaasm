#ifndef CONSENSUS_HPP
#define CONSENSUS_HPP

#include <memory>
#include <vector>
#include <iostream>
#include <list>
#include "Map.hpp"
#include "../common/common.hpp"

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
/*
 * string operators are defined in 'string' header
 */
    #include <string>
#endif

namespace dnaasm { namespace bst {

class Consensus
{
    struct Bases {
        Bases() {}
        Bases(char c)
        {
            inc(c);
        }

        unsigned char B[5] = {0};
        unsigned char sum = 0;

        //char of best base
        void inc(char c)
        {
            ++B[baseMap[(short)c]];
            ++sum;
        }

        float score(char c)
        {
            return (float)(2 * B[baseMap[(short)c]] - sum) / sum;
        }
    };

    struct Field {
        void set(float f, char d)
        {
            F = f;
            dir = d;
        }

        float F = 0.0f;
        char dir;
    };

public:
    CALC_DLL(Consensus(unsigned p));
    void setAssociations(std::unique_ptr<std::vector<unsigned>> associations);
    CALC_DLL(void run(std::vector<std::string>& reads));
    CALC_DLL(std::unique_ptr<std::string> toString());
    void test();

protected:
    const char ACGTN[5] = {'A', 'C', 'G', 'T', '-'};
    enum {bA, bC, bG, bT, bN, bMAX};
    enum {UP, LEFT, CROSS};

    void print();
    void f(std::string str) { std::cout << str << std::endl; }
    void p(unsigned sizeY, unsigned sizeX);
    CALC_DLL(void compare(std::string& str));
    CALC_DLL(void add(std::string& str));

    std::list<Bases>::iterator iter_;
    std::list<Bases> consensus_;
    std::unique_ptr<std::unique_ptr<Field []>[] > tab_;
    std::unique_ptr<std::vector<unsigned>> associations_;
    unsigned bestSizeX_, bestSizeY_, pathWidth_;
    std::vector<char> align_;
    std::string toAdd_;
};

}} //namespace dnaasm::bst

#endif  //CONSENSUS_HPP
