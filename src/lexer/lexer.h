#ifndef LEXER_H
# define LEXER_H

#include <stddef.h>
#include <stdio.h>

#include "token.h"

enum pop_mode
{
    MODE_STD = 0,
    MODE_CMD
};

enum input_type
{
    INTERACTIVE,
    SCRIPT,
    STRING,
    STANDARD
};

struct lex
{
    size_t i;
    size_t len;
    char *input;
    int malloc_input;

    enum input_type in_type;
    FILE *fd;
    size_t n;
    char *line_ptr;

    struct token *last_token;
};

struct lex *lexer_alloc(char *str);
void lexer_free(struct lex *lexer);
struct token *lexer_peek(struct lex *lexer);
struct token *lexer_pop(struct lex *lexer);
void token_free(struct token *token);
struct token *lexer_pop_command(struct lex *lexer);
struct token *lexer_peek_command(struct lex *lexer);

#endif /* LEXER_H */
