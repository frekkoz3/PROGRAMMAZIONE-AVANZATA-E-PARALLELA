CC = gcc
CFLAGS = -O3 -Wall -std=c17 -pedantic -fopenmp
HEADERS = ${wildcards *.h}
OBJECTS = main.o matrix.o graph.o

all: main

main: ${OBJECTS}
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f *.o
	rm -f main