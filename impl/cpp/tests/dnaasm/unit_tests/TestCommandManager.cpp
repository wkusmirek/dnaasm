/**
 * \file TestCommandManager.cpp
 * \brief the C++ file with implementation of tests for CommandManager class
 *
 */
#define BOOST_LOG_DYN_LINK

#include <boost/test/unit_test.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include "../../../src/dnaasm/CommandManager.hpp"

using namespace dnaasm::dnaasm;

BOOST_AUTO_TEST_SUITE(TestCommandManager)

BOOST_AUTO_TEST_CASE(CommandManagerTest_runAssemblyCommand)
{
    //supress logging
    boost::log::core::get()->set_filter (boost::log::trivial::severity >= boost::log::trivial::warning);

    std::map<std::string, std::string> params1;
    params1.insert(std::pair<std::string,std::string>("i1_1",">test description1\nAAT\n>test description1\nATA\n>test description2\nTAC\n>test2\nACCGT"));
    params1.insert(std::pair<std::string,std::string>("i1_2",""));
    params1.insert(std::pair<std::string,std::string>("o1_1",""));
    params1.insert(std::pair<std::string,std::string>("o1_2",""));
    params1.insert(std::pair<std::string,std::string>("paired_reads_algorithm","single"));
    params1.insert(std::pair<std::string,std::string>("correct","true"));
    params1.insert(std::pair<std::string,std::string>("output_file_name","test"));
    params1.insert(std::pair<std::string,std::string>("k","3"));
    params1.insert(std::pair<std::string,std::string>("genome_length","8"));
    params1.insert(std::pair<std::string,std::string>("insert_size_mean_inward","0"));
    params1.insert(std::pair<std::string,std::string>("insert_size_std_dev_inward","0"));
    params1.insert(std::pair<std::string,std::string>("insert_size_mean_outward","0"));
    params1.insert(std::pair<std::string,std::string>("insert_size_std_dev_outward","0"));
    params1.insert(std::pair<std::string,std::string>("quality_threshold","0"));
    params1.insert(std::pair<std::string,std::string>("bfcounter_threshold","0"));
    params1.insert(std::pair<std::string,std::string>("single_edge_counter_threshold","0"));
    params1.insert(std::pair<std::string,std::string>("paired_reads_pet_threshold_from","0"));
    params1.insert(std::pair<std::string,std::string>("paired_reads_pet_threshold_to","0"));
    params1.insert(std::pair<std::string,std::string>("paired_reads_mp_threshold_from","0"));
    params1.insert(std::pair<std::string,std::string>("paired_reads_mp_threshold_to","0"));
    std::map<std::string, std::string> params2;
    params2.insert(std::pair<std::string,std::string>("i1_1",""));
    params2.insert(std::pair<std::string,std::string>("i1_2",""));
    params2.insert(std::pair<std::string,std::string>("o1_1",""));
    params2.insert(std::pair<std::string,std::string>("o1_2",""));
    params2.insert(std::pair<std::string,std::string>("paired_reads_algorithm","paired"));
    params2.insert(std::pair<std::string,std::string>("correct","true"));
    params2.insert(std::pair<std::string,std::string>("output_file_name","test"));
    params2.insert(std::pair<std::string,std::string>("k","3"));
    params2.insert(std::pair<std::string,std::string>("genome_length","4"));
    params2.insert(std::pair<std::string,std::string>("insert_size_mean_inward","0"));
    params2.insert(std::pair<std::string,std::string>("insert_size_std_dev_inward","0"));
    params2.insert(std::pair<std::string,std::string>("insert_size_mean_outward","0"));
    params2.insert(std::pair<std::string,std::string>("insert_size_std_dev_outward","0"));
    params2.insert(std::pair<std::string,std::string>("quality_threshold","0"));
    params2.insert(std::pair<std::string,std::string>("bfcounter_threshold","0"));
    params2.insert(std::pair<std::string,std::string>("single_edge_counter_threshold","0"));
    params2.insert(std::pair<std::string,std::string>("paired_reads_pet_threshold_from","0"));
    params2.insert(std::pair<std::string,std::string>("paired_reads_pet_threshold_to","0"));
    params2.insert(std::pair<std::string,std::string>("paired_reads_mp_threshold_from","0"));
    params2.insert(std::pair<std::string,std::string>("paired_reads_mp_threshold_to","0"));
    std::map<std::string, std::string> params3;
    params3.insert(std::pair<std::string,std::string>("i1_1",">test description1\nAAT\n>test description1\nATA\n>test description2\nTAC\n>test2\nACG"));
    params3.insert(std::pair<std::string,std::string>("i1_2",""));
    params3.insert(std::pair<std::string,std::string>("o1_1",""));
    params3.insert(std::pair<std::string,std::string>("o1_2",""));
    params3.insert(std::pair<std::string,std::string>("paired_reads_algorithm","single"));
    params3.insert(std::pair<std::string,std::string>("correct","false"));
    params3.insert(std::pair<std::string,std::string>("output_file_name","test"));
    params3.insert(std::pair<std::string,std::string>("k","3"));
    params3.insert(std::pair<std::string,std::string>("genome_length","6"));
    params3.insert(std::pair<std::string,std::string>("insert_size_mean_inward","0"));
    params3.insert(std::pair<std::string,std::string>("insert_size_std_dev_inward","0"));
    params3.insert(std::pair<std::string,std::string>("insert_size_mean_outward","0"));
    params3.insert(std::pair<std::string,std::string>("insert_size_std_dev_outward","0"));
    params3.insert(std::pair<std::string,std::string>("quality_threshold","0"));
    params3.insert(std::pair<std::string,std::string>("bfcounter_threshold","0"));
    params3.insert(std::pair<std::string,std::string>("single_edge_counter_threshold","0"));
    params3.insert(std::pair<std::string,std::string>("paired_reads_pet_threshold_from","0"));
    params3.insert(std::pair<std::string,std::string>("paired_reads_pet_threshold_to","0"));
    params3.insert(std::pair<std::string,std::string>("paired_reads_mp_threshold_from","0"));
    params3.insert(std::pair<std::string,std::string>("paired_reads_mp_threshold_to","0"));
    mt4cpp::CommandID id1 = CommandManager::getInstance().runAssemblyCommand(1, params1);
    mt4cpp::CommandID id2 = CommandManager::getInstance().runAssemblyCommand(2, params2);
    mt4cpp::CommandID id3 = CommandManager::getInstance().runAssemblyCommand(3, params3);

    std::vector<mt4cpp::CommandID> keys = CommandManager::getInstance().commandKeys();

    BOOST_CHECK_EQUAL(keys.size(), 3U);
    BOOST_CHECK_EQUAL(keys[0], id1);
    BOOST_CHECK_EQUAL(keys[1], id2);
    BOOST_CHECK_EQUAL(keys[2], id3);

    /* simple tests for get- and set- methods */
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getTaskId(id1), 1);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getTaskId(id2), 2);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getTaskId(id3), 3);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id1), false);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id2), false);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id3), false);
    CommandManager::getInstance().setIsSavedInDatabase(id2, true);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id1), false);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id2), true);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id3), false);

    for (unsigned int i = 0; i < 1000; ++i)   //after 10 sec all commands need to be finished
    {
        boost::this_thread::sleep(boost::posix_time::millisec(10));
        if (CommandManager::getInstance().findCommandDesc(id1).state_ == mt4cpp::CommandDesc::DONE && CommandManager::getInstance().findCommandDesc(id2).state_ == mt4cpp::CommandDesc::DONE && CommandManager::getInstance().findCommandDesc(id3).state_ == mt4cpp::CommandDesc::DONE)
            break;
    }

    BOOST_CHECK_EQUAL(CommandManager::getInstance().findCommandDesc(id1).state_, mt4cpp::CommandDesc::DONE);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().findCommandDesc(id2).state_, mt4cpp::CommandDesc::DONE);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().findCommandDesc(id3).state_, mt4cpp::CommandDesc::DONE);

    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! without BFCounter (output file) application returns empty string !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getResult(id1), ">test_0_8\r\nAATACCGT\r\n"); FIXME (write proper test)
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getResult(id2), "");
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getResult(id3), ">test_0_6\r\nAATACG\r\n");
    */

    BOOST_CHECK_EQUAL(CommandManager::getInstance().commandKeys().size(), 3U);
    CommandManager::getInstance().clearHistory();
    BOOST_CHECK_EQUAL(CommandManager::getInstance().commandKeys().size(), 0U);
}

