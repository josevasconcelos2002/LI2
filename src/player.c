#include <ncurses.h>
#include "player.h"

void inicializa_player(PLAYER *player){
    player->x = 15;
    player->y = 15;
    player->hp = 50;
    player->attack = 10;
	player->only_dots = false;
}

void do_movement_action(PLAYER *player, char map[ROWS][COLS], int dx, int dy) {
    map[player->y][player->x] = ' ';
	player->x += dx;
	player->y += dy;
}

bool valid_move(PLAYER *player, char map[ROWS][COLS], char key){
    int x = player->x, y = player->y;
    switch(key) {
        case 'w': if(map[y-1][x] == '#' || map[y-1][x] == '!') return false;
            break;
        case 's': if(map[y+1][x] == '#' || map[y+1][x] == '!') return false;
            break;
        case 'a': if(map[y][x-1] == '#' || map[y][x-1] == '!') return false;
            break;
        case 'd': if(map[y][x+1] == '#' || map[y][x+1] == '!') return false;
            break;            
    }
	return true;
}
/*
void light_up(int y, int x, char map[ROWS][COLS]) {
	attron(COLOR_PAIR(COLOR_YELLOW));
	if(dentro_mapa(y-3,x) && map[y-3][x] == ' ') map[y-3][x] =  '.';
	if(dentro_mapa(y-3,x-1) && map[y-3][x-1] == ' ') map[y-3][x-1] =  '.';
	if(dentro_mapa(y-3,x+1) && map[y-3][x+1] == ' ') map[y-3][x+1] =  '.';
	if(dentro_mapa(y-3,x-2) && map[y-3][x-2] == ' ') map[y-3][x-2] =  '.';
	if(dentro_mapa(y-3,x+2) && map[y-3][x+2] == ' ') map[y-3][x+2] =  '.';
	if(dentro_mapa(y-2,x) && map[y-2][x] == ' ') map[y-2][x] =  '.';
	if(dentro_mapa(y-2,x-1) && map[y-2][x-1] == ' ') map[y-2][x-1] =  '.';
	if(dentro_mapa(y-2,x+1) && map[y-2][x+1] == ' ') map[y-2][x+1] =  '.';
	if(dentro_mapa(y-1,x) && map[y-1][x] == ' ') map[y-1][x] =  '.';
	attroff(COLOR_PAIR(COLOR_YELLOW));
}

void light_down(int y, int x, char map[ROWS][COLS]) {
	attron(COLOR_PAIR(COLOR_YELLOW));
	if(dentro_mapa(y+3,x) && map[(y+3)][x] == ' ') map[y+3][x] =  '.';
	if(dentro_mapa(y+3,x-1) && map[(y+3)][x-1] == ' ') map[y+3][x-1] =  '.';
	if(dentro_mapa(y+3,x+1) && map[(y+3)][x+1] == ' ') map[y+3][x+1] =  '.';
	if(dentro_mapa(y+3,x-2) && map[(y+3)][x-2] == ' ') map[y+3][x-2] =  '.';
	if(dentro_mapa(y+3,x+2) && map[(y+3)][x+2] == ' ') map[y+3][x+2] =  '.';
	if(dentro_mapa(y+2,x) && map[(y+2)][x] == ' ') map[y+2][x] =  '.';
	if(dentro_mapa(y+2,x-1) && map[(y+2)][x-1] == ' ') map[y+2][x-1] =  '.';
	if(dentro_mapa(y+2,x+1) && map[(y+2)][x+1] == ' ') map[y+2][x+1] =  '.';
	if(dentro_mapa(y+1,x) && map[(y+1)][x] == ' ') map[y+1][x] =  '.';
	attroff(COLOR_PAIR(COLOR_YELLOW));
}

void light_right(int y, int x, char map[ROWS][COLS]) {
	attron(COLOR_PAIR(COLOR_YELLOW));
	if(dentro_mapa(y,x-3) && map[y][x-3] == ' ') map[y][x-3] = '.';
	if(dentro_mapa(y-1,x-3) && map[y-1][x-3] == ' ') map[y-1][x-3] = '.';
	if(dentro_mapa(y+1,x-3) && map[y+1][x-3] == ' ') map[y+1][x-3] = '.';
	if(dentro_mapa(y-2,x-3) && map[y-2][x-3] == ' ') map[y-2][x-3] = '.';
	if(dentro_mapa(y+2,x-3) && map[y+2][x-3] == ' ') map[y+2][x-3] = '.';
	if(dentro_mapa(y,x-2) && map[y][x-2] == ' ') map[y][x-2] = '.';
	if(dentro_mapa(y-1,x-2) && map[y-1][x-2] == ' ') map[y-1][x-2] = '.';
	if(dentro_mapa(y+1,x-2) && map[y+1][x-2] == ' ') map[y+1][x-2] = '.';
	if(dentro_mapa(y,x-1) && map[y][x-1] == ' ') map[y][x-1] = '.';
	attroff(COLOR_PAIR(COLOR_YELLOW));
}

void light_left(int y, int x, char map[ROWS][COLS]) {
	attron(COLOR_PAIR(COLOR_YELLOW));
	if(dentro_mapa(y,x+3) && map[y][x+3] == ' ') map[y][x+3] =  '.';
	if(dentro_mapa(y-1,x+3) && map[y-1][x+3] == ' ') map[y-1][x+3] =  '.';
	if(dentro_mapa(y+1,x+3) && map[y+1][x+3] == ' ') map[y+1][x+3] =  '.';
	if(dentro_mapa(y-2,x+3) && map[y-2][x+3] == ' ') map[y-2][x+3] =  '.';
	if(dentro_mapa(y+2,x+3) && map[y+2][x+3] == ' ') map[y+2][x+3] =  '.';
	if(dentro_mapa(y,x+2) && map[y][x+2] == ' ') map[y][x+2] =  '.';
	if(dentro_mapa(y-1,x+2) && map[y-1][x+2] == ' ') map[y-1][x+2] =  '.';
	if(dentro_mapa(y+1,x+2) && map[y+1][x+2] == ' ') map[y+1][x+2] =  '.';
	if(dentro_mapa(y,x+1) && map[y][x+1] == ' ') map[y][x+1] =  '.';
	attroff(COLOR_PAIR(COLOR_YELLOW));
}*/

