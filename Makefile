lisp500 : lisp500.o
	gcc -o lisp500 lisp500.o -lm -ldl

lisp500.o : lisp500.c defs.h
	gcc -ggdb -fPIC -c lisp500.c

clean :
	rm -f lisp500 lisp500.o
