#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
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

//MONSTER monstros[10];
bool only_dots = false;

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

bool is_monster(char c){
	bool resultado = false;
	if(c == '!') resultado = true;
	return resultado;
}

void inicializa_player(PLAYER *player){
    player->playerX = 20;
    player->playerY = 20;
    player->playerHealth = 100;
    player->playerAtack = 10;
}


void inicializa_monster(MONSTER *monster){
	monster->monsterX = 25;
    monster->monsterY = 25;
    monster->monsterHealth = 50;
    monster->monsterAtack = 5;

}

void remove_monster(STATE *st){
	int x = st->monster->monsterX;
	int y = st->monster->monsterY;
	mvaddch(y,x, ' ' | A_BOLD);
	st->monster = NULL;
}

void inicializa_state(STATE *st){
	st->player = malloc(sizeof(PLAYER));
	inicializa_player(st->player);
	st->monster = malloc(sizeof(MONSTER));
	inicializa_monster(st->monster);
}

/**
 *
 * Um pequeno exemplo que mostra o que se pode fazer
 */
void do_movement_action(STATE *st, int dx, int dy) {
	st->player->playerX += dx;
	st->player->playerY += dy;
}
/*
void game_over() {
    // Configura a janela
    int height = 3; // altura da janela
    int width = 10; // largura da janela
    int starty = (LINES - height) / 2; // posição y da janela
    int startx = (COLS - width) / 2; // posição x da janela
    WINDOW *win = newwin(height, width, starty, startx); // cria a janela
    box(win, 0, 0); // adiciona uma borda à janela
    refresh();
    wrefresh(win);

    // Configura as cores
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    wbkgd(win, COLOR_PAIR(1));

    // Imprime a mensagem na janela
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 1, 3, "GAME OVER");
    wattroff(win, COLOR_PAIR(3));

    // Espera 3 segundos antes de fechar a janela
    wrefresh(win);
    sleep(3);

    // Libera a janela
    delwin(win);
    endwin();
}
*/



