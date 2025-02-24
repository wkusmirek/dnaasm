#include <iostream>
#include <stdlib.h>
#include <chrono>

#include "AssemblyManager.hpp"
#include "Consensus.hpp"

using namespace dnaasm::bst;
using namespace std;

int main(int argv, char * argc[]) {
    string path = "../sandbox/winiarski/generator/results/";
    string file = path + "out200E10";
    unique_ptr<AssemblyManager> am;
    if(argv == 7)
    {
        am = make_unique<AssemblyManager>
            (argc[1],           //filename
             atoi(argc[2]),     //W
             atoi(argc[3]),     //minimal word count
             atoi(argc[4]),     //maximal word count
             atoi(argc[5]),     //minimal association
             atoi(argc[6]));    //path width
        am->run();
    }
    else if(argv == 6)
    {
        am = make_unique<AssemblyManager>
            (argc[1],           //filename
             atoi(argc[2]),     //W
             atoi(argc[3]),     //minimal word count
             10000,
             atoi(argc[4]),     //minimal association
             atoi(argc[5]));    //path width
        am->run();
    } else {
        cout << "Wrong arg count! Should be 6 instead of " << argv - 1;
    }

    return 1;
}
