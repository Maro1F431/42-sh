#include "lexer.h"
#include "token.h"
#include "token_rec.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NB_TOKENS 35

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
** \brief associate a token type to a word of the input string
**
** \return the matched token
** \param token the token that has to have its type modified
** \param str the input string
** \param ptr_i a pointer to the index where the word to identify starts
*/
static struct token *match_type(char *word, struct token *token, int mode)
{
    if (word[0] == '\0')
    {
        token->type = END_OF_FILE;
        free(word);
        return token;
    }

    unsigned i = 0;
    while (i < NB_TOKENS)
    {
        if (!strcmp(word, g_token_map_list[i].input))
        {
            int type = g_token_map_list[i].type;
            if (mode == MODE_CMD && type >= WHILE && type <= FUNCTION)
            {
                token->type = WORD;
                token->value = word;
            }
            else
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

    if (token->type != WORD)
        free(word);

    return token;
}


static char *end_of_file(void)
{
    char *res = malloc(sizeof(char));
    res[0] = '\0';

    return res;
}


static char *delimit(const char *str, int start, int end)
{
    if (end <= start)
        return NULL;

    size_t len = end - start;
    char *res = malloc((len + 1) * sizeof(char));

    for (size_t i = 0; i < len; i++)
    {
        res[i] = str[start + i];
    }
    res[len] = '\0';

    return res;
}


/*
 * \brief Check if string between start and end in str
 *  can be part of an operator
*/
static int is_operator(const char *str, int start, int end)
{
    char *word = delimit(str, start, end);
    int token_type = -1;

    unsigned i = 0;
    while (i < NB_TOKENS)
    {
        if (!strncmp(word, g_token_map_list[i].input, end - start))
        {
            token_type = g_token_map_list[i].type;
            break;
        }
        i++;
    }

    free(word);
    return (token_type >= AMPERSAND && token_type <= CHEV_SIMPLE_L);
}


static int is_word(const char *str, int start, int end)
{
    return !is_operator(str, start, end);
}


static char *get_next_token(const char *str, size_t *ptr_i)
{
    int i = *ptr_i;

    int delimited = 0;
    int start = i;

    char *res = end_of_file();

    while (!delimited || start == i)
    {
        if (!str)
        {
            //return eof
            *ptr_i = i + 1;
            return res;
        }
        //1
        else if (str[i] == '\0' && start != i)
        {
            //delimiter le token
            delimited = 1;
        }
        //2,3
        else if (start < i && is_operator(str, start, i))
        {
            if (is_operator(str, start, i + 1))
                i++;
            else
            {
                //delimiter
                delimited = 1;
            }
        }
        //6
        else if (is_operator(str, i, i + 1))
        {
            if (start == i)
                i++;
            else
            {
                //delimiter
                delimited = 1;
            }
        }
        //7
        else if (str[i] == '\n')
        {
            //delimiter
            delimited = 1;
        }
        //8
        else if (isblank(str[i]))
        {
            if (start == i)
            {
                start++;
                i++;
            }
            else
            {
                //delimiter
                delimited = 1;
            }
        }
        //9
        else if (is_word(str, start, i))
        {
            i++;
        }
        else // 11
        {
            start = i;
        }
    }

    free(res);
    res = delimit(str, start, i);
    *ptr_i = i;
    return res;
}


/*
 * \ brief Returns next token
*/
struct token *token_recognition(const char *str, size_t *ptr_i, int mode)
{
    char *next_token_word = get_next_token(str, ptr_i);
    struct token *new_token = init_token();

    match_type(next_token_word, new_token, mode);

    return new_token;
}


