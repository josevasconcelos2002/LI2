#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
//#include "player.h"
//#include "state.h"
//#include "monsters.h"
//#include "testeGeraMapa.h"
//#include "menus.h"

#define WALL_PROB 0.465
#define ITERATIONS 10
#define ROWS 30//52
#define COLS 100//211


typedef struct{
	int playerX;
	int playerY;
	int playerHealth;
	int playerAttack;
} PLAYER;

typedef struct{
    int monsterX;
    int monsterY;
    int monsterHealth;
    int monsterAttack;
} MONSTER;

MONSTER monster;
PLAYER player;

typedef struct state {
	PLAYER *player;
	MONSTER monstros[10];
} STATE;

void init_map(char map[ROWS][COLS]) {
    // Inicializa o mapa com caminhos e paredes aleatórios
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (rand() < WALL_PROB * RAND_MAX) {
                map[i][j] = '#';
            } else {
                map[i][j] = ' ';
            }
        }
    }
}

void update_map(char map[ROWS][COLS]) {
    // Faz update ao mapa usando o algoritmo cellular automata, para o melhorar
    char new_map[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int num_walls = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (i+di >= 0 && i+di < ROWS && j+dj >= 0 && j+dj < COLS) {
                        if (map[i+di][j+dj] == '#') {
                            num_walls++;
                        }
                    }
                }
            }
            if (num_walls >= 5 || (num_walls == 1 && rand() < 0.2 * RAND_MAX)) {
                new_map[i][j] = '#';
            } else {
                new_map[i][j] = ' ';
            }
			if(map[i][j] == '.') new_map[i][j] = '.';
        }
    }
    // Copia o novo mapa para o original
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = new_map[i][j];
        }
    }
}

void remove_isolated_walls(char map[ROWS][COLS]) {
    // Remove paredes isoladas e pequenos blocos de paredes
    char new_map[ROWS][COLS];
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (map[i][j] == '#') {
                int num_walls = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (i+di >= 0 && i+di < ROWS && j+dj >= 0 && j+dj < COLS) {
                            if (map[i+di][j+dj] == '#') {
                                num_walls++;
                            }
                        }
                    }
                }
                if (num_walls >= 1 && num_walls <= 5) {
                    // Verifica se há mais paredes numa area de 3x3 à volta de uma parede. Se estiver isolada, transforma em caminho
                    int num_surrounding_walls = 0;
                    for (int di = -1; di <= 1; di++) {
                        for (int dj = -1; dj <= 1; dj++) {
                            if (i+di >= 0 && i+di < ROWS && j+dj >= 0 && j+dj < COLS) {
                                if (map[i+di][j+dj] == '#') {
                                    num_surrounding_walls++;
                                }
                            }
                        }
                    }
                    if (num_surrounding_walls <= 5) {
                        new_map[i][j] = ' ';
                    } else {
                        new_map[i][j] = '#';
                    }
                }
            } else {
                new_map[i][j] = ' ';
            }
        }
    }
    // Copia o novo mapa para o original
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            map[i][j] = new_map[i][j];
        }
    }
}

void roguelite(){
	clear();
	WINDOW *wnd = initscr();
	curs_set(0);
	attron(A_BOLD);
	attron(COLOR_PAIR(1));
	int x,y;
	getmaxyx(wnd,y,x);
	mvprintw(y/2,x/2,"Roguelite");
	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));
	sleep(2);
	delwin(wnd);
}


