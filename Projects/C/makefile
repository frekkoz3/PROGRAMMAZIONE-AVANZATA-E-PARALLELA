CC = gcc
CFLAGS = -O3 -Wall -std=c17 -pedantic
HEADERS = ${wildcards *.h}

all: main

main: main.o utils.o scene.o ppm.o
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean all

clean:
	rm -f *.o
	rm -f main