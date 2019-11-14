#include <stdio.h>

#include "lexer.h"

int main(void)
{
    char *str = "<< ; ( ) >>";

    struct lex *l = lexer_alloc(str);

    struct token *token = l->head;
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", token->type);
        token = token->next;
    }
    printf("\n");

    return 0;
}
