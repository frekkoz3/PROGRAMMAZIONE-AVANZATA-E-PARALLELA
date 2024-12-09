#!/bin/sh

gcc -fPIC -c stat.c

gcc -o libstat.so -shared stat.o
gcc -o main main.c -L. -lstat

mkdir -p lib
mv libstat.so lib/

export LD_LIBRARY_PATH=./lib/:$LD_LIBRARY_PATH
./main
