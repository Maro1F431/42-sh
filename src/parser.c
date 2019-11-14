#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"
#include "lexer.h"

static struct *ast_node parse_command(struct lexer *lexer)
{
    struct token *token = lexer_peek(lexer);
    if (!token)
        return NULL;

    if (token->type == WORD)
    {
        struct ast_node *cmd_node = ast_node_alloc();
        cmd_node->type = COMMAND;
        while (lexer_peek(lexer)->type == WORD)
        {
            token = lexer_pop(lexer);
            struct ast_node *word_child = ast_node_alloc();
            word_child->type = WORD;
            word_child->data = token->value;
            insert_children(cmd_node, word_child);
        }
    }
    else
        return NULL;

    token_free(token);
    return cmd_node;
}

static bool parse_list(struct lexer *lexer)
{
    if (!(struct ast_node *first_child_command 
                = parse_command(lexer, ast_node)))
        return NULL;

    list_node = ast_node_alloc();
    list_node->type = LIST;
    insert_children(list_node, first_child_command);
    while (lexer_peek(lexer)->type == SEMICOL)
    {
        lexer_pop(lexer);
        struct ast_node *child_command = parse_command(lexer, ast_node);
        insert_children(list_node, child_command);
    };

    return list_node;
}
