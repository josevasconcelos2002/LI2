#include "player.h"
#include "state.h"

struct player{
	int playerX;
	int playerY;
	int playerHealth;
	int playerAtack;
};


int get_playerX(PLAYER *player){
    return player->playerX;
}

int get_playerY(PLAYER *player){
    return player->playerY;
}

int get_playerHealth(PLAYER *player){
    return player->playerHealth;
}

int get_playerAtack(PLAYER *player){
    return player->playerAtack;
}

void set_playerX(PLAYER *player, int x){
    player->playerX = x;
}

void set_playerY(PLAYER *player, int y){
    player->playerY = y;
}

void set_playerHealth(PLAYER *player, int health){
    player->playerHealth = health;
}

void set_playerAtack(PLAYER *player, int atack){
    player->playerAtack = atack;
}

void inicializa_player(PLAYER *player){
    set_playerX(player,20);
    set_playerY(player,20);
    set_playerHealth(player,100);
    set_playerAtack(player,10);
}