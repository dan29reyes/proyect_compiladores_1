#include "AST.hpp"

namespace AST
{
    // Statement
    std::string VarDecl::toString() const
    {
        std::string s = dataTypeToString(type) + " " + name;
        if (initializer)
        {
            s += " = " + initializer->toString();
        }
        return s;
    }

    std::string Assignment::toString() const
    {
        return name + " = " + value->toString();
    }

    std::string IfStmt::toString() const
    {
        std::string s = "if (" + cond->toString() + ")" + whenTrueBranch->toString();
        if (whenFalseBranch)
        {
            s += " else " + whenFalseBranch->toString();
        }
        return s;
    }

    std::string WhileStmt::toString() const
    {
        return "while (" + cond->toString() + ")" + stmt->toString();
    }

    std::string PrintStmt::toString() const
    {
        return "print(" + expr->toString() + ")";
    }

    std::string NumberLiteral::toString() const
    {
        return std::to_string(value);
    }

    std::string Identifier::toString() const
    {
        return name;
    }

    // Expr
    std::string RelationalExpr::toString() const
    {
        
    }
};
