/**
 * \file TestScaffold.cpp
 * \brief the C++ file with implementation of tests for scaffold function
 *
 */

#include <boost/test/unit_test.hpp>
#include <boost/filesystem/operations.hpp>
#include <fstream>
#include "../../../src/scfr/scaffold.hpp"

using namespace dnaasm::scfr;

struct FixSCFD {

    ~FixSCFD() {
        std::remove(contigsFilePath.c_str());
        std::remove(readsFilePath.c_str());
        std::remove(scaffoldFilePath.c_str());
        std::remove(contigCorrFilePath.c_str());
        std::remove(contigPairsFilePath.c_str());
        boost::filesystem::remove_all(gapSequencesDir);
    }

    std::string runScaffold() {
        return scaffold(contigsFilePath, readsFilePath,
                        kmerSize, distance,
                        step, minLinks,
                        minReads, minLinksPerRead,
                        maxRatio, minContigLength,
                        gapFilling, nullptr);
    }

    std::string getCSV() {
        BOOST_REQUIRE(boost::filesystem::exists(scaffoldFilePath));
        std::ifstream csvFile(scaffoldFilePath.c_str());
        return std::string((std::istreambuf_iterator<char>(csvFile)),
                           (std::istreambuf_iterator<char>()));
    }
    
    void checkIfAdditionalFilesExist() {
        BOOST_CHECK(boost::filesystem::exists(scaffoldFilePath));
        BOOST_CHECK(boost::filesystem::exists(gapSequencesDir));
        BOOST_CHECK(boost::filesystem::exists(contigCorrFilePath));
        BOOST_CHECK(boost::filesystem::exists(contigPairsFilePath));
    }

    void createSeqsFile(const std::string &fileName,
                           const std::vector<std::string>& seqs) {
        std::ofstream file(fileName.c_str());
        unsigned int counter = 1;

        for (const auto &s : seqs) {
            file << ">" << counter << " " << s.size() << std::endl
                 << s << std::endl;
            ++counter;
        }
        file.close();
    }

    void createContigsFile(const std::vector<std::string>& seqs) {
        createSeqsFile(contigsFilePath, seqs);
    }

    void createReadsFile(const std::vector<std::string>& seqs) {
        createSeqsFile(readsFilePath, seqs);
    }

    std::string genomeFilePath = "./cpp/tests/scfr/unit_tests/genome.txt";
    std::string contigsFilePath = "contigs.fa";
    std::string readsFilePath = "reads.fa";
    std::string scaffoldFilePath = "scaffolds.csv";
    std::string gapSequencesDir = "./gap_sequences";
    std::string contigCorrFilePath = "./contig_correspondence.log";
    std::string contigPairsFilePath = "./contig_pairs.log";

    // scaffolder parameters used in most of tests below
    unsigned short int kmerSize = 3;
    unsigned short int distance = 9;
    unsigned short int step = 1;
    unsigned short int minLinks = 1;
    unsigned short int minReads = 1;
    unsigned short int minLinksPerRead = 1;
    float maxRatio = 0.3;
    unsigned int minContigLength = 6;
    bool gapFilling = false;
};

BOOST_FIXTURE_TEST_SUITE(TestScaffold, FixSCFD)

BOOST_AUTO_TEST_CASE(scaffold_empty_input_file)
{
    /* scaffolder settings */
    kmerSize = 0;
    distance = 0;
    step = 0;
    minLinks = 0;
    minLinksPerRead = 0;
    maxRatio = 0.0;
    minContigLength = 0;
    gapFilling = false;

    /* run scaffold with empty input file name */
    contigsFilePath = "";
    BOOST_CHECK_EQUAL(runScaffold(),"");
    BOOST_REQUIRE(!boost::filesystem::exists(scaffoldFilePath));
    contigsFilePath = "contigs.fa";
    readsFilePath = "";
    BOOST_CHECK_EQUAL(runScaffold(),"");
    BOOST_REQUIRE(!boost::filesystem::exists(scaffoldFilePath));

    // reset
    contigsFilePath = "contigs.fa";
    readsFilePath = "reads.fa";

    /* create empty file with contigs and non-empty reads file*/
    createContigsFile({});
    createReadsFile({"CATTTAGCA"});

    /* create scaffold - should return empty string */
    BOOST_CHECK_EQUAL(runScaffold(),"");
    BOOST_REQUIRE(!boost::filesystem::exists(scaffoldFilePath));

    /* now create non-empty contigs file and empty reads file */
    createContigsFile({"CCCATT", "AGCAGG"});
    createReadsFile({});

    /* create scaffold - should return empty string again */
    BOOST_CHECK_EQUAL(runScaffold(),"");
    BOOST_REQUIRE(!boost::filesystem::exists(scaffoldFilePath));
}

