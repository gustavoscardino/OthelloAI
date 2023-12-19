/*
  Othello - Monte Carlo Method based AI - Hard difficulty

  Works by simulating 'max_simulation' games ahead of the position and giving each
  possible move a score that will determine whats the next move
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define max_simulation 100 /* define how many simulations will be run */

void choosemove(int board[8][8], int color, int* line, int* column);
int canplay(int board[8][8], int color, int l, int c);
void play(int board[8][8], int color, int l, int c);
void print_board(int board[8][8]);

int main() {
    int user_color = 0, program_color = 0, ok = 0, who_play = 0, i, j;
    int board[8][8] = { 0 }, line = 0, column = 0, cont_program = 0, cont_user = 0;

    /* Initial Board */
    board[3][3] = board[4][4] = 1;
    board[3][4] = board[4][3] = -1;

    printf("Type 1 to play as white or -1 to play as black: ");
    scanf("%d", &user_color);

    switch (user_color) {
        case 1:
            printf("You chose white, the program will make the first move.\n");
            program_color = -1;
            print_board(board);
            break;
        case -1:
            printf("You chose black.\n");
            program_color = 1;
            print_board(board);
            break;
        default:
            printf("You did not choose a valid color.\n");
            return 0;
    }

    who_play = user_color + 1;
    while (1) {
        if (!who_play) {
            ok = 0;
            for (i = 0; i < 8; i++)
                for (j = 0; j < 8; j++)
                    if (canplay(board, user_color, i, j)) ok = 1;
            if (ok) {
                printf("Choose your next move by typing the line[0,7] and column[0,7] in which you want to place your disk: ");
                scanf("%d %d", &line, &column);
                if (canplay(board, user_color, line, column)) {
                    play(board, user_color, line, column);
                    who_play = 1;
                    print_board(board);
                }
                else {
                    printf("You made an illegal move, the game has ended.\n");
                    return 0;
                }
            }
            else {
                ok = 0;
                for (i = 0; i < 8; i++)
                    for (j = 0; j < 8; j++)
                        if (canplay(board, program_color, i, j)) ok = 1;
                if (ok) {
                    printf("There aren't valid moves for you, your turn has been skipped.\n");
                    who_play = 1;
                }
                else {
                    printf("There aren't valid moves for any of the players.\n");
                    break;
                }
            }
        }
        if (who_play) {
            ok = 0;
            for (i = 0; i < 8; i++)
                for (j = 0; j < 8; j++)
                    if (canplay(board, program_color, i, j)) ok = 1;
            if (ok) {
                choosemove(board, program_color, &line, &column);
                play(board, program_color, line, column);
                who_play = 0;
                printf("The AI has placed a disk in (%d,%d)\n", line, column);
                print_board(board);
            }
            else {
                ok = 0;
                for (i = 0; i < 8; i++)
                    for (j = 0; j < 8; j++)
                        if (canplay(board, user_color, i, j)) ok = 1;
                if (ok) {
                    printf("The AI didn't have any valid moves, it's your turn again.\n");
                    who_play = 0;
                }
                else {
                    printf("There aren't valid moves for any of the players.\n");
                    break;
                }
            }
        }

    }


    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++) {
            if (board[i][j] == user_color) cont_user++;
            else if (board[i][j] == program_color) cont_program++;
        }
    if (cont_user > cont_program) printf("You won! %dx%d\n", cont_user, cont_program);
    else if (cont_user < cont_program) printf("You lost. %dx%d\n", cont_program, cont_user);
    else if (cont_user == cont_program) printf("Draw! %dx%d\n", cont_program, cont_user);

    return 0;
}

/* Functions */

