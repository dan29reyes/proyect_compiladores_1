#include <string>
#include "AST.hpp"
#include <vector>
#include <conio.h>
#include <iostream>

int main()
{
    std::vector<AST::StatementPtr> statements;
    statements.push_back(std::make_unique<AST::Assignment>("x", std::make_unique<AST::NumberLiteral>(10)));
    statements.push_back(std::make_unique<AST::Assignment>("y", std::make_unique<AST::NumberLiteral>(20)));
    statements.push_back(std::make_unique<AST::PrintStmt>(std::make_unique<AST::Identifier>("x")));
    statements.push_back(std::make_unique<AST::PrintStmt>(std::make_unique<AST::Identifier>("y")));
    AST::ExprPtr exptr = std::make_unique<AST::BinRelationalExpr>(
        std::make_unique<AST::Identifier>("x"),
        RelationalOperator::Equal,
        std::make_unique<AST::Identifier>("x"));

    statements.push_back(
        std::make_unique<AST::IfStmt>(
            std::move(exptr),
            std::make_unique<AST::PrintStmt>(std::make_unique<AST::Identifier>("y")),
            std::make_unique<AST::PrintStmt>(std::make_unique<AST::Identifier>("x"))
        )
    );

    AST::Program program(std::move(statements));
    std::string programStr = program.toString();
    std::cout << programStr << std::endl;
    _getch();
    return 0;
}