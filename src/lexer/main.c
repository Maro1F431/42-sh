#include <stdio.h>

#include "lexer.h"
#include "token.h"

int main(void)
{
    char str[] = "";

    struct lex *l = lexer_alloc(str);

    struct token *token = lexer_pop(l);
    token_free(token);
    token = lexer_pop(l);
    token_free(token);

    lexer_free(l);
    return 0;
}