void kill(STATE *st){
	if(is_monster(mvinch(st->player->playerY,st->player->playerX+1))){
		st->monster->monsterHealth -= st->player->playerAtack; // como saber qual monster se está a referir?
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(is_monster(mvinch(st->player->playerY,st->player->playerX-1))){
		st->monster->monsterHealth -= st->player->playerAtack;
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(is_monster(mvinch(st->player->playerY+1,st->player->playerX))){
		st->monster->monsterHealth -= st->player->playerAtack;
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(is_monster(mvinch(st->player->playerY-1,st->player->playerX))){
		st->monster->monsterHealth -= st->player->playerAtack;
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(st->monster->monsterHealth <= 0) remove_monster(st);
	/*if(st->player->playerHealth <= 0){
		endwin();
		game_over();
	}
	*/
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
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-3)) && !is_monster(mvinch(st->player->playerY, st->player->playerX-3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ ,  st->player->playerX/*get_playerY(get_player(st))*/-3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX-3)) && !is_monster(mvinch(st->player->playerY-1, st->player->playerX-3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 1,  st->player->playerX/*get_playerY(get_player(st))*/ - 3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX-3)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX-3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/ -3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX-3)) && !is_monster(mvinch(st->player->playerY-2, st->player->playerX-3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 2,  st->player->playerX/*get_playerY(get_player(st))*/ - 3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX-3)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX-3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ + 2,  st->player->playerX/*get_playerY(get_player(st))*/ -3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-2)) && !is_monster(mvinch(st->player->playerY, st->player->playerX-2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,  st->player->playerX/*get_playerY(get_player(st))*/-2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX-2)) && !is_monster(mvinch(st->player->playerY-1, st->player->playerX-2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 1,  st->player->playerX/*get_playerY(get_player(st))*/ - 2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX-2)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX-2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/ -2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX-1)) && !is_monster(mvinch(st->player->playerY, st->player->playerX-1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,  st->player->playerX/*get_playerY(get_player(st))*/-1, '.' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_up((int)key)){
		attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX)) && !is_monster(mvinch(st->player->playerY-3, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ -3,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX-1)) && !is_monster(mvinch(st->player->playerY-3, st->player->playerX-1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 3,  st->player->playerX/*get_playerY(get_player(st))*/ - 1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX+1)) && !is_monster(mvinch(st->player->playerY-3, st->player->playerX+1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ -3,  st->player->playerX/*get_playerY(get_player(st))*/ +1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX-2)) && !is_monster(mvinch(st->player->playerY-3, st->player->playerX-2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 3,  st->player->playerX/*get_playerY(get_player(st))*/ - 2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-3, st->player->playerX+2)) && !is_monster(mvinch(st->player->playerY-3, st->player->playerX+2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ -3,  st->player->playerX/*get_playerY(get_player(st))*/ +2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX)) && !is_monster(mvinch(st->player->playerY-2, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/-2,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX-1)) && !is_monster(mvinch(st->player->playerY-2, st->player->playerX-1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 2,  st->player->playerX/*get_playerY(get_player(st))*/ - 1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX+1)) && !is_monster(mvinch(st->player->playerY-2, st->player->playerX+1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ -2,  st->player->playerX/*get_playerY(get_player(st))*/ +1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX)) && !is_monster(mvinch(st->player->playerY-1, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/-1,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_right((int)key)){
		attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX+3)) && !is_monster(mvinch(st->player->playerY, st->player->playerX+3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ ,  st->player->playerX/*get_playerY(get_player(st))*/+3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX+3)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX+3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 1,  st->player->playerX/*get_playerY(get_player(st))*/ +3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX+3)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX+3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/ +3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-2, st->player->playerX+3)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX+3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 2,  st->player->playerX/*get_playerY(get_player(st))*/ +3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX+3)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX+3))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ + 2,  st->player->playerX/*get_playerY(get_player(st))*/ +3, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX+2)) && !is_monster(mvinch(st->player->playerY, st->player->playerX+2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,  st->player->playerX/*get_playerY(get_player(st))*/+2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY-1, st->player->playerX+2)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX+2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ - 1,  st->player->playerX/*get_playerY(get_player(st))*/ +2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX+2)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX+2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +1,  st->player->playerX/*get_playerY(get_player(st))*/ +2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY, st->player->playerX+1)) && !is_monster(mvinch(st->player->playerY, st->player->playerX+1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/,  st->player->playerX/*get_playerY(get_player(st))*/+1, '.' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_down((int)key)){
		attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX)) && !is_monster(mvinch(st->player->playerY+3, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +3,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX-1)) && !is_monster(mvinch(st->player->playerY+3, st->player->playerX-1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +3,  st->player->playerX/*get_playerY(get_player(st))*/ -1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX+1)) && !is_monster(mvinch(st->player->playerY+3, st->player->playerX+1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +3,  st->player->playerX/*get_playerY(get_player(st))*/ +1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX-2)) && !is_monster(mvinch(st->player->playerY+3, st->player->playerX-2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +3,  st->player->playerX/*get_playerY(get_player(st))*/ -2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+3, st->player->playerX+2)) && !is_monster(mvinch(st->player->playerY+3, st->player->playerX+2))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +3,  st->player->playerX/*get_playerY(get_player(st))*/ +2, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/+2,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX-1)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX-1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +2,  st->player->playerX/*get_playerY(get_player(st))*/ -1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+2, st->player->playerX+1)) && !is_monster(mvinch(st->player->playerY+2, st->player->playerX+1))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/ +2,  st->player->playerX/*get_playerY(get_player(st))*/ +1, '.' | A_BOLD);
		if(!is_parede(mvinch(st->player->playerY+1, st->player->playerX)) && !is_monster(mvinch(st->player->playerY+1, st->player->playerX))) mvaddch(st->player->playerY/*get_playerX(get_player(st))*/+1,  st->player->playerX/*get_playerY(get_player(st))*/, '.' | A_BOLD);
		attroff(COLOR_PAIR(COLOR_YELLOW));
	}
}

