#include "lexer.h"

#include <malloc.h>
#include "token.h"

struct token *init_token(void)
{
    struct token *new = malloc(sizeof(struct token));
    if (!new)
        return NULL;

    new->value = NULL;
    new->type = -1;
    new->next = NULL;

    return new;
}


void token_free(struct token *token)
{
    if (!token)
        return;

    if (token->value)
        free(token->value);
    free(token);
}


