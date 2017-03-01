#include "my.h"

/**
 * copies chars from src into dst,
 * overwriting any content already
 * in dst. always copies a '/0'
 * does not allocate any new memory
 */
char *my_strcpy(char *dst, char *src){
    int i;

    if (dst == NULL)
        return NULL;
    if (src == NULL)
        return dst;

    i = 0;
    while(src[i] != '\0'){
        dst[i] = src[i];
        i++;
    }

    dst[i] = '\0';

    return dst;
}
