/**
 * \file CommandManager.hpp
 * \brief the C++ file with declaration of class for Commands
 */

#ifndef COMMANDMANAGER_HPP
#define COMMANDMANAGER_HPP

#include <fstream>

#include <boost/lexical_cast.hpp>
#include <mt4cpp/Command.hpp>
#include <mt4cpp/OstreamCommandObserver.hpp>

#include "../common/log.hpp"

#include "../dbj/AlignCommand.hpp"
#include "../dbj/AssemblyCommand.hpp"
#include "../scfr/ScaffoldCommand.hpp"
#include "../olc/OlcCommand.hpp"
#include "../bst/BstCommand.hpp"

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
//msvc disable warnings for sheduler_ and history_ member
#pragma warning(disable:4251)
#endif

namespace dnaasm { namespace dnaasm {

    /**
    singleton, active object design pattern
    */
    class CALC_DLL(CommandManager) {
    public:
        static CommandManager& getInstance();

        /** execute assembling command */
        mt4cpp::CommandID runAssemblyCommand(int taskId,
                                             std::map<std::string, std::string> params);

        /** execute align command */
        mt4cpp::CommandID runAlignCommand(int taskId,
                                          std::map<std::string, std::string> params);

        /** execute scaffolding command */
        mt4cpp::CommandID runScaffoldCommand(int taskId,
                                             std::map<std::string, std::string> params);

        /** execute OLC assembly command */
        mt4cpp::CommandID runOlcCommand(int taskId,
                                        std::map<std::string, std::string> params);

        /** execute BST assembly command */
        mt4cpp::CommandID runBstCommand(int taskId,
                                        std::map<std::string, std::string> params);

        /** keys for stored commands */
        std::vector<mt4cpp::CommandID> commandKeys() const;

        /** description for command with given id */
        mt4cpp::CommandDesc findCommandDesc(mt4cpp::CommandID id) const;

        void clearHistory();

        void breakCmd(long id);

        std::string getResult(mt4cpp::CommandID id);

        int getTaskId(mt4cpp::CommandID id);

        bool getIsSavedInDatabase(mt4cpp::CommandID id);

        void setIsSavedInDatabase(mt4cpp::CommandID id, bool isSavedInDatabase);

        CommandType getCommandType(mt4cpp::CommandID id);

        void setCommandObserver(mt4cpp::CommandID id, mt4cpp::PCommandObserver observer);

    private:
        CommandManager();

        mt4cpp::Scheduler scheduler_;
        mt4cpp::CommandHistory history_;

        CommandManager(const CommandManager&)= delete;
        CommandManager operator=(const CommandManager&)= delete;
    };

}} //namespace dnaasm::dnaasm
#endif     //COMMANDMANAGER_HPP
