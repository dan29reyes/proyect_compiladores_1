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
    if (currToken == Token::KEYWORD_ELSE)
    {
        currToken = lexer.nextToken();
        Statement();
    }
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
    LogicalOr();
}

void Parser::LogicalOr()
{
    LogicalAnd();
    while (currToken == Token::OR_OPERATOR)
    {
        currToken = lexer.nextToken();
        LogicalAnd();
    }
}

void Parser::LogicalAnd()
{
    Equality();
    while (currToken == Token::AND_OPERATOR)
    {
        currToken = lexer.nextToken();
        Equality();
    }
}

void Parser::Equality()
{
    Comparison();
    while (currToken == Token::EQUAL_OPERATOR || currToken == Token::NOT_EQUAL_OPERATOR)
    {
        currToken = lexer.nextToken();
        Comparison();
    }
}

void Parser::Comparison()
{
    Term();
    while (currToken == Token::LESS_OPERATOR || currToken == Token::GREATER_OPERATOR || currToken == Token::LESS_EQUAL_OPERATOR || currToken == Token::GREATER_EQUAL_OPERATOR)
    {
        currToken = lexer.nextToken();
        Term();
    }
}

void Parser::Term()
{
    Factor();
    while (currToken == Token::ADD_OPERATOR || currToken == Token::SUB_OPERATOR)
    {
        currToken = lexer.nextToken();
        Factor();
    }
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