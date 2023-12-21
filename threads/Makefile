CXX = g++
CXXFLAGS = -std=c++17 -Wconversion -Wall -Werror -Wextra -pedantic

all: thread wait

thread: thread.cpp
	$(CXX) $(CXXFLAGS) thread.cpp -o thread

wait: wait.cpp
	$(CXX) $(CXXFLAGS) wait.cpp -o wait

clean:
	rm -rf thread wait *.dSYM

.PHONY: clean