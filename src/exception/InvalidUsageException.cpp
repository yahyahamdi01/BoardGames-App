#include "../../include/exception/InvalidUsageException.hpp"

InvalidUsageException::InvalidUsageException(const std::string &message): m_message(message) {}

const char* InvalidUsageException::what() const throw()
{
    return m_message.c_str();
}