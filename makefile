CC = gcc
CFLAGS= -Wall -Wextra -pedantic -O2
LIBS= -lm -lcurses -lasound

jogo:  main.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

main.o: main.c

clean:
	rm jogo *.o