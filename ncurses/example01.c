#include <ncurses.h>
int main() {
    int ch;
    char *msg="Message\n";
    initscr();
    raw();
    keypad(stdscr,TRUE);
    noecho();
    mvprintw(1,2,msg);
    ch=getch();
    if(ch==KEY_F(2))
        printw("F2 key pressed\n");
    else {
        printw("The pressed key is ");
        attron(A_BOLD);
        printw("%c\n",ch);
        attroff(A_BOLD);
    }
    refresh();
    getch();
    endwin();
}