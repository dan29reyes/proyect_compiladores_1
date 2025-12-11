#include <memory>
#include "../AstKind.h"
#include <string>
#include <vector>

namespace AST
{
    class Node
    {
    public:
        Node(Kind k) : kind(k) {}
        virtual ~Node() = default;

        virtual std::string toString() const = 0;
        Kind getKind() const { return kind; }

    private:
        Kind kind;
    };

    class Node;
    using NodePtr = std::unique_ptr<Node>;
    class Expr;
    using ExprPtr = std::unique_ptr<Expr>;
    class Statement;
    using StatementPtr = std::unique_ptr<Statement>;

    // Nodes
    class Program : public Node
    {
    private:
        std::vector<StatementPtr> statements;

    public:
        Program(std::vector<StatementPtr> stmts) : Node(Kind::Program), statements(std::move(stmts)) {}
        const std::vector<StatementPtr> &getStatements() const { return statements; }
        std::string toString() const override;
    };

    class Expr : public Node
    {
    public:
        Expr(Kind k) : Node(k) {}
    };

    class Statement : public Node
    {
    public:
        Statement(Kind k) : Node(k) {}
    };

    // Statement Nodes
    class VarDecl : public Statement
    {
    public:
        VarDecl(DataType t, const std::string &n, ExprPtr init = nullptr) : Statement(Kind::VarDecl), type(t), name(n), initializer(std::move(init)) {}

        std::string toString() const override;
        DataType getType() const { return type; }
        std::string getName() const { return name; }
        const Expr *getInitializer() const { return initializer.get(); }

    private:
        DataType type;
        std::string name;
        ExprPtr initializer;
    };

    class Assignment : public Statement
    {
    public:
        Assignment(const std::string &n, ExprPtr val) : Statement(Kind::Assignment), name(n), value(std::move(val)) {}

        std::string toString() const override;
        std::string getName() const { return name; }
        const Expr *getValue() const { return value.get(); }

    private:
        std::string name;
        ExprPtr value;
    };

    class IfStmt : public Statement
    {
    public:
        IfStmt(ExprPtr cond, StatementPtr trueBranch, StatementPtr falseBranch = nullptr) : Statement(Kind::If), cond(std::move(cond)), whenTrueBranch(std::move(trueBranch)), whenFalseBranch(std::move(falseBranch)) {}

        std::string toString() const override;
        const Expr *getCondition() const { return cond.get(); }
        const Statement *getTrueBranch() const { return whenTrueBranch.get(); }
        const Statement *getFalseBranch() const { return whenFalseBranch.get(); }

    private:
        ExprPtr cond;
        StatementPtr whenTrueBranch;
        StatementPtr whenFalseBranch;
    };

    class WhileStmt : public Statement
    {
    public:
        WhileStmt(ExprPtr cond, StatementPtr stmt) : Statement(Kind::While), cond(std::move(cond)), stmt(std::move(stmt)) {}

        std::string toString() const override;
        const Expr *getCondition() const { return cond.get(); }
        const Statement *getStatement() const { return stmt.get(); }

    private:
        ExprPtr cond;
        StatementPtr stmt;
    };

    class ForStmt : public Statement
    {
    public:
        ForStmt(VarDecl contVar, ExprPtr cond, Assignment incVar, StatementPtr stmt) : Statement(Kind::For), controlVar(std::move(contVar)), condition(std::move(cond)), incrementVar(std::move(incVar)), stmt(std::move(stmt)) {}
        std::string toString() const override;
        const VarDecl &getControlVar() const { return controlVar; }
        const Expr *getCondition() const { return condition.get(); }
        const Assignment &getIncrementVar() const { return incrementVar; }
        const Statement *getStatement() const { return stmt.get(); }

    private:
        VarDecl controlVar;
        ExprPtr condition;
        Assignment incrementVar;
        StatementPtr stmt;
    };

    class PrintStmt : public Statement
    {
    public:
        PrintStmt(ExprPtr expr) : Statement(Kind::Print), expr(std::move(expr)) {}

        std::string toString() const override;
        const Expr *getExpression() const { return expr.get(); }

    private:
        ExprPtr expr;
    };

    class BlockStmt : public Statement
    {
    public:
        BlockStmt(std::vector<StatementPtr> stmts) : Statement(Kind::Block), stmts(std::move(stmts)) {}

        std::string toString() const override;
        const std::vector<StatementPtr> &getStatements() const { return stmts; }

    private:
        std::vector<StatementPtr> stmts;
    };

    // Expression Nodes
    class NumberLiteral : public Expr
    {
    public:
        NumberLiteral(int v) : Expr(Kind::Number), value(v) {}

        std::string toString() const override;
        int getValue() const { return value; }

    private:
        int value;
    };

    class Identifier : public Expr
    {
    public:
        Identifier(const std::string &n) : Expr(Kind::Identifier), name(n) {}

        std::string toString() const override;
        std::string getName() const { return name; }

    private:
        std::string name;
    };

    class RecursiveExpr : public Expr
    {
    public:
        RecursiveExpr(ExprPtr l, AritmeticOperator op, ExprPtr r) : Expr(Kind::AritmeticExpr), op(op), left(std::move(l)), right(std::move(r)) {}

        std::string toString() const override;
        const Expr *getLeftExpr() const { return left.get(); }
        const Expr *getRightExpr() const { return right.get(); }
        AritmeticOperator getOperator() const { return op; }

    private:
        AritmeticOperator op;
        ExprPtr left;
        ExprPtr right;
    };

    class BinRelationalExpr : public Expr
    {
    public:
        BinRelationalExpr(ExprPtr l, RelationalOperator op, ExprPtr r) : Expr(Kind::RelationalExpr), op(op), left(std::move(l)), right(std::move(r)) {}

        std::string toString() const override;
        RelationalOperator getOperator() const { return op; }
        const Expr *getLeft() const { return left.get(); }
        const Expr *getRight() const { return right.get(); }

    private:
        RelationalOperator op;
        ExprPtr left;
        ExprPtr right;
    };

    class UniRelationalExpr : public Expr
    {
    public:
        UniRelationalExpr(RelationalOperator op, ExprPtr l) : Expr(Kind::RelationalExpr), op(op), left(std::move(l)) {}

        std::string toString() const override;
        RelationalOperator getOperator() const { return op; }
        const Expr *getLeft() const { return left.get(); }

    private:
        RelationalOperator op;
        ExprPtr left;
    };

    inline std::string dataTypeToString(DataType t)
    {
        switch (t)
        {
        case DataType::Int:
            return "int";
        default:
            return "UnknownType";
        }
    }

    inline std::string relOperatorToString(RelationalOperator op)
    {
        switch (op)
        {
        case RelationalOperator::Equal:
            return "==";
        case RelationalOperator::GreaterThan:
            return ">";
        case RelationalOperator::GreaterThanOrEqual:
            return ">=";
        case RelationalOperator::LessThan:
            return "<";
        case RelationalOperator::LessThanOrEqual:
            return "<=";
        case RelationalOperator::NotEqual:
            return "!=";
        case RelationalOperator::Not:
            return "!";
        default:
            return "UnknownOp";
        }
    }

    inline std::string aritOperatorToString(AritmeticOperator op)
    {
        switch (op)
        {
        case AritmeticOperator::Add:
            return "+";
        case AritmeticOperator::Subtract:
            return "-";
        case AritmeticOperator::Multiply:
            return "*";
        case AritmeticOperator::Divide:
            return "/";
        default:
            return "UnknownAritOp";
        }
    }
};