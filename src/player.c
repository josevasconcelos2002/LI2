#include <ncurses.h>
#include "player.h"

void init_player(PLAYER *player, char map[ROWS][COLS]){
    do {
		player->y = rand() % (COLS - 2) + 1;
		player->x = rand() % (COLS - 2) + 1;
	} while(map[player->y][player->x] == '#' || !dentro_mapa(player->y, player->x));
    player->hp = 100;
    player->attack = 10;
	player->only_dots = false;
}

void do_movement_action(PLAYER *player, char map[ROWS][COLS], int dx, int dy) {
    map[player->y][player->x] = ' ';
	player->x += dx;
	player->y += dy;
	if(map[player->y][player->x] == '+'){
		player->hp += 20;
		map[player->y][player->x] = '@';
	}
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

void spawn_potions(char map[ROWS][COLS]){
	for (int i = 0; i < 10; i++) {
		int x, y;
		do {
			// Gera uma posição aleatória
			x = rand() % COLS;
			y = rand() % ROWS;
		} while (!dentro_mapa(y,x) || map[y][x] == '#' || map[y][x] == '@' || map[y][x] == '+');
		map[y][x] = '+';
	}
}


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

	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
            start_color();
            init_pair(4,COLOR_YELLOW,COLOR_BLACK);
            attron(COLOR_PAIR(4));
			if(map[i][j] == '.') mvaddch(i,j,'.');
            attroff(COLOR_PAIR(4));
		}
	}
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