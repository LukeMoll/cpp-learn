CC=g++
CFLAGS=-Wall -Wextra -Wpedantic

hello: hello.cpp
	$(CC) -o hello hello.cpp $(CFLAGS)