void choosemove(int board[8][8], int color, int* line, int* column) {
    int move_line[64], move_collumn[64], points_aux[max_simulation] = { 0 }, board_aux[8][8];
    int i, max, j, k = 0, m, n, o, other_color, ok, random, cont_program = 0, move_line_aux[64], move_collumn_aux[64], move_points[64] = { 0 };

    srand(time(NULL));

    if (color == 1) other_color = -1;
    else other_color = 1;

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (canplay(board, color, i, j)) {
                move_line[k] = i;
                move_collumn[k] = j;
                k++;
            }
        }
    }
    for (m = 0; m < k; m++) {
        for (n = 0; n < max_simulation; n++) {
            /* restart  board aux */
            for (i = 0; i < 8; i++)
                for (j = 0; j < 8; j++)
                    board_aux[i][j] = board[i][j];
            play(board_aux, color, move_line[m], move_collumn[m]);
            while (1) {
                ok = 0;
                o = 0;
                for (i = 0; i < 8; i++)
                    for (j = 0; j < 8; j++)
                        if (canplay(board_aux, other_color, i, j)) {
                            ok = 1;
                            move_line_aux[o] = i;
                            move_collumn_aux[o] = j;
                            o++;
                        }
                if (ok) {
                    random = rand() % o;
                    play(board_aux, other_color, move_line_aux[random], move_collumn_aux[random]);
                }
                else {
                    ok = 0;
                    for (i = 0; i < 8; i++)
                        for (j = 0; j < 8; j++)
                            if (canplay(board_aux, color, i, j)) ok = 1;
                    if (!ok) break;
                }
                ok = 0;
                o = 0;
                for (i = 0; i < 8; i++)
                    for (j = 0; j < 8; j++)
                        if (canplay(board_aux, color, i, j)) {
                            ok = 1;
                            move_line_aux[o] = i;
                            move_collumn_aux[o] = j;
                            o++;
                        }
                if (ok) {
                    random = rand() % o;
                    play(board_aux, color, move_line_aux[random], move_collumn_aux[random]);
                }
                else {
                    ok = 0;
                    for (i = 0; i < 8; i++)
                        for (j = 0; j < 8; j++)
                            if (canplay(board_aux, other_color, i, j)) ok = 1;
                    if (!ok) break;
                }
            }
            cont_program = 0;
            for (i = 0; i < 8; i++)
                for (j = 0; j < 8; j++)
                    if (board_aux[i][j] == color) cont_program++;
            points_aux[n] = cont_program;
        }
        for (i = 0; i < max_simulation; i++)
            move_points[m] += points_aux[i];
    }
    max = 0;
    for (i = 0; i < k; i++)
        if (move_points[i] > move_points[max]) max = i;

    *line = move_line[max];
    *column = move_collumn[max];
}

void print_board(int board[8][8]) {
    int i, j;
    printf("\n      [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]\n\n\n");
    for (i = 0; i < 8; i++) {
        printf("[%d]", i);
        for (j = 0; j < 8; j++)
            printf("%5d", board[i][j]);
        printf("\n");
        printf("\n");
    }
    printf("\n");
}

int canplay(int board[8][8], int color, int l, int c) {
    int i, j, other_color;

    if (board[l][c] != 0 || l > 7 || l < 0 || c > 7 || c < 0) return 0;
    if (color == 1) other_color = -1;
    else other_color = 1;
    if (c < 6 && board[l][c + 1] == other_color) {
        for (i = c + 2; i < 8; i++) {
            if (board[l][i] == 0) break;
            if (board[l][i] == color) return 1;
        }
    }
    if (c > 1 && board[l][c - 1] == other_color) {
        for (i = c - 2; i >= 0; i--) {
            if (board[l][i] == 0) break;
            if (board[l][i] == color) return 1;
        }
    }
    if (l < 6 && board[l + 1][c] == other_color) {
        for (i = l + 2; i < 8; i++) {
            if (board[i][c] == 0) break;
            if (board[i][c] == color) return 1;
        }
    }
    if (l > 1 && board[l - 1][c] == other_color) {
        for (i = l - 2; i >= 0; i--) {
            if (board[i][c] == 0) break;
            if (board[i][c] == color) return 1;
        }
    }
    if (l < 6 && c < 6 && board[l + 1][c + 1] == other_color) {
        for (i = l + 2, j = c + 2; i < 8 && j < 8; i++, j++) {
            if (board[i][j] == 0) break;
            if (board[i][j] == color) return 1;
        }
    }
    if (l > 1 && c < 6 && board[l - 1][c + 1] == other_color) {
        for (i = l - 2, j = c + 2; i >= 0 && j < 8; i--, j++) {
            if (board[i][j] == 0) break;
            if (board[i][j] == color) return 1;
        }
    }
    if (l < 6 && c > 1 && board[l + 1][c - 1] == other_color) {
        for (i = l + 2, j = c - 2; i < 8 && j >= 0; i++, j--) {
            if (board[i][j] == 0) break;
            if (board[i][j] == color) return 1;
        }
    }
    if (l > 1 && c > 1 && board[l - 1][c - 1] == other_color) {
        for (i = l - 2, j = c - 2; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 0) break;
            if (board[i][j] == color) return 1;
        }
    }
    return 0;
}