// Função para exibir o menu principal
int show_main_menu() {
    clear(); // Limpa a tela
    int x, y; // Variáveis para armazenar a posição atual do cursor
    int choice = 0; // Variável para armazenar a escolha do jogador
    char *options[] = {"Jogar", "Sair"}; // Opções do menu

    // Configurações iniciais
    curs_set(0); // Oculta o cursor
    attron(A_BOLD); // Define a fonte em negrito
    attron(COLOR_PAIR(1)); // Define a cor do texto
    mvprintw(5, 15, "Bem-vindo ao jogo!");
    attroff(COLOR_PAIR(1)); // Desativa a cor do texto
    attroff(A_BOLD); // Desativa a fonte em negrito
    mvprintw(7, 15, "Selecione uma opção:");

    // Imprime as opções do menu
    for (int i = 0; i < 2; i++) {
        y = 9 + i*2;
        x = 15;
        if (i == choice) {
            attron(A_REVERSE);
        }
        mvprintw(y, x, "%s", options[i]);
        attroff(A_REVERSE);
    }
    refresh();

    // Aguarda a seleção do jogador
    int c;
    while (1) {
        c = getch(); // Lê a entrada do jogador
        switch(c) {
            case KEY_UP:
                if (choice > 0) {
                    choice--;
                }
                break;
            case KEY_DOWN:
                if (choice < 1) {
                    choice++;
                }
                break;
            case '\n':
                return choice; // Retorna a escolha do jogador
        }

        // Atualiza o destaque da opção selecionada
        for (int i = 0; i < 2; i++) {
            y = 9 + i*2;
            x = 15;
            if (i == choice) {
                attron(A_REVERSE);
            }
            mvprintw(y, x, "%s", options[i]);
            attroff(A_REVERSE);
        }
        refresh();
    }
}

void show_pause_menu() {
    clear();
    int menu_choice = 0;
    int x, y;
    getmaxyx(stdscr, y, x);

    // Define as opções do menu
    char *menu_items[] = {
        "Continuar",
        "Recomecar",
        "Sair"
    };
    int num_items = sizeof(menu_items) / sizeof(menu_items[0]);

    // Desenha o menu na tela
    mvprintw(y/2-2, x/2-5, "Pause");
    for (int i = 0; i < num_items; i++) {
        if (i == menu_choice) {
            attron(A_REVERSE);
        }
        mvprintw(y/2+i, x/2-5, menu_items[i]);
        attroff(A_REVERSE);
    }
    refresh();

    // Processa as teclas pressionadas pelo jogador
    while (true) {
        int key = getch();
        if (key == KEY_UP) {
            menu_choice--;
            if (menu_choice < 0) {
                menu_choice = num_items-1;
            }
        } else if (key == KEY_DOWN) {
            menu_choice++;
            if (menu_choice >= num_items) {
                menu_choice = 0;
            }
        } else if (key == '\n') {
            // Executa a opção escolhida
            if (menu_choice == 0) {
                return;
            } else if (menu_choice == 1) {
                //restart_game();
                return;
            } else if (menu_choice == 2) {
                endwin();
                exit(0);
            }
        }
        // Atualiza o menu com a opção selecionada
        clear();
        mvprintw(y/2-2, x/2-5, "Pause");
        for (int i = 0; i < num_items; i++) {
            if (i == menu_choice) {
                attron(A_REVERSE);
            }
            mvprintw(y/2+i, x/2-5, menu_items[i]);
            attroff(A_REVERSE);
        }
        refresh();
    }
}

// esta função apenas está definida para um monstro, falta generalizar
/*
void monster_attack(STATE *st) {
    int dx = st->monster->monsterX - st->player->playerX;
    int dy = st->monster->monsterY - st->player->playerY;

	// Calcula a distância entre o monstro e o jogador
    int distance = abs(dx) + abs(dy);

	if (distance == 1){
		while (st->player->playerHealth > 0) {
			st->monster -> monsterHealth -= 15;
			st->player -> playerHealth -= 5;
		}
	}
}
*/
bool only_dots = false;

PLAYER *get_player(STATE *st){
	return st->player;
}

int get_playerX(STATE *state){
	int pX = get_player(state)->playerX;
    return pX;
}

int get_playerY(STATE *state){
	int pY = get_player(state)->playerY;
    return pY;
}

int get_playerHealth(STATE *state){
	int pH = get_player(state)->playerHealth;
    return pH;
}

int get_playerAtack(STATE *state){
	int pA = get_player(state)->playerAttack;
    return pA;
}

void set_playerX(STATE *state, int x){
    get_player(state)->playerX = x;
}

void set_playerY(STATE *state, int y){
    get_player(state)->playerY = y;
}

void set_playerHealth(STATE *state, int health){
    get_player(state)->playerHealth = health;
}

void set_playerAtack(STATE *state, int attack){
    get_player(state)->playerAttack = attack;
}

void inicializa_player(STATE *state){
    get_player(state)->playerX = 15;
    get_player(state)->playerY = 15;
    get_player(state)->playerHealth = 100;
    get_player(state)->playerAttack = 10;
}

