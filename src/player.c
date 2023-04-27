#include "player.h"
#include "state.h"
#include <ncurses.h>
#include "testeGeraMapa.h"


int get_playerX(PLAYER *player){
    return player->playerX;
}

int get_playerY(PLAYER *player){
    return player->playerY;
}

int get_playerHealth(PLAYER *player){
    return player->playerHealth;
}

int get_playerAtack(PLAYER *player){
    return player->playerAtack;
}

void set_playerX(PLAYER *player, int x){
    player->playerX = x;
}

void set_playerY(PLAYER *player, int y){
    player->playerY = y;
}

void set_playerHealth(PLAYER *player, int health){
    player->playerHealth = health;
}

void set_playerAtack(PLAYER *player, int atack){
    player->playerAtack = atack;
}

void inicializa_player(PLAYER *player){
    player->playerX = 20;
    player->playerY = 20;
    player->playerHealth = 100;
    player->playerAtack = 10;
}

/*
void kill(STATE *st){
	if(is_monster(mvinch(st->player->playerY,st->player->playerX+1))){
		st->monster->monsterHealth -= st->player->playerAtack; // como saber qual monster se está a referir?
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(is_monster(mvinch(st->player->playerY,st->player->playerX-1))){
		st->monster->monsterHealth -= st->player->playerAtack;
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(is_monster(mvinch(st->player->playerY+1,st->player->playerX))){
		st->monster->monsterHealth -= st->player->playerAtack;
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(is_monster(mvinch(st->player->playerY-1,st->player->playerX))){
		st->monster->monsterHealth -= st->player->playerAtack;
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(st->monster->monsterHealth <= 0) remove_monster(st);
		if(st->player->playerHealth <= 0){
		endwin();
		game_over();
	}

}
*/

