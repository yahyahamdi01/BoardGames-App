#include "../../include/exception/PathNotFoundException.hpp"

PathNotFoundException::PathNotFoundException(const std::string &message): m_message(message) {}

const char *PathNotFoundException::what() const noexcept
{
    return m_message.c_str();
}