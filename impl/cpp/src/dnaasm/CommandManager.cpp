/**
 * \file CommandManager.cpp
 * \brief the C++ file with implementation of classes for Commands
 */

#include "CommandManager.hpp"

using namespace std;

namespace dnaasm { namespace dnaasm {

    CommandManager::CommandManager()
        : scheduler_(16)
        , history_ ()
    {}

    CommandManager& CommandManager::getInstance()
    {
        static CommandManager instance;
        return instance;
    }

    mt4cpp::CommandID CommandManager::runAssemblyCommand(int taskId,
                                                         std::map<std::string, std::string> params)
    {
        mt4cpp::CommandID commandId
            = mt4cpp::executeAsynchronouslyAndRemember(scheduler_,
                    history_,
                    mt4cpp::PCommand(new dbj::AssemblyCommand(taskId,
                                                              params)));
        logInfo("start assembly command with id = " + std::to_string((long)commandId));
        return commandId;
    }

    mt4cpp::CommandID CommandManager::runAlignCommand(int taskId,
                                                      std::map<std::string, std::string> params) {
        mt4cpp::CommandID commandId
            = mt4cpp::executeAsynchronouslyAndRemember(scheduler_,
                    history_,
                    mt4cpp::PCommand(new dbj::AlignCommand(taskId,
                                                      params)));

        logInfo("start align command with id = " + std::to_string((long)commandId));
        return commandId;
    }

    mt4cpp::CommandID CommandManager::runScaffoldCommand(int taskId,
                                                         std::map<std::string, std::string> params)
    {
        mt4cpp::CommandID commandId
                = mt4cpp::executeAsynchronouslyAndRemember(scheduler_,
                       history_,
                       mt4cpp::PCommand(new scfr::ScaffoldCommand(taskId,
                                                                  params)));

        logInfo("start scaffold command with id = " + std::to_string((long)commandId));
        return commandId;
    }


    mt4cpp::CommandID CommandManager::runOlcCommand(int taskId,
                                                    std::map<std::string, std::string> params)
    {
        mt4cpp::CommandID commandId
            = mt4cpp::executeAsynchronouslyAndRemember(scheduler_,
                    history_,
                    mt4cpp::PCommand(new olc::OlcCommand(taskId,
                                                         params)));

        logInfo("start olc command with id = " + std::to_string((long)commandId));
        return commandId;
    }

    mt4cpp::CommandID CommandManager::runBstCommand(int taskId,
                                                    std::map<std::string, std::string> params)
    {
        mt4cpp::CommandID commandId
            = mt4cpp::executeAsynchronouslyAndRemember(scheduler_,
                    history_,
                    mt4cpp::PCommand(new bst::BstCommand(taskId,
                                                         params)));

        logInfo("start bst command with id = " + std::to_string((long)commandId));
        return commandId;
    }

    vector<mt4cpp::CommandID> CommandManager::commandKeys() const
    {
        return history_.keys();
    }

    mt4cpp::CommandDesc CommandManager::findCommandDesc(mt4cpp::CommandID id) const
    {
        //logInfo("find command description for command with id = " + std::to_string((long)id));
        return mt4cpp::findCommandDescriptor(history_, id);
    }

    void CommandManager::clearHistory()
    {
        logInfo("clear history");
        history_.clear();
    }

    void CommandManager::breakCmd(long id)
    {
        mt4cpp::PCommand cmd = history_.find(id);
        if (cmd.get() != 0L) {
            logInfo("break command with id = " + std::to_string(id));
            return cmd->halt();
        } else {
            logInfo("command with id = " + std::to_string(id)+ "does not exist");
            return;
        }
    }

    string CommandManager::getResult(mt4cpp::CommandID id)
    {
        //logInfo("get result for command with id = " + std::to_string((long)id));
        return boost::dynamic_pointer_cast<CustomCommand>(history_.find(id))->getResult();
    }

    int CommandManager::getTaskId(mt4cpp::CommandID id)
    {
        //logInfo("get task id for command with id = " + std::to_string((long)id));
        return boost::dynamic_pointer_cast<CustomCommand>(history_.find(id))->getTaskId();
    }

    bool CommandManager::getIsSavedInDatabase(mt4cpp::CommandID id)
    {
        //logInfo("get isSavedInDatabase for command with id = " + std::to_string((long)id));
        return boost::dynamic_pointer_cast<CustomCommand>(history_.find(id))->getIsSavedInDatabase();
    }

    void CommandManager::setIsSavedInDatabase(mt4cpp::CommandID id, bool isSavedInDatabase)
    {
        //logInfo("set isSavedInDatabase for command with id = " + std::to_string((long)id)+ " to " + std::to_string(isSavedInDatabase));
        return boost::dynamic_pointer_cast<CustomCommand>(history_.find(id))->setIsSavedInDatabase(isSavedInDatabase);
    }

    CommandType CommandManager::getCommandType(mt4cpp::CommandID id)
    {
        //logInfo("get command type for command with id = " + std::to_string((long)id));
        return boost::dynamic_pointer_cast<CustomCommand>(history_.find(id))->getCommandType();
    }

    void CommandManager::setCommandObserver(mt4cpp::CommandID id, mt4cpp::PCommandObserver observer) {
        boost::dynamic_pointer_cast<CustomCommand>(history_.find(id))->attach(observer);
    }

}} //namespace dnaasm::dnaasm
