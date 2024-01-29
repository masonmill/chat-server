#include <arpa/inet.h>   // htons()
#include <stdio.h>       // printf(), perror()
#include <stdlib.h>      // atoi()
#include <sys/socket.h>  // socket(), bind(), listen(), accept(), send(), recv()
#include <unistd.h>      // close()

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include "helpers.h"  // make_server_sockaddr(), get_port_number()

const int MAX_MESSAGE_SIZE = 1024;
std::mutex m;

/*
 *  Initialize the chat server and begin listening for connections from new users
 *
 *  TODO:
 *      Figure out how to store messages efficiently
 *      -   Shared hashtable?
 *      Create threads to handle message operations
 *      -   Receive new messages
 *      -   Identify who is sending the message
 *      -   Identify which users to send the message to
 *      Include mutexes to ensure safeness
 *      Include condition variables to ensure correctness
 *      How to appropriately handle shutdown
 *
 */

// initialize the chat server
int main(int argc, char* argv[]) {
}