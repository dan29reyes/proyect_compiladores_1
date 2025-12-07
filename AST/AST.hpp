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
    };

    class Statement : public Node
    {
    public:
        Statement(Kind k) : Node(k) {}
    };

    // Statement Nodes
    class PrintStmt : public Statement
    {
    public:
        PrintStmt(std::unique_ptr<Expr> expr) : Statement(Kind::Print), expr(std::move(expr)) {}

    private:
        std::unique_ptr<Expr> expr;
    };

    class VarDecl : public Statement
    {
    public:
        VarDecl(const std::string &n, std::unique_ptr<Expr> init) : Statement(Kind::VarDecl), name(n), initializer(std::move(init)) {}

    private:
        std::string name;
        std::unique_ptr<Expr> initializer;
    };

    class Assignment : public Statement
    {
    public:
        Assignment(const std::string &n, std::unique_ptr<Expr> val) : Statement(Kind::Assignment), name(n), value(std::move(val)) {}

    private:
        std::string name;
        std::unique_ptr<Expr> value;
    };

    class IfStmt : public Statement
    {
    public:
        IfStmt(std::unique_ptr<Expr> cond, std::unique_ptr<Statement> trueBranch, std::unique_ptr<Statement> falseBranch = nullptr) : Statement(Kind::If), cond(std::move(cond)), whenTrueBranch(std::move(trueBranch)), whenFalseBranch(std::move(falseBranch)) {}

    private:
        std::unique_ptr<Expr> cond;
        std::unique_ptr<Statement> whenTrueBranch;
        std::unique_ptr<Statement> whenFalseBranch;
    };

    // Expression Nodes
    class NumberLiteral : public Expr
    {
    public:
        NumberLiteral(int v) : Expr(Kind::Number), value(v) {}

    private:
        int value;
    };

    class Identifier : public Expr
    {
    public:
        Identifier(const std::string &n) : Expr(Kind::Identifier), name(n) {}

    private:
        std::string name;
    };

    class RelationalExpr : public Expr
    {
    public:
        RelationalExpr(RelationalOperator op, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) : Expr(Kind::RelationalExpr), op(op), left(std::move(l)), right(std::move(r)) {}

    private:
        RelationalOperator op;
        std::unique_ptr<Expr> left;
        std::unique_ptr<Expr> right;
    };

};