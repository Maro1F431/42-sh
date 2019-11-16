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
#define GNU_SOURCE
#define SIZE 100
void interactive_mode(void)
{
    char *str = readline("42sh ");
    if (str == NULL)
        exit (1);
    add_history(str);
    struct lex *l = lexer_alloc(str);
    struct ast_node ast;
    ast_node_init(&ast);
    parse_list(l, &ast);
    execute(&ast);
}

void parse_file(char *file)
{
    FILE *file_desrciptor = fopen(file, "r");
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

int main(int argc, char *argv[])
{
    if (argc == 1)
        interactive_mode();
    else
    {
        struct option opt;
        init_option(&opt);
        int k = parse_option(&opt, argc, argv);
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
        }
        if (S_ISREG(finfo.st_mode))
        {
            parse_file(argv[k]);
        }
    }
    /*char str[] = "echo wow ; echo omg ; if echo 1 then echo 2 else echo 3 ;";
    struct lex *l = lexer_alloc(str);
    struct ast_node ast;
    ast_node_init(&ast);
    if (parse_list(l, &ast))
        printf("succes\n");
    else
        printf("failure\n");
    print_ast(&ast);
    //char *test = ast.children[0].children[0].data;
    //printf("test %d", ast.children[0].children[0].type);
    //printf("EXEC TIME\n");
    execute(&ast);
    ast_node_free_children(&ast);
    lexer_free(l);*/
}

