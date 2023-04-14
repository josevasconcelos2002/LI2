#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
//#include "player.h"
//#include "state.h"
//#include "monsters.h"


/**
 *
 * Falta muita coisa, incluindo por exemplo:
 * - o mapa
 * - os monstros
 * - a fila de prioridade para saber quem se move
 * - o que está em cada casa
 *
 */

typedef struct player{
	int playerX;
	int playerY;
	int playerHealth;
	int playerAtack;
} PLAYER;



typedef struct state {
	PLAYER *player;
	//MONSTER *monstros;
} STATE;



void inicializa_player(PLAYER *player){
    player->playerX = 20;
    player->playerY = 20;
    player->playerHealth = 100;
    player->playerAtack = 10;
}

void inicializa_state(STATE *st){
	st->player = malloc(sizeof(PLAYER));
	inicializa_player(st->player);
}

/**
 *
 * Um pequeno exemplo que mostra o que se pode fazer
 */
void do_movement_action(STATE *st, int dx, int dy) {
	st->player->playerX += dx;//set_playerX(get_player(st),get_playerX(get_player(st)) + dx);
	st->player->playerY += dy;//set_playerY(get_player(st),get_playerY(get_player(st)) + dy);
}


void draw_player(STATE *st){
	attron(COLOR_PAIR(COLOR_WHITE));
    mvaddch(st->player->playerX, st->player->playerY, '@' | A_BOLD);
    attroff(COLOR_PAIR(COLOR_WHITE));
}

void draw_light(STATE *st){
	attron(COLOR_PAIR(COLOR_YELLOW));
		mvaddch(st->player->playerX/*get_playerX(get_player(st))*/ -3,  st->player->playerY/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		mvaddch(st->player->playerX/*get_playerX(get_player(st))*/ - 3,  st->player->playerY/*get_playerY(get_player(st))*/ - 1, '.' | A_BOLD);
		mvaddch(st->player->playerX/*get_playerX(get_player(st))*/ - 3,  st->player->playerY/*get_playerY(get_player(st))*/ + 1, '.' | A_BOLD);
		mvaddch(st->player->playerX/*get_playerX(get_player(st))*/ - 3,  st->player->playerY/*get_playerY(get_player(st))*/ - 2, '.' | A_BOLD);
		mvaddch(st->player->playerX/*get_playerX(get_player(st))*/ - 3,  st->player->playerY/*get_playerY(get_player(st))*/ +2, '.' | A_BOLD);
		mvaddch(st->player->playerX/*get_playerX(get_player(st))*/-2,  st->player->playerY/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		mvaddch(st->player->playerX/*get_playerX(get_player(st))*/ - 2,  st->player->playerY/*get_playerY(get_player(st))*/ - 1, '.' | A_BOLD);
		mvaddch(st->player->playerX/*get_playerX(get_player(st))*/ -2,  st->player->playerY/*get_playerY(get_player(st))*/ +1, '.' | A_BOLD);
		mvaddch(st->player->playerX/*get_playerX(get_player(st))*/-1,  st->player->playerY/*get_playerY(get_player(st))*/, '.' | A_BOLD);
                attroff(COLOR_PAIR(COLOR_YELLOW));
}

void update(STATE *st) {
	int key = getch();

	mvaddch(st->player->playerX/*get_playerX(get_player(st))*/,st->player->playerY /*get_playerY(get_player(st))*/, ' ');
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
	draw_player(st);
	draw_light(st);
}




void menu(){

}

void mapa1(){

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
	inicializa();
	STATE *st = malloc(sizeof(STATE));;
	inicializa_state(st);
	WINDOW *wnd = initscr();
	int ncols, nrows;
	getmaxyx(wnd,nrows,ncols);
	while(1) {
		move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		printw("(%d, %d) %d %d", st->player->playerX, st->player->playerY, ncols, nrows);
		attroff(COLOR_PAIR(COLOR_BLUE));
		draw_player(st);
		move(st->player->playerX, st->player->playerY);
		draw_light(st);
		update(st);
	}
	free(st->player);
	free(st);
	return 0;
}