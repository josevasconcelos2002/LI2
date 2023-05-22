#include <ncurses.h>
#include "map.h"
#include "menu.h"
#include "player.h"
#include "mob.h"
#include "state.h"

void update(STATE *state, PLAYER *player, MOB *mobs[], char map[ROWS][COLS]) {
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
			if (show_pause_menu() == 1) {
				state->gameState = MENU;
				return;
			}
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
}

bool is_win(MOB *mobs[]) {
	for(int i = 0; i < 10; i++) {
		if(!mobs[i]->is_dead) {
			return false;
		}
	}
	return true;
}

void play_game(STATE *state, PLAYER *player, MOB *mobs[], char map[ROWS][COLS]) {
	init_map(map);    
	init_player(player, map);
    init_mobs(map, mobs);
	spawn_potions(map);
	spawn_sword(map);
	WINDOW* window = newwin(ROWS, COLS, 1, 1);
	box(window, '#', '#');
	refresh();
	clear();
    draw_map(map);
    draw_mobs(player, mobs, map);
    draw_player(player,map);
    draw_light(player, map);

	while(state->gameState == RUNNING) {
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
		update(state, player, mobs, map);
		if(player->hp <= 0) state->gameState = LOST;
		if(is_win(mobs)) state->gameState = WON;
	}
}

int main(){
	srand(time(NULL));
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);
	initscr();
	STATE *state = malloc(sizeof(STATE));
	init_state(state);
    PLAYER *player = malloc(sizeof(PLAYER));
	char map[ROWS][COLS];
	MOB *mobs[10];
    for (int i = 0; i < 10; i++) {
    	mobs[i] = malloc(sizeof(MOB));
	}

	bool quit = false;
	do {
		if(show_main_menu() == 0) {
			state->gameState = RUNNING;
			while(state->gameState == RUNNING) {
				play_game(state, player, mobs, map);
			}
			if(state->gameState == LOST) {
				game_over();
				state->gameState = MENU;
			}else if(state->gameState == WON) {
				you_won();
				state->gameState = MENU;
			}
		}else quit = true;
	}while(!quit);

    free(player);
    for (int i = 0; i < 10; i++) {
        free(mobs[i]);
    }
	free(state);
	endwin();
	return 0;
}