CC=gcc
CFLAGS=-Wall -std=c99 -g
# LDFLAGS=-lm

all: producao

producao: main.o
	$(CC) $(CFLAGS) -o producao main.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f main main.o