#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int myArray[9][9];
int originalBoard[9][9];

void fillArrayEasy();
void fillArrayMed();
void fillArrayHard();
void displayBoard();
void welcomeScreen();
void gameModeSelection();
void startGame();
void youWon();
void clearScreen();

int isValidMove(int row, int col, int num);
int isBoardFull();
int checkWinCondition();

int main() {
    startGame();
    printf("\nExiting IZTECH Sudoku Game. Goodbye!\n");
    return 0;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void youWon() {
    clearScreen();
    printf("\n\n********************************\n");
    printf("* *\n");
    printf("* CONGRATULATIONS!             *\n");
    printf("* YOU WON!!                    *\n");
    printf("* *\n");
    printf("********************************\n");
    printf("\nPress Enter to return to the main menu...\n");
    getchar();
    getchar();
}

void welcomeScreen() {
    clearScreen();
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 33; j++) {
            if (i == 0) {
                if ((j) % 2 == 0) {
                    printf("*");
                } else {
                    printf("-");
                }
                if (j == 15) {
                    printf("Welcome to IZTECH Sudoku Game");
                }
            } else if (i == 1) {
                printf("\n\t\t1-Start Game\n\t\t2-Load Previous Game\n\t\t3-Quit");
                break;
            }
        }
        if (i == 3) {
            for (j = 0; j < 61; j++) {
                if ((j) % 2 == 0) {
                    printf("*");
                } else {
                    printf("-");
                }
            }
        }
        printf("\n");
    }
}

void gameModeSelection() {
    clearScreen();
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 33; j++) {
            if (i == 0) {
                if ((j) % 2 == 0) {
                    printf("*");
                } else {
                    printf("-");
                }
                if (j == 15) {
                    printf("Game Mode");
                }
            } else if (i == 1) {
                printf("\n\t\t1-Easy\n\t\t2-Medium\n\t\t3-Hard");
                break;
            }
        }
        if (i == 3) {
            for (j = 0; j < 41; j++) {
                if ((j) % 2 == 0) {
                    printf("*");
                } else {
                    printf("-");
                }
            }
        }
        printf("\n");
    }
}

void startGame() {
    int choice;
    char temp_char;
    int difficulty_choice;
    int r, c, val;
    char input_buffer[10];
    int simulate_win;
    int i, j;

    while (1) {
        welcomeScreen();
        printf("Your selection: ");
        scanf("%d", &choice);
        scanf("%c", &temp_char);

        if (choice == 3) {
            return;
        } else if (choice == 1) {
            gameModeSelection();
            printf("Your selection: ");
            scanf("%d", &difficulty_choice);
            scanf("%c", &temp_char);

            switch (difficulty_choice) {
                case 1:
                    fillArrayEasy();
                    break;
                case 2:
                    fillArrayMed();
                    break;
                case 3:
                    fillArrayHard();
                    break;
                default:
                    printf("Invalid difficulty choice. Please try again.\n");
                    printf("\nPress Enter to continue...\n");
                    getchar();
                    continue;
            }

            while (1) {
                clearScreen();
                displayBoard();
                printf("\nEnter your move (Row Col Value, e.g., 1 5 7)\n");
                printf("Enter 'Q' to Quit to main menu, 'S' to Save (not fully implemented): ");

                fgets(input_buffer, sizeof(input_buffer), stdin);

                if (input_buffer[0] == 'Q' || input_buffer[0] == 'q') {
                    printf("Quitting current game to main menu.\n");
                    printf("Press Enter to continue...\n");
                    getchar();
                    break;
                }
                if (input_buffer[0] == 'S' || input_buffer[0] == 's') {
                    printf("Save game feature is not fully implemented yet.\n");
                    printf("Press Enter to continue...\n");
                    getchar();
                    continue;
                }

                if (sscanf(input_buffer, "%d %d %d", &r, &c, &val) != 3) {
                    printf("Invalid input format. Please use 'Row Col Value' (e.g., 1 5 7).\n");
                    printf("Press Enter to continue...\n");
                    getchar();
                    continue;
                }

                r--;
                c--;

                if (r < 0 || r >= 9 || c < 0 || c >= 9 || val < 1 || val > 9) {
                    printf("Invalid input. Row and Column must be 1-9, Value must be 1-9.\n");
                    printf("Press Enter to continue...\n");
                    getchar();
                    continue;
                }

                if (originalBoard[r][c] != 0) {
                    printf("You cannot change the original numbers!\n");
                    printf("Press Enter to continue...\n");
                    getchar();
                    continue;
                }

                if (isValidMove(r, c, val)) {
                    myArray[r][c] = val;

                    if (isBoardFull() && checkWinCondition()) {
                        youWon();
                        break;
                    }
                } else {
                    printf("Invalid move! This number cannot be placed there according to Sudoku rules.\n");
                    printf("Press Enter to continue...\n");
                    getchar();
                }
            }

        } else if (choice == 2) {
            printf("Load game feature not yet implemented.\n");
            printf("Press Enter to continue...\n");
            getchar();
        } else {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
            printf("Press Enter to continue...\n");
            getchar();
        }
    }
}

