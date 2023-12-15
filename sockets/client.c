#include <arpa/inet.h>   // ntohs()
#include <stdio.h>       // printf(), perror()
#include <stdlib.h>      // atoi()
#include <string.h>      // strlen()
#include <sys/socket.h>  // socket(), connect(), send(), recv()
#include <unistd.h>      // close()

#include "helpers.h"  // make_client_sockaddr()

static const int MAX_MESSAGE_SIZE = 256;

// sends a string message to the server
int send_message(const char *hostname, int port, const char *message) {
    // create a socket

    // create a sockaddr_in to specify remote host and port

    // connect to remote server

    // send message to remote server

    // close connection

    return 0;
}

int main(int argc, const char **argv) {
    // parse command line arguments
    if (argc != 4) {
        printf("Usage: ./client hostname port_num message\n");
        return 1;
    }
    const char *hostname = argv[1];
    int port = atoi(argv[2]);
    const char *message = argv[3];

    printf("Sending message %s to %s:%d\n", message, hostname, port);
    if (send_message(hostname, port, message) == -1) {
        return 1;
    }

    return 0;
}