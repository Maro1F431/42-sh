#define _GNU_SOURCE

#include "lexer.h"
#include "token.h"
#include "token_rec.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 ** \brief build a lexer from the input string and a malloc'd lexer
 **
 ** \return the built lexer
 ** \param str the input string
 ** \param l the malloc'd lexer to build to
 */
static struct token *lex(char *str, size_t *ptr_i, int mode)
{
    struct token *token = token_recognition(str, ptr_i, mode);

    return token;
}


void get_input(struct lex *l, enum input_type in_type)
{
    if (in_type == STRING)
        l->input = NULL;
    else if (in_type == SCRIPT)
    {
        int nb_char = getline(&l->line_ptr, &l->n, l->fd);
        if (nb_char == -1)
            l->input = NULL;
        else
        {
            l->input = l->line_ptr;
            l->i = 0;
            l->len = nb_char;
        }
    }
    else if (in_type == STANDARD)
        l->input = NULL;
    else // interactive
    {
        char *str = readline(">");
        while (str && str[0] == '\0')
        {
            free(str);
            str = readline(">");
        }

        add_history(str);

        if (l->malloc_input)
            free(l->input);
        l->input = str;

        if (str)
            l->len = strlen(str);
        l->i = 0;
        l->malloc_input = 1;
    }
}


/**
 ** \brief This is your struct lex forward declaration.
 **
 ** You should not edit this struct declaration but define one with the
 ** same name in another header file.
 */
struct lex *lexer_alloc(char *str)
{
    struct lex *l = malloc(sizeof(struct lex));
    if (!l)
        return NULL;

    l->input = str;
    l->len = strlen(str);
    l->i = 0;
    l->malloc_input = 0;


    l->line_ptr = NULL;

    return l;
}
/**
 ** \brief Wrapper to release every resources still held in a lexer.
 **
 ** \param lexer the lexer to free
 */
void lexer_free(struct lex *lexer)
{
    if (lexer->malloc_input)
        free(lexer->input);

    free(lexer);
}

struct token *eof_token(void)
{
    struct token *token = init_token();
    token->type = END_OF_FILE;
    return token;
}

/**
 ** \brief Return the first token from the input stream without consuming it.
 **
 ** \return the next token from the input stream
 ** \param lexer the lexer to lex from
 */
struct token *lexer_peek(struct lex *lexer)
{
    if (lexer->i > lexer->len || lexer->len == 0)
        get_input(lexer, lexer->in_type);

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
    if (lexer->i >= lexer->len || lexer->len == 0)
        get_input(lexer, lexer->in_type);
    struct token *next_token = lex(lexer->input, &(lexer->i), MODE_STD);

    return next_token;
}

struct token *lexer_pop_command(struct lex *lexer)
{
    if (lexer->i >= lexer->len || lexer->len == 0)
    {
        get_input(lexer, lexer->in_type);
    }
    struct token *next_token = lex(lexer->input, &(lexer->i), MODE_CMD);

    return next_token;

}


struct token *lexer_peek_command(struct lex *lexer)
{
    if (lexer->i >= lexer->len || lexer->len == 0)
        get_input(lexer, lexer->in_type);

    size_t i = lexer->i;
    struct token *next_token = lex(lexer->input, &i, MODE_CMD);

    return next_token;
}
