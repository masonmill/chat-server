# Sockets

A simple demonstration of socket programming in C

- `server.c`: Runs a server that listens for messages from clients
- `client.c`: Creates a client that sends a single message to the server

The file `helpers.h` contains functions to help setup `sockaddr_in` structs for sockets

## Compile

The Makefile has recipes to build the client and server programs

```
# build
$ make server
$ make client
# OR
$ make all

# clean
$ make clean
```

## Run the server

In one terminal, run the server and begin listening

```
$ ./server 8888
Server listening on port 8888...
```

## Run the client

In another terminal, create a client and send a message

```
$ ./client localhost 8888 "hi server"
Sending message Hello to localhost:8888
```

The server should print the message it receives to the terminal

```
$ ./server 8888
Server listening on port 8888...
New connection 4
Client 4 says 'hi server'
```

When finished, use `^C` in the terminal to stop the server
