CC = gcc
CFLAGS = -O3 -march=native -Wall -pedantic -std=c17 -fopenmp
HEADERS = vector_sim.h
OBJECTS = vector_sim.o main.o

all: main

main: ${OBJECTS}
	${CC} ${CFLAGS} -o $@ $^ -lm

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f *.o
	rm -f main