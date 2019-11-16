#include "../option/option.c"
#include "parse_file.h"
#include <err.h>
#include <sys/stat.h>
#include <unistd.h>
#define GNU_SOURCE

void parse_file(int argc, char *argv[])
{
    struct option opt;
    init_option(&opt);
    int k = parse_option(&opt, argc, argv);
    if (k == argc)
    {
        errx(1, "Missing input or files");
    }
    struct stat finfo;
    int index_files = lstat(argv[k], &finfo);
    if (index_files == -1)
    {
        //create a function parse_command;
    }
    if (S_ISREG(finfo.st_mode))
    {
        printf("Hey I am a regular file");
    }
}
