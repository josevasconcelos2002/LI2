#include "testeGeraMapa.h"
#include <stdbool.h>
#include "monsters.h"
#include "player.h"

typedef struct state STATE;

PLAYER *get_player(STATE *st);
MONSTER *get_monsters(STATE *st)
void inicializa_state(STATE *st);
void do_movement_action(STATE *st, int dx, int dy,char map[ROWS][COL]);
bool is_parede(int key);
bool is_move_right(int key);
bool is_move_left(int key);
bool is_move_up(int key);
bool is_move_down(int key);
bool valid_move(STATE *st,int key,char map[ROWS][COL]);
void desenha_pontos(char map[ROWS][COL]);
/*void game_over();*/
void update(STATE *st,char map[ROWS][COL]);