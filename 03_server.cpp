// Most of this code is C with C++ sprinkled in
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <stdlib.h>  // for exit
#include <stdio.h> // for perror
#include <unistd.h> // for close
#include <string.h>

static void die(const char *msg){
    perror(msg); // prints error
    exit(1);
}

static void msg(const char * msg){
    printf("%s\n", msg);
}

static void do_something(int connfd) {
    char rbuf[64] = {};
    ssize_t n  = read(connfd, rbuf, sizeof(rbuf) - 1);
    if (n<0){
        msg("read() error");
        return;
    }
    printf("client says: %s\n", rbuf);

    char wbuf[] = "world";
    write(connfd, wbuf, strlen(wbuf));
}

int main() {
    int tcp_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    int val = 1;
    setsockopt(tcp_socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    //Bind to an address
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET; //IPV4
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = htonl(0); // wildcard IP 0.0.0.0

    int rv  = bind(tcp_socket_fd, (const struct sockaddr *)&addr, sizeof(addr)); // Return value
    if (rv) { die("bind()"); } // If bind returns anything other than 0 then it failed
        
    // listen
    rv = listen(tcp_socket_fd, SOMAXCONN);
    if (rv) { die("listen()"); }

    // Enter a loop that accepts and processes each client connection
    while(true) {
        struct sockaddr_in client_addr = {}; //IPv4 Internet domain socket address.
        // Accept needs to know how much space we've allocated for address structure
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(tcp_socket_fd, (struct sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            continue; // error
        }
        do_something(connfd);
        close(connfd);
    }

    // #left off at https://build-your-own.org/redis/03_hello_cs step 3

}