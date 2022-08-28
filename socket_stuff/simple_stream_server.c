#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT "3490"
#define BACKLOG 10

void sigchld_handler(int s) {
    int saved_errno = errno;
    while (waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno;
}
void *get_in_addr(struct sockaddr* sa) {
    if(sa->sa_family == AF_INET)
        return &(((struct sockaddr_in *)sa)->sin_addr);
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}
int main(int argc, char **argv) {
    int sock_fd, new_fd;
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr;
    socklen_t addrlen;
    struct sigaction sa;
    int yes = 1;
    char s[INET6_ADDRSTRLEN];
    int rv;
    char *hello = "Hello, world!";

    // Filling hints structure
    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n",gai_strerror(rv));
        return 1;
    }
    for(p = servinfo;p;p=p->ai_next) {
        if((sock_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            fprintf(stderr,"server: socket\n");
            continue;
        }
        if(setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            fprintf(stderr,"setsockopt\n");
            exit(1);
        }
        if(bind(sock_fd, p->ai_addr, p->ai_addrlen) == -1) {
            fprintf(stderr,"server: bind\n");
            continue;
        }
        break;
    }
    if(!p) {
        fprintf(stderr,"server: failed to bind\n");
        exit(1);
    }
    freeaddrinfo(servinfo);
    if(listen(sock_fd, BACKLOG) == -1) {
        fprintf(stderr,"server: listen\n");
        exit(1);
    }
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if(sigaction(SIGCHLD, &sa, NULL) == -1) {
        fprintf(stderr,"server: sigaction\n");
        exit(1);
    }
    printf("server: waiting for connetions...\n");
    while(1) { // main accept() loop
        addrlen = sizeof their_addr;
        if((new_fd = accept(sock_fd, (struct sockaddr *)&their_addr, &addrlen)) == -1) {
            fprintf(stderr,"server: accept\n");
            continue;
        }
        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        printf("server: got connection from: %s\n", s);
        if(!fork()) {
            close(sock_fd);
            if(send(new_fd, hello, strlen(hello),0) == -1)
                fprintf(stderr,"server: send\n");
            close(new_fd);
            exit(0);
        }
        close(new_fd);
    }
    return 0;
}
