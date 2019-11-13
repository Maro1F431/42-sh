#include <string.h>
#include <ctype.h>
#include <stddef.h>


//increment i while current char is a space
size_t skip_space(char *str, size_t i)
{
    while (isspace(str[i]))
        i++;

    return i;
}

//get length of current_word
size_t get_len(char *str, size_t i)
{
    size_t len = 0;
    while (!isspace(str[i]))
    {
        i++;
        len++;
    }

    return len;
}

// get next word in string str at index *ptr_i
// must increment ptr_i by length of word
static char *get_word(char *str, size_t *ptr_i)
{
    size_t i = *ptr_i;

    i = skip_spaces(str, i);

    size_t len_word = get_len(str, i);

    char *word = malloc((len_word + 1) * sizeof(char));
    if (!word)
        return NULL;

    size_t j = 0;
    while (!isspace(str[i]))
    {
        word[j] = str[i];
        i++;
        j++;
    }
    word[j] = '\0';

    return word;
}



