#include "my.h"

/**
 * Returns a pointer to the first 
 * char in the string which matches
 */

char *my_strfind(char *s, char c){

    int i;
    i = my_strindex(s, c);

    if(i == -1 || s == NULL)
        return NULL;

    return s + i;
}
