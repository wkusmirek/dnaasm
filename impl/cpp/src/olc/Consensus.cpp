#include "Consensus.hpp"

namespace dnaasm {
    namespace olc {
        Consensus::Consensus(unsigned pathWidth)
                : ACGTN({'A', 'C', 'G', 'T', '-'}), bestSizeX_(0), bestSizeY_(0)
                , pathWidth_(pathWidth) {
            iter_ = consensus_.begin();
        }

        void Consensus::test() {
            std::string a = "ABC", b = "BCD";
        }

        std::string Consensus::toString() {
            std::string ret;
            unsigned j, best, base;
            int counter = 0;

            for (auto &node : consensus_) {
                best = node.B[bA];
                base = bA;
                for (j = bC; j < bMAX; j++) {
                    if (node.B[j] > best) {
                        best = node.B[j];
                        base = j;
                    }
                }

                if (base != bN) {
                    ret.push_back(ACGTN[base]);
                } else {
                    counter++;
                }
            }

            return ret;
        }

        void Consensus::run(Layout &layout, ReadVector &reads) {
            add(reads[layout[0]]);
            for (unsigned i = 1; i < layout.size(); ++i) {
                compare(reads[layout[i]]);
            }
        }

        void Consensus::add(std::string &str) {
            auto it = iter_;
            for (unsigned i = 0; i < str.size(); i++) {
                if (it == consensus_.end()) {
                    consensus_.emplace_back();
                    --it;
                }
                it++->inc(str[i]);
            }
        }

        void Consensus::print() {
            std::cout << "Print consensus!" << std::endl;
            for (auto it = consensus_.begin(); it != consensus_.end(); ++it) {
                for (unsigned i = 0; i < 5; i++)
                    std::cout << (int) it->B[i] << " ";
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        void Consensus::p(unsigned sizeY, unsigned sizeX) {
            std::cout << std::endl;
            for (unsigned i = 0; i <= sizeY; i++) {
                for (unsigned j = 0; j <= sizeX; j++) {
                    //if(tab_[i][j].F >= 0)
                    //    std::cout << " ";
                    //std::cout << tab_[i][j].F;
                    switch (tab_[i][j].dir) {
                        case UP:
                            std::cout << "U";
                            break;
                        case LEFT:
                            std::cout << "L";
                            break;
                        case CROSS:
                            std::cout << "C";
                            break;
                    }
                    std::cout << " ";
                }
                std::cout << std::endl;
            }
        }

        void Consensus::compare(std::string &str) {
            //sizeY - new string
            //sizeX - consensus
            unsigned sizeY = str.size();
            unsigned sizeX = 0;

            auto cIt = consensus_.end();
            while (sizeX < sizeY && cIt-- != consensus_.begin()) {
                sizeX++;
            }
            //std::cout << sizeX << " " << sizeY << std::endl;
            if (sizeY > bestSizeY_ || sizeX > bestSizeX_) {
                if (sizeY > bestSizeY_) {
                    tab_ = std::make_unique<std::unique_ptr<Field[]>[]>(sizeY + 1);
                    bestSizeY_ = sizeY;
                }

                for (unsigned i = 0; i <= sizeY; i++) {
                    tab_[i] = std::make_unique<Field[]>(sizeX + 1);
                }
                bestSizeX_ = sizeX;

                for (unsigned j = 0; j <= sizeX; j++) {
                    for (unsigned i = j + 1; i <= sizeY; i++) {
                        tab_[i][j].set(2 * j + i * -4.0f, UP);
                    }
                }
                for (unsigned i = 0; i <= sizeY; i++) {
                    for (unsigned j = i + 1; j <= sizeX; j++) {
                        tab_[i][j].set(2 * i + j * -4.0f, LEFT);
                    }
                }
            }
            //p(sizeY, sizeX);
            unsigned maxX = sizeX / pathWidth_;

            unsigned j, endX;
            for (unsigned i = 1; i <= sizeY; i++) {
                j = 1;
                if (i > maxX) {
                    j += i - maxX;
                    ++cIt;
                }

                endX = (i + maxX > sizeX ? sizeX : i + maxX - 1);
                auto it = cIt;
                for (; j <= endX; j++) {
                    float m = tab_[i - 1][j - 1].F + (*it++).score(str[i - 1]);
                    float d = tab_[i - 1][j].F - 1;
                    float in = tab_[i][j - 1].F - 1;
                    if (m > d) {
                        if (m >= in) {//m
                            tab_[i][j].set(m, CROSS);
                        } else {//in
                            tab_[i][j].set(in, LEFT);
                        }
                    } else if (in > d) {//in
                        tab_[i][j].set(in, LEFT);
                    } else {//d
                        tab_[i][j].set(d, UP);
                    }
                }
            }
            //p(sizeY, sizeX);
            align_.clear();
            auto it = consensus_.end();

            unsigned i = sizeY;
            j = sizeX;
            while (i > 0 || j > 0) {
                char dir = tab_[i][j].dir;
                if (dir == CROSS) {
                    //std::cout << "C";
                    align_.push_back(str[i - 1]);
                    --i;
                    --j;
                } else if (dir == UP) {
                    //std::cout << "U";
                    align_.push_back(str[i - 1]);
                    consensus_.insert(it, Bases('-'));
                    --i;
                } else {
                    //std::cout << "L";
                    align_.push_back('-');
                    --j;
                }
                --it;
            }
            //print();
            toAdd_.clear();
            for (int i = align_.size() - 1; i >= 0; i--) {
                toAdd_.push_back(align_[i]);
            }
            //std::cout << toAdd_ << std::endl;
            iter_ = it;
            add(toAdd_);
        }
    }
}
