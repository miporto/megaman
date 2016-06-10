#include "Logger.h"

Logger::Logger() : appender(NULL), layout(NULL),
                   out(CATEGORY::getInstance(APPENDER)) {
    this->init_log4cpp();
}

void Logger::init_log4cpp() {
    this->layout = new log4cpp::PatternLayout();
    this->layout->setConversionPattern("[%d] [%p] %m%n");
    this->appender = new log4cpp::RollingFileAppender(APPENDER, LOG_NAME);
    this->appender->setLayout(this->layout);
    this->out.addAppender(this->appender);
}

Logger* Logger::instance() {
    if (!l_instance)
        l_instance = new Logger();
    return l_instance;
}
