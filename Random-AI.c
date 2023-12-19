/*
  Othello - Random moves AI - Easy difficulty

  Works by choosing a random moves of the ones available.
*/

/* includes & defines*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define empty 0
#define white 1
#define black -1

/* function prototypes */

void print_board(int board[8][8]);
void choosemove(int board[8][8], int colour, int* line, int* column);
int canplay(int board[8][8], int colour, int l, int c);
void play(int board[8][8], int colour, int l, int c);

/* main function */

int main() {
    int board[8][8] = { empty };
    int i, j, colour_user, colour_program, line, column, ok, count_user = 0, count_program = 0;

    board[3][3] = board[4][4] = white; /* starting board */
    board[3][4] = board[4][3] = black; /* starting board */
    printf("Welcome to Othello! Choose your colour (1 for white, -1 for black): ");

    start: /* beggining of the program */

    scanf("%d", &colour_user);
    switch (colour_user) { /* select what happens based on the colour the player picked */
        case 1:
            colour_program = -1;
            printf("You chose white (1), the AI goes first, lets begin!\n");
            print_board(board);
            goto program_turn;
        case -1:
            colour_program = 1;
            printf("You chose black (-1), the first move is yours, lets begin!\n");
            print_board(board);
            goto user_turn;
        default:
            printf("Choose a valid colour to continue.\n");
            goto start;
    }

    user_turn: /* player's turn */

    ok = 0;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            if (canplay(board, colour_user, i, j)) ok = 1; /* verifies if there are valid moves to the user */
    if (ok) { /* if there are valid moves to the user */
        printf("Choose a coordinate by entering a line and a column (from 0 to 7), separated by a space, in which you want to place your disk: ");
        scanf("%d %d", &line, &column);
        if (canplay(board, colour_user, line, column)) { /* verifies if the move is legal, if it's not the game is ended awarding the victory to the AI */
            play(board, colour_user, line, column);
            print_board(board);
            goto program_turn; /* with the player's turn ended, it's the AI's turn*/
        }
        else {
            printf("You made an illegal move, the game has ended.\n");
            for (i = 0; i < 8; i++) /* counts the points to display in the end */
                for (j = 0; j < 8; j++) {
                    if (board[i][j] == colour_user) count_user++;
                    else if (board[i][j] == colour_program) count_program++;
                }
            printf("You lost! (User %dx%d AI).", count_user, count_program);
            return 0;
        }
    }
    else if (!ok) { /* if there aren't valid moves to the user */
        ok = 0;
        for (i = 0; i < 8; i++)
            for (j = 0; j < 8; j++)
                if (canplay(board, colour_program, i, j)) ok = 1; /* verifies if the AI has available moves */
        if (ok) { /* if there are valid moves to the AI */
            printf("There aren't valid moves for you, your turn has been skipped.\n");
            goto program_turn;
        }
        else if (!ok) { /* if there aren't valid moves for the AI as well, the game is ended */
            printf("There aren't valid moves for any of the players.\n");
            goto count;
        }
    }

    program_turn: /* AI's turn */

    choosemove(board, colour_program, &line, &column);
    play(board, colour_program, line, column);
    printf("The AI has placed a disk in (%d, %d)\n", line, column);
    print_board(board);
    goto user_turn;

    count: /* counts the amount of disks of each colour */

    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++) {
            if (board[i][j] == colour_user) count_user++;
            else if (board[i][j] == colour_program) count_program++;
        }
    if (count_user > count_program) {
        printf("You won! (User %dx%d AI).", count_user, count_program);
        return 0;
    }
    else if (count_user < count_program) {
        printf("You lost! (User %dx%d AI).", count_user, count_program);
        return 0;
    }
    else if (count_user == count_program) {
        printf("Draw! (User %dx%d AI).", count_user, count_program);
        return 0;
    }
}

/* function definitions */

