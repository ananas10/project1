#include <stdio.h>

char storePattern(char coordinates[100][100], int lenght);

int main(){
    int lenght,l;
    char coordinates[100][100];


    storePattern(coordinates, lenght);
}




char storePattern(char coordinates[100][100], int lenght){
    scanf("%d", &lenght);
    int i, j, l;

    for( i=0; i<=lenght; i++){
        for(j=0; j<=lenght; j++){
            if(i==0 || j==0 || i-1==lenght || j-1==lenght) {
                coordinates[i][j]='*';
            }
            else if(i==j || lenght==j || i==lenght || lenght-i==j){
                coordinates[l][l]='*';
            }
            else if(i>j-1 && j<lenght/2){
                coordinates[l][l]='1';
            }
            else if (j>i && j<lenght/2){
                coordinates[l][l]='2';
            }
            else if(i>j || lenght-i==j){
                coordinates[l][l]='4';
            }
            else if(j>i ){
                coordinates[l][l]='3';
            }




            printf("%c", coordinates[l][l]);
    }
    printf("\n");
    }


    }

