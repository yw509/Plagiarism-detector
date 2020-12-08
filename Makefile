CC = clang
CFLAGS = -Wall -std=c11 -fsanitize=undefined,address
LIBS += -lm

all: plagiarism 

plagiarism: plagiarism.c cleanup.o tfidf.o cossim.o
	$(CC) $(CFLAGS) plagiarism.c cleanup.o tfidf.o cossim.o -o plagiarism $(LIBS)

cleanup.o: cleanup.c
	$(CC) -c $(CFLAGS) cleanup.c

tfidf.o: tfidf.c
	$(CC) -c $(CFLAGS) tfidf.c 

cossim.o: cossim.c
	$(CC) -c $(CFLAGS) cossim.c 

clean:
	rm -f *.o cleanup tfidf plagiarism cossim ./-g