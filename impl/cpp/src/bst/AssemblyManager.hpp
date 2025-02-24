#ifndef ASSEMBLYMANAGER_HPP
#define ASSEMBLYMANAGER_HPP

#include <fstream>
#include <chrono>
#include "Blast.hpp"
#include "GraphBuilder.hpp"
#include "Consensus.hpp"

namespace dnaasm { namespace bst {

class AssemblyManager
{
public:
    CALC_DLL(AssemblyManager(std::string readsFilePath,
                    short wordLength,
                    short minimalWordCount,
                    short wordWeight,
                    short minimalAssociation,
                    short similarity);)

    CALC_DLL(void run();)

protected:
    void loadFastaReads();

    std::string readsPath_;
    unsigned wordLength_;
    unsigned wordWeight_;
    unsigned minimalAssociation_;
    unsigned similarity_;

    std::unique_ptr<Blast> blast_;
    std::unique_ptr<std::vector<WordAssoc> []> associationTable_;
    std::unique_ptr<GraphBuilder> graphBuilder_;
    std::vector<std::string> reads_;

private:
    std::chrono::system_clock::time_point start;
    int totalTime_;
    void tstart(std::string s);
    void tstop();
};

}} //namespace dnaasm::bst

#endif  //ASSEMBLYMANAGER_HPP