void draw_light(PLAYER *player, char map[ROWS][COLS]){
    int centerX = player->x;
    int centerY = player->y;
    int xOffset = 3;
    int yOffset = 2;

    for (int i = centerX - xOffset; i <= centerX + xOffset; i++) {
        for (int j = centerY - yOffset; j <= centerY + yOffset; j++) {
            if (dentro_mapa(j,i) && map[j][i] == ' ') {
                map[j][i] = '.';
            }
        }
    }

    attron(COLOR_PAIR(COLOR_YELLOW));

	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
            start_color();
            init_pair(4,COLOR_YELLOW,COLOR_BLACK);
            attron(COLOR_PAIR(4));
			if(map[i][j] == '.') mvaddch(i,j,'.');
            attroff(COLOR_PAIR(4));
		}
	}
    attroff(COLOR_PAIR(COLOR_YELLOW));
}

void remove_light(char map[ROWS][COLS]){
	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == '.'){
				mvaddch(i,j,' ');
				map[i][j] = ' ';
			}
		}
	}
}

void draw_player(PLAYER *player, char map[ROWS][COLS]){
    start_color();
    init_pair(3,COLOR_GREEN,COLOR_BLACK);	
	map[player->y][player->x] = '@';
	attron(COLOR_PAIR(3));
    for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == '@') mvaddch(i,j,'@');
		}
	}
    attroff(COLOR_PAIR(3));
	refresh();
}