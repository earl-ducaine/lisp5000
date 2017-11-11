lisp500 : lisp500.c
	cc  -o lisp500 -lm  lisp500.c

# lisp500.o : lisp500.c
# 	cc -c lisp500.c

clean :
	rm lisp500 lisp500.o
