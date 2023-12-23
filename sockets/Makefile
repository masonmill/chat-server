C = gcc
CFLAGS = -g -pedantic

CXX = g++
CXXFLAGS = -std=c++17 -pedantic

all: server client shutdown

server: server.c
	$(C) $(CFLAGS) server.c -o server

client: client.c
	$(C) $(CFLAGS) client.c -o client

shutdown: shutdown.cpp
	$(CXX) $(CXXFLAGS) shutdown.cpp -o shutdown

clean:
	rm -rf client server shutdown *.dSYM

.PHONY: clean