MONSTER *get_monsters(STATE *st){
	return st->monstros;
}

/*
int get_monsterX(STATE *st){
    int mX = st->monstros;
    return mX;
}

int get_monsterY(STATE *st){
    int mY = st->monster->monsterY;
    return mY;
}

int get_monsterHealth(STATE *st){
    int mH = st->monster->monsterHealth;
    return mH;
}

int get_monsterAttack(STATE *st){
    int mA = st->monster->monsterAttack;
    return mA;
}

void set_monsterX(STATE *st, int x){
    st->monster->monsterX = x;
}

void set_monsterY(STATE *st, int y){
    st->monster->monsterY = y;
}

void set_monsterHealth(STATE *st, int health){
    st->monster->monsterHealth = health;
}

void set_monsterAttack(STATE *st, int attack){
    st->monster->monsterAttack = attack;
}
*/

void spawn_mobs(STATE *st) {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Gera 10 monstros com posições aleatórias no mapa
    for (int i = 0; i < 10; i++) {
        int x, y;
        do {
            // Gera uma posição aleatória
            x = rand() % COLS;
            y = rand() % ROWS;
        } while (mvinch(y, x) == '#'); // Verifica se a posição é uma parede
        
        // Inicializa o monstro com a posição gerada e atributos aleatórios
        get_monsters(st)[i].monsterX = x;
        get_monsters(st)[i].monsterY = y;
        get_monsters(st)[i].monsterHealth = rand() % 10 + 1;
        get_monsters(st)[i].monsterAttack = rand() % 5 + 1;
        
        // Define o par de cor 1 como vermelho
		init_pair(1, COLOR_RED, COLOR_BLACK);

		// Ativa a cor vermelha para imprimir o monstro
		attron(COLOR_PAIR(1));
		mvaddch(get_monsters(st)[i].monsterY, get_monsters(st)[i].monsterX, '!');
		attroff(COLOR_PAIR(1));

    }
}

void move_mobs(STATE *st, char map[ROWS][COLS]) {
    // Itera sobre a lista de monstros
    for (int i = 0; i < 10; i++) {
		if(&st->monstros[i] != NULL){
			int x, y;
			do {
				// Gera uma posição aleatória adjacente
				x = get_monsters(st)[i].monsterX + rand() % 3 - 1;
				y = get_monsters(st)[i].monsterY + rand() % 3 - 1;
			} while (map[y][x] == '#'); // Verifica se a posição é uma parede
			
			// Apaga o monstro da posição anterior
			if(mvinch(get_monsters(st)[i].monsterY, get_monsters(st)[i].monsterX) != '#')
				mvaddch(get_monsters(st)[i].monsterY, get_monsters(st)[i].monsterX, ' ');
			
			// Atualiza a posição do monstro
			get_monsters(st)[i].monsterX = x;
			get_monsters(st)[i].monsterY = y;
			
			// Define o par de cor 1 como vermelho
			init_pair(1, COLOR_RED, COLOR_BLACK);

			// Ativa a cor vermelha para imprimir o monstro
			attron(COLOR_PAIR(1));
			mvaddch(get_monsters(st)[i].monsterY, get_monsters(st)[i].monsterX, '!');
			attroff(COLOR_PAIR(1));
		}
    }
}



bool is_monster(char c){
	bool resultado = false;
	if(c == '!') resultado = true;
	return resultado;
}


void inicializa_monster(MONSTER monstros[],int N){
	for(int i = 0; i<N ; i++){
		monstros[i].monsterAttack = 5;
		monstros[i].monsterHealth = 50;
		monstros[i].monsterY = 15+ 3*i;
		monstros[i].monsterX = 25 + 5*i;
	}
}


void set_player(STATE *st){
	st->player = malloc(sizeof(PLAYER));
}

void inicializa_state(STATE *st){
	set_player(st);
	inicializa_player(st);
	inicializa_monster(st->monstros,10);
}

void do_movement_action(STATE *st, int dx, int dy,char map[ROWS][COLS]) {
	st->player->playerX += dx;
	st->player->playerY += dy;
	map[get_playerY(st)-dy][get_playerX(st)-dx] = ' ';
}

bool is_parede(int key){
	return (key == 35);
}

