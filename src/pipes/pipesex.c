#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    pid_t pid;
    int maxBufferSize = 150;
    int p[2];
    int status;
    char *str;
    char buffer[maxBufferSize];
    int numbytes;

    if(argc <= 1){
        perror("No arguments given"), exit(1);
    }
    if(pipe(p) < 0){
        perror("Failed on creating pipe"), exit(1);
    }
    if((pid=fork())<0){
        perror("Error creating fork"), exit(1);
    } else if (pid == 0){
        /* child */
        printf("Hello from child!\n");
        close(p[1]);
        if((numbytes = read(p[0], buffer, maxBufferSize)) < 0){
            perror("Error reading from pipe"), exit(1);
        }
        printf("Child: %s\n", buffer);
        close(p[0]);

        exit(5);
    } else {
        /* adult */
        str = argv[1];
        printf("parent: %s\n", str);
        close(p[0]);

        if(write(p[1], str, strlen(str)+1)<0){
            perror("Error writing on pipe"), exit(1);
        }
        close(p[1]);

        wait(&status);
        printf("hello from parent! Child exited with code %i\n", WEXITSTATUS(status));
    }
    return 0;
}
