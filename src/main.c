#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <alsa/asoundlib.h>
#include "map.h"
#include "menu.h"
#include "player.h"
#include "mob.h"

#define WALL_PROB 0.465
#define ITERATIONS 10
#define ROWS 30
#define COLS 100

bool only_dots = false;

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
				mvaddch(i,j,map[i][j]);
			}
        }
    }
}

void draw_mobs(MOB *mobs[]) {
    for(int i = 0; i < 10; i++) {
        if(only_dots && mobs[i]->is_visible && !mobs[i]->is_dead) {
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            mvaddch(mobs[i]->y , mobs[i]->x, '!');
            attroff(COLOR_PAIR(1));
        }
        else if(!mobs[i]->is_dead && !only_dots){
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            mvaddch(mobs[i]->y , mobs[i]->x, '!');
            attroff(COLOR_PAIR(1));
        }
    }
}

void update(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]) {
	char key = getch();
	mvaddch(player->y,player->x, ' ');
	remove_light(map);
	switch(key) {
		case 'w': 
            if(valid_move(player, map, key)) do_movement_action(player, map, 0, -1);
            break;
		case 's':
            if(valid_move(player, map, key)) do_movement_action(player, map, 0, 1);
            break;
		case 'a':
            if(valid_move(player, map, key)) do_movement_action(player, map, -1, 0);
            break;
		case 'd':
            if(valid_move(player, map, key)) do_movement_action(player, map, 1, 0);
            break;
		case 'k':
            kill(player, mobs, map);
            break;
		case 'v':
            only_dots = !only_dots;
            desenha_pontos(map);
            break; //altera o modo de visao
		case ' ':
            show_pause_menu();
            break; // espaco
		case 'q':
            endwin();
            exit(0);
            break;
	}
	draw_player(player, map);
	draw_light(player, map, key);
    move_mobs(player, mobs, map);
    draw_mobs(mobs);
	refresh();
}

int main(){
	srand(time(NULL));
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);
	WINDOW *wnd = initscr();
	//roguelite(wnd);
    show_main_menu();

    PLAYER *player = malloc(sizeof(PLAYER));
    inicializa_player(player);
    char map[ROWS][COLS];
	init_map(map);
    MOB *mobs[10];
    for (int i = 0; i < 10; i++) {
        mobs[i] = malloc(sizeof(MOB));
    }
    spawn_mobs(map, mobs);
    
    do {
		player->y = rand() % (COLS - 2) + 1;
		player->x = rand() % (COLS - 2) + 1;
	} while(map[player->y][player->x] == '#' || !dentro_mapa(player->y, player->x));

	WINDOW* window = newwin(ROWS, COLS, 1, 1);
	box(window, '#', '#');
	refresh();
    clear();
    draw_map(map);
    draw_mobs(mobs);
    draw_player(player,map);
    draw_light(player, map, 'w');

	int nrows;
	nrows = getmaxx(wnd);
	while(1) {
		move(nrows - 1, 0);
        start_color();
        init_pair(2,COLOR_BLUE, COLOR_BLACK);
		attron(COLOR_PAIR(2));
		if(player != NULL){
			mvprintw(ROWS-30, COLS +4,"Player state:");
			mvprintw(ROWS-27,COLS+3,"	Health: %d", player->hp);
			mvprintw(ROWS-25,COLS+3,"	Atack: %d", player->attack);
		}
		MOB *mob = get_mob(player, mobs);
		if(mob != NULL){
			mvprintw(ROWS-30, COLS +22,"Monster state:");
			mvprintw(ROWS-27,COLS+21,"	Health: %d",mob->hp);
			mvprintw(ROWS-25,COLS+21,"	Atack: %d",mob->attack);
		}
		else{
			mvprintw(ROWS-30, COLS +22,"Monster state:");
			mvprintw(ROWS-27,COLS+21,"	Health: ");
			mvprintw(ROWS-25,COLS+21,"	Atack: ");
		}
		//mvprintw(ROWS-23,COLS+4,"Posição: (%d, %d) %d %d\n", st->player->playerX, st->player->playerY, ncols, nrows);
		attroff(COLOR_PAIR(2));
		refresh();
		move(player->y, player->x);
		update(player, mobs, map);
		noecho();
	}
    free(player);
    for (int i = 0; i < 10; i++) {
        free(mobs[i]);
    }
	return 0;
}