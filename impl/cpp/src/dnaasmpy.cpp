/**
 * \file assemblypy.cpp
 * \brief the Python interface for C++ calculation library
 */

#if defined(_MSC_VER)&& (_MSC_VER >= 1800)
//msvc13.0 warnings for boost.Python
#pragma warning(disable:4512)
#pragma warning(disable:4244)
#pragma warning(disable:4127)
#pragma warning(disable:4100)
#pragma warning(disable:4267)
#pragma warning(disable:4456)
#pragma warning(disable:4459)
#endif

#define BOOST_PYTHON_MAX_ARITY 31

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "dnaasm/CommandManager.hpp"
#include "common/log.hpp"

using namespace boost::python;

/** Python intreface to CommandManager
 */
class CommandManagerPy {
public:
    std::vector<long> getIds() {
        return dnaasm::dnaasm::CommandManager::getInstance().commandKeys();
    }

    long startAssembly(int taskId,
                       boost::python::dict params) {
        return dnaasm::dnaasm::CommandManager::getInstance().runAssemblyCommand(taskId,
                                                                                convertDictToMap(params));
    }

    long startAlign(int taskId,
                    boost::python::dict params) {
        return dnaasm::dnaasm::CommandManager::getInstance().runAlignCommand(taskId,
                                                                             convertDictToMap(params));
    }

    long startScaffold(int taskId,
                       boost::python::dict params) {
        return dnaasm::dnaasm::CommandManager::getInstance().runScaffoldCommand(taskId,
                                                                                convertDictToMap(params));
    }

    long startOlcAssembly(int taskId,
                       boost::python::dict params) {
        return dnaasm::dnaasm::CommandManager::getInstance().runOlcCommand(taskId,
                                                                           convertDictToMap(params));
    }

    long startBstAssembly(int taskId,
                       boost::python::dict params) {
        return dnaasm::dnaasm::CommandManager::getInstance().runBstCommand(taskId,
                                                                           convertDictToMap(params));
    }

    void breakCmd(long id) {
        return dnaasm::dnaasm::CommandManager::getInstance().breakCmd(id);
    }

    void clearHistory() {
        return dnaasm::dnaasm::CommandManager::getInstance().clearHistory();
    }

    mt4cpp::CommandDesc::State getState(long id) {
        return dnaasm::dnaasm::CommandManager::getInstance().findCommandDesc(id).state_;
    }

    double getProgress(long id) {
        return dnaasm::dnaasm::CommandManager::getInstance().findCommandDesc(id).progress_;
    }

    std::string getResult(long id) {
        return dnaasm::dnaasm::CommandManager::getInstance().getResult(id);
    }

    int getTaskId(long id) {
        return dnaasm::dnaasm::CommandManager::getInstance().getTaskId(id);
    }

    bool getIsSavedInDatabase(long id) {
        return dnaasm::dnaasm::CommandManager::getInstance().getIsSavedInDatabase(id);
    }

    void setIsSavedInDatabase(long id, bool isSavedInDatabase) {
        return dnaasm::dnaasm::CommandManager::getInstance().setIsSavedInDatabase(id, isSavedInDatabase);
    }

    dnaasm::CommandType getCommandType(long id) {
        return dnaasm::dnaasm::CommandManager::getInstance().getCommandType(id);
    }

private:

    std::map<std::string, std::string> convertDictToMap(boost::python::dict& paramsPy) {
        std::map<std::string, std::string> paramsCpp;
        boost::python::list keys = paramsPy.keys();
        for (int i = 0; i < len(keys); ++i) {
            boost::python::extract<std::string> extractedKey(keys[i]);
            if(!extractedKey.check()){
                std::cout<<"Key invalid, map might be incomplete"<<std::endl;
                continue;
            }
            std::string key = extractedKey;
            boost::python::extract<std::string> extractedVal(paramsPy[key]);
            if(!extractedVal.check()) {
                std::cout<<"Value invalid for key: " << key
                         << ", map might be incomplete" << std::endl;
                continue;
            }
            std::string value = extractedVal;
            std::cout << key << " " << value << endl;
            paramsCpp.insert(std::pair<std::string,std::string>(key,value));
        }
        return paramsCpp;
    }

};

/**
 * Python wrapper using Boost.Python
 */
BOOST_PYTHON_MODULE(dnaasmpy)
{

    dnaasm::initCalcModule();

    boost::python::enum_<mt4cpp::CommandDesc::State>("CommandState")
        .value("NONE",mt4cpp::CommandDesc::NONE)
        .value("QUEUED",mt4cpp::CommandDesc::QUEUED)
        .value("PENDING",mt4cpp::CommandDesc::PENDING)
        .value("INTERRUPTED",mt4cpp::CommandDesc::INTERRUPTED)
        .value("EXCEPTION",mt4cpp::CommandDesc::EXCEPTION)
        .value("DONE",mt4cpp::CommandDesc::DONE)
        .export_values()
        ;

    class_<std::vector<long> >("CommandKeys")
        .def(vector_indexing_suite<std::vector<long> >())
        ;

    boost::python::enum_<dnaasm::CommandType>("CommandType")
        .value("NONE_COMMAND_TYPE",dnaasm::CommandType::NONE)
        .value("ASSEMBLY_COMMAND_TYPE",dnaasm::CommandType::ASSEMBLY)
        .value("ALIGN_COMMAND_TYPE",dnaasm::CommandType::ALIGN)
        .value("SCAFFOLD_COMMAND_TYPE",dnaasm::CommandType::SCAFFOLD)
        .value("OLC_COMMAND_TYPE",dnaasm::CommandType::OLC)
        .value("BST_COMMAND_TYPE",dnaasm::CommandType::BST)
        .export_values()
        ;

    class_<CommandManagerPy>("CommandManager")
        .def("getIds", &CommandManagerPy::getIds)
        .def("clearHistory", &CommandManagerPy::clearHistory)
        .def("startAssembly", &CommandManagerPy::startAssembly)
        .def("startAlign", &CommandManagerPy::startAlign)
        .def("startScaffold", &CommandManagerPy::startScaffold)
        .def("startOlcAssembly", &CommandManagerPy::startOlcAssembly)
        .def("startBstAssembly", &CommandManagerPy::startBstAssembly)
        .def("breakCmd", &CommandManagerPy::breakCmd)
        .def("getState", &CommandManagerPy::getState)
        .def("getProgress", &CommandManagerPy::getProgress)
        .def("getResult", &CommandManagerPy::getResult)
        .def("getTaskId", &CommandManagerPy::getTaskId)
        .def("getIsSavedInDatabase", &CommandManagerPy::getIsSavedInDatabase)
        .def("setIsSavedInDatabase", &CommandManagerPy::setIsSavedInDatabase)
        .def("getCommandType", &CommandManagerPy::getCommandType)
        ;
}
