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
    if (currToken != Token::KEYWORD_INT)
    {
        ErrorHandler::throwUnexpectedTokenError("int", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
    if (currToken != Token::IDENTIFIER)
    {
        ErrorHandler::throwUnexpectedTokenError("identifier", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
    if (currToken == Token::ASSIGNMENT)
    {
        currToken = lexer.nextToken();
        Expression();
    }
    else if (currToken != Token::SEMICOLON)
    {
        ErrorHandler::throwUnexpectedTokenError("= or ;", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
}

void Parser::Assignment()
{
    if (currToken != Token::IDENTIFIER)
    {
        ErrorHandler::throwUnexpectedTokenError("identifier", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
    if (currToken != Token::ASSIGNMENT)
    {
        ErrorHandler::throwUnexpectedTokenError("=", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
    Expression();
    if (currToken != Token::SEMICOLON)
    {
        ErrorHandler::throwUnexpectedTokenError(";", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
}

void Parser::IfStmt()
{
    if (currToken != Token::KEYWORD_IF)
    {
        ErrorHandler::throwUnexpectedTokenError("if", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
    if (currToken != Token::LEFT_PAREN)
    {
        ErrorHandler::throwUnexpectedTokenError("(", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
    Expression();
    if (currToken != Token::RIGHT_PAREN)
    {
        ErrorHandler::throwUnexpectedTokenError(")", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
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