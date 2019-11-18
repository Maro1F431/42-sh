#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "../lexer/lexer.h"

bool parse_simple_command(struct lex *lexer, struct ast_node *s_cmd_node);
bool parse_rule_if(struct lex *lexer, struct ast_node *if_node);
bool parse_command(struct lex *lexer, struct ast_node *cmd_node);
bool parse_compound_list(struct lex *lexer, struct ast_node *cl_node);
bool parse_compound_list_break(struct lex *lexer, struct ast_node *clb_node);
bool parse_list(struct lex *lexer, struct ast_node *list_node);
void parse_input(struct lex *lexer, struct ast_node *input_node);
bool double_check_tty(struct lex *lexer, unsigned token_type);
void skip_line_break(struct lex *lexer);

#endif
