# ifndef LEXER_H
# define LEXER_H

#define NB_TOKENS 38


enum token_type
{
    END_OF_FILE = 0,
    IONUMBER,
    WORD,
    HEREDOC,
    ASSIGNMENT_WORD,
    LINE_BREAK,
    SEMICOL,
    DOUBLE_SEMICOL,
    AMPERSAND,
    DOUBLE_AMPERSAND,
    PIPE,
    DOUBLE_PIPE,
    EXCLAMATION,
    OPEN_CURLY_BRACKET,
    CLOSE_CURLY_BRACKET,
    OPEN_PAR,
    CLOSE_PAR,
    FUNCTION,
    CHEV_SIMPLE_R,
    CHEV_SIMPLE_L,
    CHEV_DOUBLE_R,
    CHEV_DOUBLE_L,
    CHEV_DOUBLE_H,
    CHEV_AMP_R,
    CHEV_AMP_L,
    CHEV_PIPE,
    LEFT_RIGHT,
    WHILE,
    UNTIL,
    CASE,
    ESAC,
    IN,
    IF,
    FI,
    THEN,
    ELSE,
    ELIF,
    DO,
    DONE
};



struct token_type_map[NB_TOKENS]
{
    {
        .input "\0",
        .type END_OF_FILE
    },
    {
        .input "\n",
        .type LINE_BREAK
    },
    {
        .input ";",
        .type SEMICOL
    },
    {
        .input ";;",
        .type DOUBLE_SEMICOL
    },
    {
        .input "&",
        .type AMPERSAND
    },
    {
        .input "&&",
        .type DOUBLE_AMPERSAND
    },
    {
        .input "|",
        .type PIPE
    },
    {
        .input "||",
        .type DOUBLE_PIPE
    },
    {
        .input "!",
        .type EXCLAMATION
    },
    {
        .input "{",
        .type OPEN_CURLY_BRACKET
    },
    {
        .input "}",
        .type CLOSE_CURLY_BRACKET
    },
    {
        .input "(",
        .type OPEN_PAR
    },
    {
        .input ")",
        .type CLOSE_PAR
    },
    {
        .input "function",
        .type FUNCTION
    },
    {
        .input ">",
        .type CHEV_SIMPLE_R
    },
    {
        .input "<",
        .type CHEV_SIMPLE_L
    },
    {
        .input ">>",
        .type CHEV_DOUBLE_R
    },
    {
        .input "<<",
        .type CHEV_DOUBLE_L
    },
    {
        .input "<<-",
        .type CHEV_DOUBLE_H
    },
    {
        .input ">&",
        .type CHEV_AMP_R
    },
    {
        .input "<&",
        .type CHEV_AMP_L
    },
    {
        .input ">|",
        .type CHEV_PIPE
    },
    {
        .input "<>",
        .type LEFT_RIGHT
    },
    {
        .input "while",
        .type WHILE
    },
    {
        .input "until",
        .type UNTIL
    },
    {
        .input "case",
        .type CASE
    },
    {
        .input "esac",
        .type ESAC
    },
    {
        .input "in",
        .type IN
    },
    {
        .input "if",
        .type IF
    },
    {
        .input "fi",
        .type FI
    },
    {
        .input "then",
        .type THEN
    },
    {
        .input "else",
        .type ELSE
    },
    {
        .input "elif",
        .type ELIF
    },
    {
        .input "do",
        .type DO
    },
    {
        .input "done",
        .type DONE
    }
};

struct token_map
{
    char *input;
    enum token_type *type;
};

struct token
{
    char *value;
    enum token_type type;
    struct token *next;
};

struct lex
{
    struct token *head;
};

#endif /* LEXER_H */
