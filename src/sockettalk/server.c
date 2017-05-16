//Khayyam Saleem
//I pledge my honor that I have abided by the Stevens Honor System.
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <strings.h>
#include "my.h"
#include "list.h"


//struct to define client
struct client {
    int fd;
    char* usr;
    struct hostent *h;
    char *hostaddr;
};

//client constructor
struct client* user(int fd, char* usr, struct hostent* h, char* hostaddr){
    struct client* cli = (struct client*)malloc(sizeof(struct client));
    cli->fd = fd;
    cli->usr = usr;
    cli->h = h;
    cli->hostaddr = hostaddr;
    return cli;
}

int spec_options(char msg[512]){
    char *cmd  = (char *)malloc(sizeof(char) * 7);
    int i = 0; //maintains current char index
    for(i = 0; i < 4; i++){
        cmd[i] = msg[i];
    }
    if(my_strcmp(cmd, "/me ") == 0){
        return 1;
    } else {
        //advance to length of longest possible special cmd
        cmd[i] = msg[i];
        cmd[i+1] = msg[i+1];
        if(my_strcmp(cmd, "/nick ") == 0){
            return 2;
        } else if (my_strcmp(cmd, "/exit") == 0 || my_strcmp(cmd, "/exit ") == 0){
            return 3;
        } else {
            return -1;
        }
    }
}

char* get_usr(char buf[1024]){
    int x = my_strlen(buf);
    char *usr = (char*)malloc(sizeof(char) * (x+1)); //leaving space for null terminator
    int i = 0;
    for (i = 0; i < x; i++){
        usr[i] = buf[i];
    }
    usr[i] = '\0';
    return usr;
}

//commands


