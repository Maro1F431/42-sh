#include <stdio.h>

#include "lexer.h"
#include "token.h"

int main(void)
{
    char str[] = "<< word {(&";

    struct lex *l = lexer_alloc(str);

    struct token *token = lexer_pop_command(l);
    token = lexer_pop_command(l);
    token = lexer_pop(l);
    token = lexer_pop(l);
    token = lexer_pop(l);
    token = lexer_pop(l);

    (void)token;

    lexer_free(l);
    return 0;
}
