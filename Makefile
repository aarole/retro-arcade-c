CC=gcc
CFLAGS=-lcurl
main: Menu.c
	$(CC) -o main Menu.c $(CFLAGS)
