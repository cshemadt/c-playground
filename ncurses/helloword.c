#include <ncurses.h>
int main() {
    initscr();              /* allocates memory for windows which is called stdscr */
    echo();                 /* enable echoing characters typed by the user (to disable - noecho()) */
    keypad(stdscr,TRUE);    /* enable reading functional keys */
    raw();                  /* disable line buffering (to enable - cbreak()) */
    printw("Hello world");  /* analog of printf */
    refresh();              /* show the changes */
    getch();
    endwin();               /* end of the program */
    return 0;
}