bool is_move_right(int key){
	return key == 100;
}

bool is_move_left(int key){
	return key == 97;
}

bool is_move_up(int key){
	return key == 119;
}

bool is_move_down(int key){
	return key == 115;
}

bool valid_move(STATE *st,int key,char map[ROWS][COLS]){
	bool r = true;
	if(!only_dots){
		if((is_move_right(key) && (is_parede((int)map[get_playerY(st)][get_playerX(st)+1]))) || is_monster(map[get_playerY(st)][get_playerX(st)+1])) r = false;
		if((is_move_left(key) && (is_parede((int)map[get_playerY(st)][get_playerX(st)-1]))) || is_monster(map[get_playerY(st)][get_playerX(st)-1])) r = false;
		if((is_move_up(key) && (is_parede((int)map[get_playerY(st)-1][get_playerX(st)]))) || is_monster(map[get_playerY(st)-1][get_playerX(st)])) r = false;
		if((is_move_down(key) && (is_parede((int)map[get_playerY(st)+1][get_playerX(st)]))) || is_monster(map[get_playerY(st)+1][get_playerX(st)])) r = false;
	}
	else{
		if(is_move_right(key) && (is_parede((int)map[get_playerY(st)][get_playerX(st)+1]))) r = false;
		if(is_move_left(key) && (is_parede((int)map[get_playerY(st)][get_playerX(st)-1]))) r = false;
		if(is_move_up(key) && (is_parede((int)map[get_playerY(st)-1][get_playerX(st)]))) r = false;
		if(is_move_down(key) && (is_parede((int)map[get_playerY(st)+1][get_playerX(st)]))) r = false;
	}
	return r;
}


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
				if(map[i][j] == '#'){
					mvaddch(i,j,map[i][j]);
				}
			}
        }
    }
}

/*
void game_over() {
    // Configura a janela
    int height = 3; // altura da janela
    int width = 10; // largura da janela
    int starty = (LINES - height) / 2; // posição y da janela
    int startx = (COLS - width) / 2; // posição x da janela
    WINDOW *win = newwin(height, width, starty, startx); // cria a janela
    box(win, 0, 0); // adiciona uma borda à janela
    refresh();
    wrefresh(win);

    // Configura as cores
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    wbkgd(win, COLOR_PAIR(1));

    // Imprime a mensagem na janela
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, 1, 3, "GAME OVER");
    wattroff(win, COLOR_PAIR(3));

    // Espera 3 segundos antes de fechar a janela
    wrefresh(win);
    sleep(3);

    // Libera a janela
    delwin(win);
    endwin();
}
*/

