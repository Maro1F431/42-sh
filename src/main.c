#include "lexer/lexer.h"
#include "parser/parser.c"
#include "parser/ast.h"

int main()
{
    char *str = "echo wow";
    struct lex *l = lexer_alloc(str);
    struct ast_node *ast = parse_list(l);
}

