#include <ncurses.h>
#include "mob.h"

void spawn_mobs(char map[ROWS][COLS], MOB *mobs[]) {    
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

double distancia(PLAYER *player, MOB *mob){
	int dx = abs(player->x - mob->x);
	int dy = abs(player->y - mob->y);
	return sqrt(dx * dx + dy * dy);
}

MOB *get_mob(PLAYER *player, MOB *mobs[]){
	MOB *resultado = NULL;
	for(int i = 0; i<10 ; i++){
        if(player && mobs[i]){
            if(distancia(player,mobs[i]) == 1.0){
                resultado = mobs[i];
            }
        }
	}
	return resultado;
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
    char *buffer = (char *)malloc(desiredBytes);

    // Ler apenas 1 segundo do arquivo de áudio
    if(!fread(buffer, sizeof(char), desiredBytes, file)) exit(0);
    fclose(file);

    // Reproduzir o áudio
    snd_pcm_writei(handle, buffer, desiredBytes / 2);  // Dividir por 2, pois o tamanho do buffer é em bytes

    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);
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
		map[player->y][player->x] = ' ';
        mvaddch(player->y,player->x, ' ');
		//endwin();
		game_over();
	}

    bool win = true;
    for(int i = 0; i < 10; i++){
        if(!mobs[i]->is_dead) {
            win = false;
            break;
        }
    }
    
    if(win){
        you_won();
    }
}