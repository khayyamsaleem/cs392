#include "my.h"

/**
 * same as my_strcmp except only compares n chars 
 * or until the end of the string has been reached
 */
int my_strncmp(char *x, char *y, int n){
    if (x == NULL && y == NULL)
        return 0;

    if (x == NULL)
        return -1;

    if (y == NULL)
        return 1;

    if (n < 0)
        return 0;

    while(n > 0 && *x == *y){
        x++;
        y++;
        n--;
    }

    return (n == 0) ? (0) : (*x - *y);
} 
