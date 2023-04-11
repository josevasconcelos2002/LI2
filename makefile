CFLAGS=-Wall -Wextra -pedantic -O2 -Iincludes
LIBS=-lm -lcurses

jogo: main.o src/player.o src/state.o
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

main.o: main.c

src/player.o: src/player.c

src/state.o: src/state.c

#src/monsters.o: src/monsters.c

clean:
	rm jogo *.o
