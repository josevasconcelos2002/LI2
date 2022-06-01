Guiao1: main.o stack.o operadores.o handle.o
	gcc -std=c11 -Wall -Wextra -pedantic -O2 main.o stack.o operadores.o handle.o -o Guiao1 -lm


main.o: main.c
	gcc -c main.c

stack.o : stack.h
	gcc -c stack.c 

operadores.o: operadores.h
	gcc -c operadores.c 

handle.o: handle.h
	gcc -c handle.c

clean:
	rm *.o Guiao1