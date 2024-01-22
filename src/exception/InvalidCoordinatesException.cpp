#include "../../include/exception/InvalidCoordinatesException.hpp"

InvalidCoordinatesException::InvalidCoordinatesException(const std::string &message): m_message(message) {}

const char* InvalidCoordinatesException::what() const throw()
{
    return m_message.c_str();
}