#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "player.h"
#include "state.h"
#include "monsters.h"


/**
 *
 * Falta muita coisa, incluindo por exemplo:
 * - o mapa
 * - os monstros
 * - a fila de prioridade para saber quem se move
 * - o que está em cada casa
 *
 */


/**
 *
 * Um pequeno exemplo que mostra o que se pode fazer
 */
void do_movement_action(STATE *st, int dx, int dy) {
	set_playerX(get_player(st),get_playerX(get_player(st)) + dx);
	set_playerY(get_player(st),get_playerY(get_player(st)) + dy);
}

void update(STATE *st) {
	int key = getch();

	mvaddch(get_playerX(get_player(st)), get_playerY(get_player(st)), ' ');
	switch(key) {
		case KEY_A1:
		case '7': do_movement_action(st, -1, -1); break;
		case KEY_UP:
		case '8': do_movement_action(st, -1, +0); break;
		case KEY_A3:
		case '9': do_movement_action(st, -1, +1); break;
		case KEY_LEFT:
		case '4': do_movement_action(st, +0, -1); break;
		case KEY_B2:
		case '5': break;
		case KEY_RIGHT:
		case '6': do_movement_action(st, +0, +1); break;
		case KEY_C1:
		case '1': do_movement_action(st, +1, -1); break;
		case KEY_DOWN:
		case '2': do_movement_action(st, +1, +0); break;
		case KEY_C3:
		case '3': do_movement_action(st, +1, +1); break;
		case 'w': do_movement_action(st, -1, +0); break;
		case 's': do_movement_action(st, +1, +0); break;
		case 'a': do_movement_action(st, +0, -1); break;
		case 'd': do_movement_action(st, +0, +1); break;
		case 'q': endwin(); exit(0); break;
	}
}

void draw_player(STATE *st){
	attron(COLOR_PAIR(COLOR_WHITE));
    mvaddch(get_playerX(get_player(st)), get_playerY(get_player(st)), '@' | A_BOLD);
    attroff(COLOR_PAIR(COLOR_WHITE));
}

void draw_light(STATE *st){
	attron(COLOR_PAIR(COLOR_YELLOW));
		mvaddch(get_playerX(get_player(st)) - 1, get_playerY(get_player(st)) - 1, '.' | A_BOLD);
		mvaddch(get_playerX(get_player(st)) - 1, get_playerY(get_player(st)) + 0, '.' | A_BOLD);
		mvaddch(get_playerX(get_player(st)) - 1, get_playerY(get_player(st)) + 1, '.' | A_BOLD);
		mvaddch(get_playerX(get_player(st)) + 0, get_playerY(get_player(st)) - 1, '.' | A_BOLD);
		mvaddch(get_playerX(get_player(st)) + 0, get_playerY(get_player(st)) + 1, '.' | A_BOLD);
		mvaddch(get_playerX(get_player(st)) + 1, get_playerY(get_player(st)) - 1, '.' | A_BOLD);
		mvaddch(get_playerX(get_player(st)) + 1, get_playerY(get_player(st)) + 0, '.' | A_BOLD);
		mvaddch(get_playerX(get_player(st)) + 1, get_playerY(get_player(st)) + 1, '.' | A_BOLD);
                attroff(COLOR_PAIR(COLOR_YELLOW));
}

void inicializa(){
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
}


int main(){
	STATE *st = NULL;
	inicializa_state(st);
	inicializa();
	WINDOW *wnd = initscr();
	int ncols, nrows;
	getmaxyx(wnd,nrows,ncols);
	while(1) {
		move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		printw("(%d, %d) %d %d", get_playerX(get_player(st)), get_playerY(get_player(st)), ncols, nrows);
		attroff(COLOR_PAIR(COLOR_BLUE));
		draw_player(st);
		draw_light(st);
		move(get_playerX(get_player(st)), get_playerY(get_player(st)));
		update(st);
	}
	return 0;
}