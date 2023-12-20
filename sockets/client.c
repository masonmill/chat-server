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
    // check message length
    const size_t message_len = strlen(message);
    if (message_len > MAX_MESSAGE_SIZE) {
        perror("Error: Message exceeds maximum length\n");
        return -1;
    }

    // create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    // create a sockaddr_in to specify remote host and port
    struct sockaddr_in addr;
    if (make_client_sockaddr(&addr, hostname, port) == -1) {
        return -1;
    }

    // connect to remote server
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Error connecting stream socket");
        return -1;
    }

    // send message to remote server
    ssize_t sent = 0;
    do {
        const ssize_t n = send(sockfd, message + sent, message_len - sent, 0);
        if (n == -1) {
            perror("Error sending on stream socket");
            return -1;
        }
        sent += n;
    } while (sent < message_len);

    // close connection
    close(sockfd);

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