void play(int board[8][8], int color, int l, int c) {
    int i, j, m, n, other_color;

    board[l][c] = color;
    if (color == 1) other_color = -1;
    else other_color = 1;
    if (c < 6 && board[l][c + 1] == other_color) {
        for (i = c + 2; i < 8; i++) {
            if (board[l][i] == 0) break;
            if (board[l][i] == color) {
                for (m = c + 1; m < i; m++) board[l][m] = color;
                break;
            }
        }
    }
    if (c > 1 && board[l][c - 1] == other_color) {
        for (i = c - 2; i >= 0; i--) {
            if (board[l][i] == 0) break;
            if (board[l][i] == color) {
                for (m = c - 1; m > i; m--) board[l][m] = color;
                break;
            }
        }
    }
    if (l < 6 && board[l + 1][c] == other_color) {
        for (i = l + 2; i < 8; i++) {
            if (board[i][c] == 0) break;
            if (board[i][c] == color) {
                for (m = l + 1; m < i; m++) board[m][c] = color;
                break;
            }
        }
    }
    if (l > 1 && board[l - 1][c] == other_color) {
        for (i = l - 2; i >= 0; i--) {
            if (board[i][c] == 0) break;
            if (board[i][c] == color) {
                for (m = l - 1; m > i; m--) board[m][c] = color;
                break;
            }
        }
    }
    if (l < 6 && c < 6 && board[l + 1][c + 1] == other_color) {
        for (i = l + 2, j = c + 2; i < 8 && j < 8; i++, j++) {
            if (board[i][j] == 0) break;
            if (board[i][j] == color) {
                for (m = l + 1, n = c + 1; m < i && n < j; m++, n++) board[m][n] = color;
                break;
            }
        }
    }
    if (l > 1 && c < 6 && board[l - 1][c + 1] == other_color) {
        for (i = l - 2, j = c + 2; i >= 0 && j < 8; i--, j++) {
            if (board[i][j] == 0) break;
            if (board[i][j] == color) {
                for (m = l - 1, n = c + 1; m > i && n < j; m--, n++) board[m][n] = color;
                break;
            }
        }
    }
    if (l < 6 && c > 1 && board[l + 1][c - 1] == other_color) {
        for (i = l + 2, j = c - 2; i < 8 && j >= 0; i++, j--) {
            if (board[i][j] == 0) break;
            if (board[i][j] == color) {
                for (m = l + 1, n = c - 1; m < i && n > j; m++, n--) board[m][n] = color;
                break;
            }
        }
    }
    if (l > 1 && c > 1 && board[l - 1][c - 1] == other_color) {
        for (i = l - 2, j = c - 2; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 0) break;
            if (board[i][j] == color) {
                for (m = l - 1, n = c - 1; m > i && n > j; m--, n--) board[m][n] = color;
                break;
            }
        }
    }
}
