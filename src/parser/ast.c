#include <string.h>
#include <stdlib.h>
#include "ast.h"
#include "../lexer/lexer.h"


//this is a test
struct ast_node *ast_node_alloc(void)
{
    struct ast_node *res = malloc(sizeof(struct ast_node));
    memset(res, 0, sizeof(*res));
    res->nb_children = 0;
    res->children_array_size = 10;
    res->children = malloc(sizeof(struct ast_node) * res->children_array_size);
    res->data = NULL;
    return res;
}

void ast_node_free(struct ast_node *ast)
{
    //TODO, FREE the children list and everything else;
}

void insert_children(struct ast_node *ast, struct ast_node *to_insert)
{
    //TODO, CHECK IF to_insert type match AST type for insertion as a child.
    if (ast->nb_children == ast->children_array_size)
    {
        ast->children_array_size *= 2;
        ast->children = realloc(ast->children,
            sizeof(struct ast_node) * ast->children_array_size);
    }
    ast->children[ast->nb_children] = *to_insert;
    ast->nb_children += 1;
}
