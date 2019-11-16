#include <stdio.h>

#include "lexer.h"
#include "token.h"

int main(void)
{
    char str[] = "if << word {(&";

    struct lex *l = lexer_alloc(str);

    printf("%s", lexer_pop(l)->value);
    printf("%s", lexer_pop_command(l)->value);
    printf("%s", lexer_pop_command(l)->value);
    printf("%s", lexer_pop_command(l)->value);
    printf("%s", lexer_pop_command(l)->value);

    lexer_free(l);
    return 0;
}
