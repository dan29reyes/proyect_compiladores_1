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
    Statement();
}

void Parser::WhileStmt()
{
    if (currToken != Token::KEYWORD_WHILE)
    {
        ErrorHandler::throwUnexpectedTokenError("while", Lexer::tokenToString(currToken));
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
    Statement();
}

void Parser::PrintStmt()
{
    if (currToken != Token::KEYWORD_PRINT)
    {
        ErrorHandler::throwUnexpectedTokenError("print", Lexer::tokenToString(currToken));
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
    if (currToken != Token::SEMICOLON)
    {
        ErrorHandler::throwUnexpectedTokenError(";", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
}

void Parser::Block()
{
    if (currToken != Token::LEFT_BRACE)
    {
        ErrorHandler::throwUnexpectedTokenError("{", Lexer::tokenToString(currToken));
    }
    currToken = lexer.nextToken();
    while (currToken != Token::RIGHT_BRACE)
    {
        Statement();
    }
    currToken = lexer.nextToken();
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
    Unary();
    while (currToken == Token::MUL_OPERATOR || currToken == Token::DIV_OPERATOR || currToken == Token::MOD_OPERATOR)
    {
        currToken = lexer.nextToken();
        Unary();
    }
}

void Parser::Unary()
{
    if (currToken == Token::NOT_OPERATOR || currToken == Token::SUB_OPERATOR)
    {
        currToken = lexer.nextToken();
        Unary();
    }
    else
    {
        Primary();
    }
}

void Parser::Primary()
{
    if (currToken == Token::NUMBER || currToken == Token::IDENTIFIER)
    {
        currToken = lexer.nextToken();
    }
    else if (currToken == Token::LEFT_PAREN)
    {
        currToken = lexer.nextToken();
        Expression();
        if (currToken != Token::RIGHT_PAREN)
        {
            ErrorHandler::throwUnexpectedTokenError(")", Lexer::tokenToString(currToken));
        }
        currToken = lexer.nextToken();
    }
    else
    {
        ErrorHandler::throwUnexpectedTokenError("a primary expression", Lexer::tokenToString(currToken));
    }
}