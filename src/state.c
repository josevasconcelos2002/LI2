#include "state.h"
#include "player.h"
#include "monsters.h"


struct state {
	PLAYER *player;
	MONSTER *monstros;
};

void inicializa_state(STATE *st){
	inicializa_player(get_player(st));
	//inicializa_monster(get_monster(st));
}

struct player *get_player(STATE *st){
	return (struct player *)st->player;
}