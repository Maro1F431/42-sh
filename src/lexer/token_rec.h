#ifndef TOKEN_REC_H
#define TOKEN_REC_H

#include "token.h"
#include <stddef.h>

struct token_map
{
    char *input;
    enum token_type type;
};

struct token *token_recognition(const char *str, size_t *ptr_i, int mode);

#endif
