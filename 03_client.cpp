#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void die(const char *msg) {
    perror(msg);
    exit(1);
}


int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        die("socket()");
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(1234);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); //127.0.0.1

    int rv = connect(client_fd, (const struct sockaddr *)&addr, sizeof(addr));
    if(rv){
        die("connect() failed");
    }

    char msg[] = "Hello";
    write(client_fd, msg, strlen(msg));

    char rbuf[64] = {};
    ssize_t n = read(client_fd, rbuf, sizeof(rbuf)-1);
    if(n < 0){
        die("read()");
    }
    printf("server says: %s\n", rbuf);
    close(client_fd);

}