void draw_light(STATE *st, char key, char map[ROWS][COLS]){
	if(is_move_left((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)-3)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)-3))) map[get_playerY(st)][get_playerX(st)-3] = '.';
		if(!is_parede(mvinch(get_playerY(st)-1, get_playerX(st)-3)) && !is_monster(mvinch(get_playerY(st)-1, get_playerX(st)-3))) map[get_playerY(st)-1][get_playerX(st)-3] = '.';
		if(!is_parede(mvinch(get_playerY(st)+1, get_playerX(st)-3)) && !is_monster(mvinch(get_playerY(st)+1, get_playerX(st)-3))) map[get_playerY(st)+1][get_playerX(st)-3] = '.';
		if(!is_parede(mvinch(get_playerY(st)-2, get_playerX(st)-3)) && !is_monster(mvinch(get_playerY(st)-2, get_playerX(st)-3))) map[get_playerY(st)-2][get_playerX(st)-3] = '.';
		if(!is_parede(mvinch(get_playerY(st)+2, get_playerX(st)-3)) && !is_monster(mvinch(get_playerY(st)+2, get_playerX(st)-3))) map[get_playerY(st)+2][get_playerX(st)-3] = '.';
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)-2)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)-2))) map[get_playerY(st)][get_playerX(st)-2] = '.';
		if(!is_parede(mvinch(get_playerY(st)-1, get_playerX(st)-2)) && !is_monster(mvinch(get_playerY(st)-1, get_playerX(st)-2))) map[get_playerY(st)-1][get_playerX(st)-2] = '.';
		if(!is_parede(mvinch(get_playerY(st)+1, get_playerX(st)-2)) && !is_monster(mvinch(get_playerY(st)+1, get_playerX(st)-2))) map[get_playerY(st)+1][get_playerX(st)-2] = '.';
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)-1)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)-1))) map[get_playerY(st)][get_playerX(st)-1] = '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_up((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(get_playerY(st)-3, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)-3, get_playerX(st)))) map[get_playerY(st)-3][get_playerX(st)] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-3, get_playerX(st)-1)) && !is_monster(mvinch(get_playerY(st)-3, get_playerX(st)-1))) map[get_playerY(st)-3][get_playerX(st)-1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-3, get_playerX(st)+1)) && !is_monster(mvinch(get_playerY(st)-3, get_playerX(st)+1))) map[get_playerY(st)-3][get_playerX(st)+1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-3, get_playerX(st)-2)) && !is_monster(mvinch(get_playerY(st)-3, get_playerX(st)-2))) map[get_playerY(st)-3][get_playerX(st)-2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-3, get_playerX(st)+2)) && !is_monster(mvinch(get_playerY(st)-3, get_playerX(st)+2))) map[get_playerY(st)-3][get_playerX(st)+2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-2, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)-2, get_playerX(st)))) map[get_playerY(st)-2][get_playerX(st)] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-2, get_playerX(st)-1)) && !is_monster(mvinch(get_playerY(st)-2, get_playerX(st)-1))) map[get_playerY(st)-2][get_playerX(st)-1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-2, get_playerX(st)+1)) && !is_monster(mvinch(get_playerY(st)-2, get_playerX(st)+1))) map[get_playerY(st)-2][get_playerX(st)+1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-1, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)-1, get_playerX(st)))) map[get_playerY(st)-1][get_playerX(st)] =  '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_right((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)+3)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)+3))) map[get_playerY(st)][get_playerX(st)+3] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-1, get_playerX(st)+3)) && !is_monster(mvinch(get_playerY(st)-1, get_playerX(st)+3))) map[get_playerY(st)-1][get_playerX(st)+3] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+1, get_playerX(st)+3)) && !is_monster(mvinch(get_playerY(st)+1, get_playerX(st)+3))) map[get_playerY(st)+1][get_playerX(st)+3] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-2, get_playerX(st)+3)) && !is_monster(mvinch(get_playerY(st)-2, get_playerX(st)+3))) map[get_playerY(st)-2][get_playerX(st)+3] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+2, get_playerX(st)+3)) && !is_monster(mvinch(get_playerY(st)+2, get_playerX(st)+3))) map[get_playerY(st)+2][get_playerX(st)+3] =  '.';
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)+2)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)+2))) map[get_playerY(st)][get_playerX(st)+2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)-1, get_playerX(st)+2)) && !is_monster(mvinch(get_playerY(st)-1, get_playerX(st)+2))) map[get_playerY(st)-1][get_playerX(st)+2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+1, get_playerX(st)+2)) && !is_monster(mvinch(get_playerY(st)+1, get_playerX(st)+2))) map[get_playerY(st)+1][get_playerX(st)+2] =  '.';
		if(!is_parede(mvinch(get_playerY(st), get_playerX(st)+1)) && !is_monster(mvinch(get_playerY(st), get_playerX(st)+1))) map[get_playerY(st)][get_playerX(st)+1] =  '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	if(is_move_down((int)key)){
			attron(COLOR_PAIR(COLOR_YELLOW));
		if(!is_parede(mvinch(get_playerY(st)+3, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)+3, get_playerX(st)))) map[get_playerY(st)+3][get_playerX(st)] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+3, get_playerX(st)-1)) && !is_monster(mvinch(get_playerY(st)+3, get_playerX(st)-1))) map[get_playerY(st)+3][get_playerX(st)-1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+3, get_playerX(st)+1)) && !is_monster(mvinch(get_playerY(st)+3, get_playerX(st)+1))) map[get_playerY(st)+3][get_playerX(st)+1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+3, get_playerX(st)-2)) && !is_monster(mvinch(get_playerY(st)+3, get_playerX(st)-2))) map[get_playerY(st)+3][get_playerX(st)-2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+3, get_playerX(st)+2)) && !is_monster(mvinch(get_playerY(st)+3, get_playerX(st)+2))) map[get_playerY(st)+3][get_playerX(st)+2] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+2, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)+2, get_playerX(st)))) map[get_playerY(st)+2][get_playerX(st)] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+2, get_playerX(st)-1)) && !is_monster(mvinch(get_playerY(st)+2, get_playerX(st)-1))) map[get_playerY(st)+2][get_playerX(st)-1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+2, get_playerX(st)+1)) && !is_monster(mvinch(get_playerY(st)+2, get_playerX(st)+1))) map[get_playerY(st)+2][get_playerX(st)+1] =  '.';
		if(!is_parede(mvinch(get_playerY(st)+1, get_playerX(st))) && !is_monster(mvinch(get_playerY(st)+1, get_playerX(st)))) map[get_playerY(st)+1][get_playerX(st)] =  '.';
			attroff(COLOR_PAIR(COLOR_YELLOW));
	}
	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == '.') mvaddch(i,j,'.');
		}
	}
}

