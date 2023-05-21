#ifndef STATE_H
#define STATE_H

typedef enum {
    RUNNING,
    WON,
    LOST,
    MENU
} GAMESTATE;

typedef struct{
    double score;
    GAMESTATE gameState;
} STATE;

void init_state(STATE *state);

#endif