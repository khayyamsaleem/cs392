#include "my.h"

/**
 * Prints a number using the length of the string as the base and the contents as the alphabet
 * (9, "RFTM") -> "FT"
 */
void my_num_base(int a, char *s){

    int base; 
    long num;
    int i = 0;
    char out[32];


    /*if string is null*/
    if (s == NULL || *s == '\0'){
        my_str("Error: string was null");
        return;
    }

    base = my_strlen(s);

    num = a; /* to account for min_int */

    /* if number is negative */
    if (num < 0){
        my_char('-');
        num = -num;
    }

    /* if number is zero */
    if (num == 0){
        my_char(s[0]);
        return;
    }

    /* if base 1, then essentially tally marks */
    if (base == 1){
        for(i = 0; i < num; i++)
            my_char(s[0]);
        return;
    }

    /* start at 1th cell bc base 1 case has been handled */
    while (num > 0){
        out[i++] = s[num % base];
        num /= base;
    }
    out[i] = '\0';

    /* output reversed, must fix */
    my_revstr(out);
    my_str(out);

}
