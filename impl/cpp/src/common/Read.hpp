/**
 * \file Read.hpp
 * \brief the C++ file with declaration of class for representing single read with quality
 *
 */

#ifndef READ_HPP
#define READ_HPP

#include <string>
#include <algorithm>

#include "common.hpp"

#define LOWEST_QUALITY_ASCII 33

namespace dnaasm {
    /**
     * \brief Class to represent single read with quality.
     */
    class Read {
    public:
        /**
         * \brief Read constructor.
         *
         */
        CALC_DLL(explicit Read();)
        /**
         * \brief Read constructor.
         *
         * \param threshold quality threshold value (0-93)
         */
        CALC_DLL(explicit Read(unsigned short int threshold);)

        /**
        * \brief Makes complementary strand from read.
        *
        * \return returns code of error or 0
        */
        CALC_DLL(int makeComplementaryStrand();)

        /**
        * \brief Filters single read. Filtering is based on quality for this read.
        *
        * \return returns void
        */
        CALC_DLL(void filterReadBasedOnQuality();)

        /**
         * \brief Gets read.
         *
         * \return returns read
         */
        CALC_DLL(std::string getRead() const;)

        /**
         * \brief Sets read value.
         *
         * \param read read value
         * \return returns void
         */
        CALC_DLL(void setRead(std::string read);)

        /**
         * \brief Gets quality of read.
         *
         * \return returns quality of read
         */
        CALC_DLL(std::string getQuality() const;)

        /**
         * \brief Sets quality value.
         *
         * \param quality quality value
         * \return returns void
         */
        CALC_DLL(void setQuality(std::string quality);)

        /**
         * \brief Gets description of read.
         *
         * \return returns description of read
         */
        CALC_DLL(std::string getDescription() const;)

        /**
         * \brief Sets description value.
         *
         * \param description description value
         * \return returns void
         */
        CALC_DLL(void setDescription(std::string description);)


    private:
        std::string read_;
        std::string quality_;
        std::string description_;
        unsigned short int threshold_;
        //Read& operator=(const Read&)= delete;
    };

}

#endif    //READ
