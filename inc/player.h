#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

typedef struct{
	int x;
	int y;
	int hp;
	int attack;
	bool only_dots;
} PLAYER;

void inicializa_player(PLAYER *player);
void do_movement_action(PLAYER *player, char map[ROWS][COLS], int dx, int dy);
bool valid_move(PLAYER *player, char map[ROWS][COLS], char key);
void draw_light(PLAYER *player, char map[ROWS][COLS]);
void remove_light(char map[ROWS][COLS]);
void draw_player(PLAYER *player, char map[ROWS][COLS]);

#endif