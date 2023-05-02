#include "player.h"
#include "state.h"
#include <ncurses.h>
#include "testeGeraMapa.h"

typedef struct player{
	int playerX;
	int playerY;
	int playerHealth;
	int playerAttack;
} PLAYER;

int get_playerX(STATE *state){
	int pX = get_player(state)->playerX;
    return pX;
}

int get_playerY(STATE *state){
	int pY = get_player(state)->->playerY;
    return pY;
}

int get_playerHealth(STATE *state){
	int pH = get_player(state)->->playerHealth;
    return pH;
}

int get_playerAtack(STATE *state){
	int pA = get_player(state)->->playerAttack;
    return pA;
}

void set_playerX(STATE *state, int x){
    get_player(state)->->playerX = x;
}

void set_playerY(STATE *state, int y){
    get_player(state)->->playerY = y;
}

void set_playerHealth(STATE *state, int health){
    get_player(state)->playerHealth = health;
}

void set_playerAtack(STATE *state, int attack){
    get_player(state)->playerAttack = attack;
}

void inicializa_player(STATE *state){
    get_player(state)->playerX = 20;
    get_player(state)->playerY = 20;
    get_player(state)->playerHealth = 100;
    get_player(state)->playerAttack = 10;
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
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)-3)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)-3))) map[get_playerY(st)][get_playerX(st)-3] = '.';
		if(!is_parede(mvinch(get_playerY(st)-1, get_playerX(st)-3)) && !is_monster(mvinch(get_playerY(st)-1, get_playerX(st)-3))) map[get_playerY(st)-1][get_playerX(st)-3] = '.';
		if(!is_parede(mvinch(get_playerY(st)+1, get_playerX(st)-3)) && !is_monster(mvinch(get_playerY(st)+1, get_playerX(st)-3))) map[get_playerY(st)+1][get_playerX(st)-3] = '.';
		if(!is_parede(mvinch(get_playerY(st)-2, get_playerX(st)-3)) && !is_monster(mvinch(get_playerY(st)-2, get_playerX(st)-3))) map[get_playerY(st)-2][get_playerX(st)-3] = '.';
		if(!is_parede(mvinch(get_playerY(st)+2, get_playerX(st)-3)) && !is_monster(mvinch(get_playerY(st)+2, get_playerX(st)-3))) map[get_playerY(st)+2][get_playerX(st)-3] = '.';
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)-2)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)-2))) map[get_playerY(st)][get_playerX(st)-2] = '.';
		if(!is_parede(mvinch(get_playerY(st)-1, get_playerX(st)-2)) && !is_monster(mvinch(get_playerY(st)-1, get_playerX(st)-2))) map[get_playerY(st)-1][get_playerX(st)-2] = '.';
		if(!is_parede(mvinch(get_playerY(st)+1, get_playerX(st)-2)) && !is_monster(mvinch(get_playerY(st)+1, get_playerX(st)-2))) map[get_playerY(st)+1][get_playerX(st)-2] = '.';
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)-1)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)-1))) map[get_playerY(st)][get_playerX(st)-1] = '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_up((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(get_playerY(st)-3, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)-3, get_playerX(st)))) map[get_playerY(st)-3][get_playerX(st)] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-3, get_playerX(st)-1)) && !is_monster(mvinch(get_playerY(st)-3, get_playerX(st)-1))) map[get_playerY(st)-3][get_playerX(st)-1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-3, get_playerX(st)+1)) && !is_monster(mvinch(get_playerY(st)-3, get_playerX(st)+1))) map[get_playerY(st)-3][get_playerX(st)+1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-3, get_playerX(st)-2)) && !is_monster(mvinch(get_playerY(st)-3, get_playerX(st)-2))) map[get_playerY(st)-3][get_playerX(st)-2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-3, get_playerX(st)+2)) && !is_monster(mvinch(get_playerY(st)-3, get_playerX(st)+2))) map[get_playerY(st)-3][get_playerX(st)+2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-2, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)-2, get_playerX(st)))) map[get_playerY(st)-2][get_playerX(st)] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-2, get_playerX(st)-1)) && !is_monster(mvinch(get_playerY(st)-2, get_playerX(st)-1))) map[get_playerY(st)-2][get_playerX(st)-1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-2, get_playerX(st)+1)) && !is_monster(mvinch(get_playerY(st)-2, get_playerX(st)+1))) map[get_playerY(st)-2][get_playerX(st)+1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-1, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)-1, get_playerX(st)))) map[get_playerY(st)-1][get_playerX(st)] =  '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_right((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)+3)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)+3))) map[get_playerY(st)][get_playerX(st)+3] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-1, get_playerX(st)+3)) && !is_monster(mvinch(get_playerY(st)-1, get_playerX(st)+3))) map[get_playerY(st)-1][get_playerX(st)+3] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+1, get_playerX(st)+3)) && !is_monster(mvinch(get_playerY(st)+1, get_playerX(st)+3))) map[get_playerY(st)+1][get_playerX(st)+3] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-2, get_playerX(st)+3)) && !is_monster(mvinch(get_playerY(st)-2, get_playerX(st)+3))) map[get_playerY(st)-2][get_playerX(st)+3] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+2, get_playerX(st)+3)) && !is_monster(mvinch(get_playerY(st)+2, get_playerX(st)+3))) map[get_playerY(st)+2][get_playerX(st)+3] =  '.';
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)+2)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)+2))) map[get_playerY(st)][get_playerX(st)+2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-1, get_playerX(st)+2)) && !is_monster(mvinch(get_playerY(st)-1, get_playerX(st)+2))) map[get_playerY(st)-1][get_playerX(st)+2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+1, get_playerX(st)+2)) && !is_monster(mvinch(get_playerY(st)+1, get_playerX(st)+2))) map[get_playerY(st)+1][get_playerX(st)+2] =  '.';
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)+1)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)+1))) map[get_playerY(st)][get_playerX(st)+1] =  '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_down((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(get_playerY(st)+3, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)+3, get_playerX(st)))) map[get_playerY(st)+3][get_playerX(st)] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+3, get_playerX(st)-1)) && !is_monster(mvinch(get_playerY(st)+3, get_playerX(st)-1))) map[get_playerY(st)+3][get_playerX(st)-1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+3, get_playerX(st)+1)) && !is_monster(mvinch(get_playerY(st)+3, get_playerX(st)+1))) map[get_playerY(st)+3][get_playerX(st)+1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+3, get_playerX(st)-2)) && !is_monster(mvinch(get_playerY(st)+3, get_playerX(st)-2))) map[get_playerY(st)+3][get_playerX(st)-2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+3, get_playerX(st)+2)) && !is_monster(mvinch(get_playerY(st)+3, get_playerX(st)+2))) map[get_playerY(st)+3][get_playerX(st)+2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+2, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)+2, get_playerX(st)))) map[get_playerY(st)+2][get_playerX(st)] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+2, get_playerX(st)-1)) && !is_monster(mvinch(get_playerY(st)+2, get_playerX(st)-1))) map[get_playerY(st)+2][get_playerX(st)-1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+2, get_playerX(st)+1)) && !is_monster(mvinch(get_playerY(st)+2, get_playerX(st)+1))) map[get_playerY(st)+2][get_playerX(st)+1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+1, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)+1, get_playerX(st)))) map[get_playerY(st)+1][get_playerX(st)] =  '.';
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
		if(mvinch(get_playerY(st), get_playerX(st)-3) == '.') map[get_playerY(st)][get_playerX(st)-3] =  ' ';
		if(mvinch(get_playerY(st)-1, get_playerX(st)-3) == '.') map[stget_playerY(st)-1][get_playerX(st)-3] =  ' ';
		if(mvinch(get_playerY(st)+1, get_playerX(st)-3) == '.') map[stget_playerY(st)+1][get_playerX(st)-3] =  ' ';
		if(mvinch(get_playerY(st)-2, get_playerX(st)-3) == '.') map[stget_playerY(st)-2][get_playerX(st)-3] =  ' ';
		if(mvinch(get_playerY(st)+2, get_playerX(st)-3) == '.') map[stget_playerY(st)+2][get_playerX(st)-3] =  ' ';
		if(mvinch(get_playerY(st), get_playerX(st)-2) == '.') map[get_playerY(st)][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st)-1, get_playerX(st)-2) == '.') map[stget_playerY(st)-1][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st)+1, get_playerX(st)-2) == '.') map[stget_playerY(st)+1][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st), get_playerX(st)-1) == '.') map[get_playerY(st)][get_playerX(st)-1] =  ' ';
	}
	if(is_move_up((int)key)){
		if(mvinch(get_playerY(st)-3, get_playerX(st)) == '.') map[stget_playerY(st)-3][get_playerX(st)] =  ' ';
		if(mvinch(get_playerY(st)-3, get_playerX(st)-1) == '.') map[stget_playerY(st)-3][get_playerX(st)-1] =  ' ';
		if(mvinch(get_playerY(st)-3, get_playerX(st)+1) == '.') map[stget_playerY(st)-3][get_playerX(st)+1] =  ' ';
		if(mvinch(get_playerY(st)-3, get_playerX(st)-2) == '.') map[stget_playerY(st)-3][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st)-3, get_playerX(st)+2) == '.') map[stget_playerY(st)-3][get_playerX(st)+2] =  ' ';
		if(mvinch(get_playerY(st)-2, get_playerX(st)) == '.') map[stget_playerY(st)-2][get_playerX(st)] =  ' ';
		if(mvinch(get_playerY(st)-2, get_playerX(st)-1) == '.') map[stget_playerY(st)-2][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st)-2, get_playerX(st)+1) == '.') map[stget_playerY(st)-2][get_playerX(st)+1] =  ' ';
		if(mvinch(get_playerY(st)-1, get_playerX(st)) == '.') map[stget_playerY(st)-1][get_playerX(st)] =  ' ';
	}
	if(is_move_right((int)key)){
		if(mvinch(get_playerY(st), get_playerX(st)+3) == '.') map[get_playerY(st)][get_playerX(st)+3] =  ' ';
		if(mvinch(get_playerY(st)-1, get_playerX(st)+3) == '.') map[get_playerY(st)-1][get_playerX(st)+3] =  ' ';
		if(mvinch(get_playerY(st)+1, get_playerX(st)+3) == '.') map[get_playerY(st)+1][get_playerX(st)+3] =  ' ';
		if(mvinch(get_playerY(st)-2, get_playerX(st)+3) == '.') map[get_playerY(st)-2][get_playerX(st)+3] =  ' ';
		if(mvinch(get_playerY(st)+2, get_playerX(st)+3) == '.') map[get_playerY(st)+2][get_playerX(st)+3] =  ' ';
		if(mvinch(get_playerY(st), get_playerX(st)+2) == '.') map[get_playerY(st)][get_playerX(st)+2] =  ' ';
		if(mvinch(get_playerY(st)-1, get_playerX(st)+2) == '.') map[get_playerY(st)-1][get_playerX(st)+2] =  ' ';
		if(mvinch(get_playerY(st)+1, get_playerX(st)+2) == '.') map[get_playerY(st)+1][get_playerX(st)+2] =  ' ';
		if(mvinch(get_playerY(st), get_playerX(st)+1) == '.') map[get_playerY(st)][get_playerX(st)+1] =  ' ';
	}
	if(is_move_down((int)key)){
		if(mvinch(get_playerY(st)+3, get_playerX(st)) == '.') map[get_playerY(st)+3][get_playerX(st)] =  ' ';
		if(mvinch(get_playerY(st)+3, get_playerX(st)-1) == '.') map[get_playerY(st)+3][get_playerX(st)-1] =  ' ';
		if(mvinch(get_playerY(st)+3, get_playerX(st)+1) == '.') map[get_playerY(st)+3][get_playerX(st)+1] =  ' ';
		if(mvinch(get_playerY(st)+3, get_playerX(st)-2) == '.') map[get_playerY(st)+3][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st)+3, get_playerX(st)+2) == '.') map[get_playerY(st)+3][get_playerX(st)+2] =  ' ';
		if(mvinch(get_playerY(st)+2, get_playerX(st)) == '.') map[get_playerY(st)+2][get_playerX(st)] =  ' ';
		if(mvinch(get_playerY(st)+2, get_playerX(st)-1) == '.') map[get_playerY(st)+2][get_playerX(st)-1] =  ' ';
		if(mvinch(get_playerY(st)+2, get_playerX(st)+1) == '.') map[get_playerY(st)+2][get_playerX(st)+1] =  ' ';
		if(mvinch(get_playerY(st)+1, get_playerX(st)) == '.') map[get_playerY(st)+1][get_playerX(st)] =  ' ';
	}
	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == ' ') mvaddch(i,j,' ');
		}
	}
}

void draw_player(STATE *st,char map[ROWS][COL]){
	attron(COLOR_PAIR(COLOR_WHITE));
	map[get_playerY(st)][get_playerX(st)] = '@';
    for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == '@') mvaddch(i,j,'@');
		}
	}
    attroff(COLOR_PAIR(COLOR_WHITE));
	refresh();
}