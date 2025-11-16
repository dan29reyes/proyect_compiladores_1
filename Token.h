enum class Token
{
    // Token para fin de archivo
    END_OF_FILE,

    // Token para manejo de numeros
    NUMBER,
    KEYWORD_INT,

    // Token para identificadores
    IDENTIFIER,

    // Tokens para condicionales y bucles
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_WHILE,

    // Token para salida
    KEYWORD_PRINT,

    // Tokens para operadores aritmeticos
    ADD_OPERATOR,
    SUB_OPERATOR,
    MUL_OPERATOR,
    DIV_OPERATOR,
    MOD_OPERATOR,

    // Tokens para operadores relacionales
    EQUAL_OPERATOR,
    NOT_EQUAL_OPERATOR,
    LESS_OPERATOR,
    LESS_EQUAL_OPERATOR,
    GREATER_OPERATOR,
    GREATER_EQUAL_OPERATOR,

    // Tokens para operadores logicos
    AND_OPERATOR,
    OR_OPERATOR,
    NOT_OPERATOR,

    // Tokens para asignacion y puntuacion
    ASSIGNMENT,

    // Tokens para puntuacion y delimitadores
    SEMICOLON,
    COMMA,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE
};