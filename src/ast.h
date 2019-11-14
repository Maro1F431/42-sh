#ifndef AST_H
#define AST_H

enum ast_type
{
    COMMAND = 0,
    AND,
    OR,
    PIPE,
    LIST
}

struct ast_node
{
    enum ast_type type;
    size_t nb_children;
    size_t children_array_size;
    struct ast_node *children;
    void *data
    //maybe coding an 'insert_children' method would be nice to make sure a node has the 
    //good children according to his type
};

void insert_children(struct ast *ast);

struct ast *ast_alloc(void);

void ast_free(struct ast *ast);

#endif
