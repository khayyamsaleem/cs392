#include "my.h"

void my_int(int c){
    int n = c;
    int temp  =c;
    int count;
    int ind;
    if(c<0)
        my_char('-');
    if(c==0)
        my_char('0');
    else{
        /*set counter to zero so temp can be 0 */
        for(count=0; count == 0 || n != 0; count++)
            n /= 10;
        count--;
        while(count>=0){
            temp = c;
            for(ind = 0; ind < count; ind++){
                temp /= 10;
            }
            temp %= 10;
            if(temp<0)
                temp*=-1;
            my_char(temp + '0');
            count--;
        }
    }
}
