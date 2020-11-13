CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic
LIBS += -lm

all: plagiarism 

plagiarism: plagiarism.c cleanup.o tfidf.o
	$(CC) $(CFLAGS) plagiarism.c cleanup.o tfidf.o -o plagiarism $(LIBS)

cleanup.o: cleanup.c
	$(CC) -c $(CFLAGS) cleanup.c

tfidf.o: tfidf.c
	$(CC) -c $(CFLAGS) $(LIBS) tfidf.c 



clean:
	rm -f *.o cleanup tfidf plagiarism ./-g