#include "lexer.h"

#include <string.h>
#include <stddef.h>
#include <stdlib.h>

// get last element of list
static struct token *get_tail(struct lex *l)
{
    if (!l->head)
        return NULL;

    struct token *current_token = l->head;
    while (current_token->next)
        current_token = current_token->next;

    return current_token;
}

// add token at end of linked list
static struct lex *add_token(struct lex *l, struct token *token)
{
    struct token *tail = get_tail(l);

    if (!tail)
    {
        l->head = malloc(sizeof(struct token));
        if (!l->head)
            return NULL;

        l->head->token = token;
        l->head->next = NULL;
        return l;
    }

    tail->next = malloc(sizeof(struct token));
    if (!tail->next)
        return NULL;

    tail->next->token = token;
    tail->next->next = NULL;

    return l;
}


static struct lex *add_eof(struct lex *l)
{
    struct token *eof = malloc(sizeof(struct token));
    if (!eof)
        return NULL;
    eof->type = END_OF_FILE;
    eof->value = NULL;
    eof->next = NULL;

    struct token *tail = get_tail(l);

    if (!tail)
        l->head = eof;
    else
        tail->next = eof;

    return l;
}


size_t nb_digits(int value)
{
    size_t res = 0;

    if (value < 0)
    {
        res++;
        value = -value;
    }

    while (value > 0)
    {
        value /= 10;
        res++;
    }

    return res;
}




static struct token *match_type(const char *str,
        struct token *token, size_t *ptr_i)
{
    size_t i = *ptr_i;

    if (str[i] == '(')
        token->type = TOKEN_LEFT_PARENTHESIS;
    else if (str[i] == ')')
        token->type = TOKEN_RIGHT_PARENTHESIS;
    else if (str[i] == '+')
        token->type = TOKEN_PLUS;
    else if (str[i] == '-')
        token->type = TOKEN_MINUS;
    else if (str[i] == '*')
        token->type = TOKEN_MULTIPLY;
    else if (str[i] == '/')
        token->type = TOKEN_DIVIDE;
    else if (str[i] >= '0' && str[i] <= '9')
    {
        token->type = TOKEN_NUMBER;
        token->value = atoi(str + i);
        *ptr_i += nb_digits(token->value) - 1;
    }
    else
        return NULL;

    return token;
}


static struct lex *lex(const char *str, struct lex *l)
{
    size_t i = 0;
    while (str[i] != '\0')
    {
        struct token *token = malloc(sizeof(struct token));
        if (!token)
            return NULL;

        while (str[i] == ' ')
            i++;

        if (str[i] == '\0')
            break;

        token = match_type(str, token, &i);
        if (!token)
            return NULL;

        l = add_token(l, token);
        if (!l)
            return NULL;

        i++;
    }

    l = add_eof(l);
    if (!l)
        return NULL;

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
        lexer_pop(lexer);

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

    return lexer->head->token;
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