int main(int argc, char* argv[]){
    struct sockaddr_in server;
    struct sockaddr_in cli;
    char buf[100];
    char msg[1024];
    int options;
    int n;
    int port;
    socklen_t cli_len;
    int cfd;
    int pfd;
    struct hostent *h;
    char *hostaddr;
    int c = 0;

    if(argc != 2){
        my_str("Usage: ./server <port>\n");
        return 1;
    }

    port = my_atoi(argv[1]);
    pfd = socket(AF_INET, SOCK_STREAM, 0);
    if (pfd < 0){
        my_str("error while creating socket\n");
        return 1;
    }

    options = 1;
    if(setsockopt(pfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&options, sizeof(int)) < 0){
        my_str("error occurred with setsockopt\n");
        return 1;
    }

    bzero((char *)&server, sizeof(server));
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons((unsigned short)port);
    server.sin_family = AF_INET;

    int x = bind(pfd, (struct sockaddr *)&server, sizeof(server));
    if(x < 0){
        my_str("Error while binding\n");
        return 1;
    }

    my_str("Server is running...\n");

    x = listen(pfd, 20);
    if(x < 0){
        my_str("Error while listening\n");
        return 1;
    }

    fd_set r;

    cli_len = sizeof(cli);
    int users = 0;
    int max_fd = 0;
    struct s_node* head = (struct s_node*)malloc(sizeof(struct s_node));
    head = NULL;
    struct s_node* t;
    struct client* u = (struct client*)malloc(sizeof(struct client));


    //continuous run, only breaks on certain conditions
    while(1){
        FD_ZERO(&r);
        FD_SET(0, &r);
        FD_SET(pfd, &r);
        t = head; //traversal node

        //traverse list
        while(t != NULL){
            u = t->elem;
            FD_SET(u->fd, &r);
            if(u->fd > max_fd)
                max_fd = u->fd;
            t = t->next;
        }

        if(max_fd < pfd){
            max_fd = pfd;
        }

        select(max_fd+1, &r, NULL, NULL, NULL);

        if(FD_ISSET(pfd, &r)){
            if((cfd = accept(pfd, (struct sockaddr *)&cli, &cli_len)) < 0){
                my_str("Error accepting\n");
                return 1;
            }
            for(int i = 0; i < users; i++){
                u = elem_at(head, i);
                if (cfd == u->fd)
                    c = 1;

            }
            if(c == 0){
                h = gethostbyaddr((const char *)&cli.sin_addr.s_addr, sizeof(cli.sin_addr.s_addr), AF_INET);
                if (h == NULL){
                    my_str("error with gethostbyaddr\n");
                    return 1;
                }
                hostaddr = inet_ntoa(cli.sin_addr);
                if(hostaddr == NULL){
                    my_str("error with inet_ntoa\n");
                    return 1;
                }
                my_str(h->h_name);
                my_str(" has now joined the server!\n");
                my_str("hostaddr: ");
                my_str(hostaddr);
                my_str("\n");

                bzero(buf, 1024);

                if ((n = read(cfd, buf, 100)) < 0){
                    my_str("error reading socket.\n");
                    return 1;
                }

                if(n > 0){
                    char *usr = get_usr(buf);

                    append(new_node(user(cfd, usr, h, hostaddr)), &head);

                    users = count_s_nodes(head);

                    char* init_msg = my_strconcat(usr, " is now on the chat!");

                    my_str(my_strconcat(init_msg, "\n"));

                    for (int i = 0; i < users; i++){
                        u = elem_at(head, i);
                        if ((n = write(u->fd, init_msg, my_strlen(init_msg))) < 0){
                            my_str("Error writing to socket!\n");
                            return 1;
                        }
                    }
                }
            }

            c = 0;
        }

        users = count_s_nodes(head);
        for(int i = 0; i < users; i++){
            u = elem_at(head, i);
            if(FD_ISSET(u->fd, &r)){
                bzero(msg, 1024);
                if ((n = read(u->fd, msg, 1024)) < 0){
                    my_str("error while reading socket\n");
                    return 1;
                }
                if (n == 0){
                    char* name = u->usr;
                    free(remove_node_at(&head, i));
                    users-=1;

                    char* exit_msg = my_strconcat(name, " has left the chat.");
                    my_str(my_strconcat(exit_msg, "\n"));
                    for(int i = 0; i < users; i++){
                        u = elem_at(head, i);
                        int msg_len = my_strlen(exit_msg);
                        if((n = write(u->fd, exit_msg, msg_len)) < 0){
                            my_str("error while writing\n");
                            return 1;
                        }
                    }
                } else if (msg[0] == '/'){
                    int special = spec_options(&msg[0]);
                    switch(special){
                        case 1:
                            {
                            char* usr_msg = my_strconcat(u->usr, &msg[3]);
                            my_str(my_strconcat(usr_msg, "\n"));
                            for(int i = 0; i < users; i++){
                                u = elem_at(head, i);
                                if ((n = write(u->fd, usr_msg, my_strlen(usr_msg))) < 0){
                                    my_str("Error while writing\n");
                                    return 1;
                                }
                            }
                            break;
                            }
                        case 2:
                            {
                            char* new_name = (char *)malloc(sizeof(char) * 1024);
                            my_strcpy(new_name, &msg[6]);
                            u->usr = new_name;
                            char* show_msg = my_strconcat(u->usr, my_strconcat(" is now ", new_name));
                            my_str(my_strconcat(show_msg, "\n"));
                            for(int i = 0; i < users; i++){
                                u = elem_at(head, i);
                                if ((n = write(u->fd, show_msg, my_strlen(show_msg))) < 0){
                                    my_str("error while writing!\n");
                                    return 1;
                                }
                            }
                            break;
                            }
                        case 3:
                            {
                            char* exit_msg = my_strconcat(u->usr, " has left the chat!");
                            char* gib = "garbage";
                            my_str(my_strconcat(exit_msg, "\n"));
                            if((n = write(u->fd, gib, my_strlen(gib))) < 0){
                                my_str("error while writing\n");
                                return 1;
                            }
                            free(remove_node_at(&head, i));
                            users-=1;
                            for(int i = 0; i < users; i++){
                                u = elem_at(head, i);
                                if((n = write(u->fd, exit_msg, my_strlen(exit_msg))) < 0){
                                    my_str("error while writing\n");
                                    return 1;
                                }
                            }
                            break;
                            }
                        default:
                            {
                            char* invalid_msg = "Valid commands: /nick <text>, /me <text>, /exit";
                            my_str(invalid_msg);
                            my_char('\n');
                            if ((n = write(u->fd, invalid_msg, my_strlen(invalid_msg))) < 0) {
                                my_str("error while writing\n");
                                return 1;
                            }
                            break;
                            }
                    }
                } else {
                    char* usr_message = my_strconcat(my_strconcat(u->usr, ": "), msg);
                    my_str(my_strconcat(usr_message, "\n"));
                    for(int i = 0; i < users; i++){
                        u = elem_at(head, i);
                        if((n = write(u->fd, usr_message, my_strlen(usr_message))) < 0){
                            my_str("error while writing!\n");
                            return 1;
                        }
                    }
                }
            }
        }
    }

    //cleanup for no memory leaks!
    while(head != NULL){
        u = head->elem;
        close(u->fd);
        head = head->next;
        free(head->prev);
    }

    free(buf);
    free(msg);
    free(&head);
    free(u);
    return 0;
}
