CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic
LIBS += -lm

all: plagiarism 

plagiarism: plagiarism.c cleanup.o tfidf.o cossim.o
	$(CC) $(CFLAGS) plagiarism.c cleanup.o tfidf.o cossim.o -o plagiarism $(LIBS)

cleanup.o: cleanup.c
	$(CC) -c $(CFLAGS) cleanup.c

tfidf.o: tfidf.c
	$(CC) -c $(CFLAGS) $(LIBS) tfidf.c 

cossim.o: cossim.c
	$(CC) -c $(CFLAGS) $(LIBS) cossim.c 

clean:
	rm -f *.o cleanup tfidf plagiarism cossim ./-g