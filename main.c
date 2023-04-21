#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include "src/testeGeraMapa.h"
//#include "player.h"
//#include "state.h"
//#include "monsters.h"

/**
 *
 * Falta muita coisa, incluindo por exemplo:
 * - o mapa
 * - os monstros
 * - a fila de prioridade para saber quem se move
 * - o que está em cada casa
 *
 */

typedef struct player{
	int playerX;
	int playerY;
	int playerHealth;
	int playerAtack;
} PLAYER;

typedef struct monster{
	int monsterX;
	int monsterY;
	int monsterHealth;
	int monsterAtack;
} MONSTER;

typedef struct state {
	PLAYER *player;
	MONSTER *monster;
} STATE;




void init_map(char map[ROWS][COLS]) {
    // Inicializa o mapa com caminhos e paredes aleatórios
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (rand() < WALL_PROB * RAND_MAX) {
                map[i][j] = '#';
            } else {
                map[i][j] = ' ';
            }
        }
    }
}

void update_map(char map[ROWS][COLS]) {
    // Faz update ao mapa usando o algoritmo cellular automata, para o melhorar
    char new_map[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int num_walls = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (i+di >= 0 && i+di < ROWS && j+dj >= 0 && j+dj < COLS) {
                        if (map[i+di][j+dj] == '#') {
                            num_walls++;
                        }
                    }
                }
            }
            if (num_walls >= 5 || (num_walls == 1 && rand() < 0.2 * RAND_MAX)) {
                new_map[i][j] = '#';
            } else {
                new_map[i][j] = ' ';
            }
        }
    }
    // Copia o novo mapa para o original
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = new_map[i][j];
        }
    }
}

void remove_isolated_walls(char map[ROWS][COLS]) {
    // Remove paredes isoladas e pequenos blocos de paredes
    char new_map[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (map[i][j] == '#') {
                int num_walls = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (i+di >= 0 && i+di < ROWS && j+dj >= 0 && j+dj < COLS) {
                            if (map[i+di][j+dj] == '#') {
                                num_walls++;
                            }
                        }
                    }
                }
                if (num_walls >= 1 && num_walls <= 5) {
                    // Verifica se há mais paredes numa area de 3x3 à volta de uma parede. Se estiver isolada, transforma em caminho
                    int num_surrounding_walls = 0;
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            if (i+di >= 0 && i+di < ROWS && j+dj >= 0 && j+dj < COLS) {
                                if (map[i+di][j+dj] == '#') {
                                    num_surrounding_walls++;
                                }
                            }
                        }
                    }
                    if (num_surrounding_walls <= 5) {
                        new_map[i][j] = ' ';
                    } else {
                        new_map[i][j] = '#';
                    }
                }
            } else {
                new_map[i][j] = ' ';
            }
        }
    }
    // Copia o novo mapa para o original
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = new_map[i][j];
        }
    }
}



void inicializa_player(PLAYER *player){
    player->playerX = 20;
    player->playerY = 20;
    player->playerHealth = 100;
    player->playerAtack = 10;
}

/*
void inicializa_monster(MONSTER *monster){
	monster->monsterX = ...;
    monster->monsterY = ...;
    monster->monsterHealth = ...;
    monster->monsterAtack = ...;

}
*/

void inicializa_state(STATE *st){
	st->player = malloc(sizeof(PLAYER));
	inicializa_player(st->player);
	//st->monster = malloc(sizeof(MONSTER));
	//inicializa_monster(st->monster);
}

/**
 *
 * Um pequeno exemplo que mostra o que se pode fazer
 */
void do_movement_action(STATE *st, int dx, int dy) {
	st->player->playerX += dx;//set_playerX(get_player(st),get_playerX(get_player(st)) + dx);
	st->player->playerY += dy;//set_playerY(get_player(st),get_playerY(get_player(st)) + dy);
}



bool is_parede(int key){
	return (key == 35);
}

bool is_move_right(int key){
	return key == 100;
}

bool is_move_left(int key){
	return key == 97;
}

bool is_move_up(int key){
	return key == 119;
}

bool is_move_down(int key){
	return key == 115;
}

