#include <ncurses.h>
#include "map.h"

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

bool dentro_mapa(int y, int x){
	bool resultado = true;
	if(y<1 || y>ROWS-1 || x<1 || x>COLS-1) resultado = false;
	return resultado;
}

void draw_map(char map[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
            if(map[i][j] == ' '){
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
            else if(map[i][j] == '+'){
                start_color();
                init_pair(10,COLOR_RED,COLOR_BLACK);
                attron(COLOR_PAIR(10));
                mvaddch(i, j, map[i][j]);
                attroff(COLOR_PAIR(10));
            }
		}
	}
}

void desenha_pontos(char map[ROWS][COLS]) {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
			if(map[i][j] == '#') {
				mvaddch(i,j,' ');
			}
			if(map[i][j] == '.' && mvinch(i,j) == '!') {
                mvaddch(i,j,'!');
            }else if(map[i][j] == '.') {
					mvaddch(i,j,'.');
			}
        }
    }
}