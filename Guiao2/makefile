
CFLAGS=-Wall -Wextra -pedantic -std=c11

Guiao1: main.o stack.o handle.o
	gcc $(CFLAGS) $^ -o Guiao2 -lm


main.o: main.c
	gcc $(CFLAGS) -c $^

stack.o : stack.c
	gcc $(CFLAGS) -c $^ 


handle.o: handle.c
	gcc $(CFLAGS) -c $^

clean:
	rm *.o Guiao1