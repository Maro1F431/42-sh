#include "lexer.h"
#include "helper.h"
#include "token.h"
#include "token_rec.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
** \brief get last element of list
**
** \return the last token of the list
** \param l the lexer to get the last element from

static struct token *get_tail(struct lex *l)
{
    if (!l->head)
        return NULL;

    struct token *current_token = l->head;
    while (current_token->next)
        current_token = current_token->next;

    return current_token;
}
*/

/**
** \brief add token at the end of the linked list
**
** \return the updated lexer
** \param l the lexer to add the element to
** \param token the token to add to the lexer

static struct lex *add_token(struct lex *l, struct token *token)
{
    struct token *tail = get_tail(l);

    if (!tail)
    {
        l->head = token;
        l->head->next = NULL;
        return l;
    }

    tail->next = token;
    tail->next->next = NULL;

    return l;
}
*/

/**
** \brief build a lexer from the input string and a malloc'd lexer
**
** \return the built lexer
** \param str the input string
** \param l the malloc'd lexer to build to
*/
static struct token *lex(const char *str, size_t *ptr_i, int mode)
{
    struct token *token = token_recognition(str, ptr_i, mode);

    return token;
}


/**
** \brief This is your struct lex forward declaration.
**
** You should not edit this struct declaration but define one with the
** same name in another header file.
*/
struct lex *lexer_alloc(const char *str)
{
    struct lex *l = malloc(sizeof(struct lex));
    if (!l)
        return NULL;

    l->head = NULL;
    l->input = str;
    l->len = strlen(str);
    l->i = 0;

    return l;
}
/**
** \brief Wrapper to release every resources still held in a lexer.
**
** \param lexer the lexer to free
*/
void lexer_free(struct lex *lexer)
{
    while (lexer_peek(lexer))
    {
        token_free(lexer_pop(lexer));
    }

    // maybe free input

    free(lexer);
}

/**
** \brief Return the first token from the input stream without consuming it.
**
** \return the next token from the input stream
** \param lexer the lexer to lex from
*/
struct token *lexer_peek(struct lex *lexer)
{
   if (lexer->i > lexer->len)
        return NULL;

    size_t i = lexer->i;
    struct token *next_token = lex(lexer->input, &i, MODE_STD);

    return next_token;
}

/**
** \brief Return and consume the next token from the input stream.
**
** \return the next token from the input stream
** \param lexer the lexer to lex from
*/
struct token *lexer_pop(struct lex *lexer)
{
    if (lexer->i > lexer->len)
        return NULL;

    struct token *next_token = lex(lexer->input, &(lexer->i), MODE_STD);

    return next_token;
}

struct token *lexer_pop_command(struct lex *lexer)
{
    if (lexer->i > lexer->len)
        return NULL;

    struct token *next_token = lex(lexer->input, &(lexer->i), MODE_CMD);
    next_token->type = WORD;

    return next_token;

}
