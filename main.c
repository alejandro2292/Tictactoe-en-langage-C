#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 3
#define MAX_MOVES 9

typedef struct {
    int x;
    int y;
} Position;

char plateau[TAILLE][TAILLE];
char joueurActuel = 'X';
int jeuTermine = 0;
Position historiqueMouvements[MAX_MOVES];
int nombreMouvements = 0;

void initialiserPlateau();
void afficherPlateau(WINDOW *win);
int verifierGagnant();
int verifierMatchNul();
void mouvementJoueur(WINDOW *win);
Position getPositionCurseur(WINDOW *win);
void rejouerPartie(WINDOW *win);
void mouvementIA();
void afficherMenu();

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    srand(time(NULL));

    afficherMenu();

    endwin();
    return 0;
}

void afficherMenu() {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    char *menu_items[] = {"Joueur vs Joueur", "Joueur vs IA", "IA vs IA", "Replay", "Quitter"};
    int num_items = 5;
    int selected_item = 0;

    while (1) {
        clear();
        mvprintw(max_y / 4, (max_x - 10) / 2, "TIC-TAC-TOE");
        for (int i = 0; i < num_items; i++) {
            if (i == selected_item) attron(A_REVERSE);
            mvprintw(max_y / 4 + 2 + i, (max_x - 10) / 2, "%s", menu_items[i]);
            attroff(A_REVERSE);
        }

        int ch = getch();
        switch (ch) {
            case KEY_UP: selected_item = (selected_item - 1 + num_items) % num_items; break;
            case KEY_DOWN: selected_item = (selected_item + 1) % num_items; break;
            case 10:
                if (selected_item == 0 || selected_item == 1 || selected_item == 2) {
                    WINDOW *plateauWin = newwin(TAILLE * 3 + 3, TAILLE * 5 + 3, 5, 10);
                    box(plateauWin, 0, 0);
                    refresh();
                    initialiserPlateau();
                    afficherPlateau(plateauWin);
                    jeuTermine = 0;
                    joueurActuel = 'X';
                    nombreMouvements = 0;

                    while (!jeuTermine) {
                        if ((selected_item == 1 && joueurActuel == 'O') || selected_item == 2) {
                            mouvementIA();
                        } else {
                            Position pos = getPositionCurseur(plateauWin);
                            plateau[pos.y][pos.x] = joueurActuel;
                        }

                        afficherPlateau(plateauWin);
                        if (verifierGagnant()) {
                            jeuTermine = 1;
                            mvwprintw(plateauWin, TAILLE * 3 + 1, 2, "Le joueur %c a gagné !", joueurActuel);
                        } else if (verifierMatchNul()) {
                            jeuTermine = 1;
                            mvwprintw(plateauWin, TAILLE * 3 + 1, 2, "Match nul !");
                        } else {
                            joueurActuel = (joueurActuel == 'X') ? 'O' : 'X';
                        }
                    }
                    wrefresh(plateauWin);
                    getch();
                    delwin(plateauWin);
                }
                return;
        }
        refresh();
    }
}

void initialiserPlateau() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau[i][j] = ' ';
        }
    }
}

void afficherPlateau(WINDOW *win) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            mvwprintw(win, i * 3 + 2, j * 5 + 3, "%c", plateau[i][j]);
        }
    }
    wrefresh(win);
}

int verifierGagnant() {
    for (int i = 0; i < TAILLE; i++) {
        if (plateau[i][0] == plateau[i][1] && plateau[i][1] == plateau[i][2] && plateau[i][0] != ' ') return 1;
        if (plateau[0][i] == plateau[1][i] && plateau[1][i] == plateau[2][i] && plateau[0][i] != ' ') return 1;
    }
    if ((plateau[0][0] == plateau[1][1] && plateau[1][1] == plateau[2][2] && plateau[0][0] != ' ') ||
        (plateau[0][2] == plateau[1][1] && plateau[1][1] == plateau[2][0] && plateau[0][2] != ' ')) {
        return 1;
    }
    return 0;
}

int verifierMatchNul() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (plateau[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void mouvementIA() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (plateau[i][j] == ' ') {
                plateau[i][j] = joueurActuel;
                return;
            }
        }
    }
}

Position getPositionCurseur(WINDOW *win) {
    Position pos = {0, 0};
    int ch;
    while (1) {
        ch = getch();
        switch (ch) {
            case KEY_UP: pos.y = (pos.y - 1 + TAILLE) % TAILLE; break;
            case KEY_DOWN: pos.y = (pos.y + 1) % TAILLE; break;
            case KEY_LEFT: pos.x = (pos.x - 1 + TAILLE) % TAILLE; break;
            case KEY_RIGHT: pos.x = (pos.x + 1) % TAILLE; break;
            case 10: if (plateau[pos.y][pos.x] == ' ') return pos;
        }
        wmove(win, pos.y * 3 + 2, pos.x * 5 + 3);
        wrefresh(win);
    }
}