void print_board(int board[8][8]) {
    int i, j;

    printf("\n     0  1  2  3  4  5  6  7\n\n");
    for (i = 0; i < 8; i++) {
        printf("%d   ", i);
        for (j = 0; j < 8; j++) {
            if (board[i][j] == -1) printf("%d ", board[i][j]);
            else printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void choosemove(int board[8][8], int colour, int* line, int* column) {
    int k = 0, i, j, random;
    int line_aux[60], column_aux[60];

    srand(time(NULL)); /* generates a random seed to later choose a random move */
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            if (canplay(board, colour, i, j)) { /* places the possible moves in an auxiliary array */
                line_aux[k] = i;
                column_aux[k] = j;
                k++;
            }
    random = rand() % (k); /* generates a random number in the interval of [0,k - 1] */
    *line = line_aux[random]; /* uses the number to return a random move of the ones listed in the array */
    *column = column_aux[random];
    return;
}

int canplay(int board[8][8], int colour, int l, int c) {
    int i, j, colour_opposite;

    if (board[l][c] != empty || l > 7 || l < 0 || c > 7 || c < 0) return 0; /* positions already occupied or out of the board are not valid */
    if (colour == white) colour_opposite = black;
    else colour_opposite = white;
    if (board[l][c + 1] == colour_opposite && c < 6) { /* verifying right */ /* if the square immediate to the right is not of the opposite colour, or if the chosen square is one square before the border it does not make sense to verify the move */
        for (i = c + 2; i < 8; i++) { /* walking searching for a same colour disk so that the move exists */
            if (board[l][i] == empty) break; /* if there's an empty space the move is not valid */
            else if (board[l][i] == colour) return 1;
        }
    }
    if (board[l][c - 1] == colour_opposite && c > 1) { /* verifying left */
        for (i = c - 2; i > -1; i--) {
            if (board[l][i] == empty) break;
            else if (board[l][i] == colour) return 1;
        }
    }
    if (board[l - 1][c] == colour_opposite && l > 1) { /* verifying up */
        for (i = l - 2; i > -1; i--) {
            if (board[i][c] == empty) break;
            else if (board[i][c] == colour) return 1;
        }
    }
    if (board[l + 1][c] == colour_opposite && l < 6) { /* verifying down */
        for (i = l + 2; i < 8; i++) {
            if (board[i][c] == empty) break;
            else if (board[i][c] == colour) return 1;
        }
    }
    if (board[l - 1][c + 1] == colour_opposite && l > 1 && c < 6) { /* verifying upper right diagonal */
        for (i = l - 2, j = c + 2; i > -1 && j < 8; i--, j++) {
            if (board[i][j] == empty) break;
            else if (board[i][j] == colour) return 1;
        }
    }
    if (board[l + 1][c + 1] == colour_opposite && l < 6 && c < 6) { /* verifying lower right diagonal */
        for (i = l + 2, j = c + 2; i < 8 && j < 8; i++, j++) {
            if (board[i][j] == empty) break;
            else if (board[i][j] == colour) return 1;
        }
    }
    if (board[l - 1][c - 1] == colour_opposite && l > 1 && c > 1) { /* verifying upper left diagonal */
        for (i = l - 2, j = c - 2; i > -1 && j > -1; i--, j--) {
            if (board[i][j] == empty) break;
            else if (board[i][j] == colour) return 1;
        }
    }
    if (board[l + 1][c - 1] == colour_opposite && l < 6 && c > 1) { /* verifying lower left diagonal */
        for (i = l + 2, j = c - 2; i < 8 && j > -1; i++, j--) {
            if (board[i][j] == empty) break;
            else if (board[i][j] == colour) return 1;
        }
    }
    return 0;
}

void play(int board[8][8], int colour, int l, int c) {
    int i, j, k, m, colour_opposite;

    if (colour == white) colour_opposite = black;
    else colour_opposite = white;
    if (board[l][c + 1] == colour_opposite && c < 6) { /* verifying right */
        for (i = c + 2; i < 8; i++) {
            if (board[l][i] == empty) break;
            else if (board[l][i] == colour) {
                for (k = c + 1; k < i; k++) board[l][k] = colour; /* works the same way canplay works, but change the disks' colours instead of returning 1 */
                break;
            }
        }
    }
    if (board[l][c - 1] == colour_opposite && c > 1) { /* verifying left */
        for (i = c - 2; i > -1; i--) {
            if (board[l][i] == empty) break;
            else if (board[l][i] == colour) {
                for (k = c - 1; k > i; k--) board[l][k] = colour;
                break;
            }
        }
    }
    if (board[l - 1][c] == colour_opposite && l > 1) { /* verifying up */
        for (i = l - 2; i > -1; i--) {
            if (board[i][c] == empty) break;
            else if (board[i][c] == colour) {
                for (k = l - 1; k > i; k--) board[k][c] = colour;
                break;
            }
        }
    }
    if (board[l + 1][c] == colour_opposite && l < 6) { /* verifying down */
        for (i = l + 2; i < 8; i++) {
            if (board[i][c] == empty) break;
            else if (board[i][c] == colour) {
                for (k = l + 1; k < i; k++) board[k][c] = colour;
                break;
            }
        }
    }
    if (board[l - 1][c + 1] == colour_opposite && l > 1 && c < 6) { /* verifying upper right diagonal */
        for (i = l - 2, j = c + 2; i > -1 && j < 8; i--, j++) {
            if (board[i][j] == empty) break;
            else if (board[i][j] == colour) {
                for (k = l - 1, m = c + 1; k > i && m < j; k--, m++) board[k][m] = colour;
                break;
            }
        }
    }
    if (board[l + 1][c + 1] == colour_opposite && l < 6 && c < 6) { /* verifying lower right diagonal */
        for (i = l + 2, j = c + 2; i < 8 && j < 8; i++, j++) {
            if (board[i][j] == empty) break;
            else if (board[i][j] == colour) {
                for (k = l + 1, m = c + 1; k < i && m < j; k++, m++) board[k][m] = colour;
                break;
            }
        }
    }
    if (board[l - 1][c - 1] == colour_opposite && l > 1 && c > 1) { /* verifying upper left diagonal */
        for (i = l - 2, j = c - 2; i > -1 && j > -1; i--, j--) {
            if (board[i][j] == empty) break;
            else if (board[i][j] == colour) {
                for (k = l - 1, m = c - 1; k > i && m > j; k--, m--) board[k][m] = colour;
                break;
            }
        }
    }
    if (board[l + 1][c - 1] == colour_opposite && l < 6 && c > 1) { /* verifying lower left diagonal */
        for (i = l + 2, j = c - 2; i < 8 && j > -1; i++, j--) {
            if (board[i][j] == empty) break;
            else if (board[i][j] == colour) {
                for (k = l + 1, m = c - 1; k < i && m > j; k++, m--) board[k][m] = colour;
                break;
            }
        }
    }
    board[l][c] = colour;
}
