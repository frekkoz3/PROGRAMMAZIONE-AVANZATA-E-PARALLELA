CC = gcc
CFLAGS = -O3 -Wall -pedantic -std=c17 -fopenmp

all: main

main: mergesort.o
	${CC} ${CFLAGS} -o $@ $<

%.o: %.c
	${CC} ${CFLAGS} -c $<

.PHONY: clean all

clean:
	rm -f *.o
	rm -f main