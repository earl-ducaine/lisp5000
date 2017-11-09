lisp500 : lisp500.o
	cc -ggdb -o lisp500 lisp500.o -lm -ldl

lisp500.o : lisp500.c
	cc -ggdb -fPIC -c lisp500.c

clean :
	rm -f lisp500 lisp500.o
