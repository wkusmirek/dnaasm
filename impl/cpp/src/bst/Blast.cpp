#include "Blast.hpp"

namespace dnaasm { namespace bst {
    Blast::Blast(short wordLength, short minimalWordCount, short maximalWordCount)
        : wordLength_(wordLength),
          minimalWordCount_(minimalWordCount),
          maximalWordCount_(maximalWordCount)
    {}

    int Blast::hash(std::string str)
    {
    	unsigned ret = 0, multip = 1;
    	for(int i = str.size() - 1; i >= 0; i--)
    	{
            char a = str[i];
            ret += multip * (a <= 'C' ? (a == 'A' ? 0 : 1) : (a == 'G' ? 2 : 3));
    		multip <<= 0x02;
    	}
    	return ret;
    }

    void Blast::findWords(std::vector<std::string>& reads)
    {
        readsCount_ = reads.size();
        wordsMapSize_ = std::pow(4, wordLength_);
        wordsMap_ = std::make_unique<std::vector<Word> []>(wordsMapSize_);

        for(unsigned it = 0; it < readsCount_; it++)
        {
            for(unsigned i = 0; i <= reads[it].length() - wordLength_; ++i)
            {
                wordsMap_[hash(reads[it].substr(i, wordLength_))].emplace_back(it, i);
            }

            if(it % 1000 == 0)
            {
                std::cout << "Reads scanned: " << it << std::endl;
            }
        }
    }

    void Blast::createAssociationTable()
    {
        associationTable_ = std::make_unique<std::vector<WordAssoc> []>(readsCount_);
        std::cout << "Words map size: " << wordsMapSize_ << std::endl;
        for(unsigned i = 0; i < wordsMapSize_; i++)
        {
            std::vector<Word> &v = wordsMap_[i];
            for(unsigned it0 = 1; it0 < v.size(); it0++)
            {
                for(unsigned it1 = 0; it1 < it0; it1++)
                {
                    Word &w0 = v[it0];
                    Word &w1 = v[it1];

                    if(w0.sequence() == w1.sequence())
                    {
                        continue;
                    }

                    associationTable_[w0.sequence()].emplace_back(w1, w0.index());
                    associationTable_[w1.sequence()].emplace_back(w0, w1.index());
                }
            }

            std::vector<Word>().swap(v);

            if(i % 1000000 == 0)
            {
                std::cout << "i: " << i << std::endl;
            }
        }
    }

    void Blast::removeInfrequentMatches()
    {
        for(unsigned it = 0; it < wordsMapSize_; it++)
        {
            if(wordsMap_[it].size() < minimalWordCount_)
            {
                std::vector<Word>().swap(wordsMap_[it]);
            }
            if(wordsMap_[it].size() > maximalWordCount_)
            {
                std::vector<Word>().swap(wordsMap_[it]);
            }
        }
    }

    void Blast::deleteWordsMap()
    {
        wordsMap_.reset(nullptr);
    }

    std::unique_ptr<std::vector<WordAssoc> []> Blast::sortAssociationTable()
    {
        for(unsigned i = 0; i < readsCount_; i++)
        {
            std::sort(associationTable_[i].begin(), associationTable_[i].end());
            if(i % 1000 == 0)
            {
                std::cout << "Sorting: " << i << std::endl;
            }
        }

        return std::move(associationTable_);
    }

    void Blast::debug()
    {
        int max = 0;
        int table[10000] = {0};
        int expectedMemory = 0;
        for(unsigned it = 0; it < wordsMapSize_; it++)
        {
            int size = wordsMap_[it].size();
            if(size > max)
            {
                max = size;
            }

            table[size]++;
        }

        double dystr = 0;
        for(int i=0; i<max; i++)
        {
            expectedMemory += table[i] * i * (i-1) / 2;
        }
        int maxExpectedMemory = expectedMemory;
        for(int i=0; i<max; i++)
        {
            expectedMemory -= table[i] * i * (i-1) / 2;
            double proc = (double)table[i] / double(std::pow(4, wordLength_)) * 100;
            double memoryProc = (double) expectedMemory / maxExpectedMemory * 100;
            dystr += proc;
            //i = długość wektora, table[i] = ilość wystąpień wektora
            std::cout << i << ":\t" << table[i] << "\t";
            //expectedMemory = zużyta pamięć do reprezentacji dłuższych od i
            std::cout << expectedMemory/1000 << "KB\t";
            //memoryProc = procent pamięci użyty do reprezenw porównaniu do całej pamięci
            std::cout << memoryProc << "%" << std::endl;
        }
    }

}}
