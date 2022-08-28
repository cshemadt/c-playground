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
#define MAXDATASIZE 100 

void *get_in_addr(struct sockaddr* sa) {
    if(sa->sa_family == AF_INET)
        return &(((struct sockaddr_in *)sa)->sin_addr);
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}
int main(int argc, char **argv) {
    int socket_fd,numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    
    if(argc != 2) {
        fprintf(stderr, "usage: client <hostname>\n");
        exit(1);
    }
    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if((rv = getaddrinfo(argv[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n",gai_strerror(rv));
        return 1;
    }
    for(p=servinfo;p;p=p->ai_next) {
        if((socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            fprintf(stderr,"client: socket\n");
            continue;
        }
        if(connect(socket_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(socket_fd);
            fprintf(stderr,"client: connect\n");
            continue;
        }
        break;
    }
    if(!p) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }
    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    fprintf(stderr, "client: connecting to %s\n", s);
    freeaddrinfo(servinfo);
    if ((numbytes = recv(socket_fd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("client: received '%s'\n",buf);

    close(socket_fd);

    return 0;
}
