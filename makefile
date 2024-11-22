CC=gcc
CFLAGS=-Wall -std=c99 -g
# LDFLAGS=-lm

all: main

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main main.o