void remove_light(STATE *st, char key){
	if(is_move_left((int)key)){
		if(mvinch(st->player->playerY, st->player->playerX-3) == '.') mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ ,  st->player->playerX/*get_playerY(get_player(st))*/-3, '~' | A_BOLD);
		if(mvinch(st->player->playerY-1, st->player->playerX-3) == '.') mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ -1,  st->player->playerX-1/*get_playerY(get_player(st))*/-3, '~' | A_BOLD);
		if(mvinch(st->player->playerY+1, st->player->playerX-3) == '.') mvaddch(st->player->playerY/*get_playerX(get_player(st))*/+1 ,  st->player->playerX/*get_playerY(get_player(st))*/-3, '~' | A_BOLD);
		if(mvinch(st->player->playerY-2, st->player->playerX-3) == '.') mvaddch(st->player->playerY/*get_playerX(get_player(st))*/-2 ,  st->player->playerX/*get_playerY(get_player(st))*/-3, '~' | A_BOLD);
		if(mvinch(st->player->playerY+2, st->player->playerX-3) == '.') mvaddch(st->player->playerY/*get_playerX(get_player(st))*/+2 ,  st->player->playerX/*get_playerY(get_player(st))*/-3, '~' | A_BOLD);
		if(mvinch(st->player->playerY, st->player->playerX-2) == '.') mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ ,  st->player->playerX/*get_playerY(get_player(st))*/-2, '~' | A_BOLD);
		if(mvinch(st->player->playerY-1, st->player->playerX-2) == '.') mvaddch(st->player->playerY/*get_playerX(get_player(st))*/-1 ,  st->player->playerX/*get_playerY(get_player(st))*/-2, '~' | A_BOLD);
		if(mvinch(st->player->playerY+1, st->player->playerX-2) == '.') mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/-2, '~' | A_BOLD);
		if(mvinch(st->player->playerY, st->player->playerX-1) == '.') mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ ,  st->player->playerX/*get_playerY(get_player(st))*/-1, '~' | A_BOLD);
	}
}

void draw_light(STATE *st, char key){
	if(is_move_left((int)key)){
		attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ ,  st->player->playerX/*get_playerY(get_player(st))*/-3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX-3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 1,  st->player->playerX/*get_playerY(get_player(st))*/ - 3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX-3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/ -3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX-3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 2,  st->player->playerX/*get_playerY(get_player(st))*/ - 3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX-3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ + 2,  st->player->playerX/*get_playerY(get_player(st))*/ -3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,  st->player->playerX/*get_playerY(get_player(st))*/-2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX-2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 1,  st->player->playerX/*get_playerY(get_player(st))*/ - 2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX-2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/ -2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,  st->player->playerX/*get_playerY(get_player(st))*/-1, '.' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_up((int)key)){
		attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ -3,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX-1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 3,  st->player->playerX/*get_playerY(get_player(st))*/ - 1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX+1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ -3,  st->player->playerX/*get_playerY(get_player(st))*/ +1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX-2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 3,  st->player->playerX/*get_playerY(get_player(st))*/ - 2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX+2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ -3,  st->player->playerX/*get_playerY(get_player(st))*/ +2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/-2,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX-1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 2,  st->player->playerX/*get_playerY(get_player(st))*/ - 1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX+1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ -2,  st->player->playerX/*get_playerY(get_player(st))*/ +1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/-1,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_right((int)key)){
		attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX+3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ ,  st->player->playerX/*get_playerY(get_player(st))*/+3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX+3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 1,  st->player->playerX/*get_playerY(get_player(st))*/ +3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX+3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/ +3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX+3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 2,  st->player->playerX/*get_playerY(get_player(st))*/ +3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX+3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ + 2,  st->player->playerX/*get_playerY(get_player(st))*/ +3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX+2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,  st->player->playerX/*get_playerY(get_player(st))*/+2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX+2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 1,  st->player->playerX/*get_playerY(get_player(st))*/ +2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX+2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/ +2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX+1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,  st->player->playerX/*get_playerY(get_player(st))*/+1, '.' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_down((int)key)){
		attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +3,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX-1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +3,  st->player->playerX/*get_playerY(get_player(st))*/ -1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX+1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +3,  st->player->playerX/*get_playerY(get_player(st))*/ +1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX-2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +3,  st->player->playerX/*get_playerY(get_player(st))*/ -2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX+2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +3,  st->player->playerX/*get_playerY(get_player(st))*/ +2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/+2,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX-1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +2,  st->player->playerX/*get_playerY(get_player(st))*/ -1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX+1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +2,  st->player->playerX/*get_playerY(get_player(st))*/ +1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/+1,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_YELLOW));
	}
}

