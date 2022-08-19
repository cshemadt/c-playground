#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <syscall.h>
#define PERMS 0666

#define EOF         (-1)
#define BUFSIZ      8192
#define OPEN_MAX    20

typedef struct _iobuf {
    int  cnt;       /* characters left     */
    char *ptr;      /* next char position  */
    char *base;     /* buffer ptr          */  
    int  flag;      /* mode of file access */
    int  fd;        /* file descriptor     */
} FILE;

#define stdin       (&_iob[0])
#define stdout      (&_iob[1])
#define stderr      (&_iob[2])

enum flags {
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, _READ, 0 },
    { 0, (char *) 0, (char *) 0, _WRITE, 1 } ,
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 },
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     (((p)->flag && _EOF) != 0)
#define ferror(p)   (((p)->flag && _ERR) != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)     (--(p)->cnt >= 0 \
                    ? (unsigned char) *(p)->ptr++ \
                    : _fillbuf(p))
#define putc(x,p)   (++(p)->cnt >= BUFSIZ \
                    ? (unsigned char) * (p)->ptr++ = (x) \
                    : _flushbuf((x),p))
#define getchar()   getc(stdin)
#define putchar(x)  putc((x),stdout)


int _fillbuf(FILE *fp) {
    int bufsize;
    if(((fp->flag) & (_READ | _EOF)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if(!fp->base)
        if( (fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if(--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}
int _flushbuf(int c, FILE *fp) {
    if(!fp)
        return EOF;
    fp->base = (char *)malloc(BUFSIZ);
    if(!fp->base)
        return EOF;
    fp->ptr = fp->base;
    fp->cnt = BUFSIZ;
    *fp->ptr++ = (unsigned char) c;
    fp->cnt--;
    return 0;
}
FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;
    if(*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for(fp=_iob;fp < _iob+OPEN_MAX;fp++)
        if((fp->flag & (_READ | _WRITE)) == 0)
            break;
    if(fp>=_iob+OPEN_MAX)
        return NULL;
    if(*mode == 'w')
        creat(name,PERMS);
    else if (*mode == 'r')
        fd=open(name,O_RDONLY, 0);
    else {
        if((fd=open(name,O_WRONLY,0)) == -1)
            fd=creat(name,PERMS);
        lseek(fd, 0L, 2);
    }
    if(fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}
int fflush(FILE *fp) {
    int ret_val = 0;
    if(fp == NULL) {
        // flush all output streams
        for(size_t i=0;i<OPEN_MAX; i++) {
            if((fp->flag & _WRITE) && (fflush(&_iob[i])==-1))
                ret_val=-1;
        }
    } else {
        if((fp->flag & _WRITE) == 0)
            return -1;
        if(fp->flag & _ERR)
            return -1;
    }
    return ret_val;
}
int fclose(FILE *fp) {
    int fd;
    if(fp == NULL)
        return -1;
    if(fflush(fp) == -1)
        return -1;
    fd = fp->fd;
    fp->cnt=0;
    fp->ptr=NULL;
    if(fp->base)
        free(fp->base);
    fp->base = NULL;
    fp->flag = 0;
    fp->fd = -1;
    return close(fd);
}
int main(void) {
    FILE *fp = fopen("hello.txt","w");
    _fillbuf(fp);
    fclose(fp);
    return 0;
}
