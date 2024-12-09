CC = gcc
CFLAGS = -O3 -Wall -std=c17 -pedantic
HEADERS = ${wildcard *.h}
OBJECTS = main.o tree.o ctree.o

all: main

main: ${OBJECTS}
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f *.o
	rm -f main