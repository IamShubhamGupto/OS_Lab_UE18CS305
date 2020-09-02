CC=gcc
CFLAGS=-c -Wall
all: prog
prog: Client.o Server.o
	$(CC) Client.o Server.o -o prog
Client.o: Client.c
	$(CC) $(CFLAGS) Client.c
Server.o: Header.h Server.c
	$(CC) $(CFLAGS) Server.c
clean:
	rm -f *.o