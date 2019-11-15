#include "lexer/lexer.h"
#include "parser/parser.c"
#include "parser/ast.h"
#include <stdio.h>

int main()
{
    char str[] = "echo1 wow ; echo2 wow2";
    struct lex *l = lexer_alloc(str);
    struct ast_node *ast = parse_list(l);
    ast_node_free(ast);
    free(ast);
}

