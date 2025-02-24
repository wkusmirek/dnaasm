/**
 * \file OutwardPairedReadsAdding.hpp
 * \brief the C++ file with implementation of template class for adding outward (<- ->) paired reads to graph
 *
 */

#ifndef OUTWARD_PAIRED_READS_ADDING_HPP
#define OUTWARD_PAIRED_READS_ADDING_HPP

#include <mt4cpp/Scheduler.hpp>
#include "../common/FileReader.hpp"
#include "../common/log.hpp"
#include <fstream>

namespace dnaasm { namespace dbj {
    /**
     * \brief Class to add outward paired reads to sequences graph
    */
    template<class SequencesGraph> class OutwardPairedReadsAdding {
    public:

        /**
         * \brief OutwardPairedReadsAdding constructor.
         *
         * \param fileReader reference to a FileReader object class to read data from files
         * \param sequencesGraph reference to SequencesGraph object
         * \param qualityThreshold quality threshold value (0-93)
         * \param progress actual task's progress
         * \return returns void
         */
        OutwardPairedReadsAdding(FileReader& fileReader,
                                 SequencesGraph& sequencesGraph,
                                 unsigned short int qualityThreshold,
                                 mt4cpp::Progress* progress)
            : fileReader_(fileReader)
            , sequencesGraph_(sequencesGraph)
            , qualityThreshold_(qualityThreshold)
            , progress_(progress)
        {}

        /**
         * \brief Adds edges for paired reads to sequences graph.
         *
         * \return returns void
         */
        void operator()() {
            Read read(qualityThreshold_), pairedRead(qualityThreshold_);
            Read read2(qualityThreshold_), pairedRead2(qualityThreshold_);
            unsigned int numOfReads = fileReader_.getNumOfReads();    //sum of all reads in file(s)
            unsigned int k = 0U;
            fileReader_.reset();
            logInfo("mapping outward paired reads...");

            while (true) {
                fileReader_.readData(read, pairedRead);

                read2 = read;
                pairedRead2 = pairedRead;

                read.makeComplementaryStrand();
                read.filterReadBasedOnQuality();
                pairedRead.filterReadBasedOnQuality();

                if (read.getRead().size() < pairedRead.getRead().size())
                    pairedRead.setRead(pairedRead.getRead().substr(0, read.getRead().size()));
                else
                    read.setRead(read.getRead().substr(0, pairedRead.getRead().size()));
                sequencesGraph_.addPairedReads(read.getRead(), pairedRead.getRead());
                k+=2;

                if (progress_ != NULL)
                    progress_->setProgress(0.75 + static_cast<float>(k)/static_cast<float>(numOfReads)/8.0);

                if (k%1000==0) {
                    logInfo("processing read number: " + std::to_string(k));
                }

                pairedRead2.makeComplementaryStrand();
                read2.filterReadBasedOnQuality();
                pairedRead2.filterReadBasedOnQuality();
                if (read2.getRead().size() < pairedRead2.getRead().size())
                    pairedRead2.setRead(pairedRead2.getRead().substr(0, read2.getRead().size()));
                else
                    read2.setRead(read2.getRead().substr(0, pairedRead2.getRead().size()));
                sequencesGraph_.addPairedReads(pairedRead2.getRead(), read2.getRead());

                if (!fileReader_.getIsMoreSequences()) {
                    logInfo("adding outward paired reads done");
                    return;
                }
            }
        }

    private:
        FileReader &fileReader_;
        SequencesGraph& sequencesGraph_;
        unsigned short int qualityThreshold_;
        mt4cpp::Progress* progress_;
        OutwardPairedReadsAdding& operator=(const OutwardPairedReadsAdding&)= delete;
    };

}}

#endif    // OUTWARD_PAIRED_READS_ADDING_HPP
