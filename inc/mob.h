#ifndef MOB_H
#define MOB_H

#include "player.h"
#include "map.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <alsa/asoundlib.h>

typedef struct{
    int x;
    int y;
    int hp;
    int attack;
	bool is_visible;
    bool is_dead;
} MOB;

void spawn_mobs(char map[ROWS][COLS], MOB *mobs[]);
void move_mobs(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]);
MOB *get_closest_mob(MOB *mobs[], PLAYER *player);
void player_attack(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]);
void mob_attack(PLAYER *player, MOB *mobs[]);
void draw_mobs(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]);
bool is_mob_visible(MOB *mob, PLAYER *player, char map[ROWS][COLS]);

#endif