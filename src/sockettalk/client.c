#include "my.h"
#include <errno.h>
#include <netdb.h>
#include <poll.h>
#include <signal.h>
#include <sys/socket.h>

//0 if stopped, 1 if running
int status;

char *get_input(){
    char *buffer = calloc(1, 1024 + 1);
    int s = read(0, buffer, 1024);

    //reached end of input
    if (s == 0) {
        free(buffer);
        return NULL;
    }
    
    if (s < 0){ //error case
        perror("error while reading input.");
        free(buffer);
        return NULL;
    }

    if (buffer[s - 1] == '\n'){
        buffer[s-1] = '\0'; //terminate input
    }
    buffer[s] = '\0';

    return buffer;
}

char *get_sock(int fd){
    char *buffer = calloc(1, 1024 + 1);
    int s = recv(fd, buffer, 1024, 0);

    //error cases
    if (s == 0) {
        my_str("The server has disconnected.\n");
        free(buffer);
        return NULL;
    }

    if (s < 0){
        perror("Receipt error");
        free(buffer);
        return NULL;
    }

    //null-terminate
    buffer[s] = '\0';
    return buffer;
}

void kill_client_conn(){
    status = 0;
}

int main(int argc, char *argv[]){
    if (argc != 3){
        my_str("Usage: ./client <host> <port>\n");
        return 1;
    }

    //store arguments
    char *host = argv[1];
    int p = my_atoi(argv[2]);



    
}
