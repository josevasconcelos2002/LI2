#include <ncurses.h>
#include "menu.h"

// Função para exibir o menu principal
int show_main_menu() {
    clear(); // Limpa a tela
    int x, y; // Variáveis para armazenar a posição atual do cursor
    int choice = 0; // Variável para armazenar a escolha do jogador
    const char *options[] = {"Jogar", "Sair"}; // Opções do menu

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
    const char *menu_items[] = {
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