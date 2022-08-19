#include <unistd.h>
#include <syscall.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#define PERMS 0666
void error(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
int main(int argc, char **argv) {
    int f1,f2,n;
    size_t i = 0;
    char buf[BUFSIZ];
    if(argc != 3) 
        error("Usage: cp from to");
    else if((f1=open(argv[1],O_RDONLY,0)) == -1)
        error("Can't open %s file", argv[1]);
    else if((f2=creat(argv[2],PERMS)) == -1)
        error("Can't create file", argv[2]);
    while((n=read(f1,buf,BUFSIZ)) > 0) {
        if(write(f2,buf,n) != n)
            error("Write error on file", argv[2]);
    }
    return 0;
}
