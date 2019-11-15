#ifndef PARSER_H
#define PARSER_H

struct ast_node;
struct lex;
bool parse_simple_command(struct lex *lexer, struct ast_node *cmd_node);
bool parse_list(struct lex *lexer, struct ast_node *list_node);
#endif
