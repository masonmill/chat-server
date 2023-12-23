#include <arpa/inet.h>   // htons()
#include <stdio.h>       // printf(), perror()
#include <stdlib.h>      // atoi()
#include <sys/socket.h>  // socket(), bind(), listen(), accept(), send(), recv()
#include <sys/time.h>    // struct timeval
#include <unistd.h>      // close()

#include <chrono>
#include <iostream>
#include <thread>

#include "helpers.h"  // make_server_sockaddr(), get_port_number()

using namespace std;

static const size_t MAX_MESSAGE_SIZE = 256;
static bool shutdown_signal = false;

/*
 * runs a server that listens for connections and serves them synchronously
 * if message received, prints it to stdout
 * exits when a shutdown signal is received
 */
int server(int port, int queue_size) {
    // wait on a message from a socket OR a shutdown signal
    cout << "server() starting\n";

    // create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (sockfd == -1) {
        perror("Error opening stream socket");
        return -1;
    }

    // set the "reuse port" socket option
    int yesval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yesval, sizeof(yesval)) == -1) {
        perror("Error setting reuse port");
        return -1;
    }

    // set the "recieve timeout" option
    struct timeval timeout;
    timeout.tv_sec = 1;   // 1 second
    timeout.tv_usec = 0;  // 0 microseconds

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) == -1) {
        perror("Error setting receive timeout");
        return -1;
    }

    // create a sockaddr_in struct for the proper port and bind() to it
    struct sockaddr_in addr;
    if (make_server_sockaddr(&addr, port) == -1) {
        return -1;
    }

    // bind to the port
    if (::bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("Error binding stream socket");
        return -1;
    }

    // detect which port was chosen
    port = get_port_number(sockfd);
    cout << "Server listening on port " << port << "...\n";

    // begin listening for incoming connections
    if (listen(sockfd, queue_size) == -1) {
        perror("Error listening");
        return -1;
    }

    while (!shutdown_signal) {
        cout << "waiting...\n";

        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(sockfd, &rfds);

        int selectResult = select(sockfd + 1, &rfds, nullptr, nullptr, &timeout);
        if (selectResult == -1) {
            perror("Error in select");
            return -1;
        } else if (selectResult == 0) {
            // timeout occurred
            continue;
        }

        int connectionfd = accept(sockfd, NULL, NULL);
        if (connectionfd == -1) {
            perror("Error accepting connection");
            return -1;
        }

        // handle connection
        cout << "Connection from " << connectionfd << "\n";

        // receive message from client
        char msg[MAX_MESSAGE_SIZE + 1];
        memset(msg, 0, sizeof(msg));

        ssize_t recvd = 0;
        ssize_t rval;
        do {
            rval = recv(connectionfd, msg + recvd, MAX_MESSAGE_SIZE - recvd, 0);
            if (rval == -1) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    // timeout occurred
                    continue;
                } else {
                    perror("Error reading stream message");
                    return -1;
                }
            }
            recvd += rval;
        } while (rval > 0);

        // print out the message
        cout << msg << "\n";

        // close connection
        close(connectionfd);
    }
    cout << "server() shutting down\n";
    return 0;
}

int main() {
    // main() thread which spawns a second server() thread
    cout << "main() starting\n";
    thread t(server, 8888, 10);
    this_thread::sleep_for(chrono::seconds(10));  // give up execution to the server thread
    shutdown_signal = true;                       // tell the server thread to shutdown
    t.join();                                     // wait for the server thread to shutdown
    cout << "main() shutting down\n";
}