void draw_player(STATE *st){
	attron(COLOR_PAIR(COLOR_WHITE));
    mvaddch(st->player->playerY, st->player->playerX, '@' | A_BOLD);
    attroff(COLOR_PAIR(COLOR_WHITE));
}

void draw_monster(STATE *st){
	attron(COLOR_PAIR(COLOR_RED));
	if(st->monster != NULL){
		mvaddch(st->monster->monsterY, st->monster->monsterX, '!' | A_BOLD);
	}
	attroff(COLOR_PAIR(COLOR_RED));
}

bool valid_move(STATE *st,int key,char map[ROWS][COLS]){
	bool r = true;
	if(!only_dots){
		if(is_move_right(key) && (is_parede((int)mvinch(st->player->playerY, st->player->playerX+1)) || is_monster(mvinch(st->player->playerY, st->player->playerX+1)))) r = false;
		if(is_move_left(key) && (is_parede((int)mvinch(st->player->playerY, st->player->playerX-1)) || is_monster(mvinch(st->player->playerY, st->player->playerX-1)))) r = false;
		if(is_move_up(key) && (is_parede((int)mvinch(st->player->playerY-1, st->player->playerX)) || is_monster(mvinch(st->player->playerY-1, st->player->playerX)))) r = false;
		if(is_move_down(key) && (is_parede((int)mvinch(st->player->playerY+1, st->player->playerX)) || is_monster(mvinch(st->player->playerY+1, st->player->playerX)))) r = false;
	}
	else{
		if(is_move_right(key) && (is_parede((int)map[st->player->playerY][st->player->playerX+1]))) r = false;
		if(is_move_left(key) && (is_parede((int)map[st->player->playerY][st->player->playerX-1]))) r = false;
		if(is_move_up(key) && (is_parede((int)map[st->player->playerY-1][st->player->playerX]))) r = false;
		if(is_move_down(key) && (is_parede((int)map[st->player->playerY+1][st->player->playerX]))) r = false;
	}
	return r;
}
/*
int spawn_mob(STATE *st){
	int i;
	for (i = 0; i < 10; i++) {
      	st->monster->monsterX = rand() % ROWS;
      	st->monster->monsterY = rand() % COLS;
      	mvaddch(MONSTER.monsterY, MONSTER.monsterX, MOB);
   }
}
*/



void desenha_pontos(char map[ROWS][COLS]) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {

			if(only_dots){
				if(mvinch(i,j) == '#'){
					mvaddch(i,j,' ');
				}
			}
			else{
				if(map[i][j] == '#'){
					mvaddch(i,j,map[i][j]);
				}
				else{
					mvaddch(i,j,mvinch(i,j));
				}
			}
        }
    }
}


void update(STATE *st,char map[ROWS][COLS]) {
	int key = getch();
	mvaddch(st->player->playerY,st->player->playerX, ' ');
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
		case 'w': if(valid_move(st,(int)'w',map)) do_movement_action(st, +0, -1); break;
		case 's': if(valid_move(st,(int)'s',map)) do_movement_action(st, +0, +1); break;
		case 'a': if(valid_move(st,(int)'a',map)) do_movement_action(st, -1, +0); break;
		case 'd': if(valid_move(st,(int)'d',map)) do_movement_action(st, +1, +0); break;
		case 'k': kill(st); break;
		case 'v': only_dots =  !only_dots;  desenha_pontos(map); break; //altera o modo de visao
		case 'q': endwin(); exit(0); break;
	}

	//spawn_mob(st);
	draw_monster(st);
	draw_player(st);
	draw_light(st,key);
	remove_light(st,key);
}


