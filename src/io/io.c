#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int key = 5;
    int r = 1;

    int enc = open("encrypted.txt", O_RDONLY, S_IREAD);
    int sol = open("solution.txt", O_RDWR, S_IWRITE);

    char buf[3];

    while(r != 0){
        r=read(enc, buf, 3);

        for (int i = 0; i < 3; i++){
            int diff = buf[i] - key;
            if(buf[i] <= 'Z' && buf[i] >= 'A'){
                buf[i] = 'A' + (((diff - 'A') % 26) + 26) % 26;
            } else if (buf[i] <= 'z' && buf[i] >= 'a'){
                buf[i] = 'a' + (((diff - 'a') % 26) + 26) % 26;
            } else {
                ;
            }
        }

        write(sol, buf, r);

        key+=2;
    }

    int rc = close(enc);
    rc = close(sol);

}
