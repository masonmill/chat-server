CXX = g++
CXXFLAGS = -std=c++20 -pedantic

all: server user

server: server.cpp
	$(CXX) $(CXXFLAGS) server.cpp -o server

user: user.cpp
	$(CXX) $(CXXFLAGS) user.cpp -o user

clean:
	rm -rf client server shutdown *.dSYM

.PHONY: clean