BOOST_AUTO_TEST_CASE(scaffold_simple1_f1_f2_same_lengths)
{
    // scenario:
    // contig pairs in graph:
    //    f1 -> f2, r2 -> r1
    // seed: c1 (contigs have same lengths, so lowest id is a seed) - insert f1 to scaffold
    // 1. try extend right:
    //    f1 -> f2 pair found - f2 is appended to the right of f1 in scaffold
    // gap requence is NOT reverse compl. because read maps to positive contigs

    /* prepare input files */
    createContigsFile({"CCCATT", "AGCAGG"});
    createReadsFile({"CATTTAGCA"});

    /* test WITHOUT gapfilling */
    gapFilling = false;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,12,f1Z6k1a0.00n1i+1o4m1_f2z6\nCCCATTNAGCAGG\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,12,f1Z6k1a0.00n1i+1o4m1_f2z6\n");

    std::remove(scaffoldFilePath.c_str());

    /* test WITH gapfilling */
    gapFilling = true;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,12,f1Z6k1a0.00n1i+1o4m1_f2z6\nCCCATTtAGCAGG\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,12,f1Z6k1a0.00n1i+1o4m1_f2z6\n");
}

BOOST_AUTO_TEST_CASE(scaffold_simple2_f1_f2_first_longer)
{
    // scenario:
    // contig pairs in graph:
    //    f1 -> f2, r2 -> r1
    // seed: c1 (longer) - insert f1 to scaffold
    // 1. try extend right:
    //    f1 -> f2 pair found - f2 is appended to the right of f1 in scaffold
    // gap requence is NOT reverse compl. because read maps to positive seed (f1)

    /* prepare input files */
    createContigsFile({"CCCATTC", "AGCAGG"});
    createReadsFile({"CATTCATAGCA"});

    /* test WITHOUT gapfilling */
    gapFilling = false;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,13,f1Z7k2a0.00n1i+1o5m2_f2z6\nCCCATTCNNAGCAGG\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,13,f1Z7k2a0.00n1i+1o5m2_f2z6\n");

    std::remove(scaffoldFilePath.c_str());

    /* test WITH gapfilling */
    gapFilling = true;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,13,f1Z7k2a0.00n1i+1o5m2_f2z6\nCCCATTCatAGCAGG\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,13,f1Z7k2a0.00n1i+1o5m2_f2z6\n");
}

BOOST_AUTO_TEST_CASE(scaffold_simple3_f1_r2_first_longer)
{
    // scenario:
    // contig pairs in graph:
    //    f1 -> r2, f2 -> r1
    // seed: c1 (longer) - insert f1 to scaffold
    // 1. try extend right:
    //    f1 -> r2 pair found - f2 is appended to the right of f1 in scaffold
    // gap requence is NOT reverse compl. because read maps to positive seed (f1)

    /* prepare input files */
    createContigsFile({"CCCATTC", "CCTGCT"});
    createReadsFile({"CATTCATGAGCA"});

    /* test WITHOUT gapfilling */
    gapFilling = false;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,13,f1Z7k1a0.00n1i+1o5m3_r2z6\nCCCATTCNNNAGCAGG\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,13,f1Z7k1a0.00n1i+1o5m3_r2z6\n");

    std::remove(scaffoldFilePath.c_str());

    /* test WITH gapfilling */
    gapFilling = true;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,13,f1Z7k1a0.00n1i+1o5m3_r2z6\nCCCATTCatgAGCAGG\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,13,f1Z7k1a0.00n1i+1o5m3_r2z6\n");
}

