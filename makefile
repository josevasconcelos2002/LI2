CC = gcc
CFLAGS= -Wall -Wextra -pedantic -O2 -Iincludes
LIBS= -lm -lcurses

jogo: src/player.o src/main.o src/state.o src/monsters.o 
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

src/main.o: src/main.c

src/player.o: src/player.c

src/state.o: src/state.c

src/monsters.o: src/monsters.c

clean:
	rm *.o jogo  src/*.o