#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#include <string>
#include <iostream>

class ErrorHandler
{
public:
    static void throwInvalidCharacterError(char invalidChar, int lineNumber);
    static void throwUnexpectedTokenError(const std::string &expected, const std::string &found);
};

#endif
