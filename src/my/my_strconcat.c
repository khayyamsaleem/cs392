#include "my.h"

/**
 * Allocates new memory
 * copies concatenated strings into new memory
 * returns pointer to location of concatenated strings
 * if both null, return null
 */
char *my_strconcat(char *a, char *b){

    int a_length;
    int b_length;
    char *out;

    if (a == NULL && b == NULL)
        return NULL;

    if (a == NULL)
        return my_strdup(b);

    if (b == NULL)
        return my_strdup(a);

    a_length = my_strlen(a);
    b_length = my_strlen(b);
    out = malloc(a_length + b_length + 1);
    my_strcpy(out, a);
    my_strcpy(out + a_length, b);

    return out;
}
