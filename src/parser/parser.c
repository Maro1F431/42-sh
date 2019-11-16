#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <err.h>
#include "ast.h"
#include "parser.h"
#include <stdio.h>
#include "../lexer/lexer.h"


bool parse_simple_command(struct lex *lexer, struct ast_node *s_cmd_node)
{
    struct token *token = lexer_peek(lexer);
    if (!token) //if token->type == EOF
        return false;

    if (token->type == WORD || token->type == ASSIGNMENT_WORD)
    {
        s_cmd_node->type = AST_SIMPLE_COMMAND;
        bool switch_to_word = false;
        while (lexer_peek(lexer)->type == ASSIGNMENT_WORD
            || lexer_peek(lexer)->type == WORD)
        {
            if (!switch_to_word && lexer_peek(lexer)->type == WORD)
                switch_to_word = true;
            if (switch_to_word && lexer_peek(lexer)->type == ASSIGNMENT_WORD)
                    errx(1, "assignment_word after a word in command parsing");
                    //should exit the program
            token = lexer_pop(lexer);
            struct ast_node word_child;
            ast_node_init(&word_child);
            word_child.type = AST_WORD;
            word_child.data = malloc(sizeof(char) * strlen(token->value) + 1);
            strcpy(word_child.data, token->value);
            insert_children(s_cmd_node, word_child);
            token_free(token);
        }
        return true;
    }
    else
        return false;//should not exit the program
}

bool parse_rule_if(struct lex *lexer, struct ast_node *if_node)
{
    //3 children, 1 condition, 1 body, 1 else body.
    //We are going to cheat for now and use list (as we have already done it),
    //instead of compound_list_break
    struct token *token = lexer_peek(lexer);

    if (token->type == IF)
    {
        token_free(lexer_pop(lexer));
        if_node->type = AST_IF;
        struct ast_node condition_list_node;
        ast_node_init(&condition_list_node);
        parse_list(lexer, &condition_list_node);
        insert_children(if_node, condition_list_node);

        if (lexer_peek(lexer)->type == THEN)
        {
            token_free(lexer_pop(lexer));
            struct ast_node ifbody_list_node;
            ast_node_init(&ifbody_list_node);
            parse_list(lexer, &ifbody_list_node);
            insert_children(if_node, ifbody_list_node);

            if (lexer_peek(lexer)->type == ELSE)
            {
                token_free(lexer_pop(lexer));
                struct ast_node elsebody_list_node;
                ast_node_init(&elsebody_list_node);
                parse_list(lexer, &elsebody_list_node);
                insert_children(if_node, elsebody_list_node);
            }
            return true;
        }
        else
            errx(1, "no then keyword after if");
                    //should exit the program
    }
    else
        return false;// should not exit the program
}

bool parse_command(struct lex *lexer, struct ast_node *cmd_node)
{
    cmd_node->type = AST_COMMAND;
    struct ast_node child_node;
    ast_node_init(&child_node);
    if (parse_simple_command(lexer, &child_node) || parse_rule_if(lexer, &child_node))
    {
        insert_children(cmd_node, child_node);
        return true;
    }
    else
    {
        ast_node_free_children(&child_node);
        return false;
    }
}

bool parse_list(struct lex *lexer, struct ast_node *list_node)
{
    struct ast_node first_child_command;
    ast_node_init(&first_child_command);
    if (!(parse_command(lexer, &first_child_command)))
    {
        ast_node_free_children(&first_child_command);
        return false;
    }

    list_node->type = AST_LIST;
    insert_children(list_node, first_child_command);
    while ((lexer_peek(lexer)->type) == SEMICOL)
    {
        token_free(lexer_pop(lexer));
        struct ast_node child_command;
        ast_node_init(&child_command);
        if (parse_command(lexer, &child_command))
            insert_children(list_node, child_command);
        else
            ast_node_free_children(&child_command);
    }
    return true;
}

