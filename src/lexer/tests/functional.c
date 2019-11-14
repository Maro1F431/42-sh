#include "criterion/criterion.h"
#include "../lexer.h"

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
