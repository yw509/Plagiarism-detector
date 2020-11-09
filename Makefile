CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic

all: cleanup

cleanup: cleanup.c 
	$(CC) $(CFLAGS) cleanup.c -o cleanup

clean:
	rm -f cleanup ./-g