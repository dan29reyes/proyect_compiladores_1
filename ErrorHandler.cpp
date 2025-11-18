#include "ErrorHandler.h"
#include <stdexcept>
#include <sstream>

void ErrorHandler::throwInvalidCharacterError(char invalidChar, int lineNumber)
{
    std::ostringstream oss;
    oss << "Error: Invalid character '" << invalidChar << "' at line " << lineNumber << ".";
    throw std::runtime_error(oss.str());
}