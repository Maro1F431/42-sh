#ifndef LEXER_H
# define LEXER_H

#include <stddef.h>

#include "token.h"

enum pop_mode
{
    MODE_STD = 0,
    MODE_CMD
};

struct lex
{
    size_t i;
    size_t len;
    char *input;
    int malloc_input;
};

struct lex *lexer_alloc(char *str);
void lexer_free(struct lex *lexer);
struct token *lexer_peek(struct lex *lexer);
struct token *lexer_pop(struct lex *lexer);
void token_free(struct token *token);
struct token *lexer_pop_command(struct lex *lexer);

#endif /* LEXER_H */
