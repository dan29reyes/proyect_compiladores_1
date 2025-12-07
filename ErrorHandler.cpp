#include "ErrorHandler.hpp"
#include <stdexcept>
#include <sstream>

void ErrorHandler::throwInvalidCharacterError(char invalidChar, int lineNumber)
{
    std::ostringstream oss;
    oss << "Error: Invalid character '" << invalidChar << "' at line " << lineNumber << ".";
    throw std::runtime_error(oss.str());
}

void ErrorHandler::throwUnexpectedTokenError(const std::string &expected, const std::string &found)
{
    std::ostringstream oss;
    oss << "Error: Unexpected token. Expected '" << expected << "', but found '" << found << "'.";
    throw std::runtime_error(oss.str());
}