#ifndef __CUSTOMCOMMAND_H__
#define __CUSTOMCOMMAND_H__

#include <string>

#include <mt4cpp/Scheduler.hpp>
#include <mt4cpp/CommandHistory.hpp>

namespace dnaasm {
    /**
     * \brief Type of command.
     */
    enum class CALC_DLL(CommandType) { NONE, ASSEMBLY, ALIGN, SCAFFOLD, OLC, BST };

    class CustomCommand : public mt4cpp::Command {
    public:
        explicit CustomCommand(int taskId)
            :  commandType_(CommandType::NONE)
            , result_("")
            , taskId_(taskId)
            , isSavedInDatabase_(false)
        {}

        virtual ~CustomCommand() {}

        virtual std::string getResult() { return result_; }

        virtual int getTaskId() { return taskId_; }

        virtual bool getIsSavedInDatabase() { return isSavedInDatabase_; }

        virtual void setIsSavedInDatabase(bool isSavedInDatabase) {
            isSavedInDatabase_ = isSavedInDatabase;
        }

        virtual CommandType getCommandType() { return commandType_; }

    protected:
        CommandType commandType_;
        std::string result_;
        int taskId_;

    private:
        bool isSavedInDatabase_;
    };

} //namespace dnaasm

#endif //__CUSTOMCOMMAND_H__
