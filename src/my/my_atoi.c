#include "my.h"

/**
 * returns int represented by ascii string
 * handles negs
 * ignores preceding chars and trailing numbers
 * and chars
 * does not allocate memory
 */
int my_atoi(char *s){

    int sign = 1;
    int acc = 0; /*accumulator*/

    if (s == NULL)
        return 0;

    /* while char is not a digit and char* 
     * hasn't terminated */
    while(!('0' <= *s && *s <= '9') && *s != '\0'){
        if (*s == '-') /*found neg sign */
            sign *= -1; /*negate previous sign */
        s++; /* increment char ptr */
    }

    while(*s != '\0' && 
          ('0' <= *s && *s <= '9')){ /* char is a dig */
        acc *= 10;
        acc += *s - '0'; /* distance from 0 = val */
        s++; /* increment char ptr */
    }

    return sign*acc;
}
