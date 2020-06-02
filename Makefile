CC=gcc
CFLAGS=-Wall -g
BINS=librarytest libembedded.so libstaticembedded.a runtime_librarytest static_librarytest

all: $(BINS) 

libembedded.o: src/libembedded.c inc/libembedded.h
	$(CC) $(CFLAGS) -c src/libembedded.c

libembedded.so: src/libembedded.c inc/libembedded.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ src/libembedded.c -lc

libstaticembedded.a: libembedded.o
	ar rcs $@ $^

librarytest: librarytest.c libembedded.o
	$(CC) $(CFLAGS) -o $@ $^

runtime_librarytest: librarytest.c
	$(CC) $(CFLAGS) -o $@ $^ -L. -lembedded

static_librarytest: librarytest.c
	$(CC) $(CFLAGS) -o $@ $^ -L. -lstaticembedded

clean:
	rm -r *.o $(BINS) *.dSYM
