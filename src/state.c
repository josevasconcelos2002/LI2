#include "state.h"
#include "player.h"

struct state {
	PLAYER *player;
	MONSTER monstros[100];
};


PLAYER *get_player(STATE *st){
	return st->player;
}