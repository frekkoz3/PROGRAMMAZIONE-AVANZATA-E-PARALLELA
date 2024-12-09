SHARED = n
ifeq "${SHARED}" "y"
SHFPIC = -fPIC
else
SHFPIC =
endif
OPT = -O0

main.o: main.c
	gcc ${OPT} -c main.c

node.o: node.c
	gcc ${SHFPIC} ${OPT} -c node.c

bst.o: bst.c
	gcc ${SHFPIC} ${OPT} -c bst.c

printtree.o: printtree.c
	gcc ${SHFPIC} ${OPT} -c printtree.c

ifeq "${SHARED}" "y"
libbst.so: node.o bst.o printtree.o
	gcc ${OPT} -o libbst.so -shared node.o bst.o printtree.o
main: main.o libbst.so
	gcc  ${OPT} -o main main.o -L. -lbst
else
libbst.a: bst.o node.o printtree.o
	ar r libbst.a bst.o node.o printtree.o
	ranlib libbst.a
main: main.o libbst.a
	gcc -L. ${OPT} -o main main.o -lbst
endif

clean:
	rm *.o

