#include <string>

#include "SystemError.h"

SystemError::SystemError(const std::string error_msg) throw()
        : error_msg(error_msg) {}

const char* SystemError::what() const throw() { return error_msg.c_str(); }

SystemError::~SystemError() throw() {}
