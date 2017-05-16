#include "my.h"
#include "list.h"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <ncurses.h>
#include <term.h>

void setup(){
    initscr();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    erase();
    clear();
    noecho();
    start_color();
    if ( has_colors() && COLOR_PAIRS >= 2) {
        init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
    }
}


int main(int argc, char* argv[]) {
    int sockfd, n, ch, new_line, line_jump, y_diff, last_char_x;
    struct sockaddr_in server;
    struct hostent *hp;
    char username[100];
    char bufferi[1024];
    char buffero[1124];
    char* exit_sequence = "garbage";
    fd_set readfds;
    int x = 1;
    int y = 0;
    int last_char = 0;
    int char_pos = 0;

    if (argc != 3) {
        my_str("Usage: ./client <host> <port>");
        exit(0);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        my_str("error while creating socket\n");
        exit(0);
    }
    hp = gethostbyname(argv[1]);
    if (hp == 0) {
        my_str("error while getting host\n");
        exit(0);
    }
    bzero((char *) &server, sizeof(server));
    server.sin_family = AF_INET;
    bcopy((char *)hp->h_addr_list[0], (char *)&server.sin_addr.s_addr, hp->h_length);
    server.sin_port = htons(atoi(argv[2]));


    setup();
    x = 25;
    color_set(2, NULL);
    printw("Please enter a username: ");
    move(y, x);
    while( (ch = getch()) != 10) {
        color_set(1, NULL);
        if (ch == KEY_RESIZE) {
            refresh();
        }
        else if (ch == KEY_BACKSPACE) {
            if ((y == 0 && x > 25) || y > 0) {
                if (char_pos > 0) {
                    char_pos--;
                    last_char--;
                }
                if (char_pos == last_char)
                    username[char_pos] = '\0';
                else {
                    for (int i = char_pos; i <= last_char; i++) {
                        username[i] = username[i+1];
                    }
                }
                move(0, 25);
                clrtobot();
                addstr(username);
                if (x > 0) {
                    x--;
                }
                else {
                    x = COLS - 1;
                    y--;
                }
                move(y, x);
            }
        }
        else if (ch == KEY_DC) {
            if (char_pos < last_char) {
                for (int i = char_pos; i <= last_char; i++) {
                    username[i] = username[i + 1];
                }
                move(0, 25);
                clrtobot();
                addstr(username);
                last_char--;
                move(y, x);
            }
        }
        else if (ch == KEY_LEFT) {
            if ((y == 0 && x > 25) || y > 0) {
                if (x > 0) {
                    x--;
                }
                else {
                    x = COLS - 1;
                    y--;
                }
                move(y, x);
                char_pos--;
            }
        }
        else if (ch == KEY_RIGHT) {
            if (char_pos < last_char) {
                if (x < COLS - 1) {
                    x++;
                }
                else {
                    x = 0;
                    y++;
                }
                move(y, x);
                char_pos++;
            }
        }
        else if (ch >= 32 && ch <= 126){
            if (last_char < 99) {
                if (char_pos != last_char) {
                    for (int i = last_char + 1; i > char_pos; i--) {
                        username[i] = username[i - 1];
                    }
                    username[char_pos] = (char)ch;
                    move(0, 25);
                    clrtobot();
                    addstr(username);
                }
                else {
                    username[last_char] = (char)ch;
                    username[last_char + 1] = '\0';
                    addch(ch);
                }
                char_pos++;
                last_char++;
                if (x < COLS - 1) {
                    x++;
                }
                else {
                    x = 0;
                    y++;
                }
                move(y, x);
            }
        }
    }

    last_char = 0;
    char_pos = 0;
    x = 0;
    y++;
    move(y, x);
    new_line = y;

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        endwin();
        my_str("Connection error\n");
        exit(0);
    }

    if ((n = write(sockfd, username, 100)) < 0) {
        endwin();
        my_str("Write Error: error writing to socket\n");
        exit(0);
    }

    nodelay(stdscr, TRUE);
    bzero(bufferi, 1024);

    while(1) {
        FD_ZERO(&readfds);
        FD_SET(0, &readfds);
        FD_SET(sockfd, &readfds);
        color_set(1, NULL);

        select(sockfd+1, &readfds, NULL, NULL, NULL);
        if(FD_ISSET(sockfd, &readfds)) {
            bzero(buffero, 1124);
            color_set(2, NULL);

            if ((n = read(sockfd,buffero,1124)) <= 0) {
                printw("Server closed. Exiting...");
                endwin();
                exit(0);
            }
            if (my_strcmp(exit_sequence, &buffero[0]) == 0) {
                printw("Exit Successful");
                endwin();
                exit(0);
            }
            move(new_line, 0);
            clrtobot();
            y_diff = y - new_line;
            addstr(buffero);
            line_jump = (my_strlen(buffero) / COLS) + 1;
            if (y < LINES - line_jump) {
                new_line += line_jump;
                y = new_line;
            }
            else {
                new_line = LINES - 1;
                y = LINES - 1;
                printw("\n");
            }
            move(y, 0);
            if (my_strlen(bufferi) > 0) {
                line_jump = (my_strlen(bufferi) / COLS) + 1;
                color_set(1, NULL);
                addstr(bufferi);
                if (y < LINES - line_jump) {
                    new_line = y;
                    y = new_line + y_diff;
                }
                else {
                    new_line = LINES - line_jump;
                    y = new_line + y_diff;
                }
                move(y, x);
            }
            else {
                x = 0;
            }
        }

        ch = getch();
        if (ch == ERR) {}
        else if (ch == 10) {
            if ((n = write(sockfd, bufferi, 1024)) < 0) {
                printw("error while writing.");
                endwin();
                exit(0);
            }
            bzero(bufferi, 1024);
            move(new_line, 0);
            clrtobot();
            char_pos = 0;
            last_char = 0;
            x = 0;
        }
        else if (ch == KEY_RESIZE) {
            int a, b;
            getmaxyx(stdscr, a, b);
            wresize(stdscr, a, b);
        }
        else if (ch == KEY_BACKSPACE) {
            if (x > 0 || y != new_line) {
                if (char_pos > 0) {
                    char_pos--;
                    last_char--;
                }
                if (char_pos == last_char)
                    bufferi[char_pos] = '\0';
                else {
                    for (int i = char_pos; i <= last_char; i++) {
                        bufferi[i] = bufferi[i+1];
                    }
                }
                move(new_line, 0);
                clrtobot();
                addstr(bufferi);
                if (x > 0) {
                    x--;
                }
                else {
                    x = COLS - 1;
                    y--;
                }
                move(y, x);
            }
        }
        else if (ch == KEY_DC) {
            if (char_pos < last_char) {
                for (int i = char_pos; i <= last_char; i++) {
                    bufferi[i] = bufferi[i + 1];
                }
                move(new_line, 0);
                clrtobot();
                addstr(bufferi);
                last_char--;
                move(y, x);
            }
        }
        else if (ch == KEY_LEFT) {
            if (x > 0 || y != new_line) {
                if (x > 0) {
                    x--;
                }
                else {
                    x = COLS - 1;
                    y--;
                }
                move(y, x);
                char_pos--;
            }
        }
        else if (ch == KEY_RIGHT) {
            if (char_pos < last_char) {
                if (x < COLS - 1) {
                    x++;
                }
                else {
                    x = 0;
                    y++;
                }
                move(y, x);
                char_pos++;
            }
        }
        else if (ch >= 32 && ch <= 126){
            if (last_char < 1023) {
                if (char_pos != last_char) {
                    for (int i = last_char + 1; i > char_pos; i--) {
                        bufferi[i] = bufferi[i - 1];
                    }
                    bufferi[char_pos] = (char)ch;
                    line_jump = ((my_strlen(bufferi) - 1) / COLS) + 1;
                    y_diff = y - new_line;
                    last_char_x = last_char - (COLS * (line_jump - 1));
                    move(new_line, 0);
                    if (y >= LINES - line_jump && last_char_x == COLS - 1 && last_char > 0) {
                        new_line--;
                        y--;
                    }
                    clrtobot();
                    addstr(bufferi);
                    if (x < COLS - 1) {
                        x++;
                    }
                    else {
                        x = 0;
                        y++;
                    }
                }
                else {
                    bufferi[last_char] = (char)ch;
                    bufferi[last_char + 1] = '\0';
                    addch(ch);
                    if (x < COLS - 1) {
                        x++;
                    }
                    else {
                        x = 0;
                        if (y < LINES - 1) {
                            y++;
                        }
                        else {
                            new_line--;
                        }
                    }
                }
                char_pos++;
                last_char++;
                move(y, x);
            }
        }
        refresh();
    }
    close(sockfd);
    endwin();
    return 0;
}
