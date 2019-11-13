#include "lexer.h"
#include "helper.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct token_map g_token_map_list[NB_TOKENS] =
{
    {
        .input = "\0",
        .type = END_OF_FILE
    },
    {
        .input = "\n",
        .type = LINE_BREAK
    },
    {
        .input = ";",
        .type = SEMICOL
    },
    {
        .input = ";;",
        .type = DOUBLE_SEMICOL
    },
    {
        .input = "&",
        .type = AMPERSAND
    },
    {
        .input = "&&",
        .type = DOUBLE_AMPERSAND
    },
    {
        .input = "|",
        .type = PIPE
    },
    {
        .input = "||",
        .type = DOUBLE_PIPE
    },
    {
        .input = "!",
        .type = EXCLAMATION
    },
    {
        .input = "{",
        .type = OPEN_CURLY_BRACKET
    },
    {
        .input = "}",
        .type = CLOSE_CURLY_BRACKET
    },
    {
        .input = "(",
        .type = OPEN_PAR
    },
    {
        .input = ")",
        .type = CLOSE_PAR
    },
    {
        .input = "function",
        .type = FUNCTION
    },
    {
        .input = ">",
        .type = CHEV_SIMPLE_R
    },
    {
        .input = "<",
        .type = CHEV_SIMPLE_L
    },
    {
        .input = ">>",
        .type = CHEV_DOUBLE_R
    },
    {
        .input = "<<",
        .type = CHEV_DOUBLE_L
    },
    {
        .input = "<<-",
        .type = CHEV_DOUBLE_H
    },
    {
        .input = ">&",
        .type = CHEV_AMP_R
    },
    {
        .input = "<&",
        .type = CHEV_AMP_L
    },
    {
        .input = ">|",
        .type = CHEV_PIPE
    },
    {
        .input = "<>",
        .type = LEFT_RIGHT
    },
    {
        .input = "while",
        .type = WHILE
    },
    {
        .input = "until",
        .type = UNTIL
    },
    {
        .input = "case",
        .type = CASE
    },
    {
        .input = "esac",
        .type = ESAC
    },
    {
        .input = "in",
        .type = IN
    },
    {
        .input = "if",
        .type = IF
    },
    {
        .input = "fi",
        .type = FI
    },
    {
        .input = "then",
        .type = THEN
    },
    {
        .input = "else",
        .type = ELSE
    },
    {
        .input = "elif",
        .type = ELIF
    },
    {
        .input = "do",
        .type = DO
    },
    {
        .input = "done",
        .type = DONE
    }
};

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

        l->head = token;
        l->head->next = NULL;
        return l;
    }

    tail->next = malloc(sizeof(struct token));
    if (!tail->next)
        return NULL;

    tail->next = token;
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




// associate a token type to a word of the input string
// str : input string
// token : the current token which will receive the type of token
// ptr_i : a pointer to the index where the word to identify starts
//          (muste be incremented by the size of the identified word)
static struct token *match_type(const char *str,
        struct token *token, size_t *ptr_i)
{
    char *word = get_word(str, ptr_i);

    for (int i = 0; i < NB_TOKENS; i++)
    {
        if (!strcmp(word, g_token_map_list[i]->input))
        {
            token->type = g_token_map_list[i]->type;
            break;
        }
    }

    return token;
}




static struct lex *lex(const char *str, struct lex *l)
{
    size_t i = 0;
    while (str[i] != '\0')
    {
        struct token *token = malloc(sizeof(struct token));
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