BOOST_AUTO_TEST_CASE(scaffold_simple4_f1_r2_second_longer)
{
    // scenario:
    // contig pairs in graph:
    //    f1 -> r2, f2 -> r1
    // seed: c2 (longer) - insert f2 to scaffold
    // 1. try extend right:
    //    f2 -> r1 pair found - r1 is appended to the right of f2 in scaffold
    // gap requence IS reverse compl. because read maps to reversed seed (f2)

    /* prepare input files */
    createContigsFile({"ATG", "GCTG"});
    createReadsFile({"ATGGTTCAG"});

    /* test WITHOUT gapfilling */
    minContigLength = 3;
    gapFilling = false;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,7,f2Z4k1a0.00n1i-1o3m3_r1z3\nGCTGNNNCAT\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,7,f2Z4k1a0.00n1i-1o3m3_r1z3\n");

    std::remove(scaffoldFilePath.c_str());

    /* test WITH gapfilling */
    gapFilling = true;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,7,f2Z4k1a0.00n1i-1o3m3_r1z3\nGCTGaacCAT\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,7,f2Z4k1a0.00n1i-1o3m3_r1z3\n");
}

BOOST_AUTO_TEST_CASE(scaffold_simple5_r1_f2_or_r2_f1)
{
    // scenario:
    // contig pairs in graph:
    //    r1 -> f2, r2 -> f1
    // seed: c2 (longer) - insert f2 to scaffold
    // 1. try extend right:
    //    f2 -> ? no pairings
    // 2. try extend left:
    //    r2 -> f1 pair found - r1 is appended to the left of f2 in scaffold
    // gap requence IS reverse compl. because read maps to reversed seed (r2)

    /* prepare input files */
    createContigsFile({"CCCATTC", "AGCAGGCA"}); // r1 = GAATGGG, r2 = TGCCTGCT
    createReadsFile({"GCTCTTCCCAT"}); // rev read = ATGGGAAGAGC

    /* test WITHOUT gapfilling */
    gapFilling = false;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,15,r1z7k1a0.00n1i-1o3m3_f2Z8\nGAATGGGNNNAGCAGGCA\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,15,r1z7k1a0.00n1i-1o3m3_f2Z8\n");

    std::remove(scaffoldFilePath.c_str());

    /* test WITH gapfilling */
    gapFilling = true;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,15,r1z7k1a0.00n1i-1o3m3_f2Z8\nGAATGGGaagAGCAGGCA\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,15,r1z7k1a0.00n1i-1o3m3_f2Z8\n");
}

