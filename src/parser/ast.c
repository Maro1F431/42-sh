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
            execute_command(ast);
        if (ast->type == AST_IF)
        {
            if (execute_command(&(ast->children[0])) == 1)
                execute(&(ast->children[1]));
            else if (ast->nb_children == 3)
                execute(&(ast->children[2]));
        }
        for (size_t i = 0; i < ast->nb_children ; i++)
        {
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
        if ( ast->children[i].data == NULL)
            printf("Data is NULL");
        str[ind] = ast->children[i].data;
        ind++;
    }
    printf(" m  %s", str[0]);
    char *shebangs = "/bin/";
    char *real_shebangs = calloc(sizeof(char), 50);
    sprintf(real_shebangs, "%s%s", shebangs, str[0]);
    pid_t cpid;
    int status;
    printf("%s", real_shebangs);
    cpid = fork();
    if (!cpid)
        execve(real_shebangs, str, NULL);
    else
    {
        waitpid(cpid, &status, 0);
        free(real_shebangs);
        /*for (int i = 0; i < 50; i++)
        {
            free(str[i]);
        }
        free(str);*/
    }
    return 1;
}
//this is a test
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
