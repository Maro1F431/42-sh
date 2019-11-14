#include <stdio.h>

#include "lexer.h"

int main(void)
{
    char str[] = "echo hello there";

    struct lex *l = lexer_alloc(str);

    lexer_free(l);
    return 0;
}
