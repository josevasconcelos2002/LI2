#include <ncurses.h>
#include "map.h"
#include "menu.h"
#include "player.h"
#include "mob.h"

int update(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]) {
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
            player_attack(player, mobs, map);
            break;
		case 'v':
            player->only_dots = !player->only_dots;
            if(player->only_dots) {
				desenha_pontos(map);
			}else draw_map(map);
            break; //altera o modo de visao
		case ' ':
			clear();
            if(show_pause_menu() == 1) return 3;
			draw_map(map); 
            break; // espaco
		case 'q':
            endwin();
            exit(0);
            break;
		default:
			break;
	}
	draw_player(player, map);
	move_mobs(player, mobs, map);
	for(int i = 0; i < 10; i++) {
		if(is_mob_visible(mobs[i], player, map) && !mobs[i]->is_dead) {
			mobs[i]->is_visible = true;
		}
	}
	draw_light(player, map);
    draw_mobs(player, mobs, map);
	refresh();
	return 0;
}

bool is_win(MOB *mobs[]) {
	for(int i = 0; i < 10; i++) {
		if(!mobs[i]->is_dead) {
			return false;
		}
	}
	return true;
}

int play_game(PLAYER *player, MOB *mobs[], char map[ROWS][COLS], int nrows) {
    inicializa_player(player);
	init_map(map);
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
    draw_mobs(player, mobs, map);
    draw_player(player,map);
    draw_light(player, map);

	while(1) {
		move(nrows - 1, 0);
        start_color();
        init_pair(2,COLOR_BLUE, COLOR_BLACK);
		attron(COLOR_PAIR(2));
		mvprintw(ROWS - 30, COLS + 4, "                                                ");
    	mvprintw(ROWS - 27, COLS + 3, "                                                ");
    	mvprintw(ROWS - 25, COLS + 3, "                                                ");
		if(player != NULL){
			mvprintw(ROWS-30, COLS +4,"Player state:");
			mvprintw(ROWS-27,COLS+3,"	Health: %d", player->hp);
			mvprintw(ROWS-25,COLS+3,"	Atack: %d", player->attack);
		}
		MOB *mob = get_closest_mob(mobs, player);
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
		attroff(COLOR_PAIR(2));
		refresh();
		move(player->y, player->x);
		mob_attack(player, mobs);
		if(update(player, mobs, map) == 3) return 3;
		if(player->hp <= 0) return 1;
		if(is_win(mobs)) return 2;
		noecho();
	}
	return 0;
}

int main(){
	srand(time(NULL));
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);
	WINDOW *wnd = initscr();
	int nrows;
	nrows = getmaxx(wnd);

    PLAYER *player = malloc(sizeof(PLAYER));
	char map[ROWS][COLS];
	MOB *mobs[10];
    for (int i = 0; i < 10; i++) {
    	mobs[i] = malloc(sizeof(MOB));
	}

	int play;
	bool quit = false;
	do {
		if(show_main_menu() == 0) {
			clear();
			do {
				play = play_game(player, mobs, map, nrows);
			}while(play == 0);

			if(play == 1) {
				game_over();
				play = 3;
			}else if(play == 2) {
				you_won();
				play = 3;
			}
			endwin();
		}else quit = true;
	}while(!quit);

    free(player);
    for (int i = 0; i < 10; i++) {
        free(mobs[i]);
    }
	endwin();
	return 0;
}