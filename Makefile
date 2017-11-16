lisp500 : lisp500.o memory.o
	gcc -o lisp500 memory.o lisp500.o -lm -ldl

lisp500.o : lisp500.c defs.h
	gcc -ggdb -fPIC -c lisp500.c

memory.o : memory.c defs.h
	gcc -ggdb -fPIC -c memory.c

clean :
	rm -f lisp500 lisp500.o
