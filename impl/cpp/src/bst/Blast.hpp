#ifndef BLAST_H_
#define BLAST_H_

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <utility>
#include <cmath>
#include <algorithm>
#include <numeric>

#include "../common/common.hpp"
#include "WordAssoc.hpp"
#include "Association.hpp"

namespace dnaasm {
namespace bst {


class Blast
{
    const char hashmap[5] = {3, 2, 0, -1, 1};

public:
    CALC_DLL(Blast(short wordLength = 12,
                   short minimalWordCount = 6,
                   short maximalWordCount = 40);)

    CALC_DLL(void findWords(std::vector<std::string>& reads);)
    CALC_DLL(void removeInfrequentMatches();)
    CALC_DLL(void createAssociationTable();)
    CALC_DLL(void deleteWordsMap();)
    CALC_DLL(std::unique_ptr<std::vector<WordAssoc> []> sortAssociationTable();)

    CALC_DLL(void debug();)

protected:
    CALC_DLL(int hash(std::string str));

    std::unique_ptr<std::vector<Word> []> wordsMap_;
    std::unique_ptr<std::vector<WordAssoc> []> associationTable_;

    unsigned wordLength_;
    unsigned minimalWordCount_;
    unsigned maximalWordCount_;
    unsigned wordsMapSize_;
    unsigned readsCount_;
};

}
}

#endif
