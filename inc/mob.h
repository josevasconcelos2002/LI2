#ifndef MOB_H
#define MOB_H
#define ROWS 30
#define COLS 100

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
double distancia(PLAYER *player, MOB *mob);
MOB *get_mob(PLAYER *player, MOB *mobs[]);
void playSound(const char* filename);
void game_over();
void you_won();
void kill(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]);

#endif