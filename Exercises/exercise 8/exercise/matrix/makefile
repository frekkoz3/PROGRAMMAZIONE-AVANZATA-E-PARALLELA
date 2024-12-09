CC = gcc
CFLAGS = -O3 -march=native -Wall -pedantic -std=c17 -fopenmp
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