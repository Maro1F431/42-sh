#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "parser.h"
#include "../lexer/lexer.h"


bool parse_simple_command(struct lex *lexer, struct ast_node *cmd_node)
{
    struct token *token = lexer_peek(lexer);
    if (!token)
        return false;

    if (token->type == WORD)
    {
        cmd_node->type = AST_COMMAND;
        while (lexer_peek(lexer)->type == WORD)
        {
            token = lexer_pop(lexer);
            struct ast_node word_child;
            ast_node_init(&word_child);
            word_child.type = AST_WORD;
            word_child.data = token->value;
            insert_children(cmd_node, word_child);
            token_free(token);
        }
        return true;
    }
    else
        return false;
}

bool parse_list(struct lex *lexer, struct ast_node *list_node)
{
    struct ast_node first_child_command;
    ast_node_init(&first_child_command);
    if (!(parse_simple_command(lexer, &first_child_command)))
        return false;

    list_node->type = AST_LIST;
    insert_children(list_node, first_child_command);
    while ((lexer_peek(lexer)->type) == SEMICOL)
    {
        token_free(lexer_pop(lexer));
        struct ast_node child_command;
        ast_node_init(&child_command);
        if (parse_simple_command(lexer, &child_command))
            insert_children(list_node, child_command);
    }
    return true;
}

