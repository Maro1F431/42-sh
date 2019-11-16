#ifndef OPTION_H
#define OPTION_H

struct option
{
    int flag_o_plus;
    int flag_o_minus;
    int flag_ast_print;
    int flag_c;
    int flag_norc;
};

void init_option(struct option *opt);

int parse_option(struct option *opt, int argc, char **argv);

#endif
