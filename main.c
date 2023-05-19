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

#define WALL_PROB 0.465
#define ITERATIONS 10
#define ROWS 30
#define COLS 100

typedef struct{
	int x;
	int y;
	int hp;
	int attack;
} PLAYER;

typedef struct{
    int x;
    int y;
    int hp;
    int attack;
	bool is_visible;
    bool is_dead;
} MOB;
    
void inicializa_player(PLAYER *player){
    player->x = 15;
    player->y = 15;
    player->hp = 100;
    player->attack = 10;
}

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
            case 'w':
                if (choice > 0) {
                    choice--;
                }
                break;
            case 's':
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
        if (key == 'w') {
            menu_choice--;
            if (menu_choice < 0) {
                menu_choice = num_items-1;
            }
        } else if (key == 's') {
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
    if(!fread(buffer, sizeof(char), desiredBytes, file)) exit(0);
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


bool dentro_mapa(int y, int x){
	bool resultado = true;
	if(y<1 || y>ROWS-1 || x<1 || x>COLS-1) resultado = false;
	return resultado;
}

double distancia(PLAYER *player, MOB *mob){
	int dx = abs(player->x - mob->x);
	int dy = abs(player->y - mob->y);
	return sqrt(dx * dx + dy * dy);
}

void spawn_mobs(char map[ROWS][COLS], MOB *mobs[]) {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    // Gera 10 monstros com posições aleatórias no mapa
    for (int i = 0; i < 10; i++) {
        int x, y;
        do {
            // Gera uma posição aleatória
            x = rand() % COLS;
            y = rand() % ROWS;
        } while (!dentro_mapa(y,x) || map[y][x] == '#' || map[y][x] == '@'); // Verifica se a posição é uma parede
        
        // Inicializa o monstro com a posição gerada e atributos aleatórios
        mobs[i]->x = x;
        mobs[i]->y = y;
        mobs[i]->hp = rand() % 10 + 1;
        mobs[i]->attack = rand() % 5 + 1;
		mobs[i]->is_visible = false;
        mobs[i]->is_dead = false;

		map[y][x] = '!';
    }
}

void move_mobs(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]) {
    for (int i = 0; i < 10; i++) {
        if (mobs[i]->is_dead == false) {
            int playerX = player->x;
            int playerY = player->y;
            int closestX = mobs[i]->x;
            int closestY = mobs[i]->y;
            int minDistance = 20;

            // Skip the iteration if the mob is already at the player's position
            if (playerX == closestX && playerY == closestY) {
                continue;
            }

            if (abs(playerX - closestX) + abs(playerY - closestY) > minDistance) {
                int x, y;
                do {
                    int direction = rand() % 4;
                    x = mobs[i]->x;
                    y = mobs[i]->y;

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

                        int newX = mobs[i]->x + dx;
                        int newY = mobs[i]->y + dy;
                        int distance = abs(playerX - newX) + abs(playerY - newY);

                        if (dentro_mapa(newY, newX) && map[newY][newX] != '#'
                            && map[newY][newX] != '@'  && map[newY][newX] != '!' && distance < minDistance) {
                            closestX = newX;
                            closestY = newY;
                            minDistance = distance;
                        }
                    }
                }
            }

            int prevX = mobs[i]->x;
            int prevY = mobs[i]->y;
            mobs[i]->x = closestX;
            mobs[i]->y = closestY;

            mvaddch(prevY, prevX, ' ');
            map[prevY][prevX] = ' ';
            
            map[closestY][closestX] = '!';
        }
    }
}

void do_movement_action(PLAYER *player, char map[ROWS][COLS], int dx, int dy) {
    map[player->y][player->x] = ' ';
	player->x += dx;
	player->y += dy;
}

