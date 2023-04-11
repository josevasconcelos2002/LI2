#ifndef STATE_H
#define STATE_H

#include "player.h"

typedef struct state  STATE;

//typedef struct player PLAYER;

struct player *get_player(STATE *st);

void inicializa_state(STATE *st);

#endif