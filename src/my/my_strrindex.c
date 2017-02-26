#include "my.h"

int my_strrindex(char *s, char c){
    if(s == NULL)
        return -1;

    int length = my_strlen(s);

    for(int i = length - 1; i >= 0; i--){
        if(c == s[i]){
            return i;
        }
    }
    return -1;
}
