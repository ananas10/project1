#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void randomNumberGenerator(int min, int max);

int main() {
    srand(time(NULL));

    int array[N][N];
    int choice;

    printf("Enter 1 for Random Number Generator\nEnter 2 for Game\n\nSelect one of these two option: \n");
    scanf("%d", &choice);

    if (choice == 1) {
        int min, max;
        printf("Enter the min and max value: ");
        scanf("%d%d", &min, &max);
        randomNumberGenerator(min, max);
    } else if (choice == 2) {
        float index_count = 0;
        float ratio;

        int numberOfPlayer;
        int i, j;

        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                array[i][j] = -1;
            }
        }

        printf("Number of Players: \n");
        scanf("%d", &numberOfPlayer);

        if (numberOfPlayer > N * N) {
            printf("Error: Number of players exceeds grid capacity (%d).\n", N * N);
            return 1;
        }

        int player;
        for (player = 1; player <= numberOfPlayer; player++) {
            int x, y;

            do {
                x = rand() % N;
                y = rand() % N;
                index_count++;
            } while (array[x][y] != -1);

            array[x][y] = player;
        }

        ratio = index_count / (N * N);

        printf("Number of (x,y) index generations: %.0f\n", index_count);
        printf("Ratio: %.4f\n", ratio);

        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf("%2d ", array[i][j]);
            }
            printf("\n");
        }

    } else {
        printf("Wrong choice. Please try again.\n");
        return 0;
    }

    return 0;
}

void randomNumberGenerator(int min, int max) {
    int i;
    for (i = 0; i < 10; i++) {
        printf("%d ", rand() % (max - min + 1) + min);
    }
    printf("\n");
}
