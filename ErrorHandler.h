#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H
#include <string>

class ErrorHandler
{
public:
    static void throwInvalidCharacterError(char invalidChar, int lineNumber);
};

#endif
