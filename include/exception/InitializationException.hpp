#pragma once

#include <exception>
#include <string>

class InitializationException : public std::exception
{
    private:
        std::string m_message;
    public:
        explicit InitializationException(const std::string &message);
        const char* what() const throw() override;
};