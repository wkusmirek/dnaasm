#ifndef OLCCOMMAND_HPP
#define OLCCOMMAND_HPP

#include "../common/CustomCommand.hpp"

#include "OlcParameters.hpp"
#include "OlcAssembly.hpp"

using namespace std;

namespace dnaasm {
    namespace olc {
        class OlcCommand : public CustomCommand {
        public:
            OlcCommand(int taskId,
                       std::map<std::string, std::string> &params)
                    : CustomCommand(taskId), params_(params) { commandType_ = CommandType::OLC; }

            virtual ~OlcCommand() {}

            virtual void operator()(mt4cpp::Progress &progress) {
                boost::this_thread::sleep(
                        boost::posix_time::millisec(500));    // to test break command

                OlcParameters parameters(params_);
                ifstream inputFile(parameters.getReadsFilePath());
                result_ = olcAssembly(inputFile,
                                      parameters.getKmerLength(),
                                      parameters.getSketchNum(),
                                      parameters.getMinJaccardSim(),
                                      parameters.getMatchScore(),
                                      parameters.getMismatchScore(),
                                      parameters.getGapPenalty(),
                                      parameters.getMinEdge(),
                                      parameters.getMinContigLength(),
                                      parameters.getPathWidth(),
                                      &progress);
            }

        private:
            std::map<std::string, std::string> params_;
        };

    }
} //namespace dnaasm::olc

#endif //OLCCOMMAND_HPP
