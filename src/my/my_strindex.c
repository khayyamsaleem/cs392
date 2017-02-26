#include "my.h"

/**
 * returns index of first instance of a given 
 * character in a given string. returns -1 if 
 * none found
 */
int my_strindex(char *s, char c){
    //null checks
    if(s == NULL)
        return -1;
    
    int length = my_strlen(s);

    for(int i = 0; i < length; i++){
        if(c == s[i])
            return i;
    }

    return -1;

}
