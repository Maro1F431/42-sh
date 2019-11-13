#include <stdio.h>

#include "lexer.h"

int main(void)
{
    char *str = "< ; ( ) >>";

    struct lex *l = lexer_alloc(str);

    struct token *token = l->head;
    for (int i = 0; i < 6; i++)
    {
        printf("%d ", token->type);
        token = token->next;
    }

    return 0;
}
