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
** \brief add the end of file character to the lexer
**
** \return the updated lexer
** \param l the lexer to add the end of file element to
*/
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


/**
** \brief counts the number of digits of the given integer
**
** \return the number of digits
** \param value the integer to count the digits from
*/
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




/**
** \brief associate a token type to a word of the input string
**
** \return the matched token
** \param token the token that has to have its type modified
** \param str the input string
** \param ptr_i a pointer to the index where the word to identify starts
*/
static struct token *match_type(const char *str,
        struct token *token, size_t *ptr_i)
{
    char *word = get_word(str, ptr_i);

    unsigned i = 0;
    while (i < NB_TOKENS)
    {
        if (!strcmp(word, g_token_map_list[i].input))
        {
            token->type = g_token_map_list[i].type;
            break;
        }
        i++;
    }

    if (i == NB_TOKENS)
    {
        token->type = WORD;
        token->value = word;
    }
    else
        free(word);

    return token;
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
    while (str[i] != '\0')
    {
        i = skip_space(str, i);

        if (str[i] == '\0')
            break;

        struct token *token = malloc(sizeof(struct token));
        token = match_type(str, token, &i);
        if (!token)
            return NULL;

        l = add_token(l, token);
        if (!l)
            return NULL;
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
    {
        free(lexer_pop(lexer));
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


