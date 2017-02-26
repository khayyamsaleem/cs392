#include "my.h"

int my_strrindex(char *s, char c){
    int length;
    int i;

    if(s == NULL)
        return -1;

    length = my_strlen(s);

    for(i = length - 1; i >= 0; i--){
        if(c == s[i]){
            return i;
        }
    }
    return -1;
}
