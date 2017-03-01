#include "my.h"

/**
 * copies src onto end of dst and returns dst
 */
char *my_strcat(char *dst, char *src){
    char *concat;

    if(dst == NULL)
        return NULL;

    concat = dst;

    while(*concat != '\0')
        concat++;

    my_strcpy(concat, src);

    return dst;
}
