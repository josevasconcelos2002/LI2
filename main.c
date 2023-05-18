#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <alsa/asoundlib.h>
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
	bool is_visible;
    bool is_dead;
} MONSTER;

typedef struct state {
	PLAYER *player;
	MONSTER monstros[10];
} STATE;

void generate_map(char map[ROWS][COLS]) {
    // Gera o mapa com caminhos e paredes aleatórios
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

void improve_map(char map[ROWS][COLS]) {
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

void init_map(char map[ROWS][COLS]) {

    memset(map, ' ', ROWS * COLS * sizeof(char));
	generate_map(map);
	// Limpa o mapa
	// Faz update no mapa
	for (int i = 0; i < ITERATIONS; i++) {
		improve_map(map);
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
        mvprintw(y/2+i, x/2-5, "%s", menu_items[i]);
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
            mvprintw(y/2+i, x/2-5, "%s", menu_items[i]);
            attroff(A_REVERSE);
        }
        refresh();
    }
}


void playSound(const char* filename) {
    // abrir dispositivo de áudio
    snd_pcm_t *handle;
    snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);

    // parâmetros do formato de áudio desejados
    snd_pcm_set_params(handle,
                       SND_PCM_FORMAT_S16_LE,    // Formato do áudio
                       SND_PCM_ACCESS_RW_INTERLEAVED,
                       1,                        // Número de canais
                       44100,                    // Taxa de amostragem
                       1,                        // Permitir resampling
                       50000);                   // Latência desejada em microssegundos

    // Carregar o arquivo de áudio
    FILE *file = fopen(filename, "rb");
    fseek(file, 0, SEEK_END);
    //long fileSize = ftell(file);
    rewind(file);

    // Calcular o número de amostras correspondentes a 1 segundo
    int sampleRate = 44100;  // Taxa de amostragem em Hz
    int numChannels = 1;     // Número de canais
    int bytesPerSample = 2;  // Tamanho de cada amostra em bytes (16 bits = 2 bytes)
    int samplesPerSecond = sampleRate * numChannels;
    int bytesPerSecond = samplesPerSecond * bytesPerSample;
    int desiredSeconds = 1;  // Duração desejada em segundos
    int desiredBytes = desiredSeconds * bytesPerSecond;

    // Alocar o buffer para 1 segundo de áudio
    char *buffer = malloc(desiredBytes);

    // Ler apenas 1 segundo do arquivo de áudio
    fread(buffer, sizeof(char), desiredBytes, file);
    fclose(file);

    // Reproduzir o áudio
    snd_pcm_writei(handle, buffer, desiredBytes / 2);  // Dividir por 2, pois o tamanho do buffer é em bytes

    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);
}

/*
// esta função apenas está definida para um monstro, falta generalizar
void monster_attack(STATE *st, char map[ROWS][COLS]) {
    if (distancia) {  // Jogador ataca monstros em uma distância de 1 bloco
        monsters[i].monsterHealth -= player->playerAttack;
        if (monsters[i].monsterHealth <= 0) {
            // Monstro morto, remove do mapa
			remove_monster(&monsters[i], map);

                int j;
                for (j = i; j < 9; j++) {
                    monsters[j] = monsters[j + 1];
                }
            } else {
                // Monstro atacou o jogador
                playSound("monster_attack.wav");  // Reproduz o som de ataque do monstro
                player->playerHealth -= monsters[i].monsterAttack;

                if (player->playerHealth <= 0) {
                    // Jogador morreu, fim do jogo
                    // Implemente aqui o código para encerrar o jogo
                }
            }
        }
    }
}
*/
bool only_dots = false;

void inicializa_player(STATE *state){
    state->player->playerX = 15;
    state->player->playerY = 15;
    state->player->playerHealth = 100;
    state->player->playerAttack = 10;
}

double distancia(PLAYER *player, MONSTER *monster){
	double resultado = 0.0;
	int dx = abs(player->playerX - monster->monsterX);
	int dy = abs(player->playerY - monster->monsterY);
	resultado =  sqrt(dx * dx + dy * dy);
	return resultado;
}

