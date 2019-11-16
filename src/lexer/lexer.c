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

void get_new_input(struct lex *lexer)
{
    char *str = readline(">");
    while (str && str[0] == '\0')
    {
        free(str);
        str = readline(">");
    }


    //check signal
    //add history
    if (lexer->malloc_input)
        free(lexer->input);
    lexer->input = str;

    if (str)
        lexer->len = strlen(str);
    lexer->i = 0;
    lexer->malloc_input = 1;
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
        get_new_input(lexer);

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
        get_new_input(lexer);
    struct token *next_token = lex(lexer->input, &(lexer->i), MODE_STD);

    return next_token;
}

struct token *lexer_pop_command(struct lex *lexer)
{
    if (lexer->i >= lexer->len || lexer->len == 0)
        get_new_input(lexer);

    struct token *next_token = lex(lexer->input, &(lexer->i), MODE_CMD);

    return next_token;

}
