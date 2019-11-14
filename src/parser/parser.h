#ifndef PARSER_H
#define PARSER_H

struct ast_node;
struct lex;
struct ast_node *parse_simple_command(struct lex *lexer);

struct ast_node *parse_list(struct lex *lexer);
#endif
