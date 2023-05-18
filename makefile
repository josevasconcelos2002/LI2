CC = gcc
CFLAGS= -Wall -Wextra -pedantic -O2 #-Iincludes
LIBS= -lm -lcurses -lasound

jogo:  main.o#src/player.o src/monsters.o src/state.o   src/testeGeraMapa.o src/menus.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

main.o: main.c

#src/testeGeraMapa.o : src/testeGeraMapa.c

#src/player.o: src/player.c

#src/state.o: src/state.c

#src/monsters.o: src/monsters.c

#src/menus.o: src/menus.c

clean:
	rm jogo *.o