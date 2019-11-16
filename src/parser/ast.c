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
        if (ast->type == AST_COMMAND)
        {
            for (size_t i = 0; i < ast->nb_children; i++)
            {
                if (ast->children[i].type == AST_SIMPLE_COMMAND)
                    execute_command(&ast->children[i]);
                else if (ast->children[i].type == AST_IF)
                {
                    int boo = 0;
                    if (execute_command(&ast->children[i].children[0].children[0].children[0]) == 1)
                    {
                        execute(&ast->children[i].children[1]);
                        boo = 1;
                    }
                    else if (ast->children[i].children[0].nb_children == 3 && boo == 0)
                        execute(&ast->children[i].children[2]);
                }
            }
        }
        for (size_t i = 0; i < ast->nb_children ; i++)
        {
            if (ast->type == AST_COMMAND || ast->type == AST_LIST)
                execute(&(ast->children[i]));
        }
    }
}

int execute_command(struct ast_node *ast)
{
    char **str = calloc(sizeof(char*), 50);
    int ind = 0;
    for (size_t i = 0; i < ast->nb_children; i++)
    {
        //char *ok = ast->children[i].data;
        //printf("%s", ok);
        str[ind] = ast->children[i].data;
        ind++;
    }
    //printf(" m  %s", str[0]);
    char *shebangs = "/bin/";
    char *real_shebangs = calloc(sizeof(char), 50);
    sprintf(real_shebangs, "%s%s", shebangs, str[0]);
    pid_t cpid;
    int status;
    //printf("%s", real_shebangs);
    cpid = fork();
    if (!cpid)
        execve(real_shebangs, str, NULL);
    else
    {
        waitpid(cpid, &status, 0);
        free(real_shebangs);
        free(str);
    }
    return 1;
}


void ast_node_init(struct ast_node *ast)
{
    ast->nb_children = 0;
    ast->children_array_size = 10;
    ast->children = malloc(sizeof(struct ast_node) * ast->children_array_size);
    ast->data = NULL;
}

void ast_node_free_children(struct ast_node *ast)
{
    //TODO, FREE the children list and everything else;
    if (ast->nb_children != 0)
    {
        for (size_t i = 0; i < ast->nb_children; i++)
        {
            ast_node_free_children(&(ast->children[i]));
        }
        free(ast->children);
    }
    else
    {
        free(ast->children);
        if (ast->data)
            free(ast->data);
    }
}

void print_ast(struct ast_node *ast)
{
    //TODO, FREE the children list and everything else;
    if (ast->nb_children != 0)
    {
        print_type(ast->type);
        for (size_t i = 0; i < ast->nb_children; i++)
        {
            print_ast(&(ast->children[i]));
        }
    }
    else
    {
        print_type(ast->type);
        printf("%s\n", (char*)(ast->data));
    }
}

void print_type(int i)
{
    if (i == 0)
        printf("SIMPLE_COMMAND\n");
    else if (i == 1)
        printf("COMMAND\n");
    else if (i == 2)
        printf("AND\n");
    else if (i == 3)
        printf("OR\n");
    else if (i == 4)
        printf("PIPE\n");
    else if (i == 5)
        printf("LIST\n");
    else if (i == 6)
        printf("IF\n");
    else if (i == 7)
        printf("WORD: ");
}


void insert_children(struct ast_node *ast, struct ast_node to_insert)
{
    //TODO, CHECK IF to_insert type match AST type for insertion as a child.
    if (ast->nb_children == ast->children_array_size)
    {
        ast->children_array_size *= 2;
        ast->children = realloc(ast->children,
            sizeof(struct ast_node) * ast->children_array_size);
    }
    ast->children[ast->nb_children] = to_insert;
    ast->nb_children += 1;
}
