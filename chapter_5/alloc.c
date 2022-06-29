#include <stdio.h>
#define ALLOC_BUFF_MAX_SIZE 1000
static char allocbuf[ALLOC_BUFF_MAX_SIZE]; /* allocation buffer */
static char *allocp = allocbuf;       /* pointer on last element in buffer */
char* alloc(int);    /* allocate memory */;
char* afree(char *);       /* free allocated memory */;
int main(int argc, char** argv) {
}
char* alloc(int size) {
    if(allocbuf + ALLOC_BUFF_MAX_SIZE - allocp >= size) { /* it fits */ 
        allocp+=size;
        return allocp - size;
    } 
    else
        return NULL;
}
char* afree(char* p) { /* free allocated memory */
    if(p>allocbuf && p<=allocbuf+ALLOC_BUFF_MAX_SIZE)
        allocp=p;
}