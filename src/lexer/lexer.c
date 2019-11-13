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



static struct token_table *init_token_table(void)
{
    struct token_table *token_table = malloc(sizeof(struct token_table));



}


// associate a token type to a word of the input string
// str : input string
// token : the current token which will receive the type of token
// ptr_i : a pointer to the index where the word to identify starts
//          (muste be incremented by the size of the identified word)
static struct token *match_type(const char *str,
        struct token *token, size_t *ptr_i)
{
    struct token_table *token_table = init_token_table();

    char *word = get_word(str, ptr_i);

    for (int i = 0; i < NB_TOKENS, i++)
    {
        if (!strcmp(word, token_table->input[i]))
        {
            token->type = token_table->token_type[i];
            break;
        }
    }
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


