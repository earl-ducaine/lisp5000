lisp500 : lisp500.o memory.o dispatch-system.o
	gcc -o lisp500 memory.o dispatch-system.o lisp500.o -lm -ldl

lisp500.o : lisp500.c defs.h
	gcc -ggdb -fPIC -c lisp500.c

memory.o : memory.c defs.h
	gcc -ggdb -fPIC -c memory.c

dispatch-system.o : dispatch-system.c dispatch-system.h defs.h
	gcc -ggdb -fPIC -c dispatch-system.c

clean :
	rm -f lisp500 *.o
