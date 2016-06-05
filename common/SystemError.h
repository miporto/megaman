#ifndef SYSTEMERROR_H
#define SYSTEMERROR_H

#include <exception>
#include <string>

class SystemError : public std::exception {
    private:
        const std::string error_msg;

    public:
        explicit SystemError(const std::string error_msg) throw();
        const char* what() const throw();
        ~SystemError() throw();
};


#endif //SYSTEMERROR_H
