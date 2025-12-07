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

    // Expr
    std::string RelationalExpr::toString() const
    {
        std::string leftStr = left->toString();
        if (op != RelationalOperator::No_Op)
        {
            std::string relOp = relOperatorToString(op);
            std::string rightStr = right->toString();
            return leftStr + " " + relOp + " " + rightStr;
        }
        else
        {
            return leftStr;
        }
    }

    std::string NumberLiteral::toString() const
    {
        return std::to_string(value);
    }

    std::string Identifier::toString() const
    {
        return name;
    }
};
