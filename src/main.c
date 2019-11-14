#include "lexer/lexer.h"
#include "parser/parser.c"
#include "parser/ast.h"
#include <stdio.h>

int main()
{
    char str[] = "echo wow ;";
    struct lex *l = lexer_alloc(str);
    //lexer_pop(l);
    printf("%s", l->head->value);
    struct ast_node *ast = parse_list(l);
    //printf("%s", l->head->value);
    //char *s = (ast->children[0].data);
   // printf("%s", s);
}

