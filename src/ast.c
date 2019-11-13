#include <string.h>
#include <stdlib.h>
#include "ast.h"
#include "lexer.h"

struct ast *ast_alloc(void)
{
    struct ast *res = xmalloc(sizeof(*res));
    memset(res, 0, sizeof(*res));
    return res;
}

void ast_free(struct ast *ast)
{
    if (ast && ast->type != EXPR_NUMBER)
    {
        ast_free(right_child(ast));
        ast_free(left_child(ast));
    }

    free(ast);
}

struct ast *ast_alloc_command(void)
{
    struct ast *res = ast_alloc();
    res->type = COMMAND;
    struct command *cmd = malloc(sizeof(struct command));
    cmd->argv = malloc(sizeof(char *) * 100);
    res->data.command = cmd;
    return res;
}
