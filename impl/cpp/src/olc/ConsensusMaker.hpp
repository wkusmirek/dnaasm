#ifndef CONSENSUSMAKER_HPP
#define CONSENSUSMAKER_HPP

namespace dnaasm {
    namespace olc {

        template<typename ResultType, class ConsensusImplementation, class ...Args>
        class ConsensusMaker {
        public:
            virtual ResultType operator()(Args &...) = 0;

            virtual ~ConsensusMaker() = 0;
        };

        template<class ResultType, class ConsensusImplementation, class ...Args>
        ConsensusMaker<ResultType, ConsensusImplementation, Args...>::~ConsensusMaker() {}

    }
} //namespace dnaasm::olc
#endif /* CONSENSUSMAKER_HPP */
