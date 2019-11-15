#include "lexer/lexer.h"
#include "parser/parser.c"
#include "parser/ast.h"
#include <stdio.h>

int main()
{
    char str[] = "echo1 wow ; if echo 2 then echo 3 else echo 4 ;";
    struct lex *l = lexer_alloc(str);
    struct ast_node ast;
    ast_node_init(&ast);
    if (parse_list(l, &ast))
        printf("succes\n");
    else
        printf("failure\n");
    print_ast(&ast);
    ast_node_free_children(&ast);
    lexer_free(l);
}