bool valid_move(PLAYER *player, char map[ROWS][COLS], char key){
    int x = player->x, y = player->y;
    switch(key) {
        case 'w': if(map[y-1][x] == '#' || map[y-1][x] == '!') return false;
            break;
        case 's': if(map[y+1][x] == '#' || map[y+1][x] == '!') return false;
            break;
        case 'a': if(map[y][x-1] == '#' || map[y][x-1] == '!') return false;
            break;
        case 'd': if(map[y][x+1] == '#' || map[y][x+1] == '!') return false;
            break;            
    }
	return true;
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

void light_up(int y, int x, char map[ROWS][COLS]) {
	attron(COLOR_PAIR(COLOR_YELLOW));
	if(dentro_mapa(y-3,x) && map[y-3][x] == ' ') map[y-3][x] =  '.';
	if(dentro_mapa(y-3,x-1) && map[y-3][x-1] == ' ') map[y-3][x-1] =  '.';
	if(dentro_mapa(y-3,x+1) && map[y-3][x+1] == ' ') map[y-3][x+1] =  '.';
	if(dentro_mapa(y-3,x-2) && map[y-3][x-2] == ' ') map[y-3][x-2] =  '.';
	if(dentro_mapa(y-3,x+2) && map[y-3][x+2] == ' ') map[y-3][x+2] =  '.';
	if(dentro_mapa(y-2,x) && map[y-2][x] == ' ') map[y-2][x] =  '.';
	if(dentro_mapa(y-2,x-1) && map[y-2][x-1] == ' ') map[y-2][x-1] =  '.';
	if(dentro_mapa(y-2,x+1) && map[y-2][x+1] == ' ') map[y-2][x+1] =  '.';
	if(dentro_mapa(y-1,x) && map[y-1][x] == ' ') map[y-1][x] =  '.';
	attroff(COLOR_PAIR(COLOR_YELLOW));
}

void light_down(int y, int x, char map[ROWS][COLS]) {
	attron(COLOR_PAIR(COLOR_YELLOW));
	if(dentro_mapa(y+3,x) && map[(y+3)][x] == ' ') map[y+3][x] =  '.';
	if(dentro_mapa(y+3,x-1) && map[(y+3)][x-1] == ' ') map[y+3][x-1] =  '.';
	if(dentro_mapa(y+3,x+1) && map[(y+3)][x+1] == ' ') map[y+3][x+1] =  '.';
	if(dentro_mapa(y+3,x-2) && map[(y+3)][x-2] == ' ') map[y+3][x-2] =  '.';
	if(dentro_mapa(y+3,x+2) && map[(y+3)][x+2] == ' ') map[y+3][x+2] =  '.';
	if(dentro_mapa(y+2,x) && map[(y+2)][x] == ' ') map[y+2][x] =  '.';
	if(dentro_mapa(y+2,x-1) && map[(y+2)][x-1] == ' ') map[y+2][x-1] =  '.';
	if(dentro_mapa(y+2,x+1) && map[(y+2)][x+1] == ' ') map[y+2][x+1] =  '.';
	if(dentro_mapa(y+1,x) && map[(y+1)][x] == ' ') map[y+1][x] =  '.';
	attroff(COLOR_PAIR(COLOR_YELLOW));
}

void light_right(int y, int x, char map[ROWS][COLS]) {
	attron(COLOR_PAIR(COLOR_YELLOW));
	if(dentro_mapa(y,x-3) && map[y][x-3] == ' ') map[y][x-3] = '.';
	if(dentro_mapa(y-1,x-3) && map[y-1][x-3] == ' ') map[y-1][x-3] = '.';
	if(dentro_mapa(y+1,x-3) && map[y+1][x-3] == ' ') map[y+1][x-3] = '.';
	if(dentro_mapa(y-2,x-3) && map[y-2][x-3] == ' ') map[y-2][x-3] = '.';
	if(dentro_mapa(y+2,x-3) && map[y+2][x-3] == ' ') map[y+2][x-3] = '.';
	if(dentro_mapa(y,x-2) && map[y][x-2] == ' ') map[y][x-2] = '.';
	if(dentro_mapa(y-1,x-2) && map[y-1][x-2] == ' ') map[y-1][x-2] = '.';
	if(dentro_mapa(y+1,x-2) && map[y+1][x-2] == ' ') map[y+1][x-2] = '.';
	if(dentro_mapa(y,x-1) && map[y][x-1] == ' ') map[y][x-1] = '.';
	attroff(COLOR_PAIR(COLOR_YELLOW));
}

void light_left(int y, int x, char map[ROWS][COLS]) {
	attron(COLOR_PAIR(COLOR_YELLOW));
	if(dentro_mapa(y,x+3) && map[y][x+3] == ' ') map[y][x+3] =  '.';
	if(dentro_mapa(y-1,x+3) && map[y-1][x+3] == ' ') map[y-1][x+3] =  '.';
	if(dentro_mapa(y+1,x+3) && map[y+1][x+3] == ' ') map[y+1][x+3] =  '.';
	if(dentro_mapa(y-2,x+3) && map[y-2][x+3] == ' ') map[y-2][x+3] =  '.';
	if(dentro_mapa(y+2,x+3) && map[y+2][x+3] == ' ') map[y+2][x+3] =  '.';
	if(dentro_mapa(y,x+2) && map[y][x+2] == ' ') map[y][x+2] =  '.';
	if(dentro_mapa(y-1,x+2) && map[y-1][x+2] == ' ') map[y-1][x+2] =  '.';
	if(dentro_mapa(y+1,x+2) && map[y+1][x+2] == ' ') map[y+1][x+2] =  '.';
	if(dentro_mapa(y,x+1) && map[y][x+1] == ' ') map[y][x+1] =  '.';
	attroff(COLOR_PAIR(COLOR_YELLOW));
}

void draw_light(PLAYER *player, char map[ROWS][COLS], char key){
    int y = player->y, x = player->x;

    if (!valid_move(player, map, key))
        return;

    switch(key) {
        case 'w': light_up(y, x, map);
            break;
        case 's': light_down(y, x, map);
            break;
        case 'a': light_right(y, x, map);
            break;
        case 'd': light_left(y, x, map);
            break;            
    }

    attron(COLOR_PAIR(COLOR_YELLOW));

	for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
            start_color();
            init_pair(4,COLOR_YELLOW,COLOR_BLACK);
            attron(COLOR_PAIR(4));
			if(map[i][j] == '.') mvaddch(i,j,'.');
            attroff(COLOR_PAIR(4));
		}
	}
    attroff(COLOR_PAIR(COLOR_YELLOW));
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