BOOST_AUTO_TEST_CASE(CommandManagerTest_runAlignCommand)
{
    std::map<std::string, std::string> params1;
    params1.insert(std::pair<std::string,std::string>("sequence",">sequence\nACT"));
    params1.insert(std::pair<std::string,std::string>("reference",">reference\nAGT"));
    params1.insert(std::pair<std::string,std::string>("align_algorithm","hirschberg"));
    params1.insert(std::pair<std::string,std::string>("circular","false"));
    params1.insert(std::pair<std::string,std::string>("gap_penalty","-1"));
    params1.insert(std::pair<std::string,std::string>("similarity_matrix_string","1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1"));
    std::map<std::string, std::string> params2;
    params2.insert(std::pair<std::string,std::string>("sequence",">sequence\nAAA"));
    params2.insert(std::pair<std::string,std::string>("reference",">reference\nAAA"));
    params2.insert(std::pair<std::string,std::string>("align_algorithm","hirschberg"));
    params2.insert(std::pair<std::string,std::string>("circular","false"));
    params2.insert(std::pair<std::string,std::string>("gap_penalty","-1"));
    params2.insert(std::pair<std::string,std::string>("similarity_matrix_string","1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1"));
    std::map<std::string, std::string> params3;
    params3.insert(std::pair<std::string,std::string>("sequence",">sequence\nA"));
    params3.insert(std::pair<std::string,std::string>("reference",">reference\nA"));
    params3.insert(std::pair<std::string,std::string>("align_algorithm","hirschberg"));
    params3.insert(std::pair<std::string,std::string>("circular","false"));
    params3.insert(std::pair<std::string,std::string>("gap_penalty","-1"));
    params3.insert(std::pair<std::string,std::string>("similarity_matrix_string","1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, -1, -1, 1"));
    mt4cpp::CommandID id1 = CommandManager::getInstance().runAlignCommand(1, params1);
    mt4cpp::CommandID id2 = CommandManager::getInstance().runAlignCommand(2, params2);
    mt4cpp::CommandID id3 = CommandManager::getInstance().runAlignCommand(3, params3);

    std::vector<mt4cpp::CommandID> keys = CommandManager::getInstance().commandKeys();

    BOOST_CHECK_EQUAL(keys.size(), 3U);
    BOOST_CHECK_EQUAL(keys[0], id1);
    BOOST_CHECK_EQUAL(keys[1], id2);
    BOOST_CHECK_EQUAL(keys[2], id3);

    /* simple tests for get- and set- methods */
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getTaskId(id1), 1);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getTaskId(id2), 2);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getTaskId(id3), 3);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id1), false);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id2), false);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id3), false);
    CommandManager::getInstance().setIsSavedInDatabase(id2, true);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id1), false);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id2), true);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getIsSavedInDatabase(id3), false);

    for (unsigned int i = 0; i < 1000; ++i)   //after 10 sec all commands need to be finished
    {
        boost::this_thread::sleep(boost::posix_time::millisec(10));
        if (CommandManager::getInstance().findCommandDesc(id1).state_ == mt4cpp::CommandDesc::DONE && CommandManager::getInstance().findCommandDesc(id2).state_ == mt4cpp::CommandDesc::DONE && CommandManager::getInstance().findCommandDesc(id3).state_ == mt4cpp::CommandDesc::DONE)
            break;
    }

    BOOST_CHECK_EQUAL(CommandManager::getInstance().findCommandDesc(id1).state_, mt4cpp::CommandDesc::DONE);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().findCommandDesc(id2).state_, mt4cpp::CommandDesc::DONE);
    BOOST_CHECK_EQUAL(CommandManager::getInstance().findCommandDesc(id3).state_, mt4cpp::CommandDesc::DONE);

    //BOOST_CHECK_EQUAL(CommandManager::getInstance().getResult(id1), "##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n.\t2\tsequence\tG\tC\t.\t.\t.\r\n");
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getResult(id2), "##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n");
    BOOST_CHECK_EQUAL(CommandManager::getInstance().getResult(id3), "##fileformat=VCFv4.0\r\n#CHROM\tPOS\tID\tREF\tALT\tQUAL\tFILTER\tINFO\r\n");

    BOOST_CHECK_EQUAL(CommandManager::getInstance().commandKeys().size(), 3U);
    CommandManager::getInstance().clearHistory();
    BOOST_CHECK_EQUAL(CommandManager::getInstance().commandKeys().size(), 0U);
}

