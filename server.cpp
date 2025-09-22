// Most of this code is C with C++ sprinkled in
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <stdlib.h>  // for exit
#include <stdio.h> // For perror

static void die(const char *msg){
    perror(msg); // prints error
    exit(1);
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
    // #left off at https://build-your-own.org/redis/03_hello_cs step 3

}