#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int nand(int i1, int i2) {
    if (i1 == 1 && i2 == 1) {
        return 0;
    }
    return 1;
}

int nor(int i1, int i2) {
    if (i1 == 0 && i2 == 0) {
        return 1;
    }
    return 0;
}

void simulate_nand_latch_step(int *Q_current, int *Q_bar_current, int S_bar_input, int R_bar_input) {
    int next_Q = nand(R_bar_input, *Q_bar_current);
    int next_Q_bar = nand(S_bar_input, *Q_current);

    *Q_current = next_Q;
    *Q_bar_current = next_Q_bar;
}

void simulate_nor_latch_step(int *Q_current, int *Q_bar_current, int S_input, int R_input) {
    int next_Q = nor(S_input, *Q_bar_current);
    int next_Q_bar = nor(R_input, *Q_current);

    *Q_current = next_Q;
    *Q_bar_current = next_Q_bar;
}

int main() {
    int Q_state = 0;
    int Q_bar_state = 1;
    int S_input = 0;
    int R_input = 0;
    int select_nand = 1;
    int simulation_steps = 0;
    int prev_Q, prev_Q_bar;
    int max_iterations = 10;
    int stable = 0;
    int i;
    char input_line[20];

    printf("\n--- SR Latch Simulator ---\n");
    printf("Enter 1 to select NAND Latch OR 0 to select NOR Latch: ");
    scanf("%d", &select_nand);

    printf("Enter the initial state of Q (0 or 1): ");
    scanf("%d", &Q_state);
    Q_bar_state = (Q_state == 0) ? 1 : 0;

    printf("\nInitial State: Q = %d, Q' = %d\n", Q_state, Q_bar_state);
    printf("---------------------------\n");
    printf("Enter S and R inputs (-1 to exit).\n");
    printf("For NAND Latch, inputs are active-low (0 to activate).\n");
    printf("For NOR Latch, inputs are active-high (1 to activate).\n");
    printf("---------------------------\n");

    while (getchar() != '\n');

    while (1) {
        printf("\nStep %d: Enter S and R inputs (e.g., 0 1 or 1 0): ", ++simulation_steps);
        if (fgets(input_line, sizeof(input_line), stdin) == NULL) {
            break;
        }

        if (sscanf(input_line, "%d %d", &S_input, &R_input) != 2) {
            printf("Invalid input format. Please enter two numbers.\n");
            simulation_steps--;
            continue;
        }

        if (S_input == -1 || R_input == -1) {
            printf("Exiting simulator.\n");
            break;
        }

        printf("  Simulating state change...\n");
        stable = 0;

        for (i = 0; i < max_iterations; ++i) {
            prev_Q = Q_state;
            prev_Q_bar = Q_bar_state;

            if (select_nand == 1) {
                simulate_nand_latch_step(&Q_state, &Q_bar_state, S_input, R_input);
            } else {
                simulate_nor_latch_step(&Q_state, &Q_bar_state, S_input, R_input);
            }

            printf("    Iteration %d: Q = %d, Q' = %d\n", i + 1, Q_state, Q_bar_state);

            if (Q_state == prev_Q && Q_bar_state == prev_Q_bar) {
                stable = 1;
                break;
            }
        }

        if (stable) {
            printf("  State stabilized.\n");
        } else {
            printf("  State did not stabilize or is oscillating (e.g., forbidden state).\n");
        }

        printf("Final State: Q = %d, Q' = %d\n", Q_state, Q_bar_state);
    }

    return 0;
}
