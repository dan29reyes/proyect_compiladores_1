#include <memory>
#include "../AstKind.h"
#include <string>

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

    using NodePtr = std::unique_ptr<Node>;

    // Nodes
    class Expr : public Node
    {
    public:
        Expr(Kind k) : Node(k) {}
        virtual std::string toString() const override = 0;
    };

    class Statement : public Node
    {
    public:
        Statement(Kind k) : Node(k) {}
        virtual std::string toString() const override = 0;
    };

    // Statement Nodes
    class VarDecl : public Statement
    {
    public:
        VarDecl(const std::string &n, std::unique_ptr<Expr> init = nullptr) : Statement(Kind::VarDecl), name(n), initializer(std::move(init)) {}
        virtual std::string toString() const override;

    private:
        std::string name;
        std::unique_ptr<Expr> initializer;
    };

    class Assignment : public Statement
    {
    public:
        Assignment(const std::string &n, std::unique_ptr<Expr> val) : Statement(Kind::Assignment), name(n), value(std::move(val)) {}
        virtual std::string toString() const override;

    private:
        std::string name;
        std::unique_ptr<Expr> value;
    };

    class IfStmt : public Statement
    {
    public:
        IfStmt(std::unique_ptr<Expr> cond, std::unique_ptr<Statement> trueBranch, std::unique_ptr<Statement> falseBranch = nullptr) : Statement(Kind::If), cond(std::move(cond)), whenTrueBranch(std::move(trueBranch)), whenFalseBranch(std::move(falseBranch)) {}
        virtual std::string toString() const override;

    private:
        std::unique_ptr<Expr> cond;
        std::unique_ptr<Statement> whenTrueBranch;
        std::unique_ptr<Statement> whenFalseBranch;
    };

    class WhileStmt : public Statement
    {
    public:
        WhileStmt(std::unique_ptr<Expr> cond, std::unique_ptr<Statement> stmt) : Statement(Kind::While), cond(std::move(cond)), stmt(std::move(stmt)) {}
        virtual std::string toString() const override;

    private:
        std::unique_ptr<Expr> cond;
        std::unique_ptr<Statement> stmt;
    };

    class PrintStmt : public Statement
    {
    public:
        PrintStmt(std::unique_ptr<Expr> expr) : Statement(Kind::Print), expr(std::move(expr)) {}
        virtual std::string toString() const override;

    private:
        std::unique_ptr<Expr> expr;
    };

    // Expression Nodes
    class NumberLiteral : public Expr
    {
    public:
        NumberLiteral(int v) : Expr(Kind::Number), value(v) {}
        virtual std::string toString() const override;

    private:
        int value;
    };

    class Identifier : public Expr
    {
    public:
        Identifier(const std::string &n) : Expr(Kind::Identifier), name(n) {}
        virtual std::string toString() const override;

    private:
        std::string name;
    };

    class RelationalExpr : public Expr
    {
    public:
        RelationalExpr(RelationalOperator op, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) : Expr(Kind::RelationalExpr), op(op), left(std::move(l)), right(std::move(r)) {}
        virtual std::string toString() const override;

    private:
        RelationalOperator op;
        std::unique_ptr<Expr> left;
        std::unique_ptr<Expr> right;
    };

};