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
*/
static struct token *get_tail(struct lex *l)
{
    if (!l->head)
        return NULL;

    struct token *current_token = l->head;
    while (current_token->next)
        current_token = current_token->next;

    return current_token;
}

/**
** \brief add token at the end of the linked list
**
** \return the updated lexer
** \param l the lexer to add the element to
** \param token the token to add to the lexer
*/
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


/**
** \brief build a lexer from the input string and a malloc'd lexer
**
** \return the built lexer
** \param str the input string
** \param l the malloc'd lexer to build to
*/
static struct lex *lex(const char *str, struct lex *l)
{
    size_t i = 0;
    int is_EOF = 0;
    while (!is_EOF)
    {
        struct token *token = token_recognition(str, &i);
        l = add_token(l, token);

        if (token->type == END_OF_FILE)
            is_EOF = 1;
    }
    return l;
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

    if (!lex(str, l))
        return NULL;

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
    if (!lexer || !lexer->head)
        return NULL;

    return lexer->head;
}

/**
** \brief Return and consume the next token from the input stream.
**
** \return the next token from the input stream
** \param lexer the lexer to lex from
*/
struct token *lexer_pop(struct lex *lexer)
{
    if (!lexer || !lexer->head)
        return NULL;

    struct token *head = lexer->head;
    lexer->head = lexer->head->next;

    return head;
}


