#pragma once

#include <exception>
#include <string>

class PathNotFoundException: public std::exception
{
    private:
        std::string m_message;
    public:
        explicit PathNotFoundException(const std::string &message);
        const char *what() const noexcept override;
};