void spawn_mobs(STATE *st, char map[ROWS][COLS]) {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Gera 10 monstros com posições aleatórias no mapa
    for (int i = 0; i < 10; i++) {
        int x, y;
        do {
            // Gera uma posição aleatória
            x = rand() % COLS;
            y = rand() % ROWS;
        } while (map[y][x] == '#' || map[y][x] == '@'); // Verifica se a posição é uma parede
        
        // Inicializa o monstro com a posição gerada e atributos aleatórios
        st->monstros[i].monsterX = x;
        st->monstros[i].monsterY = y;
        st->monstros[i].monsterHealth = rand() % 10 + 1;
        st->monstros[i].monsterAttack = rand() % 5 + 1;
		st->monstros[i].is_visible = false;
        st->monstros[i].is_dead = false;
        
		// Ativa a cor vermelha para imprimir o monstro
        start_color();
        init_pair(6, COLOR_RED, COLOR_BLACK);
		attron(COLOR_PAIR(6));
		map[st->monstros[i].monsterY][st->monstros[i].monsterX] = '!';
		mvaddch(st->monstros[i].monsterY, st->monstros[i].monsterX, '!');
		attroff(COLOR_PAIR(6));

    }
}

void move_mobs(STATE* st, char map[ROWS][COLS]) {
    for (int i = 0; i < 10; i++) {
        if (st->monstros[i].is_dead == false) {
            int playerX = st->player->playerX;
            int playerY = st->player->playerY;
            int closestX = st->monstros[i].monsterX;
            int closestY = st->monstros[i].monsterY;
            int minDistance = 20;

            // Skip the iteration if the mob is already at the player's position
            if (playerX == closestX && playerY == closestY) {
                continue;
            }

            if (abs(playerX - closestX) + abs(playerY - closestY) > minDistance) {
                int x, y;
                do {
                    int direction = rand() % 4;
                    x = st->monstros[i].monsterX;
                    y = st->monstros[i].monsterY;

                    // Move horizontally or vertically
                    if (direction == 0) {
                        x--;
                    } else if (direction == 1) {
                        x++;
                    } else if (direction == 2) {
                        y--;
                    } else if (direction == 3) {
                        y++;
                    }
                } while (map[y][x] == '#' || map[y][x] == '@');

                closestX = x;
                closestY = y;
            } else {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        // Skip diagonal directions
                        if (dx != 0 && dy != 0) {
                            continue;
                        }

                        int newX = st->monstros[i].monsterX + dx;
                        int newY = st->monstros[i].monsterY + dy;
                        int distance = abs(playerX - newX) + abs(playerY - newY);

                        if (newX >= 0 && newX < COLS && newY >= 0 && newY < ROWS &&
                            map[newY][newX] != '#' && map[newY][newX] != '@' && distance < minDistance) {
                            closestX = newX;
                            closestY = newY;
                            minDistance = distance;
                        }
                    }
                }
            }

            int prevX = st->monstros[i].monsterX;
            int prevY = st->monstros[i].monsterY;
            st->monstros[i].monsterX = closestX;
            st->monstros[i].monsterY = closestY;

            if (map[prevY][prevX] != '#' && map[prevY][prevX] != '@') {
                mvaddch(prevY, prevX, ' ');
                map[prevY][prevX] = ' ';
            }
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            map[st->monstros[i].monsterY][st->monstros[i].monsterX] = '!';
            mvaddch(st->monstros[i].monsterY, st->monstros[i].monsterX, '!');
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

void inicializa_state(STATE *st){
	inicializa_player(st);
	//inicializa_monster(st->monstros,10);
}

void do_movement_action(STATE *st, int dx, int dy,char map[ROWS][COLS]) {
	st->player->playerX += dx;
	st->player->playerY += dy;
	map[st->player->playerY-dy][st->player->playerX-dx] = ' ';
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
		if((is_move_right(key) && (is_parede((int)map[st->player->playerY][st->player->playerX+1]))) || is_monster(map[st->player->playerY][st->player->playerX+1])) r = false;
		if((is_move_left(key) && (is_parede((int)map[st->player->playerY][st->player->playerX-1]))) || is_monster(map[st->player->playerY][st->player->playerX-1])) r = false;
		if((is_move_up(key) && (is_parede((int)map[st->player->playerY-1][st->player->playerX]))) || is_monster(map[st->player->playerY-1][st->player->playerX])) r = false;
		if((is_move_down(key) && (is_parede((int)map[st->player->playerY+1][st->player->playerX]))) || is_monster(map[st->player->playerY+1][st->player->playerX])) r = false;
	}
	else{
		if(is_move_right(key) && (is_parede((int)map[st->player->playerY][st->player->playerX+1]))) r = false;
		if(is_move_left(key) && (is_parede((int)map[st->player->playerY][st->player->playerX-1]))) r = false;
		if(is_move_up(key) && (is_parede((int)map[st->player->playerY-1][st->player->playerX]))) r = false;
		if(is_move_down(key) && (is_parede((int)map[st->player->playerY+1][st->player->playerX]))) r = false;
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
				mvaddch(i,j,map[i][j]);
			}
        }
    }
}


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


