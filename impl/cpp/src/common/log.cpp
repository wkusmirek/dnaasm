/**
 * \file log.cpp
 * \brief the C++ logger implementation
 */

#include "log.hpp"

/** Allows building library as dynamically loaded library ("dll" or "so" for Unix)*/
#define BOOST_LOG_DYN_LINK 1

#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>

using namespace std;

namespace dnaasm {
    /** log info message */
    void logInfo(const std::string& msg) {
        boost::log::sources::severity_logger_mt< boost::log::trivial::severity_level > lg;
        BOOST_LOG_SEV(lg, boost::log::trivial::info) << msg;
    }

    /** log warning message */
    void logWarning(const std::string& msg) {
        boost::log::sources::severity_logger_mt< boost::log::trivial::severity_level > lg;
        BOOST_LOG_SEV(lg, boost::log::trivial::warning) << msg;
    }

    /** log error message */
    void logError(const std::string& msg) {
        boost::log::sources::severity_logger_mt< boost::log::trivial::severity_level > lg;
        BOOST_LOG_SEV(lg, boost::log::trivial::error) << msg;
    }

    /** init logging library - set logger file path */
    void initCalcModule() {
        /** Create a text file sink */
        typedef boost::log::sinks::synchronous_sink< boost::log::sinks::text_file_backend > file_sink;
        boost::shared_ptr< file_sink >
            sink(new file_sink(boost::log::keywords::file_name = std::string(STR(LOG_CPP_LOC))+ "dnaasm_calc_%N.log",    // file name pattern
                boost::log::keywords::rotation_size = 5 * 1024 * 1024,    // rotation size, in characters
                boost::log::keywords::auto_flush = true));

        sink->set_formatter(boost::log::expressions::format("[%1%] [%2%] - %3%")
                % boost::log::expressions::attr< boost::posix_time::ptime >("TimeStamp")
                % boost::log::trivial::severity
                % boost::log::expressions::smessage);

        // Severity level
        sink->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);

        boost::log::core::get()->add_global_attribute("TimeStamp", boost::log::attributes::local_clock());
        boost::log::core::get()->add_sink(sink);
    }
}
