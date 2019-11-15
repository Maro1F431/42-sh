#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include <unistd.h>
#include <sys/wait.h>
#include "../lexer/lexer.h"


void execute(struct ast_node *ast)
{
    if (ast->nb_children != 0)
    {
        for (int i = 0; i < ast->nb_children ; i++)
        {
            execute(&(ast->children[i]));
        }
        if (ast->type == AST_COMMAND)
            execute_command(ast);
    }
}

void execute_command(struct ast_node *ast)
{
    char **str = calloc(sizeof(char*), 50);
    int ind = 0;
    for (int i = 0; i < ast->nb_children; i++)
    {
        str[ind] = ast->children[i].data;
    }
    char *shebangs = "/bin/";
    char *real_shebangs = calloc(sizeof(char), 50);
    sprintf(real_shebangs, "%s%s", shebangs, str[0]);
    pid_t cpid;
    int status;
    cpid = fork();
    if (!cpid)
        execve(real_shebangs, str, NULL);
    else
    {
        waitpid(cpid, &status, 0);
        free(real_shebangs);
        for (int i = 0; i < 50; i++)
        {
            free(str[i]);
        }
        free(str);
    }
}

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
    if (ast->nb_children != 0)
    {
        for (size_t i = 0; i < ast->nb_children; i++)
        {
            ast_node_free(&(ast->children[i]));
        }
        free(ast->children);
    }
    else
    {
        free(ast->children);
    }
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
    free(to_insert);
    ast->nb_children += 1;
}
