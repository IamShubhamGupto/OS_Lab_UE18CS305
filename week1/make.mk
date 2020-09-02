CC=gcc
CFLAGS=-c -Wall

prog: Client.o Server.o
	$(CC) Client.o Server.o -o prog
Client.o: Client.c
	$(CC) $(CFLAGS) Client.c
Server.o: Header.h Server.c
	$(CC) $(CFLAGS) Server.c
clean:
	rm -rf *.o