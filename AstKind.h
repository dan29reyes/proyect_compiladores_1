enum class Kind
{
    Program,
    Print,
    VarDecl,
    Assignment,
    If,
    While,
    For,
    Block,
    Number,
    Identifier,
    RelationalExpr,
    AritmeticExpr
};

enum class RelationalOperator
{
    LessThan,
    LessThanOrEqual,
    GreaterThan,
    GreaterThanOrEqual,
    Equal,
    NotEqual,
    Not
};

enum class AritmeticOperator
{
    Add,
    Subtract,
    Multiply,
    Divide
};

enum class DataType
{
    Int,
};