void remove_light(STATE *st, char key, char map[ROWS][COLS]){
	if(is_move_left((int)key)){
		if(mvinch(get_playerY(st), get_playerX(st)-3) == '.') map[get_playerY(st)][get_playerX(st)-3] =  ' ';
		if(mvinch(get_playerY(st)-1, get_playerX(st)-3) == '.') map[get_playerY(st)-1][get_playerX(st)-3] =  ' ';
		if(mvinch(get_playerY(st)+1, get_playerX(st)-3) == '.') map[get_playerY(st)+1][get_playerX(st)-3] =  ' ';
		if(mvinch(get_playerY(st)-2, get_playerX(st)-3) == '.') map[get_playerY(st)-2][get_playerX(st)-3] =  ' ';
		if(mvinch(get_playerY(st)+2, get_playerX(st)-3) == '.') map[get_playerY(st)+2][get_playerX(st)-3] =  ' ';
		if(mvinch(get_playerY(st), get_playerX(st)-2) == '.') map[get_playerY(st)][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st)-1, get_playerX(st)-2) == '.') map[get_playerY(st)-1][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st)+1, get_playerX(st)-2) == '.') map[get_playerY(st)+1][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st), get_playerX(st)-1) == '.') map[get_playerY(st)][get_playerX(st)-1] =  ' ';
	}
	if(is_move_up((int)key)){
		if(mvinch(get_playerY(st)-3, get_playerX(st)) == '.') map[get_playerY(st)-3][get_playerX(st)] =  ' ';
		if(mvinch(get_playerY(st)-3, get_playerX(st)-1) == '.') map[get_playerY(st)-3][get_playerX(st)-1] =  ' ';
		if(mvinch(get_playerY(st)-3, get_playerX(st)+1) == '.') map[get_playerY(st)-3][get_playerX(st)+1] =  ' ';
		if(mvinch(get_playerY(st)-3, get_playerX(st)-2) == '.') map[get_playerY(st)-3][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st)-3, get_playerX(st)+2) == '.') map[get_playerY(st)-3][get_playerX(st)+2] =  ' ';
		if(mvinch(get_playerY(st)-2, get_playerX(st)) == '.') map[get_playerY(st)-2][get_playerX(st)] =  ' ';
		if(mvinch(get_playerY(st)-2, get_playerX(st)-1) == '.') map[get_playerY(st)-2][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st)-2, get_playerX(st)+1) == '.') map[get_playerY(st)-2][get_playerX(st)+1] =  ' ';
		if(mvinch(get_playerY(st)-1, get_playerX(st)) == '.') map[get_playerY(st)-1][get_playerX(st)] =  ' ';
	}
	if(is_move_right((int)key)){
		if(mvinch(get_playerY(st), get_playerX(st)+3) == '.') map[get_playerY(st)][get_playerX(st)+3] =  ' ';
		if(mvinch(get_playerY(st)-1, get_playerX(st)+3) == '.') map[get_playerY(st)-1][get_playerX(st)+3] =  ' ';
		if(mvinch(get_playerY(st)+1, get_playerX(st)+3) == '.') map[get_playerY(st)+1][get_playerX(st)+3] =  ' ';
		if(mvinch(get_playerY(st)-2, get_playerX(st)+3) == '.') map[get_playerY(st)-2][get_playerX(st)+3] =  ' ';
		if(mvinch(get_playerY(st)+2, get_playerX(st)+3) == '.') map[get_playerY(st)+2][get_playerX(st)+3] =  ' ';
		if(mvinch(get_playerY(st), get_playerX(st)+2) == '.') map[get_playerY(st)][get_playerX(st)+2] =  ' ';
		if(mvinch(get_playerY(st)-1, get_playerX(st)+2) == '.') map[get_playerY(st)-1][get_playerX(st)+2] =  ' ';
		if(mvinch(get_playerY(st)+1, get_playerX(st)+2) == '.') map[get_playerY(st)+1][get_playerX(st)+2] =  ' ';
		if(mvinch(get_playerY(st), get_playerX(st)+1) == '.') map[get_playerY(st)][get_playerX(st)+1] =  ' ';
	}
	if(is_move_down((int)key)){
		if(mvinch(get_playerY(st)+3, get_playerX(st)) == '.') map[get_playerY(st)+3][get_playerX(st)] =  ' ';
		if(mvinch(get_playerY(st)+3, get_playerX(st)-1) == '.') map[get_playerY(st)+3][get_playerX(st)-1] =  ' ';
		if(mvinch(get_playerY(st)+3, get_playerX(st)+1) == '.') map[get_playerY(st)+3][get_playerX(st)+1] =  ' ';
		if(mvinch(get_playerY(st)+3, get_playerX(st)-2) == '.') map[get_playerY(st)+3][get_playerX(st)-2] =  ' ';
		if(mvinch(get_playerY(st)+3, get_playerX(st)+2) == '.') map[get_playerY(st)+3][get_playerX(st)+2] =  ' ';
		if(mvinch(get_playerY(st)+2, get_playerX(st)) == '.') map[get_playerY(st)+2][get_playerX(st)] =  ' ';
		if(mvinch(get_playerY(st)+2, get_playerX(st)-1) == '.') map[get_playerY(st)+2][get_playerX(st)-1] =  ' ';
		if(mvinch(get_playerY(st)+2, get_playerX(st)+1) == '.') map[get_playerY(st)+2][get_playerX(st)+1] =  ' ';
		if(mvinch(get_playerY(st)+1, get_playerX(st)) == '.') map[get_playerY(st)+1][get_playerX(st)] =  ' ';
	}
	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == ' ') mvaddch(i,j,' ');
		}
	}
}

