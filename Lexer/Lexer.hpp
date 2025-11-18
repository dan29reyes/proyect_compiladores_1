#include <istream>
#include <string>
#include "../Token.h"

class Lexer
{
public:
    Lexer(std::istream &in_) : in(in_)
    {
        currentChar = in.get();
    }

    std::string getText() const { return text; }

    void clearText() { text.clear(); }

    Token nextToken();

    static const char *tokenToString(Token token);

    int getLineNumber() const { return lineNumber; }

    void incrementLineNumber() { ++lineNumber; }

private:
    std::istream &in;
    std::string text;
    int currentChar;
    int lineNumber = 1;
};