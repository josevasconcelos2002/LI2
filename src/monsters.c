#include "monsters.h"
#include "state.h"
#include <stdbool.h>
#include <ncurses.h>
#include "testeGeraMapa.h"

typedef struct {
    int x;
    int y;
    int health;
    int attack;
} Monster;

Monster monsters[10];

void spawn_mobs() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Gera 10 monstros com posições aleatórias no mapa
    for (int i = 0; i < 10; i++) {
        int x, y;
        do {
            // Gera uma posição aleatória
            x = rand() % COL;
            y = rand() % ROWS;
        } while (mvinch(y, x) == '#'); // Verifica se a posição é uma parede
        
        // Inicializa o monstro com a posição gerada e atributos aleatórios
        monsters[i].x = x;
        monsters[i].y = y;
        monsters[i].health = rand() % 10 + 1;
        monsters[i].attack = rand() % 5 + 1;
        
        // Define o par de cor 1 como vermelho
		init_pair(1, COLOR_RED, COLOR_BLACK);

		// Ativa a cor vermelha para imprimir o monstro
		attron(COLOR_PAIR(1));
		mvaddch(monsters[i].monsterY, monster[i].monsterX, '!');
		attroff(COLOR_PAIR(1));

    }
}

void move_mobs() {
    // Itera sobre a lista de monstros
    for (int i = 0; i < 10; i++) {
        int x, y;
        do {
            // Gera uma posição aleatória adjacente
            x = monsters[i].x + rand() % 3 - 1;
            y = monsters[i].y + rand() % 3 - 1;
        } while (mvinch(y, x) == '#'); // Verifica se a posição é uma parede
        
        // Apaga o monstro da posição anterior
        mvaddch(monsters[i].y, monsters[i].x, ' ');
        
        // Atualiza a posição do monstro
        monsters[i].x = x;
        monsters[i].y = y;
        
        // Define o par de cor 1 como vermelho
		init_pair(1, COLOR_RED, COLOR_BLACK);

		// Ativa a cor vermelha para imprimir o monstro
		attron(COLOR_PAIR(1));
		mvaddch(monsters[i].monsterY, monster[i].monsterX, '!');
		attroff(COLOR_PAIR(1));
    }
}

/*void set_monsterX(MONSTER *monster, int x){
    monster->monsterX = x;
}

void set_monsterY(MONSTER *monster, int y){
    monster->monsterY = y;
}

void set_monsterHealth(MONSTER *monster, int health){
    monster->monsterHealth = health;
}

void set_monsterAtack(MONSTER *monster, int atack){
    monster->monsterAtack = atack;
}

bool is_monster(char c){
	bool resultado = false;
	if(c == '!') resultado = true;
	return resultado;
}

void inicializa_monster(MONSTER monstros[],int N){
	for(int i = 0; i<N ; i++){
		monstros[i].monsterAtack = 5;
		monstros[i].monsterHealth = 50;
		monstros[i].monsterY = 15+ 3*i;
		monstros[i].monsterX = 25 + 5*i;
	}
}


void remove_monster(STATE *st){
	int x = st->monster->monsterX;
	int y = st->monster->monsterY;
	mvaddch(y,x, ' ' | A_BOLD);
	st->monster = NULL;
}
*/

void draw_monster(STATE *st, char map[ROWS][COL]){
	attron(COLOR_PAIR(1));
	for(int i = 0; i<10 ; i++){
		if(!is_parede(map[st->monstros[i].monsterY][st->monstros[i].monsterX])){
			map[st->monstros[i].monsterY][st->monstros[i].monsterX] = '!';
			mvaddch(st->monstros[i].monsterY, st->monstros[i].monsterX, '!' | A_BOLD);
		}
	}
	attroff(COLOR_PAIR(1));
	refresh();
}