CC = gcc
CFLAGS= -Wall -Wextra -pedantic -O2 -Iincludes
LIBS= -lm -lcurses

jogo:  src/testeGeraMapa.o src/player.o src/state.o src/monsters.o src/menus.o main.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

main.o: main.c

src/testeGeraMapa.o : src/testeGeraMapa.c

src/player.o: src/player.c

src/state.o: src/state.c

src/monsters.o: src/monsters.c

src/menus.o: src/menus.c

clean:
	rm src/*.o jogo *.o