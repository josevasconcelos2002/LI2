#include "state.h"
#include "player.h"
#include "monsters.h"
#include <stdbool.h>
#include <stdlib.h>



void inicializa_state(STATE *st){
	st->player = malloc(sizeof(PLAYER));
	inicializa_player(st->player);
	inicializa_monster(st->monstros,10);
}

struct player *get_player(STATE *st){
	return (struct player *)st->player;
}

void do_movement_action(STATE *st, int dx, int dy,char map[ROWS][COLS]) {
	st->player->playerX += dx;
	st->player->playerY += dy;
	map[st->player->playerY-dy][st->player->playerX-dx] = ' ';
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

bool valid_move(STATE *st,int key,char map[ROWS][COLS]){
	bool r = true;
	if(!only_dots){
		if((is_move_right(key) && (is_parede((int)map[st->player->playerY][st->player->playerX+1]))) || is_monster(map[st->player->playerY][st->player->playerX+1])) r = false;
		if((is_move_left(key) && (is_parede((int)map[st->player->playerY][st->player->playerX-1]))) || is_monster(map[st->player->playerY][st->player->playerX-1])) r = false;
		if((is_move_up(key) && (is_parede((int)map[st->player->playerY-1][st->player->playerX]))) || is_monster(map[st->player->playerY-1][st->player->playerX])) r = false;
		if((is_move_down(key) && (is_parede((int)map[st->player->playerY+1][st->player->playerX]))) || is_monster(map[st->player->playerY+1][st->player->playerX])) r = false;
	}
	else{
		if(is_move_right(key) && (is_parede((int)map[st->player->playerY][st->player->playerX+1]))) r = false;
		if(is_move_left(key) && (is_parede((int)map[st->player->playerY][st->player->playerX-1]))) r = false;
		if(is_move_up(key) && (is_parede((int)map[st->player->playerY-1][st->player->playerX]))) r = false;
		if(is_move_down(key) && (is_parede((int)map[st->player->playerY+1][st->player->playerX]))) r = false;
	}
	return r;
}


void desenha_pontos(char map[ROWS][COLS]) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {

			if(only_dots){
				if(map[i][j] == '#'){
					mvaddch(i,j,' ');
				}
				if(map[i][j] == '.' && mvinch(i,j) == '!') mvaddch(i,j,'!');
				else if(map[i][j] == '.'){
					mvaddch(i,j,'.');
				}
			}
			else{
				if(map[i][j] == '#'){
					mvaddch(i,j,map[i][j]);
				}
			}
        }
    }
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

void update(STATE *st,char map[ROWS][COLS]) {
	int key = getch();
	mvaddch(st->player->playerY,st->player->playerX, ' ');
	remove_light(st,key,map);
	switch(key) {
		case 'w': if(valid_move(st,(int)'w',map)) do_movement_action(st, +0, -1,map); break;
		case 's': if(valid_move(st,(int)'s',map)) do_movement_action(st, +0, +1,map); break;
		case 'a': if(valid_move(st,(int)'a',map)) do_movement_action(st, -1, +0,map); break;
		case 'd': if(valid_move(st,(int)'d',map)) do_movement_action(st, +1, +0,map); break;
		//case 'k': kill(st); break;
		case 'v': only_dots =  !only_dots;  desenha_pontos(map); break; //altera o modo de visao
		case ' ': show_pause_menu(); break; // espaco
		case 'q': endwin(); exit(0); break;
	}

	//spawn_mob(st);
	draw_monster(st,map);
	draw_player(st,map);
	draw_light(st,key,map);
	refresh();
}