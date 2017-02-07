#include "my.h"

/*Prints a string. If string is null or empty, print nothing */
void my_str(char* c){
    if (c!= NULL){
        while(*c !='\0'){
            my_char(*c);
            c++;
        }
    }
}
