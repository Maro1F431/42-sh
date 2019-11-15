#ifndef LEXER_H
# define LEXER_H

#define NB_TOKENS 35

#include <stddef.h>

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

struct token_map
{
    char *input;
    enum token_type type;
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

struct lex *lexer_alloc(const char *str);
void lexer_free(struct lex *lexer);
struct token *lexer_peek(struct lex *lexer);
struct token *lexer_pop(struct lex *lexer);
void token_free(struct token *token);

#endif /* LEXER_H */
