lisp500 : lisp500.o
	gcc -o lisp500 lisp500.o -lm -ldl
#	cc  -o lisp500 -lm  lisp500.c

lisp500.o : lisp500.c defs.h
	gcc -ggdb -c lisp500.c

clean :
	rm -f lisp500 lisp500.o