void you_won() {
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
    mvwprintw(win, 1, 3, "WIN!");
    wattroff(win, COLOR_PAIR(3));

    // Espera 3 segundos antes de fechar a janela
    wrefresh(win);
    sleep(3);

    // Libera a janela
    delwin(win);
    endwin();
}

bool dentro_mapa(int y, int x){
	bool resultado = true;
	if(y<1 || y>ROWS-1 || x<1 || x>COLS-1) resultado = false;
	return resultado;
}

void draw_light(STATE *st, char key, char map[ROWS][COLS]){
	if(is_move_left((int)key) && valid_move(st,(int)key,map)){
		if(dentro_mapa(st->player->playerY,st->player->playerX-3) && !is_parede(map[st->player->playerY][st->player->playerX-3]) && !is_monster(map[st->player->playerY][st->player->playerX-3])) map[st->player->playerY][st->player->playerX-3] = '.';
		if(dentro_mapa(st->player->playerY-1,st->player->playerX-3) &&!is_parede(map[st->player->playerY-1][st->player->playerX-3]) && !is_monster(map[st->player->playerY-1][st->player->playerX-3])) map[st->player->playerY-1][st->player->playerX-3] = '.';
		if(dentro_mapa(st->player->playerY+1,st->player->playerX-3) &&!is_parede(map[st->player->playerY+1][st->player->playerX-3]) && !is_monster(map[st->player->playerY+1][st->player->playerX-3])) map[st->player->playerY+1][st->player->playerX-3] = '.';
		if(dentro_mapa(st->player->playerY-2,st->player->playerX-3) &&!is_parede(map[st->player->playerY-2][st->player->playerX-3]) && !is_monster(map[st->player->playerY-2][st->player->playerX-3])) map[st->player->playerY-2][st->player->playerX-3] = '.';
		if(dentro_mapa(st->player->playerY+2,st->player->playerX-3) &&!is_parede(map[st->player->playerY+2][st->player->playerX-3]) && !is_monster(map[st->player->playerY+2][st->player->playerX-3])) map[st->player->playerY+2][st->player->playerX-3] = '.';
		if(dentro_mapa(st->player->playerY,st->player->playerX-2) &&!is_parede(map[st->player->playerY][st->player->playerX-2]) && !is_monster(map[st->player->playerY][st->player->playerX-2])) map[st->player->playerY][st->player->playerX-2] = '.';
		if(dentro_mapa(st->player->playerY-1,st->player->playerX-2) &&!is_parede(map[st->player->playerY-1][st->player->playerX-2]) && !is_monster(map[st->player->playerY-1][st->player->playerX-2])) map[st->player->playerY-1][st->player->playerX-2] = '.';
		if(dentro_mapa(st->player->playerY+1,st->player->playerX-2) &&!is_parede(map[st->player->playerY+1][st->player->playerX-2]) && !is_monster(map[st->player->playerY+1][st->player->playerX-2])) map[st->player->playerY+1][st->player->playerX-2] = '.';
		if(dentro_mapa(st->player->playerY,st->player->playerX-1) &&!is_parede(map[st->player->playerY][st->player->playerX-1]) && !is_monster(map[st->player->playerY][st->player->playerX-1])) map[st->player->playerY][st->player->playerX-1] = '.';
	}
	if(is_move_up((int)key)&& valid_move(st,(int)key,map)){
		if(dentro_mapa(st->player->playerY-3,st->player->playerX) &&!is_parede(map[st->player->playerY-3][st->player->playerX]) && !is_monster(map[st->player->playerY-3][st->player->playerX])) map[st->player->playerY-3][st->player->playerX] =  '.';
		if(dentro_mapa(st->player->playerY-3,st->player->playerX-1) &&!is_parede(map[st->player->playerY-3][st->player->playerX-1]) && !is_monster(map[st->player->playerY-3][st->player->playerX-1])) map[st->player->playerY-3][st->player->playerX-1] =  '.';
		if(dentro_mapa(st->player->playerY-3,st->player->playerX+1) &&!is_parede(map[st->player->playerY-3][st->player->playerX+1]) && !is_monster(map[st->player->playerY-3][st->player->playerX+1])) map[st->player->playerY-3][st->player->playerX+1] =  '.';
		if(dentro_mapa(st->player->playerY-3,st->player->playerX-2) &&!is_parede(map[st->player->playerY-3][st->player->playerX-2]) && !is_monster(map[st->player->playerY-3][st->player->playerX-2])) map[st->player->playerY-3][st->player->playerX-2] =  '.';
		if(dentro_mapa(st->player->playerY-3,st->player->playerX+2) &&!is_parede(map[st->player->playerY-3][st->player->playerX+2]) && !is_monster(map[st->player->playerY-3][st->player->playerX+2])) map[st->player->playerY-3][st->player->playerX+2] =  '.';
		if(dentro_mapa(st->player->playerY-2,st->player->playerX) &&!is_parede(map[st->player->playerY-2][st->player->playerX]) && !is_monster(map[st->player->playerY-2][st->player->playerX])) map[st->player->playerY-2][st->player->playerX] =  '.';
		if(dentro_mapa(st->player->playerY-2,st->player->playerX-1) &&!is_parede(map[st->player->playerY-2][st->player->playerX-1]) && !is_monster(map[st->player->playerY-2][st->player->playerX-1])) map[st->player->playerY-2][st->player->playerX-1] =  '.';
		if(dentro_mapa(st->player->playerY-2,st->player->playerX+1) &&!is_parede(map[st->player->playerY-2][st->player->playerX+1]) && !is_monster(map[st->player->playerY-2][st->player->playerX+1])) map[st->player->playerY-2][st->player->playerX+1] =  '.';
		if(dentro_mapa(st->player->playerY-1,st->player->playerX) &&!is_parede(map[st->player->playerY-1][st->player->playerX]) && !is_monster(map[st->player->playerY-1][st->player->playerX])) map[st->player->playerY-1][st->player->playerX] =  '.';
	}
	if(is_move_right((int)key)&& valid_move(st,(int)key,map)){
		if(dentro_mapa(st->player->playerY,st->player->playerX+3) &&!is_parede(map[st->player->playerY][st->player->playerX+3]) && !is_monster(map[st->player->playerY][st->player->playerX+3])) map[st->player->playerY][st->player->playerX+3] =  '.';
		if(dentro_mapa(st->player->playerY-1,st->player->playerX+3) &&!is_parede(map[st->player->playerY-1][st->player->playerX+3]) && !is_monster(map[st->player->playerY-1][st->player->playerX+3])) map[st->player->playerY-1][st->player->playerX+3] =  '.';
		if(dentro_mapa(st->player->playerY+1,st->player->playerX+3) &&!is_parede(map[st->player->playerY+1][st->player->playerX+3]) && !is_monster(map[st->player->playerY+1][st->player->playerX+3])) map[st->player->playerY+1][st->player->playerX+3] =  '.';
		if(dentro_mapa(st->player->playerY-2,st->player->playerX+3) &&!is_parede(map[st->player->playerY-2][st->player->playerX+3]) && !is_monster(map[st->player->playerY-2][st->player->playerX+3])) map[st->player->playerY-2][st->player->playerX+3] =  '.';
		if(dentro_mapa(st->player->playerY+2,st->player->playerX+3) &&!is_parede(map[st->player->playerY+2][st->player->playerX+3]) && !is_monster(map[st->player->playerY+2][st->player->playerX+3])) map[st->player->playerY+2][st->player->playerX+3] =  '.';
		if(dentro_mapa(st->player->playerY,st->player->playerX+2) &&!is_parede(map[st->player->playerY][st->player->playerX+2]) && !is_monster(map[st->player->playerY][st->player->playerX+2])) map[st->player->playerY][st->player->playerX+2] =  '.';
		if(dentro_mapa(st->player->playerY-1,st->player->playerX+2) &&!is_parede(map[st->player->playerY-1][st->player->playerX+2]) && !is_monster(map[st->player->playerY-1][st->player->playerX+2])) map[st->player->playerY-1][st->player->playerX+2] =  '.';
		if(dentro_mapa(st->player->playerY+1,st->player->playerX+2) &&!is_parede(map[st->player->playerY+1][st->player->playerX+2]) && !is_monster(map[st->player->playerY+1][st->player->playerX+2])) map[st->player->playerY+1][st->player->playerX+2] =  '.';
		if(dentro_mapa(st->player->playerY,st->player->playerX+1) &&!is_parede(map[st->player->playerY][st->player->playerX+1]) && !is_monster(map[st->player->playerY][st->player->playerX+1])) map[st->player->playerY][st->player->playerX+1] =  '.';
	}
	if(is_move_down((int)key)&& valid_move(st,(int)key,map)){
		if(dentro_mapa(st->player->playerY+3,st->player->playerX) &&!is_parede(map[st->player->playerY+3][st->player->playerX]) && !is_monster(map[(st->player->playerY+3)][st->player->playerX])) map[st->player->playerY+3][st->player->playerX] =  '.';
		if(dentro_mapa(st->player->playerY+3,st->player->playerX-1) &&!is_parede(map[st->player->playerY+3][st->player->playerX-1]) && !is_monster(map[(st->player->playerY+3)][st->player->playerX-1])) map[st->player->playerY+3][st->player->playerX-1] =  '.';
		if(dentro_mapa(st->player->playerY+3,st->player->playerX+1) &&!is_parede(map[st->player->playerY+3][st->player->playerX+1]) && !is_monster(map[(st->player->playerY+3)][st->player->playerX+1])) map[st->player->playerY+3][st->player->playerX+1] =  '.';
		if(dentro_mapa(st->player->playerY+3,st->player->playerX-2) &&!is_parede(map[st->player->playerY+3][st->player->playerX-2]) && !is_monster(map[(st->player->playerY+3)][st->player->playerX-2])) map[st->player->playerY+3][st->player->playerX-2] =  '.';
		if(dentro_mapa(st->player->playerY+3,st->player->playerX+2) &&!is_parede(map[st->player->playerY+3][st->player->playerX+2]) && !is_monster(map[(st->player->playerY+3)][st->player->playerX+2])) map[st->player->playerY+3][st->player->playerX+2] =  '.';
		if(dentro_mapa(st->player->playerY+2,st->player->playerX) &&!is_parede(map[st->player->playerY+2][st->player->playerX]) && !is_monster(map[(st->player->playerY+2)][st->player->playerX])) map[st->player->playerY+2][st->player->playerX] =  '.';
		if(dentro_mapa(st->player->playerY+2,st->player->playerX-1) &&!is_parede(map[st->player->playerY+2][st->player->playerX-1]) && !is_monster(map[(st->player->playerY+2)][st->player->playerX-1])) map[st->player->playerY+2][st->player->playerX-1] =  '.';
		if(dentro_mapa(st->player->playerY+2,st->player->playerX+1) &&!is_parede(map[st->player->playerY+2][st->player->playerX+1]) && !is_monster(map[(st->player->playerY+2)][st->player->playerX+1])) map[st->player->playerY+2][st->player->playerX+1] =  '.';
		if(dentro_mapa(st->player->playerY+1,st->player->playerX) &&!is_parede(map[st->player->playerY+1][st->player->playerX]) && !is_monster(map[(st->player->playerY+1)][st->player->playerX])) map[st->player->playerY+1][st->player->playerX] =  '.';
	}
	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
            start_color();
            init_pair(4,COLOR_YELLOW,COLOR_BLACK);
            attron(COLOR_PAIR(4));
			if(map[i][j] == '.') mvaddch(i,j,'.');
            attroff(COLOR_PAIR(4));
		}
	}
}