int isValidMove(int row, int col, int num) {
    int i, j;

    for (j = 0; j < 9; j++) {
        if (myArray[row][j] == num) {
            return 0;
        }
    }

    for (i = 0; i < 9; i++) {
        if (myArray[i][col] == num) {
            return 0;
        }
    }

    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (myArray[startRow + i][startCol + j] == num) {
                return 0;
            }
        }
    }

    return 1;
}

int isBoardFull() {
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (myArray[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int checkWinCondition() {
    int i, j, k;
    int blockRow, blockCol;
    int row_check[10];
    int col_check[10];
    int block_check[10];
    int row_val;
    int col_val;
    int val;

    for (i = 0; i < 9; i++) {
        for(k=0; k<10; k++) { row_check[k]=0; col_check[k]=0; }
        for (j = 0; j < 9; j++) {
            row_val = myArray[i][j];
            if (row_val < 1 || row_val > 9 || row_check[row_val]) return 0;
            row_check[row_val] = 1;

            col_val = myArray[j][i];
            if (col_val < 1 || col_val > 9 || col_check[col_val]) return 0;
            col_check[col_val] = 1;
        }
    }

    for (blockRow = 0; blockRow < 3; blockRow++) {
        for (blockCol = 0; blockCol < 3; blockCol++) {
            for(k=0; k<10; k++) { block_check[k]=0; }
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    val = myArray[blockRow * 3 + i][blockCol * 3 + j];
                    if (val < 1 || val > 9 || block_check[val]) return 0;
                    block_check[val] = 1;
                }
            }
        }
    }

    return 1;
}

void fillArrayEasy() {
    int r, c;
    for(r = 0; r < 9; r++) {
        for(c = 0; c < 9; c++) {
            myArray[r][c] = 0;
            originalBoard[r][c] = 0;
        }
    }

    originalBoard[0][0]=5; originalBoard[0][1]=3; originalBoard[0][4]=7;
    originalBoard[1][0]=6; originalBoard[1][3]=1; originalBoard[1][4]=9; originalBoard[1][5]=5;
    originalBoard[2][1]=9; originalBoard[2][2]=8; originalBoard[2][7]=6;
    originalBoard[3][0]=8; originalBoard[3][4]=6; originalBoard[3][8]=3;
    originalBoard[4][0]=4; originalBoard[4][3]=8; originalBoard[4][5]=3; originalBoard[4][8]=1;
    originalBoard[5][0]=7; originalBoard[5][4]=2; originalBoard[5][8]=6;
    originalBoard[6][1]=6; originalBoard[6][6]=2; originalBoard[6][7]=8;
    originalBoard[7][3]=4; originalBoard[7][4]=1; originalBoard[7][5]=9; originalBoard[7][8]=5;
    originalBoard[8][4]=8; originalBoard[8][7]=7; originalBoard[8][8]=9;

    for(r = 0; r < 9; r++) {
        for(c = 0; c < 9; c++) {
            myArray[r][c] = originalBoard[r][c];
        }
    }
}

void fillArrayMed() {
    int r, c;
    for(r = 0; r < 9; r++) {
        for(c = 0; c < 9; c++) {
            myArray[r][c] = 0;
            originalBoard[r][c] = 0;
        }
    }

    originalBoard[0][1]=2; originalBoard[0][5]=6;
    originalBoard[1][1]=3; originalBoard[1][6]=1; originalBoard[1][7]=7; originalBoard[1][8]=9;
    originalBoard[2][5]=9; originalBoard[2][8]=6;
    originalBoard[3][0]=4; originalBoard[3][2]=5; originalBoard[3][4]=9;
    originalBoard[4][3]=8; originalBoard[4][5]=1;
    originalBoard[5][4]=2; originalBoard[5][6]=4; originalBoard[5][8]=3;
    originalBoard[6][0]=8; originalBoard[6][3]=5;
    originalBoard[7][3]=4; originalBoard[7][4]=1; originalBoard[7][5]=9; originalBoard[7][8]=5;
    originalBoard[8][0]=9; originalBoard[8][1]=5; originalBoard[8][2]=6; originalBoard[8][7]=1;

    for(r = 0; r < 9; r++) {
        for(c = 0; c < 9; c++) {
            myArray[r][c] = originalBoard[r][c];
        }
    }
}

void fillArrayHard() {
    int r, c;
    for(r = 0; r < 9; r++) {
        for(c = 0; c < 9; c++) {
            myArray[r][c] = 0;
            originalBoard[r][c] = 0;
        }
    }

    originalBoard[0][0]=8;
    originalBoard[1][2]=3; originalBoard[1][3]=6;
    originalBoard[2][1]=7; originalBoard[2][4]=9; originalBoard[2][6]=2;
    originalBoard[3][1]=5; originalBoard[3][5]=7;
    originalBoard[4][3]=8; originalBoard[4][5]=5; originalBoard[4][6]=7;
    originalBoard[5][3]=1; originalBoard[5][7]=3;
    originalBoard[6][2]=1; originalBoard[6][7]=6; originalBoard[6][8]=8;
    originalBoard[7][2]=8; originalBoard[7][3]=5; originalBoard[7][7]=1;
    originalBoard[8][1]=9; originalBoard[8][6]=4;

    for(r = 0; r < 9; r++) {
        for(c = 0; c < 9; c++) {
            myArray[r][c] = originalBoard[r][c];
        }
    }
}

void displayBoard() {
    int i, j;
    int row_num = 1;

    printf("\n    1   2   3   4   5   6   7   8   9\n");

    for (i = 0; i < 19; i++) {
        if (i % 2 == 0) {
            printf("  ");
            for (j = 0; j < 37; j++) {
                if (j % 4 == 0) {
                    printf("+");
                } else {
                    if (i % 6 == 0) {
                        printf("=");
                    } else {
                        printf("-");
                    }
                }
            }
            printf("\n");
        } else {
            printf("%d ", row_num++);
            for (j = 0; j < 37; j++) {
                if (j % 4 == 0) {
                    if (j % 12 == 0) {
                        printf("|");
                    } else {
                        printf(":");
                    }
                } else if ((j + 2) % 4 == 0) {
                    int col_idx = (j - 1) / 4;
                    int row_idx = (i - 1) / 2;
                    if (myArray[row_idx][col_idx] == 0) {
                        printf(" ");
                    } else {
                        printf("%d", myArray[row_idx][col_idx]);
                    }
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
}

void readtxtEasy() {
    printf("Reading easy.txt (NOT IMPLEMENTED TO LOAD BOARD)\n");
}

void readtxtMedium() {
    printf("Reading medium.txt (NOT IMPLEMENTED TO LOAD BOARD)\n");
}

void readtxtHard() {
    printf("Reading hard.txt (NOT IMPLEMENTED TO LOAD BOARD)\n");
}

void fillArray() {
}

void difficultylevel() {
    printf("Please enter a difficulty level, 1, 2 or 3:\n");
}
