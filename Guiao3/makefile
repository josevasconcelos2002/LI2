
CFLAGS=-Wall -Wextra -pedantic -std=c11

Guiao3: main.o stack.o manipula_stack.o operadores_logicos.o conversoes.o operadores.o handle.o
	gcc $(CFLAGS) $^ -o Guiao3 -lm


main.o: main.c
	gcc $(CFLAGS) -c $^

stack.o : stack.c
	gcc $(CFLAGS) -c $^ 

operadores_logicos.o : operadores_logicos.c
	gcc $(CFLAGS) -c $^

manipula_stack.o: manipula_stack.c
	gcc $(CFLAGS) -c $^

conversoes.o: conversoes.c
	gcc $(CFLAGS) -c $^

operadores.o : operadores.c
	gcc $(CFLAGS) -c $^

handle.o: handle.c
	gcc $(CFLAGS) -c $^

clean:
	rm *.o Guiao3