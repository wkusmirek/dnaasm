#ifndef __ASSEMBLYCOMMAND_H__
#define __ASSEMBLYCOMMAND_H__

#include <boost/filesystem.hpp>

#include "../common/common.hpp"
#include "../common/CustomCommand.hpp"
//#include "../common/Parameters.hpp"
#include "../dbj/assembly.hpp"
#include "../dbj/AssemblyParameters.hpp"

using namespace std;

namespace dnaasm { namespace dbj {
    class AssemblyCommand : public CustomCommand {
    public:
        AssemblyCommand(int taskId,
                        std::map<std::string, std::string>& params)
            : CustomCommand(taskId)
            , params_(params)
        { commandType_ = CommandType::ASSEMBLY; }

        virtual ~AssemblyCommand() {}

        virtual void operator()(mt4cpp::Progress& progress) {
            boost::this_thread::sleep(boost::posix_time::millisec(500));    // to test break command
            ifstream bfcFile(""); //istringstream bfcFile;            // reading output file form BFCounter program not supported (yet) for web interface
            AssemblyParameters parameters(params_);

            // create tmp dir required by some objects from dbj module
            if (!boost::filesystem::exists(CALC_TMP_DIR)) {
                boost::filesystem::create_directory(CALC_TMP_DIR);
            }

            if (parameters.getI1_1()[0] != '>' && parameters.getI1_1()[0] != '@') {
                ifstream i1_1(parameters.getI1_1());
                ifstream i1_2(parameters.getI1_2());
                ifstream o1_1(parameters.getO1_1());
                ifstream o1_2(parameters.getO1_2());
                ifstream bfcFile(parameters.getBfcFile());
                result_ = dbj::assemblyMode(parameters.getK() - 1,
                                            parameters.getGenomeLength(),
                                            parameters.getInsertSizeMeanInward(),
                                            parameters.getInsertSizeStdDevInward(),
                                            parameters.getInsertSizeMeanOutward(),
                                            parameters.getInsertSizeStdDevOutward(),
                                            parameters.getQualityThreshold(),
                                            parameters.getBfcounterThreshold(),
                                            parameters.getSingleEdgeCounterThreshold(),
                                            parameters.getPairedReadsPetThresholdFrom(),
                                            parameters.getPairedReadsPetThresholdTo(),
                                            parameters.getPairedReadsMpThresholdFrom(),
                                            parameters.getPairedReadsMpThresholdTo(),
                                            i1_1,
                                            i1_2,
                                            o1_1,
                                            o1_2,
                                            bfcFile,
                                            parameters.getPairedReadsAlgorithm(),
                                            parameters.getCorrect(),
                                            parameters.getOutputFileName(),
                                            &progress);
                i1_1.close();
                i1_2.close();
                o1_1.close();
                o1_2.close();
            } else  {   // only for testing process, normally django returns absolute path to file(s) with input set of reads
                istringstream i1_1(parameters.getI1_1());
                istringstream i1_2(parameters.getO1_2());
                istringstream o1_1(parameters.getI1_1());
                istringstream o1_2(parameters.getO1_2());
                result_ = dbj::assemblyMode(parameters.getK() - 1,
                                            parameters.getGenomeLength(),
                                            parameters.getInsertSizeMeanInward(),
                                            parameters.getInsertSizeStdDevInward(),
                                            parameters.getInsertSizeMeanOutward(),
                                            parameters.getInsertSizeStdDevOutward(),
                                            parameters.getQualityThreshold(),
                                            parameters.getBfcounterThreshold(),
                                            parameters.getSingleEdgeCounterThreshold(),
                                            parameters.getPairedReadsPetThresholdFrom(),
                                            parameters.getPairedReadsPetThresholdTo(),
                                            parameters.getPairedReadsMpThresholdFrom(),
                                            parameters.getPairedReadsMpThresholdTo(),
                                            i1_1,
                                            i1_2,
                                            o1_1,
                                            o1_2,
                                            bfcFile,
                                            parameters.getPairedReadsAlgorithm(),
                                            parameters.getCorrect(),
                                            parameters.getOutputFileName(),
                                            &progress);
            }
        }

    private:
        std::map<std::string, std::string> params_;
    };

}} //namespace dnaasm::dbj

#endif //__ASSEMBLYCOMMAND_H__
