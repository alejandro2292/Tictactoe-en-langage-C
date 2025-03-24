#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // Pour usleep
 
#define SIZE 3
 
char board[SIZE][SIZE];
int moves[SIZE * SIZE][2], move_count = 0;
 
void init_board() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = ' ';
    move_count = 0;
}
 
void draw_board(int cursor_x, int cursor_y) {
    clear();
    mvprintw(0, 0, " TIC-TAC-TOE ");
    mvprintw(1, 0, "==============");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == cursor_y && j == cursor_x) {
                attron(A_REVERSE);
                mvprintw(i * 2 + 3, j * 4, " %c ", board[i][j]);
                attroff(A_REVERSE);
            } else {
                mvprintw(i * 2 + 3, j * 4, " %c ", board[i][j]);
            }
            if (j < SIZE - 1) printw("|");
        }
        if (i < SIZE - 1) mvprintw(i * 2 + 4, 0, "---+---+---");
    }
    refresh();
}
 
int check_winner() {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];
    return move_count == SIZE * SIZE ? 'D' : 0;
}
 
void player_move(char symbol) {
    int cursor_x = 0, cursor_y = 0;
    int ch;
    while (1) {
        draw_board(cursor_x, cursor_y);
        ch = getch();
        if (ch == 'q') exit(0);
        else if (ch == KEY_UP && cursor_y > 0) cursor_y--;
        else if (ch == KEY_DOWN && cursor_y < SIZE - 1) cursor_y++;
        else if (ch == KEY_LEFT && cursor_x > 0) cursor_x--;
        else if (ch == KEY_RIGHT && cursor_x < SIZE - 1) cursor_x++;
        else if (ch == ' ' && board[cursor_y][cursor_x] == ' ') {
            board[cursor_y][cursor_x] = symbol;
            moves[move_count][0] = cursor_y;
            moves[move_count][1] = cursor_x;
            move_count++;
            break;
        }
    }
}
 
void ai_move(char symbol) {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (board[y][x] != ' ');
    board[y][x] = symbol;
    moves[move_count][0] = y;
    moves[move_count][1] = x;
    move_count++;
    draw_board(-1,-1);
    usleep(500000);
}
 
void replay() {
    int saved_moves = move_count;
    init_board();
    for (int i = 0; i < saved_moves; i++) {
        board[moves[i][0]][moves[i][1]] = (i % 2 == 0) ? 'X' : 'O';
        draw_board(-1, -1);
        usleep(500000);
    }
    mvprintw(14, 0, "Replayed Winner: %c", check_winner());
    getch();
}
 
void game_loop(int mode) {
    init_board();
    char turn = 'X';
    while (!check_winner()) {
        if (mode == 3 || (mode == 2 && turn == 'O')) ai_move(turn);
        else player_move(turn);
        turn = (turn == 'X') ? 'O' : 'X';
    }
    draw_board(-1, -1);
    mvprintw(14, 0, "Winner: %c", check_winner());
    getch();
}
 
void menu() {
    int choice = 0;
    int ch;
    while (1) {
        clear();
        mvprintw(2, 0, " TIC-TAC-TOE MENU ");
        mvprintw(3, 0, "=================");
        char *options[] = {"Player vs Player", "Player vs AI", "AI vs AI", "Replay", "Quit"};
        for (int i = 0; i < 5; i++) {
            if (i == choice) {
                attron(A_REVERSE);
                mvprintw(5 + i, 0, "%s", options[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(5 + i, 0, "%s", options[i]);
            }
        }
        refresh();
        ch = getch();
        if (ch == KEY_UP && choice > 0) choice--;
        else if (ch == KEY_DOWN && choice < 4) choice++;
        else if (ch == '\n') {
            if (choice == 4) break;
            else if (choice == 3) {
                replay();
            } else game_loop(choice + 1);
        }
    }
}
 
int main() {
    srand(time(0));
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    menu();
    endwin();
    return 0;
}