void draw_player(PLAYER *player, char map[ROWS][COLS]){
    start_color();
    init_pair(3,COLOR_GREEN,COLOR_BLACK);	
	map[player->y][player->x] = '@';
	attron(COLOR_PAIR(3));
    for(int i = 0; i<ROWS ; i++){
		for(int j = 0; j<COLS; j++){
			if(map[i][j] == '@') mvaddch(i,j,'@');
		}
	}
    attroff(COLOR_PAIR(3));
	refresh();
}


MOB *get_mob(PLAYER *player, MOB *mobs[]){
	MOB *resultado = NULL;
	for(int i = 0; i<10 ; i++){
		if(distancia(player,mobs[i]) == 1.0){
			resultado = mobs[i];
		}
	}
	return resultado;
}

void kill(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]){
	
	MOB *mob = get_mob(player, mobs);
	if(mob != NULL){
		mob->hp -= player->attack;
        playSound("monster_attack.wav");
		player->hp -= mob->attack;

		if(mob->hp <= 0){
			mob->is_dead = true;
            map[mob->y][mob->x] = ' ';
            mvaddch(mob->y, mob->x, ' ');
		}
	}
	if(player->hp <= 0){
		player = NULL;
		//endwin();
		game_over();
	}
    bool win = true;
    for(int i = 0; i<10 ; i++){
        if(!mob[i].is_dead) win = false;
    }
    if(win){
        you_won();
    }

}

void draw_mobs(MOB *mobs[]) {
    for(int i = 0; i < 10; i++) {
        if(only_dots && mobs[i]->is_visible && !mobs[i]->is_dead) {
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            mvaddch(mobs[i]->y , mobs[i]->x, '!');
            attroff(COLOR_PAIR(1));
        }
        else if(!mobs[i]->is_dead && !only_dots){
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            mvaddch(mobs[i]->y , mobs[i]->x, '!');
            attroff(COLOR_PAIR(1));
        }
    }
}

void update(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]) {
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
            kill(player, mobs, map);
            break;
		case 'v':
            only_dots = !only_dots;
            desenha_pontos(map);
            break; //altera o modo de visao
		case ' ':
            show_pause_menu();
            break; // espaco
		case 'q':
            endwin();
            exit(0);
            break;
	}
	draw_player(player, map);
	draw_light(player, map, key);
    move_mobs(player, mobs, map);
    draw_mobs(mobs);
	refresh();
}

void draw_map(char map[ROWS][COLS]) {
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
}

int main(){
	srand(time(NULL));
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, false);
	keypad(stdscr, true);
	WINDOW *wnd = initscr();
	//roguelite(wnd);
    show_main_menu();

    PLAYER *player = malloc(sizeof(PLAYER));
    inicializa_player(player);
    char map[ROWS][COLS];
	init_map(map);
    MOB *mobs[10];
    for (int i = 0; i < 10; i++) {
        mobs[i] = malloc(sizeof(MOB));
    }
    spawn_mobs(map, mobs);
    
    do {
		player->y = rand() % (COLS - 2) + 1;
		player->x = rand() % (COLS - 2) + 1;
	} while(map[player->y][player->x] == '#' || !dentro_mapa(player->y, player->x));

	WINDOW* window = newwin(ROWS, COLS, 1, 1);
	box(window, '#', '#');
	refresh();
    clear();
    draw_map(map);
    draw_mobs(mobs);
    draw_player(player,map);
    draw_light(player, map, 'w');

	int nrows;
	nrows = getmaxx(wnd);
	while(1) {
		move(nrows - 1, 0);
        start_color();
        init_pair(2,COLOR_BLUE, COLOR_BLACK);
		attron(COLOR_PAIR(2));
		if(player != NULL){
			mvprintw(ROWS-30, COLS +4,"Player state:");
			mvprintw(ROWS-27,COLS+3,"	Health: %d", player->hp);
			mvprintw(ROWS-25,COLS+3,"	Atack: %d", player->attack);
		}
		MOB *mob = get_mob(player, mobs);
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
		//mvprintw(ROWS-23,COLS+4,"Posição: (%d, %d) %d %d\n", st->player->playerX, st->player->playerY, ncols, nrows);
		attroff(COLOR_PAIR(2));
		refresh();
		move(player->y, player->x);
		update(player, mobs, map);
		noecho();
	}
    free(player);
    for (int i = 0; i < 10; i++) {
        free(mobs[i]);
    }
	return 0;
}