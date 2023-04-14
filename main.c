#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
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
    mvaddch(st->player->playerY, st->player->playerX, '@' | A_BOLD);
    attroff(COLOR_PAIR(COLOR_WHITE));
}

bool is_parede(int key){
	return (key == 35 || key == 124);
}

bool fora_do_mapa(int y, int x){
	bool r = false;
	if(x>34 || x<28 || y>33|| y<27) r = true;
	return r;
}

void draw_light(STATE *st){
	attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-3)) && !fora_do_mapa(st->player->playerY, st->player->playerX-3)) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ ,  st->player->playerX/*get_playerY(get_player(st))*/-3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX-3)) && !fora_do_mapa(st->player->playerY-1, st->player->playerX-3)) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 1,  st->player->playerX/*get_playerY(get_player(st))*/ - 3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX-3)) && !fora_do_mapa(st->player->playerY+1, st->player->playerX-3)) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/ -3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX-3)) && !fora_do_mapa(st->player->playerY-2, st->player->playerX-3)) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 2,  st->player->playerX/*get_playerY(get_player(st))*/ - 3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX-3)) && !fora_do_mapa(st->player->playerY+2, st->player->playerX-3)) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ + 2,  st->player->playerX/*get_playerY(get_player(st))*/ -3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-2)) && !fora_do_mapa(st->player->playerY, st->player->playerX-2)) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,  st->player->playerX/*get_playerY(get_player(st))*/-2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX-2)) && !fora_do_mapa(st->player->playerY-1, st->player->playerX-2)) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 1,  st->player->playerX/*get_playerY(get_player(st))*/ - 2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX-2)) && !fora_do_mapa(st->player->playerY+1, st->player->playerX-2)) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/ -2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-1)) && !fora_do_mapa(st->player->playerY, st->player->playerX-1)) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,  st->player->playerX/*get_playerY(get_player(st))*/-1, '.' | A_BOLD);
                attroff(COLOR_PAIR(COLOR_YELLOW));
}


bool is_move_right(int key){
	return key == 100;
}

bool is_move_left(int key){
	return key == 97;
}

bool is_move_up(int key){
	return key == 119;
}

bool is_move_down(int key){
	return key == 115;
}

bool valid_move(STATE *st,int key){
	bool r = true;
	if(is_move_right(key) && mvinch(st->player->playerY+1, st->player->playerX) == '#') r = false;
	if(is_move_left(key) && mvinch(st->player->playerY-1, st->player->playerX) == '#') r = false;
	if(is_move_up(key) && mvinch(st->player->playerY, st->player->playerX-1) == '|') r = false;
	if(is_move_down(key) && mvinch(st->player->playerY, st->player->playerX+1) == '|') r = false;
	return r;
}

void update(STATE *st) {
	int key = getch();

	mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,st->player->playerX /*get_playerY(get_player(st))*/, ' ');
	switch(key) {
		/*
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
		*/
		case 'w': if(valid_move(st,(int)'w')) do_movement_action(st, +0, -1); break;
		case 's': if(valid_move(st,(int)'s')) do_movement_action(st, +0, +1); break;
		case 'a': if(valid_move(st,(int)'a')) do_movement_action(st, -1, +0); break;
		case 'd': if(valid_move(st,(int)'d')) do_movement_action(st, +1, +0); break;
		case 'q': endwin(); exit(0); break;
	}
	draw_player(st);
	draw_light(st);
}




void menu(){

}



void mapa1(STATE *st){
	st->player->playerX = 30;
	st->player->playerY = 30;
	mvaddch(30, 28, '#' | A_BOLD);
	mvaddch(29, 28, '#' | A_BOLD);
	mvaddch(28, 28, '#' | A_BOLD);
	mvaddch(27, 28, '#' | A_BOLD);
	mvaddch(31, 28, '#' | A_BOLD);
	mvaddch(32, 28, '#' | A_BOLD);
	mvaddch(33, 28, '#' | A_BOLD);
	mvaddch(33, 29, '|' | A_BOLD);
	mvaddch(33, 30, '|' | A_BOLD);
	mvaddch(33, 31, '|' | A_BOLD);
	mvaddch(33, 32, '|' | A_BOLD);
	mvaddch(33, 33, '|' | A_BOLD);
	mvaddch(27, 29, '|' | A_BOLD);
	mvaddch(27, 30, '|' | A_BOLD);
	mvaddch(27, 31, '|' | A_BOLD);
	mvaddch(27, 32, '|' | A_BOLD);
	mvaddch(27, 33, '|' | A_BOLD);
	mvaddch(30, 34, '#' | A_BOLD);
	mvaddch(29, 34, '#' | A_BOLD);
	mvaddch(28, 34, '#' | A_BOLD);
	mvaddch(27, 34, '#' | A_BOLD);
	mvaddch(31, 34, '#' | A_BOLD);
	mvaddch(32, 34, '#' | A_BOLD);
	mvaddch(33, 34, '#' | A_BOLD);
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
		mapa1(st);
		//draw_player(st);
		//draw_light(st);
		//update(st);
		move(st->player->playerX, st->player->playerY);
		update(st);
		noecho();
	}
	free(st->player);
	free(st);
	return 0;
}