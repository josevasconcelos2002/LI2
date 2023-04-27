#include "monsters.h"
#include "state.h"
#include <stdbool.h>
#include <ncurses.h>
#include "testeGeraMapa.h"



void set_monsterX(MONSTER *monster, int x){
    monster->monsterX = x;
}

void set_monsterY(MONSTER *monster, int y){
    monster->monsterY = y;
}

void set_monsterHealth(MONSTER *monster, int health){
    monster->monsterHealth = health;
}

void set_monsterAtack(MONSTER *monster, int atack){
    monster->monsterAtack = atack;
}

bool is_monster(char c){
	bool resultado = false;
	if(c == '!') resultado = true;
	return resultado;
}

void inicializa_monster(MONSTER monstros[],int N){
	for(int i = 0; i<N ; i++){
		monstros[i].monsterAtack = 5;
		monstros[i].monsterHealth = 50;
		monstros[i].monsterY = 15+ 3*i;
		monstros[i].monsterX = 25 + 5*i;
	}
}

/*
void remove_monster(STATE *st){
	int x = st->monster->monsterX;
	int y = st->monster->monsterY;
	mvaddch(y,x, ' ' | A_BOLD);
	st->monster = NULL;
}
*/

void draw_monster(STATE *st, char map[ROWS][COL]){
	attron(COLOR_PAIR(1));
	for(int i = 0; i<10 ; i++){
		if(!is_parede(map[st->monstros[i].monsterY][st->monstros[i].monsterX])){
			map[st->monstros[i].monsterY][st->monstros[i].monsterX] = '!';
			mvaddch(st->monstros[i].monsterY, st->monstros[i].monsterX, '!' | A_BOLD);
		}
	}
	attroff(COLOR_PAIR(1));
	refresh();
}