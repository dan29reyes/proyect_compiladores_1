#include "Parser.hpp"
#include "../ErrorHandler.h"

void Parser::Statement()
{
    switch (currToken)
    {
    case Token::KEYWORD_INT:
        VarDecl();
        break;
    case Token::IDENTIFIER:
        Assignment();
        break;
    case Token::KEYWORD_IF:
        IfStmt();
        break;
    case Token::KEYWORD_WHILE:
        WhileStmt();
        break;
    case Token::KEYWORD_PRINT:
        PrintStmt();
        break;
    case Token::LEFT_BRACE:
        Block();
        break;
    default:
        ErrorHandler::throwUnexpectedTokenError("a valid statement", Lexer::tokenToString(currToken));
        break;
    }
}

void Parser::VarDecl()
{
}

void Parser::Assignment()
{
}

void Parser::IfStmt()
{
}

void Parser::WhileStmt()
{
}

void Parser::PrintStmt()
{
}

void Parser::Block()
{
}

void Parser::Expression()
{
}

void Parser::LogicalOr()
{
}

void Parser::LogicalAnd()
{
}

void Parser::Equality()
{
}

void Parser::Comparison()
{
}

void Parser::Term()
{
}

void Parser::Factor()
{
}

void Parser::Unary()
{
}

void Parser::Primary()
{
}