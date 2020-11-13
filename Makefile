CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic

all: tfidf 

cleanup: cleanup.c 
	$(CC) $(CFLAGS) cleanup.c -o cleanup

tfidf: tfidf.c 
	$(CC) $(CFLAGS) tfidf.c -o tfidf -lm

test: test.c 
	$(CC) $(CFLAGS) test.c -o test

plagiarism: plagiarism.c 
	$(CC) $(CFLAGS) plagiarism.c -o plagiarism

clean:
	rm -f cleanup tfidf ./-g