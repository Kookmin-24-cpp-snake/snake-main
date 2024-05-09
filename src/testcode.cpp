#include <ncurses.h>
int main(){
    initscr();
    start_color();
    init_pair(1,COLOR_RED,COLOR_WHITE);
    box(stdscr,0,0);
    attron(COLOR_PAIR(1));
    wbkgd(stdscr,COLOR_PAIR(1));

    WINDOW *win=subwin(stdscr,5,60,10,10);
    init_pair(2,COLOR_BLACK,COLOR_BLUE);
    box(win,0,0);
    attron(COLOR_PAIR(2));
    wbkgd(win,COLOR_PAIR(2));
    refresh();
    

    getch();
    delwin(win);
    endwin();
    return 0;
}