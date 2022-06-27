#include <stdio.h>
#include "calc.h"
#define MAX_BUFF_SIZE 100
int buffer[MAX_BUFF_SIZE];
int curr_buffer_position=0;
/* pop char from buffer */
int getch() {
    return (curr_buffer_position>0)?buffer[--curr_buffer_position]:getchar();
}
/* push char into buffer */
void ungetch(int c) {
    if(curr_buffer_position>=MAX_BUFF_SIZE)
        printf("Too many characters\n");
    else
        buffer[curr_buffer_position++]=c;
}