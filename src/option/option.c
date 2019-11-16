#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "option.h"


void init_option(struct option *opt)
{
    opt->flag_o_plus = 0;
    opt->flag_o_minus = 0;
    opt->flag_norc = 0;
    opt->flag_ast_print = 0;
    opt->flag_c = 0;
}


int parse_option(struct option *opt, int argc, char *argv[])
{
    int longg = 0;
    int i = 1;
    for (i = 1; i < argc; i++)
    {
        //printf("wghut");
        if (strcmp("--norc", argv[i]) ==  0 && longg == 0)
            opt->flag_norc = 1;
        else if (strcmp("--ast-print", argv[i]) == 0 && longg == 0)
            opt->flag_ast_print = 1;
        else if (strcmp("-c", argv[i]) == 0)
        {
            opt->flag_c = 1;
            longg = 1;
        }
        else if (strcmp("+o", argv[i]) == 0)
        {
            opt->flag_o_plus = 1;
            longg = 1;
        }
        else if (strcmp("-o", argv[i]) == 0)
        {
            opt->flag_o_minus = 1;
            longg = 1;
        }
        else
        {
            if (i == argc - 1)
                return i;
            return i + 1;
        }
    }
    return 1;
}
