#include "my.h"

/**
 * Returns a pointer to the last char
 * in the string which matches. returns
 * null if the letter is not found or if
 * input string is null
 */
char *my_strrfind(char *s, char c){
    int i;
    i = my_strrindex(s, c);
    if(s == NULL || i == -1)
        return NULL;
    
    return s + i;
}
