#include "state.h"

void init_state(STATE *state) {
    state->score = 0;
    state->gameState = MENU;
}