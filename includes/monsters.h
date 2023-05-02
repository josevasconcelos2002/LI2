#ifndef MONSTERS_H
#define MONSTERS_H

#include <stdbool.h>
#include"testeGeraMapa.h"
#include "state.h"

typedef struct monster MONSTER;

bool is_monster(char c);

void inicializa_monster(struct monster monstros[],int N);

/*void remove_monster(STATE *st);*/

void draw_monster(STATE *st, char map[ROWS][COL]);

#endif