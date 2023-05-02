#ifndef PLAYER_H
#define PLAYER_H

#include "state.h"

typedef struct player PLAYER;

int get_playerX(STATE *state);
int get_playerY(STATE *state);
int get_playerHealth(STATE *state);
int get_playerAtack(STATE *state);
void set_playerX(STATE *state, int x);
void set_playerY(STATE *state, int y);
void set_playerHealth(STATE *state, int health);
void set_playerAtack(STATE *state, int atack);
void inicializa_player(STATE *state);
/*void kill(STATE *st);*/
void draw_light(STATE *st, char key, char map[ROWS][COL]);
void remove_light(STATE *st, char key, char map[ROWS][COL]);
void draw_player(STATE *st,char map[ROWS][COL]);

#endif