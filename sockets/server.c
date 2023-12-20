#include <arpa/inet.h>   // htons()
#include <stdio.h>       // printf(), perror()
#include <stdlib.h>      // atoi()
#include <sys/socket.h>  // socket(), bind(), listen(), accept(), send(), recv()
#include <unistd.h>      // close()

#include "helpers.h"  // make_server_sockaddr(), get_port_number()

static const size_t MAX_MESSAGE_SIZE = 256;

// receives a string message from the client and prints it to stdout
int handle_connection(int connectionfd) {
    printf("New connection %d\n", connectionfd);

    // receive message from client
    char msg[MAX_MESSAGE_SIZE + 1];
    memset(msg, 0, sizeof(msg));

    ssize_t recvd = 0;
    ssize_t rval;
    do {
        rval = recv(connectionfd, msg + recvd, MAX_MESSAGE_SIZE - recvd, 0);
        if (rval == -1) {
            perror("Error reading stream message");
            return -1;
        }
        recvd += rval;
    } while (rval > 0);

    // print out the message
    printf("Client %d says '%s'\n", connectionfd, msg);

    // close connection
    close(connectionfd);

    return 0;
}

// endlessly runs a server that listens for connections and serves them synchronously
int run_server(int port, int queue_size) {
    // create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (sockfd == -1) {
        perror("Error opening stream socket");
        return -1;
    }

    // set the "reuse port" socket option
    int yesval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yesval, sizeof(yesval)) == -1) {
        perror("Error setting socket options");
        return -1;
    }

    // create a sockaddr_in struct for the proper port and bind() to it
    struct sockaddr_in addr;
    if (make_server_sockaddr(&addr, port) == -1) {
        return -1;
    }

    // bind to the port
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Error binding stream socket");
        return -1;
    }

    // detect which port was chosen
    port = get_port_number(sockfd);
    printf("Server listening on port %d...\n", port);

    // begin listening for incoming connections
    if (listen(sockfd, queue_size) == -1) {
        perror("Error listening");
        return -1;
    }

    // serve incoming connections one by one forever
    while (1) {
        int connectionfd = accept(sockfd, NULL, NULL);
        if (connectionfd == -1) {
            perror("Error accepting connection");
            return -1;
        }

        if (handle_connection(connectionfd) == -1) {
            return -1;
        }
    }
}

int main(int argc, const char **argv) {
    // parse command line arguments
    if (argc != 2) {
        printf("Usage: ./server port_num\n");
        return 1;
    }
    const int port = atoi(argv[1]);

    if (run_server(port, 10) == -1) {
        return 1;
    }
    return 0;
}
