#include "Lexer.hpp"
#include "../ErrorHandler.h"

enum class State
{
    Q0,
    END_OF_FILE_Q1,
    NUMBER_Q1,
    IDENTIFIER_Q1,
    SPACES_Q1,
    COMMENT_Q1,
    COMMENT_Q2,
    OPERATOR_Q1,
    OPERATOR_Q2,
    AND_Q1,
    OR_Q1,
    LESS_Q1,
};

Token Lexer::nextToken()
{
    State state = State::Q0;
    clearText();

    while (true)
    {
        switch (state)
        {
        case State::Q0:
            if (currentChar == EOF)
            {
                state = State::END_OF_FILE_Q1;
            }
            // Manejo de numeros (incluye negativos)
            else if (currentChar >= '0' && currentChar <= '9')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::NUMBER_Q1;
            }
            // Manejo de identificadores y palabras clave
            else if (currentChar >= 'a' && currentChar <= 'z' ||
                     currentChar >= 'A' && currentChar <= 'Z' ||
                     currentChar == '_')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::IDENTIFIER_Q1;
            }
            // Manejo de espacios en blanco y saltos de linea
            else if (currentChar == ' ' || currentChar == '\t' || currentChar == '\n' || currentChar == '\r')
            {
                if (currentChar == '\n')
                {
                    incrementLineNumber();
                }
                currentChar = in.get();
                state = State::Q0;
            }
            // Manejo de comentarios
            else if (currentChar == '/')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::COMMENT_Q1;
            }
            else if (currentChar == ';')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::SEMICOLON;
            }
            else if (currentChar == ',')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::COMMA;
            }
            else if (currentChar == '(')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::LEFT_PAREN;
            }
            else if (currentChar == ')')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::RIGHT_PAREN;
            }
            else if (currentChar == '{')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::LEFT_BRACE;
            }
            else if (currentChar == '}')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::RIGHT_BRACE;
            }
            else if (currentChar == '-')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::LESS_Q1;
            }
            else if (currentChar == '+' || currentChar == '*' || currentChar == '%')
            {
                char op = static_cast<char>(currentChar);
                text += op;
                currentChar = in.get();
                switch (op)
                {
                case '+':
                    return Token::ADD_OPERATOR;
                case '*':
                    return Token::MUL_OPERATOR;
                case '%':
                    return Token::MOD_OPERATOR;
                }
            }
            else if (currentChar == '=' || currentChar == '<' || currentChar == '>')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::OPERATOR_Q1;
            }
            else if (currentChar == '!')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::OPERATOR_Q2;
            }
            else if (currentChar == '&')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::AND_Q1;
            }
            else if (currentChar == '|')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::OR_Q1;
            }
            else
            {
                ErrorHandler::throwInvalidCharacterError(static_cast<char>(currentChar), getLineNumber());
            }
            break;
        case State::NUMBER_Q1:
            if (currentChar >= '0' && currentChar <= '9')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::NUMBER_Q1;
            }
            else
            {
                return Token::NUMBER;
            }
            break;

        case State::IDENTIFIER_Q1:
            if (currentChar >= 'a' && currentChar <= 'z' ||
                currentChar >= 'A' && currentChar <= 'Z' ||
                currentChar == '_' || currentChar >= '0' && currentChar <= '9')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::IDENTIFIER_Q1;
            }
            else if (currentChar == ' ' || currentChar == '\t' || currentChar == EOF ||
                     currentChar == '\n' || currentChar == '\r' || currentChar == '/')
            {
                if (text == "int")
                {
                    return Token::KEYWORD_INT;
                }
                else if (text == "print")
                {
                    return Token::KEYWORD_PRINT;
                }
                else if (text == "if")
                {
                    return Token::KEYWORD_IF;
                }
                else if (text == "else")
                {
                    return Token::KEYWORD_ELSE;
                }
                else if (text == "while")
                {
                    return Token::KEYWORD_WHILE;
                }
                else
                {
                    return Token::IDENTIFIER;
                }
            }
            else
            {
                ErrorHandler::throwInvalidCharacterError(static_cast<char>(currentChar), getLineNumber());
            }
            break;

        case State::AND_Q1:
            if (currentChar == '&')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::AND_OPERATOR;
            }
            else
            {
                ErrorHandler::throwInvalidCharacterError(static_cast<char>(currentChar), getLineNumber());
            }
            break;

        case State::OR_Q1:
            if (currentChar == '|')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::OR_OPERATOR;
            }
            else
            {
                ErrorHandler::throwInvalidCharacterError(static_cast<char>(currentChar), getLineNumber());
            }
            break;

        case State::OPERATOR_Q1:
            if (currentChar == '=')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                if (text == "<=")
                {
                    return Token::LESS_EQUAL_OPERATOR;
                }
                else if (text == ">=")
                {
                    return Token::GREATER_EQUAL_OPERATOR;
                }
                else if (text == "==")
                {
                    return Token::EQUAL_OPERATOR;
                }
            }
            else
            {
                if (text == "<")
                {
                    return Token::LESS_OPERATOR;
                }
                else if (text == ">")
                {
                    return Token::GREATER_OPERATOR;
                }
                else if (text == "=")
                {
                    return Token::ASSIGNMENT;
                }
                else
                {
                    ErrorHandler::throwInvalidCharacterError(static_cast<char>(currentChar), getLineNumber());
                }
            }
            break;

        case State::OPERATOR_Q2:
            if (currentChar == '=')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                return Token::NOT_EQUAL_OPERATOR;
            }
            else
            {
                return Token::NOT_OPERATOR;
            }
            break;

        case State::LESS_Q1:
            if (currentChar >= '0' && currentChar <= '9')
            {
                text += static_cast<char>(currentChar);
                currentChar = in.get();
                state = State::NUMBER_Q1;
            }
            else
            {
                return Token::SUB_OPERATOR;
            }
            break;

        case State::SPACES_Q1:
            if (currentChar == ' ' || currentChar == '\t' || currentChar == '\n' || currentChar == '\r')
            {
                currentChar = in.get();
                state = State::SPACES_Q1;
            }
            else
            {
                state = State::Q0;
            }
            break;

        case State::COMMENT_Q1:
            if (currentChar == '/')
            {
                currentChar = in.get();
                state = State::COMMENT_Q2;
            }
            else
            {
                return Token::DIV_OPERATOR;
            }
            break;

        case State::COMMENT_Q2:
            if (currentChar != '\n' && currentChar != EOF)
            {
                currentChar = in.get();
                state = State::COMMENT_Q2;
            }
            else
            {
                state = State::Q0;
            }
            break;

        case State::END_OF_FILE_Q1:
            return Token::END_OF_FILE;
            break;
        }
    };
}