void draw_player(STATE *st,char map[ROWS][COLS]){
	attron(COLOR_PAIR(COLOR_WHITE));
	map[get_playerY(st)][get_playerX(st)] = '@';
    for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == '@') mvaddch(i,j,'@');
		}
	}
    attroff(COLOR_PAIR(COLOR_WHITE));
	refresh();
}

double distancia(PLAYER *player, MONSTER *monster){
	double resultado = 0.0;
	int dx = abs(player->playerX - monster->monsterX);
	int dy = abs(player->playerY - monster->monsterY);
	resultado =  sqrt(dx * dx + dy * dy);
	return resultado;
}


MONSTER *get_monster(STATE *st){
	MONSTER *resultado = NULL;
	for(int i = 0; i<10 ; i++){
		if(distancia(st->player,&st->monstros[i]) == 1.0){
			resultado = &st->monstros[i];
		}
	}
	return resultado;
}

void remove_monster(MONSTER *monster,char map[ROWS][COLS]){
	int x = monster->monsterX;
	int y = monster->monsterY;
	//map[y][x] = ' ';
	//mvaddch(y,x,' ');
	//monster = NULL;
}


void kill(STATE *st,char map[ROWS][COLS]){
	
	MONSTER *monstro = get_monster(st);
	if(monstro != NULL){
		monstro->monsterHealth -= st->player->playerAttack;
		st->player->playerHealth -= monstro->monsterAttack;
	}

	if(monstro->monsterHealth <= 0) remove_monster(monstro,map);
	if(st->player->playerHealth <= 0){
		endwin();
		//game_over();
	}

}