void remove_light(char map[ROWS][COLS]){
	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == '.'){
				mvaddch(i,j,' ');
				map[i][j] = ' ';
			}
		}
	}
}

void draw_player(STATE *st,char map[ROWS][COLS]){
    start_color();
    init_pair(3,COLOR_GREEN,COLOR_BLACK);
	attron(COLOR_PAIR(3));
	map[st->player->playerY][st->player->playerX] = '@';
    for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == '@') mvaddch(i,j,'@');
		}
	}
    attroff(COLOR_PAIR(3));
	refresh();
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
/*
void remove_monster(MONSTER **monster,char map[ROWS][COLS]){
	int x = (*monster)->monsterX;
	int y = (*monster)->monsterY;
	map[y][x] = ' ';
	mvaddch(y,x,' ');
	//free(*monster);
	*monster = NULL;
}
*/

void kill(STATE *st,char map[ROWS][COLS]){
	
	MONSTER *monstro = get_monster(st);
	if(monstro != NULL){
		monstro->monsterHealth -= st->player->playerAttack;
        playSound("monster_attack.wav");
		st->player->playerHealth -= monstro->monsterAttack;

		if(monstro->monsterHealth <= 0){
			monstro->is_dead = true;
            map[monstro->monsterY][monstro->monsterX] = ' ';
            mvaddch(monstro->monsterY,monstro->monsterX,' ');
		}
	}
	if(st->player->playerHealth <= 0){
		st->player = NULL;
		//endwin();
		game_over();
	}
    bool win = true;
    for(int i = 0; i<10 ; i++){
        if(st->monstros[i].is_dead == true) win = win && true;
        else win = false;
    }
    if(win){
        you_won();
    }

}


