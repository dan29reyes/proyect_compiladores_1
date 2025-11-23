#pragma once
#include "../Lexer/Lexer.hpp"
#include <string>

class Parser
{
public:
    Parser(std::istream &in) : lexer(in)
    {
        currToken = lexer.nextToken();
        while (currToken != Token::END_OF_FILE)
        {
            currToken = lexer.nextToken();
        }
    }
    ~Parser();

private:
    Lexer lexer;
    Token currToken;
};