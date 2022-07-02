#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define DELAY 3000
/* global variables */
int WIN_ROW,WIN_COL;
char PLATFORM_CHAR='*';
int PLATFORM_WIDTH = 2;
int PLATFORM_HEIGHT = 6;
int CURR_PLATFORM_POS,CURR_E_PLATFORM_POS;
char ball='o';
int CURR_BALL_POS_X;
int CURR_BALL_POS_Y;
int hor,vert;
char platform[100];
static int score1,score2;
int SCORE_POS_Y,SCORE_X_OFFSET;
int last_score=-1;
char *game_over_string="Game Over!";
void game_restart();
void fill_platform() {
    int i;
    for(i=0;i<PLATFORM_WIDTH*PLATFORM_HEIGHT+PLATFORM_HEIGHT;i++)
        if(i!=0 && (i+1)%(PLATFORM_WIDTH+1)==0) {
            platform[i]='\n';
        }
        else {
            platform[i]=PLATFORM_CHAR;
        }
}
void draw_platforms() {
    for(int r=0;r<PLATFORM_HEIGHT;r++) {
        for(int c=0;c<PLATFORM_WIDTH;c++) {
            mvprintw(CURR_E_PLATFORM_POS-r,WIN_COL-2+c,"%c",PLATFORM_CHAR);
            mvprintw(CURR_PLATFORM_POS-r,0+c,"%c",PLATFORM_CHAR);
        }
    }
}
void draw_borders(WINDOW *w) {
    /* drawing top edge border */ 
    for(int i=0;i<WIN_COL;i++)
        mvwprintw(w,0,i,"x");
    /* drawing bottom edge border */ 
    for(int i=0;i<WIN_COL;i++)
        mvwprintw(w,WIN_ROW-1,i,"x");
    wrefresh(w);
}
void move_ball() {
    switch(vert) {
        case 1:
            if(CURR_BALL_POS_Y > 1)
                CURR_BALL_POS_Y--;
            else 
                vert*=-1;
            break;
        case -1:
            if(CURR_BALL_POS_Y < WIN_ROW-2)
                CURR_BALL_POS_Y++;
            else
                vert*=-1;
            break;
    }
    switch(hor) {
        case 1:
            if(CURR_BALL_POS_X < WIN_COL)
                CURR_BALL_POS_X++;
            if(CURR_BALL_POS_X == WIN_COL-PLATFORM_WIDTH-1 && (CURR_BALL_POS_Y <= CURR_E_PLATFORM_POS && CURR_BALL_POS_Y >= CURR_E_PLATFORM_POS-PLATFORM_HEIGHT))
                hor*=-1;
            else if(CURR_BALL_POS_X == WIN_COL) {
                game_restart();
                score1++;
            }
            break;
        case -1:
            if(CURR_BALL_POS_X > 0)
                CURR_BALL_POS_X--;
            /* detecting collision */
            if(CURR_BALL_POS_X == PLATFORM_WIDTH && (CURR_BALL_POS_Y <= CURR_PLATFORM_POS && CURR_BALL_POS_Y >= CURR_PLATFORM_POS-PLATFORM_HEIGHT)) {
                hor*=-1;
            }
            else if(CURR_BALL_POS_X == 0) {
                game_restart();
                score2++;
            }
            break;
        }
}
void game_restart() {
    CURR_BALL_POS_X = (WIN_COL-1)/2;
    CURR_BALL_POS_Y = WIN_ROW/2;
    CURR_PLATFORM_POS=(WIN_ROW-PLATFORM_HEIGHT/2)/2; 
    CURR_E_PLATFORM_POS = (WIN_ROW-PLATFORM_HEIGHT/2)/2;
    hor=-last_score;
    vert=-last_score;
}
int main(int argc, char **argv) {
    int ch;
    initscr();
    noecho();
    cbreak();
    timeout(60);
    curs_set(0);
    keypad(stdscr,TRUE);
    getmaxyx(stdscr,WIN_ROW,WIN_COL);
    game_restart();
    SCORE_X_OFFSET = 3;
    SCORE_POS_Y = 4;
    fill_platform();
    /* main loop */
    while(1) {
        clear();
        draw_platforms();
        draw_borders(stdscr);
        mvvline(1,WIN_COL/2,ACS_VLINE,WIN_ROW-2); /* drawing middle line */
        mvprintw(CURR_BALL_POS_Y,CURR_BALL_POS_X,"%c",ball); /* drawing ball */
        mvprintw(SCORE_POS_Y,WIN_COL/2-SCORE_X_OFFSET,"%d",score1);
        mvprintw(SCORE_POS_Y,WIN_COL/2+SCORE_X_OFFSET,"%d",score2);
        move_ball();
        switch(ch=getch()) {
            case KEY_UP:
                if(CURR_PLATFORM_POS > PLATFORM_HEIGHT) {
                    CURR_PLATFORM_POS--;
                    draw_platforms();
                }
                break;
            case KEY_DOWN:
                if(CURR_PLATFORM_POS < WIN_ROW-2){
                    CURR_PLATFORM_POS++;
                    draw_platforms();
                }
                break;
            case 'q':
                if(CURR_E_PLATFORM_POS > PLATFORM_HEIGHT) {
                    CURR_E_PLATFORM_POS--;
                    draw_platforms();
                }
                break;
            case 'a':
                if(CURR_E_PLATFORM_POS < WIN_ROW-2){
                    CURR_E_PLATFORM_POS++;
                    draw_platforms();
                }

                break;
        }
        usleep(2000);
        refresh();
    }
    endwin();
}