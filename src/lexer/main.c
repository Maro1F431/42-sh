#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "token.h"


int main(void)
{

    FILE *f = fopen("test.sh", "r");
    char *ptr_line = NULL;
    size_t n = 0;

    getline(&ptr_line, &n, f);

    struct lex *l = lexer_alloc(ptr_line);

    l->in_type = SCRIPT;
    l->fd = f;
    l->n = n;
    l->line_ptr = ptr_line;

    struct token *token = lexer_pop(l);
    int i = 0;
    while(i < 15)
    {
        if (token->value)
            printf("%s ", token->value);
        else
            printf("%d ", token->type);
        token_free(token);
        token = lexer_pop(l);
        i++;
    }
    token_free(token);
    lexer_free(l);
    free(ptr_line);
    fclose(f);
    return 0;
}

/*
int main(void)
{
    char str[] = "if ls ; then echo 2 ; else echo 3 ; echo pog";

    struct lex *l = lexer_alloc(str);
    l->in_type = STRING;

    struct token *token = lexer_pop(l);
    int i = 0;
    while(i < 15)
    {
        if (token->value)
            printf("%s ", token->value);
        else
            printf("%d ", token->type);
        token_free(token);
        token = lexer_pop(l);
        i++;
    }
    token_free(token);
    lexer_free(l);
    return 0;
}*/
