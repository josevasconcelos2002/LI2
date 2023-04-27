#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "player.h"
#include "state.h"
#include "monsters.h"
#include "testeGeraMapa.h"
#include "menus.h"


int main(){
	srandom(time(NULL));
	start_color();

	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(1,COLOR_RED,COLOR_BLACK);
	STATE *st = malloc(sizeof(STATE));
	st->player = malloc(sizeof(PLAYER));
	//st->monstros = malloc(sizeof(MONSTER)*10);
	inicializa_state(st);
	WINDOW *wnd = initscr();
	int ncols, nrows;
	getmaxyx(wnd,nrows,ncols);
	show_main_menu();
	char map[ROWS][COLS];
	do{
		memset(map, ' ', ROWS * COLS * sizeof(char));
		init_map(map);
		// Limpa o mapa
		// Faz update no mapa
		for (int i = 0; i < ITERATIONS; i++) {
			update_map(map);
		}
		
		// Remove paredes isoladas e pequenos blocos de paredes
		remove_isolated_walls(map);

		// Adiciona paredes nas bordas do mapa
		for (int i = 0; i < ROWS; i++) {
			map[i][0] = '#';
			map[i][COLS-1] = '#';
		}
		for (int j = 0; j < COLS; j++) {
			map[0][j] = '#';
			map[ROWS-1][j] = '#';
		}
	}
	while(is_parede((int)mvinch(get_playerY(st->player),get_playerX(st->player))));
	clear();
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			mvaddch(i, j, map[i][j]);
		}
	}
	while(1) {
		move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		if(st->player != NULL){
			printw("Player state: \n");
			printw("	Health: %d\n",get_playerHealth(st->player));
			printw("	Atack: %d \n",get_playerAtack(st->player));
		}
		printw("(%d, %d) %d %d\n", get_playerX(st->player), get_playerY(st->player), ncols, nrows);
		attroff(COLOR_PAIR(COLOR_BLUE));
		refresh();
		move(get_playerY(st->player), get_playerX(st->player));
		update(st,map);
		noecho();
	}
	free(st->player);
	free(st);
	return 0;
}