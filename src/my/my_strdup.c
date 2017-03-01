#include "my.h"

/**
 * Allocates new memory
 * copies str into that new memory
 * returns pointer to that new string
 */
char *my_strdup(char *str){
    int length;
    char *copy;

    if (str == NULL)
        return NULL;

    length = my_strlen(str);
    copy = malloc(length + 1);
    my_strcpy(copy, str);

    return copy;
}
