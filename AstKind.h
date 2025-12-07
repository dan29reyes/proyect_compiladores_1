enum class Kind
{
    Print,
    VarDecl,
    Assignment,
    If,
    While,
    Block,
    Number,
    Identifier,
    RelationalExpr
};

enum class RelationalOperator
{
    LessThan,
    LessThanOrEqual,
    GreaterThan,
    GreaterThanOrEqual,
    Equal,
    NotEqual,
    No_Op
};

enum class DataType
{
    Int,
};