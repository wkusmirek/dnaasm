#include "NWConsensusMaker.hpp"
#include <sstream>
#include <string>

namespace dnaasm {
    namespace olc {
        NWConsensusMaker::~NWConsensusMaker() {}

        std::vector<Contig>
        NWConsensusMaker::operator()(LayoutVec &layoutVec, ReadVector &readVector) {
            std::vector<Contig> result;

            for (auto &layout : layoutVec) {
                Consensus c(pathWidth_);
                c.run(layout, readVector);
                result.emplace_back(c.toString());
                layout.clear();
            }

            return result;
        }

            void NWConsensusMaker::convertContigsToFasta(const std::vector<Contig> &contigVector,
                                                         std::stringstream &fastaResult) const {
                for (uint32_t i = 0; i < contigVector.size(); ++i) {
                    fastaResult << std::string(">contig ") + std::to_string(i + 1) << '\n'
                                << contigVector[i] << '\n';
                }
            }
        }
    } //namespace dnaasm::olc