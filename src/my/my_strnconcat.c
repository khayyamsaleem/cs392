#include "my.h"

/**
 * same as my_strconcat except copies all of a
 * and then n chars or all of b, whichever shorter
 */
char *my_strnconcat(char *a, char *b, int n){
    int a_length = my_strlen(a);
    int b_length = my_strlen(b);
    char *out;
    int length;

    if (a == NULL && b == NULL)
        return NULL;
    if (a == NULL){
        length = (b_length < n) ? b_length : n;
        out = malloc(length + 1);
        my_strncpy(out, b, length);
        out[length] = '\0';
        return out;
    }
    if (b == NULL)
        return my_strdup(a);

    b_length = (b_length < n) ? b_length : n;

    out = malloc(a_length + b_length + 1);
    my_strcpy(out, a);
    my_strncpy(out + a_length, b, b_length);
    out[a_length + b_length] = '\0';

    return out;

}
