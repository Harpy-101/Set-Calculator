# Target to build the executable
myset: myset.o set.o lexer.o panic.o
	gcc -ansi -pedantic -g -O0 -Wall myset.o set.o lexer.o panic.o -o myset

myset.o: myset.c
	gcc -ansi -pedantic -c -g -O0 -Wall myset.c -o myset.o

set.o: set.c
	gcc -ansi -pedantic -c -g -O0 -Wall set.c -o set.o

lexer.o: lexer.c
	gcc -ansi -pedantic -c -g -O0 -Wall lexer.c -o lexer.o

panic.o: panic.c
	gcc -ansi -pedantic -c -g -O0 -Wall panic.c -o panic.o

# Target to clean up build artifacts
clean:
	rm -f myset *.o