const char *Lexer::tokenToString(Token token)
{
    switch (token)
    {
    case Token::END_OF_FILE:
        return "END_OF_FILE";
    case Token::KEYWORD_INT:
        return "KEYWORD_INT";
    case Token::NUMBER:
        return "NUMBER";
    case Token::IDENTIFIER:
        return "IDENTIFIER";
    case Token::KEYWORD_IF:
        return "KEYWORD_IF";
    case Token::KEYWORD_ELSE:
        return "KEYWORD_ELSE";
    case Token::KEYWORD_WHILE:
        return "KEYWORD_WHILE";
    case Token::KEYWORD_PRINT:
        return "KEYWORD_PRINT";
    case Token::ADD_OPERATOR:
        return "ADD_OPERATOR";
    case Token::SUB_OPERATOR:
        return "SUB_OPERATOR";
    case Token::MUL_OPERATOR:
        return "MUL_OPERATOR";
    case Token::DIV_OPERATOR:
        return "DIV_OPERATOR";
    case Token::MOD_OPERATOR:
        return "MOD_OPERATOR";
    case Token::EQUAL_OPERATOR:
        return "EQUAL_OPERATOR";
    case Token::NOT_EQUAL_OPERATOR:
        return "NOT_EQUAL_OPERATOR";
    case Token::LESS_OPERATOR:
        return "LESS_OPERATOR";
    case Token::LESS_EQUAL_OPERATOR:
        return "LESS_EQUAL_OPERATOR";
    case Token::GREATER_OPERATOR:
        return "GREATER_OPERATOR";
    case Token::GREATER_EQUAL_OPERATOR:
        return "GREATER_EQUAL_OPERATOR";
    case Token::AND_OPERATOR:
        return "AND_OPERATOR";
    case Token::OR_OPERATOR:
        return "OR_OPERATOR";
    case Token::NOT_OPERATOR:
        return "NOT_OPERATOR";
    case Token::ASSIGNMENT:
        return "ASSIGNMENT";
    case Token::SEMICOLON:
        return "SEMICOLON";
    case Token::COMMA:
        return "COMMA";
    case Token::LEFT_PAREN:
        return "LEFT_PAREN";
    case Token::RIGHT_PAREN:
        return "RIGHT_PAREN";
    case Token::LEFT_BRACE:
        return "LEFT_BRACE";
    case Token::RIGHT_BRACE:
        return "RIGHT_BRACE";
    default:
        return "UNKNOWN_TOKEN";
    }
}