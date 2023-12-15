#include <arpa/inet.h>   // htons()
#include <stdio.h>       // printf(), perror()
#include <stdlib.h>      // atoi()
#include <sys/socket.h>  // socket(), bind(), listen(), accept(), send(), recv()
#include <unistd.h>      // close()

#include "helpers.h"  // make_server_sockaddr(), get_port_number()

static const size_t MAX_MESSAGE_SIZE = 256;

// receives a string message from the client and prints it to stdout
int handle_connection(int connectionfd) {
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
    printf("Client %d says '%s'", connectionfd, msg);

    // close connection
    close(connectionfd);

    return 0;
}

// Endlessly runs a server that listens for connections and serves
// them _synchronously_
int run_server(int port, int queue_size) {
    // create socket

    // set the "reuse port" socket option

    // create a sockaddr_in struct for the proper port and bind() to it

    // bind to the port

    // detect which port was chosen

    // begin listening for incoming connections

    // serve incoming connections one by one forever

    return 0;
}

int main(int argc, const char **argv) {
    // parse command line arguments
    if (argc != 2) {
        printf("Usage: ./server port_num\n");
        return 1;
    }
    int port = atoi(argv[1]);

    if (run_server(port, 10) == -1) {
        return 1;
    }
    return 0;
}