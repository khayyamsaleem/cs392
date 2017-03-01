#include "my.h"

/**
 * Same as my_strcpy except only copies
 * n chars or until the end of src
 */
char *my_strncpy(char *dst, char *src, int n){

    int i;

    if (src == NULL || dst == NULL)
        return dst;

    i = 0;
    while(src != '\0' && n > 0){
        dst[i] = src[i];
        i++;
        n--;
    }
    dst[i] = '\0';
    
    return dst;
}