void update(STATE *st,char map[ROWS][COLS]) {
	int key = getch();
	mvaddch(st->player->playerY,st->player->playerX, ' ');
	remove_light(st,key,map);
	switch(key) {
		case 'w': if(valid_move(st,(int)'w',map)) do_movement_action(st, +0, -1,map); break;
		case 's': if(valid_move(st,(int)'s',map)) do_movement_action(st, +0, +1,map); break;
		case 'a': if(valid_move(st,(int)'a',map)) do_movement_action(st, -1, +0,map); break;
		case 'd': if(valid_move(st,(int)'d',map)) do_movement_action(st, +1, +0,map); break;
		case 'k': kill(st,map); break;
		case 'v': only_dots =  !only_dots;  desenha_pontos(map); break; //altera o modo de visao
		case ' ': show_pause_menu(); break; // espaco
		case 'q': endwin(); exit(0); break;
	}

	//spawn_mob(st);
	draw_player(st,map);
	draw_light(st,key,map);
	move_mobs(st,map);
	refresh();
}






/*
void kill(STATE *st){
	if(is_monster(mvinch(st->player->playerY,st->player->playerX+1))){
		st->monster->monsterHealth -= st->player->playerAtack; // como saber qual monster se está a referir?
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(is_monster(mvinch(st->player->playerY,st->player->playerX-1))){
		st->monster->monsterHealth -= st->player->playerAtack;
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(is_monster(mvinch(st->player->playerY+1,st->player->playerX))){
		st->monster->monsterHealth -= st->player->playerAtack;
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(is_monster(mvinch(st->player->playerY-1,st->player->playerX))){
		st->monster->monsterHealth -= st->player->playerAtack;
		st->player->playerHealth -= st->monster->monsterAtack;
	}
	if(st->monster->monsterHealth <= 0) remove_monster(st);
		if(st->player->playerHealth <= 0){
		endwin();
		game_over();
	}

}
*/




//MONSTER monsters[10];



/*
void remove_monster(STATE *st){
	int x = st->monster->monsterX;
	int y = st->monster->monsterY;
	mvaddch(y,x, ' ' | A_BOLD);
	st->monster = NULL;
}

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
*/



int main(){
	srandom(time(NULL));
	start_color();

	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);

	init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(1,COLOR_RED,COLOR_BLACK);
	STATE *st = malloc(sizeof(STATE));
	st->player = malloc(sizeof(PLAYER));
	//st->monstros = malloc(sizeof(MONSTER)*10);
	inicializa_state(st);
	WINDOW *wnd = initscr();
	int ncols, nrows;
	getmaxyx(wnd,nrows,ncols);
	//roguelite(wnd);
	show_main_menu();
	char map[ROWS][COLS];
	do{
		memset(map, ' ', ROWS * COLS * sizeof(char));
		init_map(map);
		// Limpa o mapa
		// Faz update no mapa
		for (int i = 0; i < ITERATIONS; i++) {
			update_map(map);
		}
		
		// Remove paredes isoladas e pequenos blocos de paredes
		remove_isolated_walls(map);

		// Adiciona paredes nas bordas do mapa
		for (int i = 0; i < ROWS; i++) {
			map[i][0] = '#';
			map[i][COLS-1] = '#';
		}
		for (int j = 0; j < COLS; j++) {
			map[0][j] = '#';
			map[ROWS-1][j] = '#';
		}
		
		st->player->playerY = random() % (COLS - 2) + 1;
		st->player->playerX = random() % (COLS - 2) + 1;

		WINDOW* window = newwin(ROWS, COLS, 1, 1);
		box(window, '#', '#');
		refresh();

	}
	while(is_parede((int)map[st->player->playerY][st->player->playerX]) || st->player->playerY > ROWS-1 || st->player->playerX > COLS-1);
	clear();
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			mvaddch(i, j, map[i][j]);
		}
	}
	spawn_mobs(st);
	while(1) {
		move(nrows - 1, 0);
		attron(COLOR_PAIR(COLOR_BLUE));
		if(st->player != NULL){
			printw("Player state: \n");
			printw("	Health: %d\n",get_playerHealth(st));
			printw("	Atack: %d \n",get_playerAtack(st));
		}
		printw("(%d, %d) %d %d\n", get_playerX(st), get_playerY(st), ncols, nrows);
		attroff(COLOR_PAIR(COLOR_BLUE));
		refresh();
		move(get_playerY(st), get_playerX(st));
		update(st,map);
		noecho();
	}
	free(st->player);
	free(st);
	return 0;
}