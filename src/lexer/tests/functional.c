#include "criterion/criterion.h"
#include "../lexer.h"

Test(functional, one_token)
{
    char str[] = "<<";

    struct lex *l = lexer_alloc(str);

    cr_assert(l->head->type == CHEV_DOUBLE_L);
    cr_assert(l->head->next->type == END_OF_FILE);
    cr_assert(l->head->next->next == NULL);
}


Test(functional, no_token)
{
    char str[] = "";

    struct lex *l = lexer_alloc(str);

    cr_assert(l->head->type == END_OF_FILE);
    cr_assert(l->head->next == NULL);
}


Test(functional, only_blank)
{
    char str[] = "  	 \n ";

    struct lex *l = lexer_alloc(str);

    cr_assert(l->head->type == END_OF_FILE);
    cr_assert(l->head->next == NULL);
}

Test(functional, input_separated_by_spaces)
{
    char str[] = "<< ; (";

    struct lex *l = lexer_alloc(str);

    cr_assert(l->head->type == CHEV_DOUBLE_L);
    cr_assert(l->head->next->type == SEMICOL);
    cr_assert(l->head->next->next->type == OPEN_PAR);
    cr_assert(l->head->next->next->next->type == END_OF_FILE);
    cr_assert(l->head->next->next->next->next == NULL);
}

Test(functional, multiple_spaces)
{
    char str[] = "  <<  	;   (  ";

    struct lex *l = lexer_alloc(str);

    cr_assert(l->head->type == CHEV_DOUBLE_L);
    cr_assert(l->head->next->type == SEMICOL);
    cr_assert(l->head->next->next->type == OPEN_PAR);
    cr_assert(l->head->next->next->next->type == END_OF_FILE);
    cr_assert(l->head->next->next->next->next == NULL);
}


Test(functional, one_word)
{
    char str[] = "ls";

    struct lex *l = lexer_alloc(str);

    cr_assert(l->head->type == WORD);
    cr_assert(l->head->next->type == END_OF_FILE);
    cr_assert(l->head->next->next == NULL);
}