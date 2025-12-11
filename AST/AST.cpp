#include "AST.hpp"

namespace AST
{
    // Program
    std::string Program::toString() const
    {
        std::string s;
        for (const auto &stmt : statements)
        {
            s += stmt->toString() + "\n";
        }
        return s;
    }

    // Statement
    std::string VarDecl::toString() const
    {
        std::string s = dataTypeToString(type) + " " + getName();
        if (initializer)
        {
            s += " = " + getInitializer()->toString();
        }
        return s;
    }

    std::string Assignment::toString() const
    {
        return getName() + " = " + getValue()->toString();
    }

    std::string IfStmt::toString() const
    {
        std::string s = "if (" + getCondition()->toString() + ")" + getTrueBranch()->toString();
        if (getFalseBranch())
        {
            s += " else " + getFalseBranch()->toString();
        }
        return s;
    }

    std::string WhileStmt::toString() const
    {
        return "while (" + getCondition()->toString() + ")" + getStatement()->toString();
    }

    std::string PrintStmt::toString() const
    {
        return "print(" + getExpression()->toString() + ")";
    }

    // Expr
    std::string BinRelationalExpr::toString() const
    {
        return getLeft()->toString() + " " + relOperatorToString(getOperator()) + " " + getRight()->toString();
    }

    std::string UniRelationalExpr::toString() const
    {
        std::string s = "";
        if (getOperator() == RelationalOperator::Not)
        {
            s += relOperatorToString(getOperator()) + " ";
        }
        s += getLeft()->toString();
        return s;
    }

    std::string NumberLiteral::toString() const
    {
        return std::to_string(getValue());
    }

    std::string Identifier::toString() const
    {
        return getName();
    }
};
