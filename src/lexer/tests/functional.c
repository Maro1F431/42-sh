#include "criterion/criterion.h"
#include "../lexer.h"

Test(functional, one_token)
{
    char str[] = "<<";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_peek(l)->type == CHEV_DOUBLE_L);
    cr_assert(lexer_pop(l)->type == CHEV_DOUBLE_L);
    cr_assert(lexer_peek(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}


Test(functional, no_token)
{
    char str[] = "";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}


Test(functional, only_blank)
{
    char str[] = "  	 \n ";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_pop(l)->type == LINE_BREAK);
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}

Test(functional, input_separated_by_spaces)
{
    char str[] = "<< ; (";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_pop(l)->type == CHEV_DOUBLE_L);
    cr_assert(lexer_pop(l)->type == SEMICOL);
    cr_assert(lexer_pop(l)->type == OPEN_PAR);
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}

Test(functional, multiple_spaces)
{
    char str[] = "  <<  	;   (  ";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_pop(l)->type == CHEV_DOUBLE_L);
    cr_assert(lexer_pop(l)->type == SEMICOL);
    cr_assert(lexer_pop(l)->type == OPEN_PAR);
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}


Test(functional, one_word)
{
    char str[] = "ls";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_pop(l)->type == WORD);
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}


Test(functional, multiple_words_word)
{
    char str[] = "echo hello there";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_pop(l)->type == WORD);
    cr_assert(lexer_pop(l)->type == WORD);
    cr_assert(lexer_pop(l)->type == WORD);
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}


Test(functional, multiple_words_values)
{
    char str[] = "echo hello there";

    struct lex *l = lexer_alloc(str);

    cr_assert_str_eq(lexer_pop(l)->value, "echo");
    cr_assert_str_eq(lexer_pop(l)->value, "hello");
    cr_assert_str_eq(lexer_pop(l)->value ,"there");
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}

Test(functional, command_separated_by_operator)
{
    char str[] = "echo ls;echo zouh;";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_pop(l)->type == WORD);
    cr_assert(lexer_pop(l)->type == WORD);
    cr_assert(lexer_pop(l)->type == SEMICOL);
    cr_assert(lexer_pop(l)->type == WORD);
    cr_assert(lexer_pop(l)->type == WORD);
    cr_assert(lexer_pop(l)->type == SEMICOL);
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}




Test(functional, double_chev_simple_chev)
{
    char str[] = "<<<";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_pop(l)->type == CHEV_DOUBLE_L);
    cr_assert(lexer_pop(l)->type == CHEV_SIMPLE_L);
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}



Test(functional, multiple_operators_with_no_space)
{
    char str[] = "<<;!)(";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_pop(l)->type == CHEV_DOUBLE_L);
    cr_assert(lexer_pop(l)->type == SEMICOL);
    cr_assert(lexer_pop(l)->type == EXCLAMATION);
    cr_assert(lexer_pop(l)->type == CLOSE_PAR);
    cr_assert(lexer_pop(l)->type == OPEN_PAR);
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}


Test(functional, pop_command_multi)
{
    char str[] = "echo if;";

    struct lex *l = lexer_alloc(str);

    cr_assert(lexer_pop_command(l)->type == WORD);
    cr_assert(lexer_pop_command(l)->type == WORD);
    cr_assert(lexer_pop_command(l)->type == SEMICOL);
    cr_assert(lexer_pop(l)->type == END_OF_FILE);
    cr_assert(lexer_pop(l) == NULL);
}
