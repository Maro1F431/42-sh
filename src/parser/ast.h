#ifndef AST_H
#define AST_H

#include <stddef.h>

enum ast_type
{
    AST_COMMAND = 0,
    AST_AND,
    AST_OR,
    AST_PIPE,
    AST_LIST,
    AST_WORD
};

struct ast_node
{
    enum ast_type type;
    size_t nb_children;
    size_t children_array_size;
    struct ast_node *children;
    void *data;
    //maybe coding an 'insert_children' method would be nice to make sure a node has the 
    //good children according to his type
};
void execute(struct ast_node *ast);

void insert_children(struct ast_node *ast, struct ast_node *toinsert);

void execute_command(struct ast_node *ast);

struct ast_node *ast_node_alloc(void);

void ast_node_free(struct ast_node *ast);

#endif
