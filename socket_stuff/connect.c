#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("usage: connect <hostname>");
        return 1;
    }
    int sockfd; // socket descriptor
    int status;
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if((status = getaddrinfo(argv[1], "3490", &hints, &res)) != 0) {
        fprintf(stdout, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }
    sockfd=socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    int cstatus = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if(cstatus != -1)
        printf("Connected.\n");
    return 0;
}