// Função para exibir o menu principal
int show_main_menu() {
    clear(); // Limpa a tela
    int x, y; // Variáveis para armazenar a posição atual do cursor
    int choice = 0; // Variável para armazenar a escolha do jogador
    char *options[] = {"Jogar", "Sair"}; // Opções do menu

    // Configurações iniciais
    curs_set(0); // Oculta o cursor
    attron(A_BOLD); // Define a fonte em negrito
    attron(COLOR_PAIR(1)); // Define a cor do texto
    mvprintw(5, 15, "Bem-vindo ao jogo!");
    attroff(COLOR_PAIR(1)); // Desativa a cor do texto
    attroff(A_BOLD); // Desativa a fonte em negrito
    mvprintw(7, 15, "Selecione uma opção:");

    // Imprime as opções do menu
    for (int i = 0; i < 2; i++) {
        y = 9 + i*2;
        x = 15;
        if (i == choice) {
            attron(A_REVERSE);
        }
        mvprintw(y, x, "%s", options[i]);
        attroff(A_REVERSE);
    }
    refresh();

    // Aguarda a seleção do jogador
    int c;
    while (1) {
        c = getch(); // Lê a entrada do jogador
        switch(c) {
            case KEY_UP:
                if (choice > 0) {
                    choice--;
                }
                break;
            case KEY_DOWN:
                if (choice < 1) {
                    choice++;
                }
                break;
            case '\n':
                return choice; // Retorna a escolha do jogador
        }

        // Atualiza o destaque da opção selecionada
        for (int i = 0; i < 2; i++) {
            y = 9 + i*2;
            x = 15;
            if (i == choice) {
                attron(A_REVERSE);
            }
            mvprintw(y, x, "%s", options[i]);
            attroff(A_REVERSE);
        }
        refresh();
    }
}

void show_pause_menu() {
    clear();
    int menu_choice = 0;
    int x, y;
    getmaxyx(stdscr, y, x);

    // Define as opções do menu
    char *menu_items[] = {
        "Continuar",
        "Recomecar",
        "Sair"
    };
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);

    // Desenha o menu na tela
    mvprintw(y/2-2, x/2-5, "Pause");
    for (int i = 0; i < num_items; i++) {
        if (i == menu_choice) {
            attron(A_REVERSE);
        }
        mvprintw(y/2+i, x/2-5, menu_items[i]);
        attroff(A_REVERSE);
    }
    refresh();

    // Processa as teclas pressionadas pelo jogador
    while (true) {
        int key = getch();
        if (key == KEY_UP) {
            menu_choice--;
            if (menu_choice < 0) {
                menu_choice = num_items-1;
            }
        } else if (key == KEY_DOWN) {
            menu_choice++;
            if (menu_choice >= num_items) {
                menu_choice = 0;
            }
        } else if (key == '\n') {
            // Executa a opção escolhida
            if (menu_choice == 0) {
                return;
            } else if (menu_choice == 1) {
                restart_game();
                return;
            } else if (menu_choice == 2) {
                endwin();
                exit(0);
            }
        }
        // Atualiza o menu com a opção selecionada
        clear();
        mvprintw(y/2-2, x/2-5, "Pause");
        for (int i = 0; i < num_items; i++) {
            if (i == menu_choice) {
                attron(A_REVERSE);
            }
            mvprintw(y/2+i, x/2-5, menu_items[i]);
            attroff(A_REVERSE);
        }
        refresh();
    }
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
	STATE *st = malloc(sizeof(STATE));
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
		if(st->monster != NULL){
			printw("Mob state: \n");
			printw("	Health: %d\n",st->monster->monsterHealth);
			printw("	Atack: %d \n",st->monster->monsterAtack);
		}
		printw("(%d, %d) %d %d\n", st->player->playerX, st->player->playerY, ncols, nrows);
		attroff(COLOR_PAIR(COLOR_BLUE));
				// Inicializa o mapa
		
		//draw_player(st);
		//draw_monster(st);
		//draw_light(st);
		//update(st);
		move(st->player->playerX, st->player->playerY);
		//move(st->monster->mosnterX, st->monster->monsterY);
		update(st,map);
		noecho();
	}
	free(st->player);
	free(st);
	return 0;
}