void draw_player(STATE *st){
	attron(COLOR_PAIR(COLOR_WHITE));
    mvaddch(st->player->playerY, st->player->playerX, '@' | A_BOLD);
    attroff(COLOR_PAIR(COLOR_WHITE));
}

void draw_monster(STATE *st){
	//attron(COLOR_PAIR(COLOR_RED));
	mvaddch(st->monster->monsterY, st->monster->mosnterX, '!' | A_BOLD);
	//attroff(COLOR_PAIR(COLOR_RED));
}

bool valid_move(STATE *st,int key){
	bool r = true;
	if(is_move_right(key) && mvinch(st->player->playerY, st->player->playerX+1) == '#') r = false;
	if(is_move_left(key) && mvinch(st->player->playerY, st->player->playerX-1) == '#') r = false;
	if(is_move_up(key) && mvinch(st->player->playerY-1, st->player->playerX) == '#') r = false;
	if(is_move_down(key) && mvinch(st->player->playerY+1, st->player->playerX) == '#') r = false;
	return r;
}

void update(STATE *st) {
	int key = getch();

	mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,st->player->playerX /*get_playerY(get_player(st))*/, ' ');
	switch(key) {
		/*
		case KEY_A1:
		case '7': do_movement_action(st, -1, -1); break;
		case KEY_UP:
		case '8': do_movement_action(st, -1, +0); break;
		case KEY_A3:
		case '9': do_movement_action(st, -1, +1); break;
		case KEY_LEFT:
		case '4': do_movement_action(st, +0, -1); break;
		case KEY_B2:
		case '5': break;
		case KEY_RIGHT:
		case '6': do_movement_action(st, +0, +1); break;
		case KEY_C1:
		case '1': do_movement_action(st, +1, -1); break;
		case KEY_DOWN:
		case '2': do_movement_action(st, +1, +0); break;
		case KEY_C3:
		case '3': do_movement_action(st, +1, +1); break;
		*/
		case 'w': if(valid_move(st,(int)'w')) do_movement_action(st, +0, -1); break;
		case 's': if(valid_move(st,(int)'s')) do_movement_action(st, +0, +1); break;
		case 'a': if(valid_move(st,(int)'a')) do_movement_action(st, -1, +0); break;
		case 'd': if(valid_move(st,(int)'d')) do_movement_action(st, +1, +0); break;
		case 'v': endwin(); exit(0); break; //altera o modo de visao
		case 'q': endwin(); exit(0); break;
	}

	


	spawn_mob(st);
	//draw_monster(st);
	draw_player(st);
	draw_light(st,key);
	remove_light(st,key);
}

int spawn_mob(STATE *st){
	for (i = 0; i < 10; i++) {
      st->monster->monsterX = rand() % ROWS;
      st->monster->monsterY = rand() % COLS;
      mvaddch(MONSTER.monsterY, MONSTER.monsterX, MOB);
   }
}



void menu(){

}






void inicializa(){
	srandom(time(NULL));
	start_color();

	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
}


int main(){
	inicializa();
	STATE *st = malloc(sizeof(STATE));;
	inicializa_state(st);
	WINDOW *wnd = initscr();
	int ncols, nrows;
	getmaxyx(wnd,nrows,ncols);
	char map[ROWS][COLS];
		init_map(map);

		// Faz update no mapa
		for (int i = 0; i < ITERATIONS; i++) {
			update_map(map);
		}
		
		// Remove paredes isoladas e pequenos blocos de paredes
		remove_isolated_walls(map);

		// Adiciona paredes nas bordas do mapa
		for (int i = 0; i < ROWS; i++) {
			map[i][0] = '#';
			map[i][COLS-1] = '#';
		}
		for (int j = 0; j < COLS; j++) {
			map[0][j] = '#';
			map[ROWS-1][j] = '#';
		}

		// Desenha o mapa no ecra
		clear();
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				mvaddch(i, j, map[i][j]);
			}
		}
		//refresh();
	while(1) {
		move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		printw("(%d, %d) %d %d", st->player->playerX, st->player->playerY, ncols, nrows);
		attroff(COLOR_PAIR(COLOR_BLUE));
				// Inicializa o mapa
		
		//draw_player(st);
		//draw_monster(st);
		//draw_light(st);
		//update(st);
		move(st->player->playerX, st->player->playerY);
		//move(st->monster->mosnterX, st->monster->monsterY);
		update(st);
		noecho();
	}
	free(st->player);
	free(st);
	return 0;
}