#pragma once

#include <exception>
#include <string>

class InvalidUsageException: public std::exception
{
    private:
        std::string m_message;
    public:
        explicit InvalidUsageException(const std::string &message);
        const char *what() const throw() override;
};