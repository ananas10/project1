#include <stdio.h>
#include <math.h>
#define PI 3.14159265

char plotArray[21][41];

float generateSinusWave(float time, float Amplitude, float frequency);
void clearScreen();
void coordinate();
void printScreen();
void plotWaveform(float amplitude, float frequency);


int main(){
    float magnitude, frequency;

    printf("Welcome to Sine Wave Generator on Oscilloscope Screen\n");
    printf("Please enter magnitude (e.g., 1-10 for good visibility): ");
    scanf("%f", &magnitude);
    printf("Please enter frequency (e.g., 0.1 - 2.0 for visible waves): ");
    scanf("%f", &frequency);

    clearScreen();
    coordinate();
    plotWaveform(magnitude, frequency);

    printScreen();

    return 0;
}

float generateSinusWave(float time, float Amplitude, float frequency){
    return Amplitude * sin(2.0 * PI * frequency * (time / 40.0));
}

void clearScreen(){
    int i, j;
    for (i = 0; i < 21; i++){
        for (j = 0; j < 41; j++){
            plotArray[i][j] = ' ';
        }
    }
}

void coordinate(){
    int i, j;
    for (i = 0; i < 21; i++){
        for (j = 0; j < 41; j++){
            if (i == 10) {
                if (j % 5 == 0) {
                    plotArray[i][j] = '+';
                } else {
                    plotArray[i][j] = '-';
                }
            }
            if (j == 20) {
                if (i % 5 == 0) {
                    if (plotArray[i][j] != '+') {
                        plotArray[i][j] = '+';
                    }
                } else {
                    if (plotArray[i][j] != '-') {
                        plotArray[i][j] = '|';
                    }
                }
            }
        }
    }
}

void printScreen(){
    int i, j;
    for (i = 0; i < 21; i++){
        for (j = 0; j < 41; j++){
            printf("%c", plotArray[i][j]);
        }
        printf("\n");
    }
}

void plotWaveform(float amplitude, float frequency) {
    float y_value;
    int screen_y;
    int j;

    for (j = 0; j < 41; j++) {
        y_value = generateSinusWave((float)j, amplitude, frequency);

        float effective_amplitude = fmin(amplitude, 10.0);
        if (effective_amplitude == 0) { // Avoid division by zero if amplitude is 0
            screen_y = 10; // Plot at center if amplitude is zero
        } else {
            screen_y = (int)round(10 - (y_value / effective_amplitude) * 10.0);
        }


        if (screen_y >= 0 && screen_y < 21) {
            plotArray[screen_y][j] = '*';
        }
    }
}
