#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 


int tcp_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
bind(tcp_socket_fd, address);
int val = 1;
setsockopt(tcp_socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

#left off at https://build-your-own.org/redis/03_hello_cs step 3