CC = gcc
CFLAGS = -O3 -Wall -std=c17 -pedantic

all: main

main: main.o netpbm.o
	${CC} ${CFLAGS} -o $@ main.o netpbm.o

%.o: %.c netpbm.h
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f *.o
	rm -f main