void draw_light(STATE *st, char key, char map[ROWS][COL]){
	if(is_move_left((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-3)) && !is_monster(mvinch(st->player->playerY, st->player->playerX-3))) map[st->player->playerY][st->player->playerX-3] = '.';
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX-3)) && !is_monster(mvinch(st->player->playerY-1, st->player->playerX-3))) map[st->player->playerY-1][st->player->playerX-3] = '.';
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX-3)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX-3))) map[st->player->playerY+1][st->player->playerX-3] = '.';
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX-3)) && !is_monster(mvinch(st->player->playerY-2, st->player->playerX-3))) map[st->player->playerY-2][st->player->playerX-3] = '.';
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX-3)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX-3))) map[st->player->playerY+2][st->player->playerX-3] = '.';
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-2)) && !is_monster(mvinch(st->player->playerY, st->player->playerX-2))) map[st->player->playerY][st->player->playerX-2] = '.';
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX-2)) && !is_monster(mvinch(st->player->playerY-1, st->player->playerX-2))) map[st->player->playerY-1][st->player->playerX-2] = '.';
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX-2)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX-2))) map[st->player->playerY+1][st->player->playerX-2] = '.';
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-1)) && !is_monster(mvinch(st->player->playerY, st->player->playerX-1))) map[st->player->playerY][st->player->playerX-1] = '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_up((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX)) && !is_monster(mvinch(st->player->playerY-3, st->player->playerX))) map[st->player->playerY-3][st->player->playerX] =  '.';
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX-1)) && !is_monster(mvinch(st->player->playerY-3, st->player->playerX-1))) map[st->player->playerY-3][st->player->playerX-1] =  '.';
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX+1)) && !is_monster(mvinch(st->player->playerY-3, st->player->playerX+1))) map[st->player->playerY-3][st->player->playerX+1] =  '.';
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX-2)) && !is_monster(mvinch(st->player->playerY-3, st->player->playerX-2))) map[st->player->playerY-3][st->player->playerX-2] =  '.';
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX+2)) && !is_monster(mvinch(st->player->playerY-3, st->player->playerX+2))) map[st->player->playerY-3][st->player->playerX+2] =  '.';
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX)) && !is_monster(mvinch(st->player->playerY-2, st->player->playerX))) map[st->player->playerY-2][st->player->playerX] =  '.';
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX-1)) && !is_monster(mvinch(st->player->playerY-2, st->player->playerX-1))) map[st->player->playerY-2][st->player->playerX-1] =  '.';
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX+1)) && !is_monster(mvinch(st->player->playerY-2, st->player->playerX+1))) map[st->player->playerY-2][st->player->playerX+1] =  '.';
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX)) && !is_monster(mvinch(st->player->playerY-1, st->player->playerX))) map[st->player->playerY-1][st->player->playerX] =  '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_right((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX+3)) && !is_monster(mvinch(st->player->playerY, st->player->playerX+3))) map[st->player->playerY][st->player->playerX+3] =  '.';
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX+3)) && !is_monster(mvinch(st->player->playerY-1, st->player->playerX+3))) map[st->player->playerY-1][st->player->playerX+3] =  '.';
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX+3)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX+3))) map[st->player->playerY+1][st->player->playerX+3] =  '.';
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX+3)) && !is_monster(mvinch(st->player->playerY-2, st->player->playerX+3))) map[st->player->playerY-2][st->player->playerX+3] =  '.';
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX+3)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX+3))) map[st->player->playerY+2][st->player->playerX+3] =  '.';
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX+2)) && !is_monster(mvinch(st->player->playerY, st->player->playerX+2))) map[st->player->playerY][st->player->playerX+2] =  '.';
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX+2)) && !is_monster(mvinch(st->player->playerY-1, st->player->playerX+2))) map[st->player->playerY-1][st->player->playerX+2] =  '.';
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX+2)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX+2))) map[st->player->playerY+1][st->player->playerX+2] =  '.';
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX+1)) && !is_monster(mvinch(st->player->playerY, st->player->playerX+1))) map[st->player->playerY][st->player->playerX+1] =  '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_down((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX)) && !is_monster(mvinch(st->player->playerY+3, st->player->playerX))) map[st->player->playerY+3][st->player->playerX] =  '.';
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX-1)) && !is_monster(mvinch(st->player->playerY+3, st->player->playerX-1))) map[st->player->playerY+3][st->player->playerX-1] =  '.';
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX+1)) && !is_monster(mvinch(st->player->playerY+3, st->player->playerX+1))) map[st->player->playerY+3][st->player->playerX+1] =  '.';
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX-2)) && !is_monster(mvinch(st->player->playerY+3, st->player->playerX-2))) map[st->player->playerY+3][st->player->playerX-2] =  '.';
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX+2)) && !is_monster(mvinch(st->player->playerY+3, st->player->playerX+2))) map[st->player->playerY+3][st->player->playerX+2] =  '.';
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX))) map[st->player->playerY+2][st->player->playerX] =  '.';
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX-1)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX-1))) map[st->player->playerY+2][st->player->playerX-1] =  '.';
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX+1)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX+1))) map[st->player->playerY+2][st->player->playerX+1] =  '.';
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX))) map[st->player->playerY+1][st->player->playerX] =  '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == '.') mvaddch(i,j,'.');
		}
	}
}

