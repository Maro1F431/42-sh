#include "lexer/lexer.h"
#include "parser/parser.c"
#include "parser/ast.h"
#include <stdio.h>

int main()
{
    char str[] = "echo wow ; echo wow2";
    struct lex *l = lexer_alloc(str);
    struct ast_node *ast = parse_list(l);
    char *s = (ast->children[1].children[1].data);
    printf("%s", s);
}

