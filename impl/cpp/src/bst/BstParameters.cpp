/**
 * \file BstParameters.cpp
 * \brief the C++ file with implementation of class for representing bst parameters
 *
 */

#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include "BstParameters.hpp"

using namespace std;
using namespace boost;

namespace dnaasm {
namespace bst {

    BstParameters::BstParameters(map<string, string>& parameters)
        : Parameters(parameters)
    {
        initParameters(); parametersService(parameters);
    }

    void BstParameters::initParameters()
    {
        wordLength_ = 12U;
        minimalWordCount_ = 1U;
        maximalWordCount_ = 100U;
        minimalAssociation_ = 1U;
        pathWidth_ = 1U;
        Parameters::initParameters();
    }

    void BstParameters::printHelpForModule() {
        cout << "BST HELP MSG" << endl;
    }

    bool BstParameters::isParameterEqual(string param, string str)
    {
        return param == str || param == ("-" + str);
    }

    string BstParameters::getInputFilePath() const
    {
        return inputFilePath_;
    }

    unsigned BstParameters::getWordLength() const
    {
        return wordLength_;
    }

    unsigned BstParameters::getMinimalWordCount() const
    {
        return minimalWordCount_;
    }

    unsigned BstParameters::getMaximalWordCount() const
    {
        return maximalWordCount_;
    }

    unsigned BstParameters::getMinimalAssociation() const
    {
        return minimalAssociation_;
    }

    unsigned BstParameters::getPathWidth() const
    {
        return pathWidth_;
    }

    void BstParameters::parametersService(map<string, string>& parameters)
    {
        if (parameters.size() == 0)
        {
            printHelpForModule();
            initParameters();
            return;
        }
        for (const auto &parameter : parameters)
        {
            if (parameter.first == "./dnaasm" || parameter.first == "dnaasm.exe")
            {
                continue;
            }

            if (isParameterEqual(parameter.first, "bst"))
            {
                mode_ = "-bst";
                continue;
            }

            try
            {
                if (isParameterEqual(parameter.first, "output_file_name"))
                {
                    output_file_name_ = string(parameter.second);
                    continue;
                }
                else if (isParameterEqual(parameter.first, "word_length"))
                {
                    wordLength_ = lexical_cast<unsigned>(parameter.second);
                    if (wordLength_ < 2)
                    {
                        cout << "Word length size is too small, have to be greater than 1" << endl;
                        initParameters();
                        return;
                    }
                    continue;
                }
                else if (isParameterEqual(parameter.first, "min_word_count"))
                {
                    minimalWordCount_ = lexical_cast<unsigned>(parameter.second);
                    if (minimalWordCount_ < 1)
                    {
                        cout << "Minimum word count is too small, have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    continue;
                }
                else if (isParameterEqual(parameter.first, "max_word_count"))
                {
                    maximalWordCount_ = lexical_cast<unsigned>(parameter.second);
                    if (maximalWordCount_ < 1)
                    {
                        cout << "Maximum word count is too small, have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    continue;
                }
                else if (isParameterEqual(parameter.first, "min_association"))
                {
                    minimalAssociation_ = lexical_cast<unsigned>(parameter.second);
                    if (minimalAssociation_ < 1)
                    {
                        cout << "Minimal association is too small, have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    continue;
                }
                else if (isParameterEqual(parameter.first, "path_width"))
                {
                    pathWidth_ = lexical_cast<unsigned>(parameter.second);
                    if (pathWidth_ < 1)
                    {
                        cout << "Path width is to small, have to be greater than 0" << endl;
                        initParameters();
                        return;
                    }
                    continue;
                }
            } catch(bad_lexical_cast&) { }

            if (isParameterEqual(parameter.first, "input_file_path"))
            {
                inputFilePath_ = parameter.second;
                ifstream fileCheck(parameter.second.c_str());
                if (!fileCheck) //check if file exists
                {
                    cout << parameter.second << ": no such file" << endl;
                    initParameters();
                    return;
                }
                fileCheck.close();
                continue;
            }
        }

        if (inputFilePath_ == "")
        {
            cout << "-input_file_path parameter is obligatory!" << endl;
            initParameters();
        }
    }

}
} //namespace dnaasm::bst
