#include "lexer/lexer.h"
#include "parser/parser.c"
#include "parser/ast.h"
#include "option/option.h"
#include <fcntl.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <pwd.h>
#define GNU_SOURCE
#define SIZE 100

void sigint_handler(int signo) {
}


void interactive_mode(void)
{
    signal(SIGINT, sigint_handler);
    int tty;
    tty = isatty(STDIN_FILENO);
    while (1)
    {
        char *str = readline(tty ? "42sh$ " : NULL);
        if (str == NULL)
        {
            free(str);
            exit (1);
        }
        add_history(str);
        struct lex *l = lexer_alloc(str);
        struct ast_node ast;
        ast_node_init(&ast);
        parse_list(l, &ast);
        execute(&ast);
        ast_node_free_children(&ast);
        lexer_free(l);
        free(str);
    }
}

void parse_file(char *file)
{
    FILE *file_desrciptor = fopen(file, "r");
    if (file_desrciptor == NULL)
    {
        return;
    }
    ssize_t size;
    size_t buffsize;
    char *buff = NULL;
    while ((size = getline(&buff, &buffsize, file_desrciptor)) != -1)
    {
        struct lex *l = lexer_alloc(buff);
        struct ast_node ast;
        ast_node_init(&ast);
        parse_list(l, &ast);
        execute(&ast);
        ast_node_free_children(&ast);
        lexer_free(l);
    }
}

int main(int argc, char *argv[], char *env[])
{
    if (argc == 1)
    {
        char *home = getenv("HOME");
        char *full_path = calloc(sizeof(char), 60);
        sprintf(full_path, "%s/.42shrc", home);
        parse_file("etc/42shrc");
        parse_file(full_path);
        free(full_path);
        interactive_mode();
    }
    else
    {
        struct option opt;
        init_option(&opt);
        int k = parse_option(&opt, argc, argv);
        if (opt.flag_norc == 0)
        {
            char *home = getenv("HOME");
            char *full_path = calloc(sizeof(char), 60);
            sprintf(full_path, "%s/.42shrc", home);
            //puts(full_path);
            parse_file("etc/42shrc");
            parse_file(full_path);
            free(full_path);
        }
        struct stat finfo;
        // change the case k == argc ; interactive mode with option
        int index_files = lstat(argv[k], &finfo);
        if (index_files == -1 && opt.flag_c == 1)
        {
            char *str = calloc(sizeof(char), 50);
            int ind_str = 0;
            for (int i = k; i < argc; i++)
            {
                for (int j = 0; argv[i][j]; j++)
                {
                    str[ind_str] = argv[i][j];
                    ind_str++;
                }
                str[ind_str] = ' ';
                ind_str++;
            }
            struct lex *l = lexer_alloc(str);
            struct ast_node ast;
            ast_node_init(&ast);
            parse_list(l, &ast);
            execute(&ast);
            ast_node_free_children(&ast);
            lexer_free(l);
            free(str);
        }
        if (S_ISREG(finfo.st_mode))
        {
            parse_file(argv[k]);
        }
    }
}

