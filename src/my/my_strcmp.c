#include "my.h"

/**
 * compares strings by ascii value
 * if a == b, -> 0
 * if a < b -> neg num
 * if a > b -> pos num
 * null < any str
 */
int my_strcmp(char *x, char *y){
    int a;
    int b;
    int min;

    a = my_strlen(x);
    b = my_strlen(y);

    min = a > b ? a : b;

    return my_strncmp(x, x, min);
}
