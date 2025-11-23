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

    // Instrucciones
    void Statement();
    void VarDecl();
    void Assignment();
    void IfStmt();
    void WhileStmt();
    void PrintStmt();
    void Block();

    // Expresiones
    void Expression();
    void LogicalOr();
    void LogicalAnd();
    void Equality();
    void Comparison();
    void Term();
    void Factor();
    void Unary();
    void Primary();
};