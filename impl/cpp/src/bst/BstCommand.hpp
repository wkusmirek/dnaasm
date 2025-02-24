#ifndef BSTCOMMAND_H_
#define BSTCOMMAND_H_

#include <sstream>
#include "../common/CustomCommand.hpp"
#include "AssemblyManager.hpp"
#include "BstParameters.hpp"

using namespace std;

namespace dnaasm {
namespace bst {

        class BstCommand : public CustomCommand {
        public:
            BstCommand(int taskId, std::map<std::string, std::string>& params)
                :CustomCommand(taskId), params_(params)
            {
                commandType_ = CommandType::BST;
            }

            virtual ~BstCommand() {}

            virtual void operator()(mt4cpp::Progress& progress)
            {
                BstParameters parameters(params_);

                AssemblyManager am = AssemblyManager
                    (parameters.getInputFilePath(),           //filename
                     parameters.getWordLength(),                //W
                     parameters.getMinimalWordCount(),           //minimal word count
                     parameters.getMaximalWordCount(),           //maximal word count
                     parameters.getMinimalAssociation(),          //minimal association
                     parameters.getPathWidth());               //path width
                am.run();

                std::ifstream t("res");
                std::stringstream buffer;
                buffer << t.rdbuf();
                progress.setProgress(1.0);
                result_ = buffer.str();
            }

        private:
            std::map<std::string, std::string> params_;
        };

}
} //namespaces

#endif //BSTCOMMAND_H_