//BOOST_AUTO_TEST_CASE(CommandManagerTest_runBstCommand)
//{
//    std::map<std::string, std::string> params;
//    const std::string path = "cpp/tests/bst/unit_tests/reads";
//    params.insert(std::pair<std::string,std::string>("kmer_size","16"));
//    params.insert(std::pair<std::string,std::string>("min_similarity","2"));
//    params.insert(std::pair<std::string,std::string>("input_file_path", path));
//    params.insert(std::pair<std::string,std::string>("output_file_name", "result"));
//
//    mt4cpp::CommandID id = CommandManager::getInstance().runBstCommand(1, params);
//
//    std::vector<mt4cpp::CommandID> keys = CommandManager::getInstance().commandKeys();
//
//    BOOST_CHECK_EQUAL(keys.size(), 1U);
//    BOOST_CHECK_EQUAL(keys[0], id);
//
//    for (unsigned int i = 0; i < 200; ++i)   //after 2 sec a command needs to be finished
//    {
//        boost::this_thread::sleep(boost::posix_time::millisec(10));
//        if (CommandManager::getInstance().findCommandDesc(id).state_ == mt4cpp::CommandDesc::DONE)
//            break;
//    }
//
//    BOOST_CHECK_EQUAL(CommandManager::getInstance().getResult(id), "@res_0\nACTCAACGCTAGCTAGCTAGATCGTCCCGGTTACGGATTGC\n");
//}

BOOST_AUTO_TEST_SUITE_END()
