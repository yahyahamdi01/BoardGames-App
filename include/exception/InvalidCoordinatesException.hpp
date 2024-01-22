#pragma once

#include <exception>
#include <string>

class InvalidCoordinatesException : public std::exception
{
    private:
        std::string m_message;
    public:
        explicit InvalidCoordinatesException(const std::string &message);
        const char* what() const throw() override;
};