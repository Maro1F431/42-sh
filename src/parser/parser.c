#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "parser.h"
#include "../lexer/lexer.h"

struct ast_node *parse_simple_command(struct lex *lexer)
{
    struct token *token = lexer_peek(lexer);
    if (!token)
        return NULL;

    if (token->type == WORD)
    {
        struct ast_node *cmd_node = ast_node_alloc();
        cmd_node->type = AST_COMMAND;
        while (lexer_peek(lexer)->type == WORD)
        {
            token = lexer_pop(lexer);
            struct ast_node *word_child = ast_node_alloc();
            word_child->type = WORD;
            word_child->data = token->value;
            insert_children(cmd_node, word_child);
        }
        //token_free(token);
        return cmd_node;
    }
    else
        return NULL;

    //token_free(token);
    //return cmd_node;
}

struct ast_node *parse_list(struct lex *lexer)
{
    struct ast_node *first_child_command;
    if (!(first_child_command = parse_simple_command(lexer)))
        return NULL;

    struct ast_node *list_node = ast_node_alloc();
    list_node->type = AST_LIST;
    insert_children(list_node, first_child_command);
    while ((lexer_peek(lexer)->type) == SEMICOL)
    {
        lexer_pop(lexer);
        struct ast_node *child_command = parse_simple_command(lexer);
        insert_children(list_node, child_command);
    }

    return list_node;
}

