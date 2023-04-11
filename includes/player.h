#ifndef PLAYER_H
#define PLAYER_H

#include "state.h"

typedef struct player PLAYER;

int get_playerX(PLAYER *player);

int get_playerY(PLAYER *player);

int get_playerHealth(PLAYER *player);

int get_playerAtack(PLAYER *player);

void set_playerX(PLAYER *player, int x);

void set_playerY(PLAYER *player, int y);

void set_playerHealth(PLAYER *player, int health);

void set_playerAtack(PLAYER *player, int atack);

void inicializa_player(PLAYER *player);

#endif