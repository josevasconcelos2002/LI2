#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 52
#define COLS 211
#define WALL_PROB 0.48
#define ITERATIONS 10

void init_map(char map[ROWS][COLS]) {
    // Inicializa o mapa com caminhos e paredes aleatórios
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (rand() < WALL_PROB * RAND_MAX) {
                map[i][j] = '#';
            } else {
                map[i][j] = '.';
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
                new_map[i][j] = '.';
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
                        new_map[i][j] = '.';
                    } else {
                        new_map[i][j] = '#';
                    }
                }
            } else {
                new_map[i][j] = '.';
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

int main() {
    // Inicializa ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    srand(time(NULL));

    // Inicializa o mapa
    char map[ROWS][COLS];
    init_map(map);

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

    // Desenha o mapa no ecra
    clear();
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mvaddch(i, j, map[i][j]);
        }
    }
    refresh();

    // Clicar numa tecla para fechar programa de teste
    getch();

    // Cleanup ncurses
    endwin();

    return 0;
}
