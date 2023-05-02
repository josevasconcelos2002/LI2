#ifndef MONSTERS_H
#define MONSTERS_H

#include <stdbool.h>
#include"testeGeraMapa.h"
#include "state.h"

typedef struct monster MONSTER;

bool is_monster(char c);
int get_monsterX(STATE *st);
int get_monsterY(STATE *st);
int get_monsterHealth(STATE *st);
int get_monsterAttack(STATE *st);
int set_monsterX(STATE *st,int x);
int set_monsterY(STATE *st,int y);
int set_monsterHealth(STATE *st,int health);
int set_monsterAttack(STATE *st,int attack);
void inicializa_monster(struct monster monstros[],int N);

/*void remove_monster(STATE *st);*/

//void draw_monster(STATE *st, char map[ROWS][COL]);

#endif