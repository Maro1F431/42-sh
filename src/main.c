#include "lexer/lexer.h"
#include "parser/parser.c"
#include "parser/ast.h"
#include <stdio.h>

int main()
{
    char str[] = "echo wow ; if echo 1 then echo 2 else echo 3 ;";
    struct lex *l = lexer_alloc(str);
    struct ast_node ast;
    ast_node_init(&ast);
    if (parse_list(l, &ast))
        printf("succes\n");
    else
        printf("failure\n");
    print_ast(&ast);
    //char *test = ast.children[0].children[0].data;
    //printf("test %d", ast.children[0].children[0].type);
    printf("EXEC TIME\n");
    execute(&ast);
    ast_node_free_children(&ast);
    lexer_free(l);
}

