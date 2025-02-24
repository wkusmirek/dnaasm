/**
 * \file Parameters.hpp
 * \brief the C++ file with declaration of interface for representing parameters specified by user
 *
 */

#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

#include "common.hpp"
#include <map>
#include <set>

namespace dnaasm { namespace common {
    /**
     * \brief Class to represent parameters specified by user (only for desktop application).
     */
    class Parameters {
    public:
        using ParametersMap = std::map<std::string, std::string>;

        static const std::set<std::string> modesAllowed;

        CALC_DLL(Parameters(ParametersMap& parameters);)

        virtual ~Parameters() {}

        /**
         * \brief Converts parameters (argv to map).
         *
         * \param argc number of arguments
         * \param argv an array of char* arguments
         * \return returns void
         */
        CALC_DLL(static ParametersMap convertArgvToMap(int argc, const char* argv[]);)

        /**
         * \brief Prints detailed help instruction of selected module for user.
         *
         * \return returns void
         */
        CALC_DLL(static void printHelpForModule();)

        /**
         * \brief Gets mode of the application.
         *
         * \return returns mode of the application
         */
        CALC_DLL(const char * getMode() const;)

        /**
         * \brief Gets output file name.
         *
         * \return returns output file name
         */
        CALC_DLL(std::string getOutputFileName() const;)

        /**
         * \brief Gets print_help flag.
         *
         * \return returns print_help flag
         */
        CALC_DLL(bool getPrintHelp() const;)

    protected:
        const char* mode_;
        std::string output_file_name_;
        bool print_help_;

        /**
         * \brief Initializes parameters to default values.
         *
         * \return returns void
         */
        CALC_DLL(virtual void initParameters();)

    private:
        //std::map<std::string, std::string> parameters_;

        /**
        * \brief Services parameters specifed by the user.
        *
        * \return returns void
        */
        CALC_DLL(virtual void parametersService(ParametersMap &);)
    };

}}

#endif    //PARAMETERS
