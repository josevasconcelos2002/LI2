#include <ncurses.h>
#include "mob.h"

void init_mobs(char map[ROWS][COLS], MOB *mobs[]) {    
    // Gera 10 monstros com posições aleatórias no mapa
    for (int i = 0; i < 10; i++) {
        int x, y;
        do {
            // Gera uma posição aleatória
            x = rand() % COLS;
            y = rand() % ROWS;
        } while (!dentro_mapa(y,x) || map[y][x] == '#' || map[y][x] == '@' || map[y][x] == '+' || map[y][x] == '|'); // Verifica se a posição é uma parede
        
        // Inicializa o monstro com a posição gerada e atributos aleatórios
        mobs[i]->x = x;
        mobs[i]->y = y;
        mobs[i]->hp = rand() % 10 + 11;
        mobs[i]->attack = rand() % 5 + 1;
		mobs[i]->is_visible = false;
        mobs[i]->is_dead = false;

		map[y][x] = '!';
    }
}

void init_boss(char map[ROWS][COLS], MOB *boss) {    
        int x, y;
        do {
            // Gera uma posição aleatória
            x = rand() % COLS;
            y = rand() % ROWS;
        } while (!dentro_mapa(y,x) || map[y][x] == '#' || map[y][x] == '@' || map[y][x] == '+' || map[y][x] == '|');
        
        // Inicializa o monstro com a posição gerada e atributos aleatórios
        boss->x = x;
        boss->y = y;
        boss->hp = 150;
        boss->attack = 15;
		boss->is_visible = true; //visivel ou nao?
        boss->is_dead = false;

		map[y][x] = 'B';
}

void move_boss(PLAYER *player, MOB *boss, char map[ROWS][COLS]) {
        if (!boss->is_dead) {
            int playerX = player->x;
            int playerY = player->y;
            int closestX = boss->x;
            int closestY = boss->y;
            int minDistance = 20;

            if (abs(playerX - closestX) + abs(playerY - closestY) > minDistance) {
                int x, y;
                do {
                    int direction = rand() % 4;
                    x = boss->x;
                    y = boss->y;

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
                } while (map[y][x] == '#' || map[y][x] == '@' || map[y][x] == '+' || map[y][x] == '|');

                closestX = x;
                closestY = y;
            } else {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        // Skip diagonal directions
                        if (dx != 0 && dy != 0) {
                            continue;
                        }

                        int newX = boss->x + dx;
                        int newY = boss->y + dy;
                        int distance = abs(playerX - newX) + abs(playerY - newY);

                        if (dentro_mapa(newY, newX) && map[newY][newX] != '#'
                            && map[newY][newX] != '@'  && map[newY][newX] != '!' && distance < minDistance
                            && map[newY][newX] != '+' && map[newY][newX] != '|') {
                            closestX = newX;
                            closestY = newY;
                            minDistance = distance;
                        }
                    }
                }
            }

            int prevX = boss->x;
            int prevY = boss->y;
            boss->x = closestX;
            boss->y = closestY;

            mvaddch(prevY, prevX, ' ');
            map[prevY][prevX] = ' ';
            
            map[closestY][closestX] = '!';
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
                } while (map[y][x] == '#' || map[y][x] == '@' || map[y][x] == '+' || map[y][x] == '|');

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
                            && map[newY][newX] != '@'  && map[newY][newX] != '!' && distance < minDistance
                            && map[newY][newX] != '+' && map[newY][newX] != '|') {
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

MOB *get_closest_mob(MOB *mobs[], PLAYER *player) {
    MOB *closestMob = NULL;
    int closestDistanceSquared = 20;

    for (int i = 0; i < 10; i++) {
        MOB *mob = mobs[i];
        if (mob->is_dead || !mob->is_visible) {
            continue;
        }

        int dx = mob->x - player->x;
        int dy = mob->y - player->y;

        int distanceSquared = dx * dx + dy * dy;
        if (distanceSquared < closestDistanceSquared) {
            closestDistanceSquared = distanceSquared;
            closestMob = mob;
        }
    }
    return closestMob;
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

void player_attack(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]){
	MOB *mob = get_closest_mob(mobs, player);
	if(mob != NULL){
        //playSound("player_attack.wav");
		mob->hp -= player->attack;

		if(mob->hp <= 0){
            map[mob->y][mob->x] = ' ';
            mvaddch(mob->y, mob->x, ' ');
			mob->is_dead = true;
            mob->is_visible = false;
		}
	}
}

void player_attack_boss(PLAYER *player, MOB *boss, char map[ROWS][COLS]){
	if(boss != NULL){
        //playSound("player_attack.wav");
		boss->hp -= player->attack;

		if(boss->hp <= 0){
            map[boss->y][boss->x] = ' ';
            mvaddch(boss->y, boss->x, ' ');
			boss->is_dead = true;
            boss->is_visible = false;
		}
	}
}

void boss_attack(PLAYER *player, MOB *boss){
	if(boss && distancia(player, boss) < 1.5){
        //playSound("monster_attack.wav");
		player->hp -= boss->attack;
	}
}

void mob_attack(PLAYER *player, MOB *mobs[]){
	MOB *mob = get_closest_mob(mobs, player);
	if(mob && distancia(player, mob) < 1.5){
        //playSound("monster_attack.wav");
		player->hp -= mob->attack;
	}
}

bool is_mob_visible(MOB *mob, PLAYER *player, char map[ROWS][COLS]) {
    int centerX = player->x;
    int centerY = player->y;
    int xOffset = 3;
    int yOffset = 2;

    for (int i = centerX - xOffset; i <= centerX + xOffset; i++) {
        for (int j = centerY - yOffset; j <= centerY + yOffset; j++) {
            if (map[j][i] == '!' && mob->x == i && mob->y == j) {
                return true;
            }
        }
    }
    return false;
}


void draw_boss(PLAYER *player, MOB *boss, char map[ROWS][COLS]) {
        if(player->only_dots && is_mob_visible(boss, player, map) && !boss->is_dead) {
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            mvaddch(boss->y , boss->x, '!');
            attroff(COLOR_PAIR(1));
        }
        else if(!boss->is_dead && !player->only_dots && is_mob_visible(boss, player, map)){
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            mvaddch(boss->y , boss->x, '!');
            attroff(COLOR_PAIR(1));
        }
}


void draw_mobs(PLAYER *player, MOB *mobs[], char map[ROWS][COLS]) {
    for(int i = 0; i < 10; i++) {
        if(player->only_dots && is_mob_visible(mobs[i], player, map) && !mobs[i]->is_dead) {
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            mvaddch(mobs[i]->y , mobs[i]->x, '!');
            attroff(COLOR_PAIR(1));
        }
        else if(!mobs[i]->is_dead && !player->only_dots && is_mob_visible(mobs[i], player, map)){
            start_color();
            init_pair(1, COLOR_RED, COLOR_BLACK);
            attron(COLOR_PAIR(1));
            mvaddch(mobs[i]->y , mobs[i]->x, '!');
            attroff(COLOR_PAIR(1));
        }
    }
}