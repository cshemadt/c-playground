#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdarg.h>
#include <stdlib.h>
#include <fcntl.h>

void error(char *fmt, ...) {
    va_list ap;
    va_start(ap,fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    exit(1);
}
int main(int argc, char **argv) {
    int fd,n;
    char buf[BUFSIZ];
    if(argc != 2)
        error("usage: cat <file>");
    else if((fd=open(argv[1],O_RDONLY, 0)) == -1)
        error("can't read from %s",argv[1]);
    while((n=read(fd,buf,BUFSIZ)) > 0)
        write(1, buf,n);
    return 0;
}
