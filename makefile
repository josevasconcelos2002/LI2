CC = gcc
CFLAGS= -Wall -Wextra -pedantic -O2 #-Iincludes
LIBS= -lm -lcurses

jogo: main.o  #src/testeGeraMapa.o src/player.o main.o src/state.o src/monsters.o 
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

main.o: main.c

#src/testeGeraMapa.o : src/testeGeraMapa.c
# src/player.o: src/player.c

#  src/state.o: src/state.c

# src/monsters.o: src/monsters.c

clean:
	rm *.o jogo