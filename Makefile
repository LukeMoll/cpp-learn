CC=g++
CFLAGS=-Wall -Wextra -Wpedantic

hello: hello.o
	$(CC) -o hello hello.o $(CFLAGS)