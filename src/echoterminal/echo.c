#include <curses.h>
#include <stdlib.h>

void setup(){
    initscr();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    idlok(stdscr, TRUE);
    refresh();
    if(has_colors()){
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK); 
    }
    clear();
}

int main(){
    char *buf = malloc(sizeof(char)*1024);
    int c = 0;
    int key = 0;

    setup();

    while(key != 23){
        key = wgetch(stdscr);
        if(key < 127 && key > 31)
            buf[c++] = (char) key;
        else if (key == KEY_DOWN || key == 13 || key == 10){
            attron(COLOR_PAIR(1));
            int x,y;
            buf[c] = '\0';
            getyx(stdscr, y,x);
            move(y+1, 0);
            addch('\n');
            attron(COLOR_PAIR(2));
            addstr(buf);
            attroff(COLOR_PAIR(2));
            buf[0] = '\0';
            c = 0;
            getyx(stdscr, y, x);
            move(y+1, 0);
            addch('\n');
        }
    }
    endwin();
    exit(0);
}
