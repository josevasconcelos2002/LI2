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

bool only_dots = false;




void update(STATE *st,char map[ROWS][COLS]) {
	int key = getch();
	mvaddch(st->player->playerY,st->player->playerX, ' ');
	remove_light(st,key,map);
	switch(key) {
		case 'w': if(valid_move(st,(int)'w',map)) do_movement_action(st, +0, -1,map); break;
		case 's': if(valid_move(st,(int)'s',map)) do_movement_action(st, +0, +1,map); break;
		case 'a': if(valid_move(st,(int)'a',map)) do_movement_action(st, -1, +0,map); break;
		case 'd': if(valid_move(st,(int)'d',map)) do_movement_action(st, +1, +0,map); break;
		//case 'k': kill(st); break;
		case 'v': only_dots =  !only_dots;  desenha_pontos(map); break; //altera o modo de visao
		case ' ': show_pause_menu(); break; // espaco
		case 'q': endwin(); exit(0); break;
	}

	//spawn_mob(st);
	draw_monster(st,map);
	draw_player(st,map);
	draw_light(st,key,map);
	refresh();
}

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
	while(is_parede((int)mvinch(st->player->playerY,st->player->playerX)));


		//clear();
		// Desenha o mapa no ecra
		clear();
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				mvaddch(i, j, map[i][j]);
			}
		}
		//refresh();
	while(1) {
		move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		if(st->player != NULL){
			printw("Player state: \n");
			printw("	Health: %d\n",st->player->playerHealth);
			printw("	Atack: %d \n",st->player->playerAtack);
		}
		printw("(%d, %d) %d %d\n", st->player->playerX, st->player->playerY, ncols, nrows);
		attroff(COLOR_PAIR(COLOR_BLUE));
		refresh();
				// Inicializa o mapa
		
		//draw_player(st);
		//draw_monster(st);
		//draw_light(st);
		//update(st);
		move(st->player->playerX, st->player->playerY);
		//move(st->monster->mosnterX, st->monster->monsterY);
		update(st,map);
		noecho();
	}
	free(st->player);
	free(st);
	return 0;
}