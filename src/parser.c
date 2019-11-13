#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"
#include "lexer.h"

static bool token_is_ws(struct token *token)
{
    return token->type == SEMICOL || token->type == WORD;
}

static bool parse_command(struct lexer *lexer, struct ast **ast)
{
    struct token *token = lexer_pop(lexer);
    if (!token)
        return false;

    bool res = true;
    if (token->type == WORD)
    {
        *ast = ast_alloc_command();
        size_t index = 0;
        while ((struct token poped = lexer_pop(lexer))->type == WORD)
        {
            (*ast)->data->command->argv[index] = poped->value;
            index++;
        }
    }
    else
        res = false;

    token_free(token);
    return res;
}

static bool parse_list(struct lexer *lexer, struct ast **ast)
{
    if (!parse_command(lexer, ast))
        return false;

    bool res = true;
    struct token *token = lexer_peek(lexer);
    while (res && token && token->type == SEMICOL)
    {
        token = lexer_pop(lexer);

        struct ast *tmp = ast_alloc();
        tmp->type = SEMICOL;

        res = parse_command(lexer, &tmp->data.children.right);
        tmp->data.children.left = *ast;
        *ast = tmp;
        token_free(token);
        token = lexer_peek(lexer);
    };

    return res;
}