BOOST_AUTO_TEST_CASE(createScaffold_genome_1000000)
{
    size_t length = 1000000;
    std::string genome = "";

    /* scaffolder settings */
    kmerSize = 15;
    distance = 4000;
    step = 2;
    minLinks = 1;
    minReads = 1;
    minLinksPerRead = 1;
    maxRatio = 0.3;
    minContigLength = 500;
    gapFilling = false;

    /* prepare input files */
    size_t contigLength = 2000;
    int contigGapLength = 1000;
    size_t contigOffset = 0;

    size_t readLength = 8000;
    int readGapLength = -4000;
    size_t readOffset = 0;

    std::ifstream genomeFile(genomeFilePath.c_str());
    genome.assign((std::istreambuf_iterator<char>(genomeFile)),
                  (std::istreambuf_iterator<char>()));

    BOOST_REQUIRE_MESSAGE(genome.size() > 0, "Empty genome file!");

    std::ofstream contigsFile(contigsFilePath.c_str());
    int counter = 0;
    for(size_t i = contigOffset; i < length -1 ; i += (contigLength + contigGapLength)) {
        auto subStr = genome.substr(i, contigLength);
        contigsFile << ">" << ++counter << " " << subStr.size() << std::endl;
        contigsFile << subStr << std::endl;
    }
    contigsFile.close();

    std::ofstream longReadsFile(readsFilePath.c_str());
    counter = 0;
    for(size_t i = readOffset; i < length -1 ; i += (readLength + readGapLength)) {
        auto subStr = genome.substr(i, readLength);
        longReadsFile << ">" << ++counter << " " << subStr.size() << std::endl;
        longReadsFile << subStr << std::endl;
    }
    longReadsFile.close();

    /* create scaffold */
    BOOST_CHECK(runScaffold().size() > 0);

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,667000,f1Z2000k496a0.00n1i+1o2000m1000_f2z2000k501a0.00n1i+1o5000m1000_f3z2000k500a0.00n1i+2o4000m1000_f4z2000k501a0.00n1i+3o3000m1000_f5z2000k499a0.00n2i+4o2000m1000_f6z2000k498a0.00n1i+4o5000m1000_f7z2000k498a0.00n1i+5o4000m1000_f8z2000k501a0.00n1i+6o3000m1000_f9z2000k501a0.00n2i+7o2000m1000_f10z2000k500a0.00n1i+7o5000m1000_f11z2000k501a0.00n1i+8o4000m1000_f12z2000k500a0.00n1i+9o3000m1000_f13z2000k500a0.00n2i+10o2000m1000_f14z2000k501a0.00n1i+10o5000m1000_f15z2000k501a0.00n1i+11o4000m1000_f16z2000k500a0.00n1i+12o3000m1000_f17z2000k499a0.00n2i+13o2000m1000_f18z2000k500a0.00n1i+13o5000m1000_f19z2000k496a0.00n1i+14o4000m1000_f20z2000k501a0.00n1i+15o3000m1000_f21z2000k500a0.00n2i+16o2000m1000_f22z2000k499a0.00n1i+16o5000m1000_f23z2000k499a0.00n1i+17o4000m1000_f24z2000k499a0.00n1i+18o3000m1000_f25z2000k501a0.00n2i+19o2000m1000_f26z2000k498a0.00n1i+19o5000m1000_f27z2000k500a0.00n1i+20o4000m1000_f28z2000k499a0.00n1i+21o3000m1000_f29z2000k501a0.00n2i+22o2000m1000_f30z2000k500a0.00n1i+22o5000m1000_f31z2000k498a0.00n1i+23o4000m1000_f32z2000k498a0.00n1i+24o3000m1000_f33z2000k500a0.00n2i+25o2000m1000_f34z2000k499a0.00n1i+25o5000m1000_f35z2000k500a0.00n1i+26o4000m1000_f36z2000k500a0.00n1i+27o3000m1000_f37z2000k501a0.00n2i+28o2000m1000_f38z2000k498a0.00n1i+28o5000m1000_f39z2000k499a0.00n1i+29o4000m1000_f40z2000k498a0.00n1i+30o3000m1000_f41z2000k500a0.00n2i+31o2000m1000_f42z2000k496a0.01n1i+31o5000m1000_f43z2000k501a0.00n1i+32o4000m1000_f44z2000k501a0.00n1i+33o3000m1000_f45z2000k501a0.00n2i+34o2000m1000_f46z2000k500a0.00n1i+34o5000m1000_f47z2000k501a0.00n1i+35o4000m1000_f48z2000k501a0.00n1i+36o3000m1000_f49z2000k499a0.00n2i+37o2000m1000_f50z2000k498a0.00n1i+37o5000m1000_f51z2000k499a0.00n1i+38o4000m1000_f52z2000k496a0.00n1i+39o3000m1000_f53z2000k499a0.00n2i+40o2000m1000_f54z2000k500a0.00n1i+40o5000m1000_f55z2000k500a0.00n1i+41o4000m1000_f56z2000k501a0.00n1i+42o3000m1000_f57z2000k500a0.00n2i+43o2000m1000_f58z2000k501a0.00n1i+43o5000m1000_f59z2000k500a0.00n1i+44o4000m1000_f60z2000k499a0.00n1i+45o3000m1000_f61z2000k501a0.00n2i+46o2000m1000_f62z2000k500a0.00n1i+46o5000m1000_f63z2000k499a0.00n1i+47o4000m1000_f64z2000k500a0.00n1i+48o3000m1000_f65z2000k501a0.00n2i+49o2000m1000_f66z2000k499a0.00n1i+49o5000m1000_f67z2000k499a0.00n1i+50o4000m1000_f68z2000k498a0.00n1i+51o3000m1000_f69z2000k500a0.00n2i+52o2000m1000_f70z2000k499a0.00n1i+52o5000m1000_f71z2000k500a0.00n1i+53o4000m1000_f72z2000k498a0.00n1i+54o3000m1000_f73z2000k501a0.00n2i+55o2000m1000_f74z2000k501a0.00n1i+55o5000m1000_f75z2000k500a0.00n1i+56o4000m1000_f76z2000k499a0.00n1i+57o3000m1000_f77z2000k499a0.00n2i+58o2000m1000_f78z2000k499a0.00n1i+58o5000m1000_f79z2000k497a0.00n1i+59o4000m1000_f80z2000k499a0.00n1i+60o3000m1000_f81z2000k499a0.00n2i+61o2000m1000_f82z2000k501a0.00n1i+61o5000m1000_f83z2000k500a0.00n1i+62o4000m1000_f84z2000k500a0.00n1i+63o3000m1000_f85z2000k500a0.00n2i+64o2000m1000_f86z2000k501a0.00n1i+64o5000m1000_f87z2000k501a0.00n1i+65o4000m1000_f88z2000k499a0.00n1i+66o3000m1000_f89z2000k501a0.00n2i+67o2000m1000_f90z2000k500a0.00n1i+67o5000m1000_f91z2000k501a0.00n1i+68o4000m1000_f92z2000k499a0.00n1i+69o3000m1000_f93z2000k500a0.00n2i+70o2000m1000_f94z2000k501a0.00n1i+70o5000m1000_f95z2000k498a0.00n1i+71o4000m1000_f96z2000k499a0.00n1i+72o3000m1000_f97z2000k501a0.00n2i+73o2000m1000_f98z2000k499a0.00n1i+73o5000m1000_f99z2000k500a0.00n1i+74o4000m1000_f100z2000k501a0.00n1i+75o3000m1000_f101z2000k498a0.00n2i+76o2000m1000_f102z2000k500a0.00n1i+76o5000m1000_f103z2000k500a0.00n1i+77o4000m1000_f104z2000k500a0.00n1i+78o3000m1000_f105z2000k500a0.00n2i+79o2000m1000_f106z2000k500a0.00n1i+79o5000m1000_f107z2000k500a0.00n1i+80o4000m1000_f108z2000k501a0.00n1i+81o3000m1000_f109z2000k500a0.00n2i+82o2000m1000_f110z2000k497a0.00n1i+82o5000m1000_f111z2000k495a0.00n1i+83o4000m1000_f112z2000k499a0.00n1i+84o3000m1000_f113z2000k500a0.00n2i+85o2000m1000_f114z2000k498a0.00n1i+85o5000m1000_f115z2000k499a0.00n1i+86o4000m1000_f116z2000k498a0.00n1i+87o3000m1000_f117z2000k498a0.00n2i+88o2000m1000_f118z2000k501a0.00n1i+88o5000m1000_f119z2000k496a0.00n1i+89o4000m1000_f120z2000k500a0.00n1i+90o3000m1000_f121z2000k501a0.00n2i+91o2000m1000_f122z2000k501a0.00n1i+91o5000m1000_f123z2000k501a0.00n1i+92o4000m1000_f124z2000k500a0.00n1i+93o3000m1000_f125z2000k499a0.00n2i+94o2000m1000_f126z2000k501a0.00n1i+94o5000m1000_f127z2000k500a0.00n1i+95o4000m1000_f128z2000k500a0.00n1i+96o3000m1000_f129z2000k498a0.00n2i+97o2000m1000_f130z2000k498a0.00n1i+97o5000m1000_f131z2000k500a0.00n1i+98o4000m1000_f132z2000k500a0.00n1i+99o3000m1000_f133z2000k499a0.00n2i+100o2000m1000_f134z2000k500a0.00n1i+100o5000m1000_f135z2000k501a0.00n1i+101o4000m1000_f136z2000k500a0.00n1i+102o3000m1000_f137z2000k499a0.00n2i+103o2000m1000_f138z2000k501a0.00n1i+103o5000m1000_f139z2000k501a0.00n1i+104o4000m1000_f140z2000k500a0.00n1i+105o3000m1000_f141z2000k501a0.00n2i+106o2000m1000_f142z2000k500a0.00n1i+106o5000m1000_f143z2000k500a0.00n1i+107o4000m1000_f144z2000k501a0.00n1i+108o3000m1000_f145z2000k501a0.00n2i+109o2000m1000_f146z2000k499a0.00n1i+109o5000m1000_f147z2000k500a0.00n1i+110o4000m1000_f148z2000k501a0.00n1i+111o3000m1000_f149z2000k500a0.00n2i+112o2000m1000_f150z2000k501a0.00n1i+112o5000m1000_f151z2000k501a0.00n1i+113o4000m1000_f152z2000k500a0.00n1i+114o3000m1000_f153z2000k496a0.00n2i+115o2000m1000_f154z2000k498a0.00n1i+115o5000m1000_f155z2000k501a0.00n1i+116o4000m1000_f156z2000k499a0.00n1i+117o3000m1000_f157z2000k500a0.00n2i+118o2000m1000_f158z2000k501a0.00n1i+118o5000m1000_f159z2000k499a0.00n1i+119o4000m1000_f160z2000k501a0.00n1i+120o3000m1000_f161z2000k500a0.00n2i+121o2000m1000_f162z2000k500a0.00n1i+121o5000m1000_f163z2000k499a0.00n1i+122o4000m1000_f164z2000k498a0.00n1i+123o3000m1000_f165z2000k500a0.00n2i+124o2000m1000_f166z2000k498a0.00n1i+124o5000m1000_f167z2000k500a0.00n1i+125o4000m1000_f168z2000k498a0.00n1i+126o3000m1000_f169z2000k501a0.00n2i+127o2000m1000_f170z2000k500a0.00n1i+127o5000m1000_f171z2000k501a0.00n1i+128o4000m1000_f172z2000k497a0.00n1i+129o3000m1000_f173z2000k501a0.00n2i+130o2000m1000_f174z2000k500a0.00n1i+130o5000m1000_f175z2000k499a0.00n1i+131o4000m1000_f176z2000k501a0.00n1i+132o3000m1000_f177z2000k500a0.00n2i+133o2000m1000_f178z2000k501a0.00n1i+133o5000m1000_f179z2000k500a0.00n1i+134o4000m1000_f180z2000k497a0.00n1i+135o3000m1000_f181z2000k499a0.00n2i+136o2000m1000_f182z2000k501a0.00n1i+136o5000m1000_f183z2000k499a0.00n1i+137o4000m1000_f184z2000k499a0.00n1i+138o3000m1000_f185z2000k497a0.00n2i+139o2000m1000_f186z2000k500a0.00n1i+139o5000m1000_f187z2000k501a0.00n1i+140o4000m1000_f188z2000k500a0.00n1i+141o3000m1000_f189z2000k500a0.00n2i+142o2000m1000_f190z2000k501a0.00n1i+142o5000m1000_f191z2000k499a0.00n1i+143o4000m1000_f192z2000k501a0.00n1i+144o3000m1000_f193z2000k498a0.00n2i+145o2000m1000_f194z2000k501a0.00n1i+145o5000m1000_f195z2000k501a0.00n1i+146o4000m1000_f196z2000k496a0.00n1i+147o3000m1000_f197z2000k501a0.00n2i+148o2000m1000_f198z2000k499a0.00n1i+148o5000m1000_f199z2000k500a0.00n1i+149o4000m1000_f200z2000k499a0.00n1i+150o3000m1000_f201z2000k500a0.00n2i+151o2000m1000_f202z2000k500a0.00n1i+151o5000m1000_f203z2000k499a0.00n1i+152o4000m1000_f204z2000k501a0.00n1i+153o3000m1000_f205z2000k501a0.00n2i+154o2000m1000_f206z2000k501a0.00n1i+154o5000m1000_f207z2000k500a0.00n1i+155o4000m1000_f208z2000k501a0.00n1i+156o3000m1000_f209z2000k499a0.00n2i+157o2000m1000_f210z2000k501a0.00n1i+157o5000m1000_f211z2000k500a0.00n1i+158o4000m1000_f212z2000k501a0.00n1i+159o3000m1000_f213z2000k500a0.00n2i+160o2000m1000_f214z2000k501a0.00n1i+160o5000m1000_f215z2000k501a0.00n1i+161o4000m1000_f216z2000k499a0.00n1i+162o3000m1000_f217z2000k501a0.00n2i+163o2000m1000_f218z2000k499a0.00n1i+163o5000m1000_f219z2000k499a0.00n1i+164o4000m1000_f220z2000k501a0.00n1i+165o3000m1000_f221z2000k501a0.00n2i+166o2000m1000_f222z2000k501a0.00n1i+166o5000m1000_f223z2000k499a0.00n1i+167o4000m1000_f224z2000k501a0.00n1i+168o3000m1000_f225z2000k501a0.00n2i+169o2000m1000_f226z2000k498a0.00n1i+169o5000m1000_f227z2000k498a0.00n1i+170o4000m1000_f228z2000k499a0.00n1i+171o3000m1000_f229z2000k500a0.00n2i+172o2000m1000_f230z2000k500a0.00n1i+172o5000m1000_f231z2000k499a0.00n1i+173o4000m1000_f232z2000k496a0.00n1i+174o3000m1000_f233z2000k500a0.00n2i+175o2000m1000_f234z2000k500a0.00n1i+175o5000m1000_f235z2000k500a0.00n1i+176o4000m1000_f236z2000k499a0.00n1i+177o3000m1000_f237z2000k499a0.00n2i+178o2000m1000_f238z2000k500a0.00n1i+178o5000m1000_f239z2000k501a0.00n1i+179o4000m1000_f240z2000k500a0.00n1i+180o3000m1000_f241z2000k501a0.00n2i+181o2000m1000_f242z2000k499a0.00n1i+181o5000m1000_f243z2000k500a0.00n1i+182o4000m1000_f244z2000k498a0.00n1i+183o3000m1000_f245z2000k499a0.00n2i+184o2000m1002_f246z2000k500a0.00n1i+184o5000m1000_f247z2000k501a0.00n1i+185o4000m1000_f248z2000k499a0.00n1i+186o3000m1000_f249z2000k501a0.00n2i+187o2000m1000_f250z2000k501a0.00n1i+187o5000m1000_f251z2000k500a0.00n1i+188o4000m1000_f252z2000k498a0.00n1i+189o3000m1000_f253z2000k501a0.00n2i+190o2000m1000_f254z2000k501a0.00n1i+190o5000m1000_f255z2000k499a0.00n1i+191o4000m1000_f256z2000k501a0.00n1i+192o3000m1000_f257z2000k499a0.00n2i+193o2000m1000_f258z2000k501a0.00n1i+193o5000m1000_f259z2000k497a0.00n1i+194o4000m1000_f260z2000k501a0.00n1i+195o3000m1000_f261z2000k500a0.00n2i+196o2000m1000_f262z2000k499a0.00n1i+196o5000m1000_f263z2000k500a0.00n1i+197o4000m1000_f264z2000k499a0.00n1i+198o3000m1000_f265z2000k501a0.00n2i+199o2000m1000_f266z2000k501a0.00n1i+199o5000m1000_f267z2000k499a0.00n1i+200o4000m1000_f268z2000k500a0.00n1i+201o3000m1000_f269z2000k500a0.00n2i+202o2000m1000_f270z2000k500a0.00n1i+202o5000m1000_f271z2000k499a0.00n1i+203o4000m1000_f272z2000k498a0.00n1i+204o3000m1000_f273z2000k501a0.00n2i+205o2000m1000_f274z2000k499a0.00n1i+205o5000m1000_f275z2000k501a0.00n1i+206o4000m1000_f276z2000k500a0.00n1i+207o3000m1000_f277z2000k499a0.00n2i+208o2000m1000_f278z2000k498a0.00n1i+208o5000m1000_f279z2000k497a0.00n1i+209o4000m1000_f280z2000k498a0.00n1i+210o3000m1000_f281z2000k500a0.00n2i+211o2000m1000_f282z2000k501a0.00n1i+211o5000m1000_f283z2000k500a0.00n1i+212o4000m1000_f284z2000k501a0.00n1i+213o3000m1000_f285z2000k500a0.00n2i+214o2000m1000_f286z2000k499a0.00n1i+214o5000m1000_f287z2000k500a0.00n1i+215o4000m1000_f288z2000k500a0.00n1i+216o3000m1000_f289z2000k498a0.00n2i+217o2000m1000_f290z2000k500a0.00n1i+217o5000m1000_f291z2000k499a0.00n1i+218o4000m1000_f292z2000k496a0.00n1i+219o3000m1000_f293z2000k501a0.00n2i+220o2000m1000_f294z2000k499a0.00n1i+220o5000m1000_f295z2000k500a0.00n1i+221o4000m1000_f296z2000k500a0.00n1i+222o3000m1000_f297z2000k501a0.00n2i+223o2000m1000_f298z2000k498a0.00n1i+223o5000m1000_f299z2000k501a0.00n1i+224o4000m1000_f300z2000k501a0.00n1i+225o3000m1000_f301z2000k499a0.00n2i+226o2000m1000_f302z2000k501a0.00n1i+226o5000m1000_f303z2000k501a0.00n1i+227o4000m1000_f304z2000k500a0.00n1i+228o3000m1000_f305z2000k501a0.00n2i+229o2000m1000_f306z2000k497a0.00n1i+229o5000m1000_f307z2000k498a0.00n1i+230o4000m1000_f308z2000k498a0.00n1i+231o3000m1000_f309z2000k498a0.00n2i+232o2000m1000_f310z2000k499a0.00n1i+232o5000m1000_f311z2000k500a0.00n1i+233o4000m1000_f312z2000k500a0.00n1i+234o3000m1000_f313z2000k500a0.00n2i+235o2000m1000_f314z2000k498a0.00n1i+235o5000m1000_f315z2000k499a0.00n1i+236o4000m1000_f316z2000k500a0.00n1i+237o3000m1000_f317z2000k500a0.00n2i+238o2000m1000_f318z2000k498a0.00n1i+238o5000m1002_f319z2000k501a0.00n1i+239o4000m1000_f320z2000k498a0.00n1i+240o3000m1000_f321z2000k499a0.00n2i+241o2000m1000_f322z2000k501a0.00n1i+241o5000m1000_f323z2000k500a0.00n1i+242o4000m1000_f324z2000k500a0.00n1i+243o3000m1000_f325z2000k501a0.00n2i+244o2000m1000_f326z2000k500a0.00n1i+244o5000m1000_f327z2000k500a0.00n1i+245o4000m1000_f328z2000k500a0.00n1i+246o3000m1000_f329z2000k499a0.00n2i+247o2000m1000_f330z2000k501a0.00n1i+247o5000m1000_f331z2000k499a0.00n1i+248o4000m1000_f332z2000k500a0.00n1i+249o3000m1000_f333z2000k1a0.00n1i+249o6000m1000_f334z1000\n");
}

BOOST_AUTO_TEST_CASE(scaffold_upper_and_lowercase_mixed)
{
    // alg. should also work for lowercase letters in contigs and reads

    /* prepare input files */
    createContigsFile({"CccaTT", "AGCAgg"});
    createReadsFile({"CATtTAgcA"});

    /* test WITHOUT gapfilling */
    gapFilling = false;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,12,f1Z6k1a0.00n1i+1o4m1_f2z6\nCccaTTNAGCAgg\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,12,f1Z6k1a0.00n1i+1o4m1_f2z6\n");

    std::remove(scaffoldFilePath.c_str());

    /* test WITH gapfilling */
    gapFilling = true;
    BOOST_CHECK_EQUAL(runScaffold(), ">scaffold1,12,f1Z6k1a0.00n1i+1o4m1_f2z6\nCccaTTtAGCAgg\n");

    /* check generated csv file with scaffolds layout */
    checkIfAdditionalFilesExist();
    BOOST_CHECK_EQUAL(getCSV(), "scaffold1,12,f1Z6k1a0.00n1i+1o4m1_f2z6\n");
}

BOOST_AUTO_TEST_SUITE_END()
