#ifndef AST_H
#define AST_H

struct token;
struct lex;
struct token_table;

// for building the ast we have to use the lex struct;

/*
 * ast : It is a binary tree;
 * Thus as a left
 */

struct ast
{
    struct ast *left;
    struct ast *right;
    struct token token;
};

struct ast *buildast(struct lex *lex);

#endif
