#include <stdio.h>
#define N 10


void randomNumberGenerator(int min, int max);

int main(){
    int array[N][N];
    int a, j;
    printf("Enter 1 for Random Number Generator\nEnter 2 for Game\n\nSelect one of these two option: \n");
    scanf("%d", &a);

    if(a==1){
        int min, max;
        printf("enter the min and max value: ");
        scanf("%d%d", &min, &max);
        randomNumberGenerator(min, max);
    }

    else if (a==2){
        float index=0;
        float ratio;

        int numberOfPlayer, x, y, i;
            for(i=0; i<N; i++){
                for (j=0; j<N; j++){
                    array[i][j]=-1;

        }
    }

    printf("Number of Player: \n");
    scanf("%d", &numberOfPlayer);

	int player;
     for (player=1; player<=numberOfPlayer; player++) {
        int x, y;

        do {
            x = rand() % N;
            y = rand() % N;
            index++;
        } while (array[x][y] != -1);
        array[x][y] = player;

    }


    ratio=index/(N*N);

    printf("Number of (x,y)index generation: %f\n", index);
    printf("ratio: %f\n", ratio);

    for ( i=0; i<N; i++) {
        for ( j = 0; j <N; j++) {
            printf("%2d ", array[i][j]);
        }
        printf("\n");
    }

}

    else{
        printf("Wrong choose try again");
        return 0;
    }
}


void randomNumberGenerator(int min, int max){

	int i;
    for (i=0; i<10; i++){
        printf("%d ", rand()%  ((max - min + 1) + min))%2;
    }
}
