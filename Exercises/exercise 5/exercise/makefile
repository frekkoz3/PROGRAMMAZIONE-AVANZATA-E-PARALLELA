CC = gcc
CFLAGS = -O3 -march=native -std=c17 -Wall -pedantic
HEADERS = ${wildcard *.h}
OBJECTS = matrix.o main.o matrix_multiply.o

all: main

main: ${OBJECTS}
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f *.o
	rm -f main