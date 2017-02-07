#include "my.h"

int my_strlen(char* c){
    int l;
    l=0;
    if(c ==NULL){
        l =-1;
    }else {
        while(*c!= '\0'){
            l++;
            c++;
        }
    }
    return l;
}