void remove_light(STATE *st, char key, char map[ROWS][COL]){
	if(is_move_left((int)key)){
		if(mvinch(st->player->playerY, st->player->playerX-3) == '.') map[st->player->playerY][st->player->playerX-3] =  ' ';
		if(mvinch(st->player->playerY-1, st->player->playerX-3) == '.') map[st->player->playerY-1][st->player->playerX-3] =  ' ';
		if(mvinch(st->player->playerY+1, st->player->playerX-3) == '.') map[st->player->playerY+1][st->player->playerX-3] =  ' ';
		if(mvinch(st->player->playerY-2, st->player->playerX-3) == '.') map[st->player->playerY-2][st->player->playerX-3] =  ' ';
		if(mvinch(st->player->playerY+2, st->player->playerX-3) == '.') map[st->player->playerY+2][st->player->playerX-3] =  ' ';
		if(mvinch(st->player->playerY, st->player->playerX-2) == '.') map[st->player->playerY][st->player->playerX-2] =  ' ';
		if(mvinch(st->player->playerY-1, st->player->playerX-2) == '.') map[st->player->playerY-1][st->player->playerX-2] =  ' ';
		if(mvinch(st->player->playerY+1, st->player->playerX-2) == '.') map[st->player->playerY+1][st->player->playerX-2] =  ' ';
		if(mvinch(st->player->playerY, st->player->playerX-1) == '.') map[st->player->playerY][st->player->playerX-1] =  ' ';
	}
	if(is_move_up((int)key)){
		if(mvinch(st->player->playerY-3, st->player->playerX) == '.') map[st->player->playerY-3][st->player->playerX] =  ' ';
		if(mvinch(st->player->playerY-3, st->player->playerX-1) == '.') map[st->player->playerY-3][st->player->playerX-1] =  ' ';
		if(mvinch(st->player->playerY-3, st->player->playerX+1) == '.') map[st->player->playerY-3][st->player->playerX+1] =  ' ';
		if(mvinch(st->player->playerY-3, st->player->playerX-2) == '.') map[st->player->playerY-3][st->player->playerX-2] =  ' ';
		if(mvinch(st->player->playerY-3, st->player->playerX+2) == '.') map[st->player->playerY-3][st->player->playerX+2] =  ' ';
		if(mvinch(st->player->playerY-2, st->player->playerX) == '.') map[st->player->playerY-2][st->player->playerX] =  ' ';
		if(mvinch(st->player->playerY-2, st->player->playerX-1) == '.') map[st->player->playerY-2][st->player->playerX-2] =  ' ';
		if(mvinch(st->player->playerY-2, st->player->playerX+1) == '.') map[st->player->playerY-2][st->player->playerX+1] =  ' ';
		if(mvinch(st->player->playerY-1, st->player->playerX) == '.') map[st->player->playerY-1][st->player->playerX] =  ' ';
	}
	if(is_move_right((int)key)){
		if(mvinch(st->player->playerY, st->player->playerX+3) == '.') map[st->player->playerY][st->player->playerX+3] =  ' ';
		if(mvinch(st->player->playerY-1, st->player->playerX+3) == '.') map[st->player->playerY-1][st->player->playerX+3] =  ' ';
		if(mvinch(st->player->playerY+1, st->player->playerX+3) == '.') map[st->player->playerY+1][st->player->playerX+3] =  ' ';
		if(mvinch(st->player->playerY-2, st->player->playerX+3) == '.') map[st->player->playerY-2][st->player->playerX+3] =  ' ';
		if(mvinch(st->player->playerY+2, st->player->playerX+3) == '.') map[st->player->playerY+2][st->player->playerX+3] =  ' ';
		if(mvinch(st->player->playerY, st->player->playerX+2) == '.') map[st->player->playerY][st->player->playerX+2] =  ' ';
		if(mvinch(st->player->playerY-1, st->player->playerX+2) == '.') map[st->player->playerY-1][st->player->playerX+2] =  ' ';
		if(mvinch(st->player->playerY+1, st->player->playerX+2) == '.') map[st->player->playerY+1][st->player->playerX+2] =  ' ';
		if(mvinch(st->player->playerY, st->player->playerX+1) == '.') map[st->player->playerY][st->player->playerX+1] =  ' ';
	}
	if(is_move_down((int)key)){
		if(mvinch(st->player->playerY+3, st->player->playerX) == '.') map[st->player->playerY+3][st->player->playerX] =  ' ';
		if(mvinch(st->player->playerY+3, st->player->playerX-1) == '.') map[st->player->playerY+3][st->player->playerX-1] =  ' ';
		if(mvinch(st->player->playerY+3, st->player->playerX+1) == '.') map[st->player->playerY+3][st->player->playerX+1] =  ' ';
		if(mvinch(st->player->playerY+3, st->player->playerX-2) == '.') map[st->player->playerY+3][st->player->playerX-2] =  ' ';
		if(mvinch(st->player->playerY+3, st->player->playerX+2) == '.') map[st->player->playerY+3][st->player->playerX+2] =  ' ';
		if(mvinch(st->player->playerY+2, st->player->playerX) == '.') map[st->player->playerY+2][st->player->playerX] =  ' ';
		if(mvinch(st->player->playerY+2, st->player->playerX-1) == '.') map[st->player->playerY+2][st->player->playerX-1] =  ' ';
		if(mvinch(st->player->playerY+2, st->player->playerX+1) == '.') map[st->player->playerY+2][st->player->playerX+1] =  ' ';
		if(mvinch(st->player->playerY+1, st->player->playerX) == '.') map[st->player->playerY+1][st->player->playerX] =  ' ';
	}
	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == ' ') mvaddch(i,j,' ');
		}
	}
}

void draw_player(STATE *st,char map[ROWS][COL]){
	attron(COLOR_PAIR(COLOR_WHITE));
	map[st->player->playerY][st->player->playerX] = '@';
    for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == '@') mvaddch(i,j,'@');
		}
	}
    attroff(COLOR_PAIR(COLOR_WHITE));
	refresh();
}