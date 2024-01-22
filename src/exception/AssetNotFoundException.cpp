#include "../../include/exception/AssetNotFoundException.hpp"

AssetNotFoundException::AssetNotFoundException(const std::string &message): m_message(message) {}

const char* AssetNotFoundException::what() const throw()
{
    return m_message.c_str();
}