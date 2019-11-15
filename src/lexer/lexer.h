#ifndef LEXER_H
# define LEXER_H

#include <stddef.h>

#include "token.h"

struct lex
{
    struct token *head;
};

struct lex *lexer_alloc(const char *str);
void lexer_free(struct lex *lexer);
struct token *lexer_peek(struct lex *lexer);
struct token *lexer_pop(struct lex *lexer);

#endif /* LEXER_H */