void update(STATE *st,char map[ROWS][COLS]) {
	int key = getch();
	mvaddch(st->player->playerY,st->player->playerX, ' ');
	remove_light(map);
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
	int nrows;
	nrows = getmaxx(wnd);
	//roguelite(wnd);
	show_main_menu();
	char map[ROWS][COLS];
	init_map(map);
    do{
		st->player->playerY = random() % (COLS - 2) + 1;
		st->player->playerX = random() % (COLS - 2) + 1;
	} while(is_parede((int)map[st->player->playerY][st->player->playerX]) || st->player->playerY > ROWS-1 || st->player->playerX > COLS-1);
	WINDOW* window = newwin(ROWS, COLS, 1, 1);
	box(window, '#', '#');
	refresh();
    clear();
	spawn_mobs(st,map);
    draw_player(st,map);
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
            if(map[i][j] != '#' && map[i][j] != '@' && map[i][j] != '!'){
                start_color();
                init_pair(1, COLOR_BLACK, COLOR_BLACK);
                attron(COLOR_PAIR(1));
                mvaddch(i, j, map[i][j]);
                attroff(COLOR_PAIR(1));
            }
            else if(map[i][j] == '#'){
                start_color();
                init_pair(5, 8, COLOR_BLACK);
                attron(COLOR_PAIR(5));
                mvaddch(i, j, map[i][j]);
                attroff(COLOR_PAIR(5));
            }
		}
	}
	while(1) {
		move(nrows - 1, 0);
        start_color();
        init_pair(2,COLOR_BLUE, COLOR_BLACK);
		attron(COLOR_PAIR(2));
		if(st->player != NULL){
			mvprintw(ROWS-30, COLS +4,"Player state:");
			mvprintw(ROWS-27,COLS+3,"	Health: %d", st->player->playerHealth);
			mvprintw(ROWS-25,COLS+3,"	Atack: %d", st->player->playerAttack);
		}
		MONSTER *monstro = get_monster(st);
		if(monstro != NULL){
			mvprintw(ROWS-30, COLS +22,"Monster state:");
			mvprintw(ROWS-27,COLS+21,"	Health: %d",monstro->monsterHealth);
			mvprintw(ROWS-25,COLS+21,"	Atack: %d",monstro->monsterAttack);
		}
		else{
			mvprintw(ROWS-30, COLS +22,"Monster state:");
			mvprintw(ROWS-27,COLS+21,"	Health: ");
			mvprintw(ROWS-25,COLS+21,"	Atack: ");
		}
		//mvprintw(ROWS-23,COLS+4,"Posição: (%d, %d) %d %d\n", st->player->playerX, st->player->playerY, ncols, nrows);
		attroff(COLOR_PAIR(2));
		refresh();
		move(st->player->playerY, st->player->playerX);
		update(st,map);
		noecho();
	}
	free(st->player);
	free(st);
	return 0;
}