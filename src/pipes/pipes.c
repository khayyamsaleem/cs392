#include "my.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc <= 1){
        my_str("Usage: ./pipes <message>\n");
        return 1;
    }

    int pipe1[2];
    int pipe2[2];

    if(pipe(pipe1) < 0 || pipe(pipe2) < 0){
        my_str("bad\n");
        return 1;
    }

    pid_t child;
    pid_t gchild;

    if((child = fork()) < 0){
        my_str("child fork error\n");
        return 1;
    } else if (child > 0) { // parent
        if(close(pipe1[0]) < 0){
            my_str("error on close\n");
            return 1;
        }
        int wfd = pipe1[1];

        char *message = my_vect2str(argv + 1);
        my_str("Parent: ");
        my_str(message);
        my_str("\n");
        if(write(wfd, message, my_strlen(message)) < 0){
            my_str("Error on write\n");
            return 1;
        }
        free(message);
        if(close(wfd) < 0){
            my_str("Error on close\n");
            return 1;
        }
        if(wait(NULL) < 0){
            my_str("Error on wait\n");
            return 1;
        }
    } else { //child
        if((gchild = fork()) < 0){
            my_str("Error on fork\n");
            return 1;
        } else if (gchild > 0){
            if(close(pipe1[1]) < 0 || close(pipe2[0]) < 0){
                my_str("Error on close\n");
                return 1;
            }
            int rfd = pipe1[0];
            int wfd = pipe2[1];

            char msg[100] = {0};
            ssize_t size;

            if((size = read(rfd, &msg, 100)) < 0){
                my_str("Error on read\n");
                return 1;
            }
            my_str("Child: ");
            my_str(msg);
            my_str("\n");

            if(write(wfd, msg, size) < 0){
                my_str("Error on write\n");
                return 1;
            }

            if(close(rfd) < 0 || close(wfd) < 0 || wait(NULL) < 0){
                my_str("Error on close\n");
                return 1;
            }
        } else { // grandchild
            if(close(pipe1[0]) < 0 || close(pipe1[1]) < 0 || close(pipe2[1]) < 0){
                my_str("Error on close\n");
                return 1;
            }
            int rfd = pipe2[0];
            char msg[100] = {0};
            if(read(rfd, &msg, 100) < 0){
                my_str("Error on read\n");
                return 1;
            }
            my_str("Grandchild: ");
            my_str(msg);
            my_str("\n");
            if(close(rfd) < 0){
                my_str("Error on close\n");
                return 1;
            }
        }
    }
}
