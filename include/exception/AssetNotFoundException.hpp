#pragma once

#include <exception>
#include <string>

class AssetNotFoundException : public std::exception
{
    private:
        std::string m_message;
    public:
        explicit AssetNotFoundException(const std::string &message);
        const char* what() const throw() override;
};