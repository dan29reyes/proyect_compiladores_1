#include <string>
#include "AST.hpp"
#include <vector>
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

    // Block statement del if
    std::vector<AST::StatementPtr> trueBlock;
    trueBlock.push_back(std::make_unique<AST::PrintStmt>(std::make_unique<AST::Identifier>("x")));
    trueBlock.push_back(std::make_unique<AST::PrintStmt>(std::make_unique<AST::Identifier>("y")));

    // Block statement del else
    std::vector<AST::StatementPtr> falseBlock;
    falseBlock.push_back(std::make_unique<AST::PrintStmt>(std::make_unique<AST::Identifier>("y")));

    statements.push_back(
        std::make_unique<AST::IfStmt>(
            std::move(exptr),
            std::make_unique<AST::BlockStmt>(std::move(trueBlock)),
            std::make_unique<AST::BlockStmt>(std::move(falseBlock))));

    // Prueba de While
    AST::ExprPtr whileCond = std::make_unique<AST::BinRelationalExpr>(
        std::make_unique<AST::Identifier>("x"),
        RelationalOperator::LessThan,
        std::make_unique<AST::NumberLiteral>(15));

    // Block statement del while
    std::vector<AST::StatementPtr> whileBlock;
    whileBlock.push_back(std::make_unique<AST::PrintStmt>(std::make_unique<AST::Identifier>("x")));
    whileBlock.push_back(std::make_unique<AST::Assignment>(
        "x",
        std::make_unique<AST::BinRelationalExpr>(
            std::make_unique<AST::Identifier>("x"),
            RelationalOperator::GreaterThan,
            std::make_unique<AST::NumberLiteral>(-1)))); // x = x + 1
    statements.push_back(
        std::make_unique<AST::WhileStmt>(
            std::move(whileCond),
            std::make_unique<AST::BlockStmt>(std::move(whileBlock))));

    // Block statement del For
    std::vector<AST::StatementPtr> forBlock;
    forBlock.push_back(std::make_unique<AST::PrintStmt>(std::make_unique<AST::Identifier>("x")));
    forBlock.push_back(std::make_unique<AST::Assignment>(
        "x",
        std::make_unique<AST::RecursiveExpr>(
            std::make_unique<AST::Identifier>("x"),
            AritmeticOperator::Add,
            std::make_unique<AST::NumberLiteral>(1)))); // x = x + 1

    AST::VarDecl controlVar(DataType::Int, "i", std::make_unique<AST::NumberLiteral>(0));
    
    AST::ExprPtr forCond = std::make_unique<AST::BinRelationalExpr>(
        std::make_unique<AST::Identifier>("i"),
        RelationalOperator::LessThan,
        std::make_unique<AST::NumberLiteral>(5));

    AST::Assignment incrementVar(
        "i", 
        std::make_unique<AST::RecursiveExpr>(
            std::make_unique<AST::Identifier>("i"),
            AritmeticOperator::Add,
            std::make_unique<AST::NumberLiteral>(1))); // i = i + 1

    statements.push_back(
        std::make_unique<AST::ForStmt>(
            std::move(controlVar),
            std::move(forCond),
            std::move(incrementVar),
            std::make_unique<AST::BlockStmt>(std::move(forBlock))));

    AST::Program program(std::move(statements));
    std::string programStr = program.toString();
    std::cout << programStr << std::endl;
    return 0;
}