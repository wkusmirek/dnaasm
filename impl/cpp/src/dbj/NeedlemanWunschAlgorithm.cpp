/**
 * \file NeedlemanWunschAlgorithm.cpp
 * \brief the C++ file with implementation of class for Needleman-Wunsch algorithm (to align two xStrs)
 *
 */

#include "NeedlemanWunschAlgorithm.hpp"
#include "../common/log.hpp"
#include <limits>
#include <iostream>

using namespace std;

namespace dnaasm { namespace dbj {
    NeedlemanWunschAlgorithm::NeedlemanWunschAlgorithm(string& xStr,
                                                       string& yStr,
                                                       short int d,
                                                       short int (&substitutionMatrix)[4][4],
                                                       mt4cpp::Progress* progress,
                                                       unsigned int numOfAlignedSequences,
                                                       unsigned int numOfSequences)
        : xStr_(xStr)
        , yStr_(yStr)
        , d_(d)
        , substitutionMatrix_(substitutionMatrix)
        , xStrOut_("")
        , yStrOut_("")
        , progress_(progress)
        , numOfAlignedSequences_(numOfAlignedSequences)
        , numOfSequences_(numOfSequences)
    {}

    void NeedlemanWunschAlgorithm::align(bool withEndsPenalty) {
        unsigned int xStrLength = static_cast<unsigned int>(xStr_.length());
        unsigned int yStrLength = static_cast<unsigned int>(yStr_.length());

        int ** dynamicM = NULL;
        char ** tracebackM = NULL;

        try {
            // checking if there is enough memory space, because in 2d array bad_alloc exception is not thrown with linux default settings
            // http://www.cplusplus.com/forum/general/12215/
            dynamicM = new int * [ (yStrLength + 1)* (xStrLength + 1)];
            tracebackM = new char * [ (yStrLength + 1)* (xStrLength + 1)];
            delete[] dynamicM;
            delete[] tracebackM;

            // Dynamic programming matrix
            dynamicM = new int * [ yStrLength + 1 ];

            for (unsigned int i = 0U; i <= yStrLength; i++) {
                dynamicM[ i ] = new int [xStrLength + 1];
            }

            // Traceback matrix
            tracebackM = new char * [ yStrLength + 1 ];
            for (unsigned int i = 0U; i <= yStrLength; i++) {
                tracebackM[ i ] = new char [xStrLength + 1];
            }

        }
        catch (exception &e) {
            cerr << "exception caught: " << e.what() << '\n';
            logError("exception caught: " + string(e.what()));
            delete [] dynamicM;
            delete [] tracebackM;
            throw;
        }
        // Initialize tracebackM and dynamicM
        if (withEndsPenalty)
            matrixInit(dynamicM, tracebackM, d_);
        else
            matrixInit(dynamicM, tracebackM, 0);

        // Create alignment
        int x = 0, y = 0;
        int fU, fD, fL;
        char ptr, nuc;
        unsigned int i = 0U, j = 0U;
        for (i = 1U; i <= yStrLength; i++) {
            if (progress_ != NULL && numOfSequences_ != 0U)
                progress_->setProgress(static_cast<double>(numOfAlignedSequences_)
                        /static_cast<double>(numOfSequences_)
                        + static_cast<double>(i)
                        / static_cast<double>(yStrLength)
                        / static_cast<double>(numOfSequences_));

            for (j = 1U; j <= xStrLength; j++) {
                nuc = xStr_[ j-1 ];

                switch(nuc) {
                    case 'A': x = 0; break;
                    case 'C': x = 1; break;
                    case 'G': x = 2; break;
                    case 'T': x = 3;
                }

                nuc = yStr_[ i-1 ];

                switch(nuc) {
                    case 'A': y = 0; break;
                    case 'C': y = 1; break;
                    case 'G': y = 2; break;
                    case 'T': y = 3;
                }

                fU = dynamicM[ i-1 ][ j ] + d_;
                fD = dynamicM[ i-1 ][ j-1 ] + substitutionMatrix_[ x ][ y ];
                fL = dynamicM[ i ][ j-1 ] + d_;

                dynamicM[ i ][ j ] = max(fU, fD, fL, &ptr);
                tracebackM[ i ][ j ] = ptr;
            }
        }
        i--; j--;

        if (!withEndsPenalty) {
            unsigned int maxI = i;
            unsigned int maxJ = j;
            int maxValue = numeric_limits<int>::min();

            for (unsigned int k = 1U; k <= yStrLength; ++k) {

                if (dynamicM[k][xStrLength] > maxValue) {
                    maxValue = dynamicM[k][xStrLength];
                    maxI = k;
                    maxJ = xStrLength;
                }
            }

            for (unsigned int k = 1U; k <= xStrLength; ++k) {
                if (dynamicM[yStrLength][k] > maxValue) {
                    maxValue = dynamicM[yStrLength][k];
                    maxI = yStrLength;
                    maxJ = k;
                }
            }
            i = maxI;
            j = maxJ;
        }

        while (i > 0 || j > 0) {
            switch(tracebackM[ i ][ j ]) {
                case '|': {
                    xStrOut_ += '-';
                    yStrOut_ += yStr_[ i-1 ];
                    i--;
                    break;
                }
                case '\\': {
                    xStrOut_ += xStr_[ j-1 ];
                    yStrOut_ += yStr_[ i-1 ];
                    i--; j--;
                    break ;
                }
                case '-': {
                    xStrOut_ += xStr_[ j-1 ];
                    yStrOut_ += '-';
                    j--;
                }
            }
        }

        reverse(xStrOut_.begin(), xStrOut_.end());
        reverse(yStrOut_.begin(), yStrOut_.end());
        // Delete dynamicM and tracebackM
        for (unsigned int n = 0U; n <= yStr_.length(); n++) {
            delete dynamicM[ n ];
        }

        delete[] dynamicM;
        for (unsigned int n = 0U; n <= yStr_.length(); n++) {
            delete tracebackM[ n ];
        }

        delete[] tracebackM;

        return;
    }

    void NeedlemanWunschAlgorithm::matrixInit(int ** dynamicM, char ** tracebackM, short int endsPenalty) const {
        dynamicM[ 0 ][ 0 ] = 0;
        tracebackM[ 0 ][ 0 ] = 'n';

        for (unsigned int j = 1U; j <= xStr_.length(); j++) {
            dynamicM[ 0 ][ j ] = dynamicM[ 0 ][ j-1 ] + endsPenalty;
            tracebackM[ 0 ][ j ] = '-';
        }

        for (unsigned int i = 1U; i <= yStr_.length(); i++) {
            dynamicM[ i ][ 0 ] = dynamicM[ i-1 ][ 0 ] + endsPenalty;
            tracebackM[ i ][ 0 ] = '|';
        }
    }

    int NeedlemanWunschAlgorithm::max(int f1, int f2, int f3, char * sign) {
        int maxF = 0;

        if (f2 >= f1 && f2 >= f3) {
            maxF = f2;
            *sign = '\\';
        } else if (f1 >= f3) {
            maxF = f1;
            *sign = '|';
        } else {
            maxF = f3;
            *sign = '-';
        }

        return maxF;
    }

    string NeedlemanWunschAlgorithm::getXStrOut() const {
        return xStrOut_;
    }

    string NeedlemanWunschAlgorithm::getYStrOut() const {
        return yStrOut_;
    }
}}

