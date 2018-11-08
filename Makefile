CC=g++
CFLAGS=-Wall -Wextra -Wpedantic -std=c++11

DEPS = 

# using .o as dependencies 
hello: hello.o
	$(CC) $(CFLAGS) -o hello hello.o

aoc_2015_2: aoc_2015_2.o
	$(CC) $(CFLAGS) -o aoc_2015_2 aoc_2015_2.o

aoc_2015_6: aoc_2015_6.o
	$(CC) $(CFLAGS) -o aoc_2015_6 aoc_2015_6.o

%.o: %.cpp $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $<