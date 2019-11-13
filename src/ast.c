#include <string.h>
#include <stdlib.h>
#include "ast.h"
#include "lexer.h"

struct stack_ast
{
    struct ast *ast;
    struct stack_ast *next;
};

struct ast *pop(struct stack_ast *stack)
{
    if (stack == NULL)
    {
        return NULL;
    }
    else
    {
        struct ast *head = stack->ast;
        stack = stack->next;
        return tok;
    }
}

struct stack_ast *push(struct stack_ast *stack, struct ast *ast)
{
    struct ast_stack *new_stack = malloc(sizeof(struct ast));
    new_stack->ast = ast;
    new_stack->next = stack;
    stack = new_stack;
    return stack;
}

struct ast *buildast(struct lex *lex)
{
    struct ast *ast = malloc(sizeof(struct ast));
    struct stack_ast *operator = malloc(sizeof(struct stack_ast));
    struct stack_ast *operand = malloc(sizeof(struct stack_ast));
}
