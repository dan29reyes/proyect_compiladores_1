#include "Parser.hpp"
#include "../ErrorHandler.h"

void Parser::Statement()
{
    std::cout << "Parsing Statement at line " << lexer.getLineNumber() << std::endl;
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
    std::cout << "Token: " << Lexer::tokenToString(currToken) << " at line " << lexer.getLineNumber() << std::endl;
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
    std::cout << "Finished parsing VarDecl at line " << lexer.getLineNumber() << std::endl;
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
    std::cout << "Finished parsing Assignment at line " << lexer.getLineNumber() << std::endl;
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
    std::cout << "Finished parsing IfStmt at line " << lexer.getLineNumber() << std::endl;
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
    std::cout << "Finished parsing WhileStmt at line " << lexer.getLineNumber() << std::endl;
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
    std::cout << "Finished parsing PrintStmt at line " << lexer.getLineNumber() << std::endl;
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
    std::cout << "Finished parsing Block at line " << lexer.getLineNumber() << std::endl;
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
    std::cout << "Finished parsing LogicalOr at line " << lexer.getLineNumber() << std::endl;
}

void Parser::LogicalAnd()
{
    Equality();
    while (currToken == Token::AND_OPERATOR)
    {
        currToken = lexer.nextToken();
        Equality();
    }
    std::cout << "Finished parsing LogicalAnd at line " << lexer.getLineNumber() << std::endl;
}

void Parser::Equality()
{
    Comparison();
    while (currToken == Token::EQUAL_OPERATOR || currToken == Token::NOT_EQUAL_OPERATOR)
    {
        currToken = lexer.nextToken();
        Comparison();
    }
    std::cout << "Finished parsing Equality at line " << lexer.getLineNumber() << std::endl;
}

void Parser::Comparison()
{
    Term();
    while (currToken == Token::LESS_OPERATOR || currToken == Token::GREATER_OPERATOR || currToken == Token::LESS_EQUAL_OPERATOR || currToken == Token::GREATER_EQUAL_OPERATOR)
    {
        currToken = lexer.nextToken();
        Term();
    }
    std::cout << "Finished parsing Comparison at line " << lexer.getLineNumber() << std::endl;
}

void Parser::Term()
{
    Factor();
    while (currToken == Token::ADD_OPERATOR || currToken == Token::SUB_OPERATOR)
    {
        currToken = lexer.nextToken();
        Factor();
    }
    std::cout << "Finished parsing Term at line " << lexer.getLineNumber() << std::endl;
}

void Parser::Factor()
{
    Unary();
    while (currToken == Token::MUL_OPERATOR || currToken == Token::DIV_OPERATOR || currToken == Token::MOD_OPERATOR)
    {
        currToken = lexer.nextToken();
        Unary();
    }
    std::cout << "Finished parsing Factor at line " << lexer.getLineNumber() << std::endl;
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
    std::cout << "Finished parsing Unary at line " << lexer.getLineNumber() << std::endl;
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
    std::cout << "Finished parsing Primary at line " << lexer.getLineNumber() << std::endl;
}