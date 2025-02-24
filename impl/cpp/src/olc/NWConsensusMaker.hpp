#ifndef NWCONSENSUSMAKER_HPP
#define NWCONSENSUSMAKER_HPP

#include "common.hpp"
#include "ConsensusMaker.hpp"
#include "Consensus.hpp"

namespace dnaasm {
    namespace olc {
        using Contig = std::string;
        using NWConsensusMakerInterface = ConsensusMaker<std::vector<Contig>,
                Consensus,
                LayoutVec,
                ReadVector>;

        class NWConsensusMaker : public NWConsensusMakerInterface {
        public:
            NWConsensusMaker(unsigned short int pathWidth) : pathWidth_(pathWidth) {}

            ~NWConsensusMaker() override;

            std::vector<Contig>
            operator()(LayoutVec &layVec, ReadVector &readVector) override;

            void convertContigsToFasta(const std::vector<Contig> &, std::stringstream &) const;

        private:
            unsigned short int pathWidth_;
        };
    }
} //namespace dnaasm::olc
#endif //NWCONSENSUSMAKER_HPP
