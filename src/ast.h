#ifndef AST_H
#define AST_H

// for building the ast we have to use the lex struct;

/*
 * ast : It is a binary tree;
 * Thus as a left
 */

enum ast_type
{
    COMMAND = 0,
    AND,
    OR,
    PIPE
}

struct ast
{
    enum ast_type type;
    union {
        struct {
            struct ast *left;
            struct ast *right;
        } children;
        struct command;
    } data;
};

static inline struct ast *left_child(struct ast *ast)
{
    return ast->data.children.left;
}

static inline struct ast *right_child(struct ast *ast)
{
    return ast->data.children.right;
}

struct command
{
    struct redirection[] redirections;// TODO LATER (week 2)
    char[][] argv; //first arg is the command.
};

struct ast *ast_alloc(void);

void ast_free(struct ast *ast);

struct ast *ast_alloc_command(struct command);

#endif
