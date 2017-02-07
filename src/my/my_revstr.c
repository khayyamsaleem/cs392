#include "my.h"
int my_revstr(char* s){
    int l; // length
    int f; // forward pointer
    int b; // backward pointer
    char t; // temp char
    if(s==NULL){
        //null check, return ridiculous val
        return -1;
    }
    l = my_strlen(s); // get length
    f = 0;
    b = l-1; // stopping condition for backwards iterator
    while(f!=b && f<b){ // repeat until indices are not the same
        t = *(s+b);
        *(s+b) = *(s+f);
        *(s+f) = t; // store char in temp to pointer at correct position
        f++; // increment forward pointer
        b--; // decrement backward pointer
    }
    return l;
}
