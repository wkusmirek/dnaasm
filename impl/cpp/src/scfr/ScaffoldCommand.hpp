#ifndef __SCAFFOLDCOMMAND_H__
#define __SCAFFOLDCOMMAND_H__

#include "../common/CustomCommand.hpp"

#include "scaffold.hpp"
#include "ScaffoldParameters.hpp"

using namespace std;

namespace dnaasm { namespace scfr {

        class ScaffoldCommand : public CustomCommand {
        public:
            ScaffoldCommand(int taskId,
                            std::map<std::string, std::string>& params)
            : CustomCommand(taskId)
            , params_(params)

            {commandType_ = CommandType::SCAFFOLD;}

            virtual ~ScaffoldCommand() {}

            virtual void operator()(mt4cpp::Progress& progress) {
                boost::this_thread::sleep(boost::posix_time::millisec(500));    // to test break command

                ScaffoldParameters parameters(params_);
                result_ = scaffold(parameters.getContigsFilePath(),
                                   parameters.getReadsFilePath(),
                                   parameters.getKmerSize(),
                                   parameters.getDistance(),
                                   parameters.getStep(),
                                   parameters.getMinLinks(),
                                   parameters.getMinReads(),
                                   parameters.getMinLinksPerRead(),
                                   parameters.getMaxRatio(),
                                   parameters.getMinContigLength(),
                                   parameters.getGapFilling(),
                                   &progress);
            }

        private:
            std::map<std::string, std::string> params_;
        };

}} //namespace dnaasm::scfr

#endif //__SCAFFOLDCOMMAND_H__
