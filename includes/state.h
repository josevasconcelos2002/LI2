#ifndef STATE_H
#define STATE_H

#include "player.h"
#include "monsters.h"
typedef struct state {
	PLAYER *player;
	MONSTER monstros[10];
} STATE;

struct player *get_player(STATE *st);

void inicializa_state(STATE *st);

void do_movement_action(STATE *st, int dx, int dy,char map[ROWS][COLS]);

bool is_parede(int key);

bool is_move_right(int key);

bool is_move_left(int key);

bool is_move_up(int key);

bool is_move_down(int key);

bool valid_move(STATE *st,int key,char map[ROWS][COLS]);

void desenha_pontos(char map[ROWS][COLS]);

/*void game_over();*/

void update(STATE *st,char map[ROWS][COLS]);

#endif