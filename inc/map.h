#ifndef MAP_H
#define MAP_H
#define ROWS 30
#define COLS 100
#define WALL_PROB 0.465
#define ITERATIONS 10

#include <stdlib.h>
#include <string.h>

void init_map(char map[ROWS][COLS]);
bool dentro_mapa(int y, int x);
void draw_map(char map[ROWS][COLS]);
void desenha_pontos(char map[ROWS][COLS]);

#endif