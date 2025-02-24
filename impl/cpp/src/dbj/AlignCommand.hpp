#ifndef __ALIGNCOMMAND_H__
#define __ALIGNCOMMAND_H__

#include "../common/CustomCommand.hpp"
//#include "../common/Parameters.hpp"
#include "../dbj/assembly.hpp"
#include "../dbj/AlignParameters.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    class AlignCommand : public CustomCommand {
    public:
        AlignCommand(int taskId,
                     std::map<std::string, std::string>& params)
            : CustomCommand(taskId)
              , params_(params)
    {commandType_ = CommandType::ALIGN;}

        virtual ~AlignCommand() {}

        virtual void operator()(mt4cpp::Progress& progress) {
            boost::this_thread::sleep(boost::posix_time::millisec(500));    // to test break command
            AlignParameters parameters(params_);
            istringstream issSeq(parameters.getSequence());
            istringstream issRef(parameters.getReference());
            short int substitutionMatrixValues[16];
            vector<vector<short int>> subMatrix = parameters.getSubstitutionMatrix();
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    substitutionMatrixValues[i*4+j] = subMatrix[i][j];
                }
            }

            result_ = dbj::alignMode(issSeq,
                                     issRef,
                                     parameters.getIsHirschbergAlgorithm(),
                                     parameters.getCircular(),
                                     parameters.getGapPenalty(),
                                     substitutionMatrixValues, 
                                     &progress);
        }

    private:
        std::map<std::string, std::string> params_;
    };

}} //namespace dnaasm::dbj

#endif //__ALIGNCOMMAND_H__
