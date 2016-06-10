#ifndef LOGGER_H
#define LOGGER_H

#define LOG4CPP_FIX_ERROR_COLLISION 1

#include "log4cpp/Category.hh"
#include "log4cpp/PropertyConfigurator.hh"
#include "log4cpp/RollingFileAppender.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/Priority.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/PatternLayout.hh"

#define LOG_NAME "log"
#define APPENDER "out"

#define ERROR log4cpp::Priority::ERROR
#define INFO log4cpp::Priority::INFO

typedef log4cpp::Category CATEGORY;

class Logger {
    private:
        log4cpp::Appender *appender;
        log4cpp::PatternLayout *layout;

        static Logger* l_instance;

        void init_log4cpp();

    public:
        CATEGORY &out;
        Logger();
        static Logger* instance();
};

#endif //LOGGER_H
