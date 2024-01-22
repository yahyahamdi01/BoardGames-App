#include "../../include/exception/InitializationException.hpp"

InitializationException::InitializationException(const std::string &message): m_message(message) {}

const char* InitializationException::what() const throw()
{
    return m_message.c_str();
}