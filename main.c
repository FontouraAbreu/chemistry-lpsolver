#include <stdio.h>
#include <stdlib.h>

// Function declarations
void readInput(int n, int m, float prices[], float cost[], float limit[], float proportions[n][m]);
void generateLpSolveFile(int n, int m, float prices[], float cost[], float limit[], float proportions[n][m]);

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    float prices[n];
    float cost[m], limit[m];
    float proportions[n][m];

    readInput(n, m, prices, cost, limit, proportions);

    generateLpSolveFile(n, m, prices, cost, limit, proportions);

    printf("File 'problema.lp' successfully generated!\n");
    return 0;
}

// Function to read input data
void readInput(int n, int m, float prices[], float cost[], float limit[], float proportions[n][m]) {
    for (int i = 0; i < n; i++) {
        scanf("%f", &prices[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%f %f", &cost[i], &limit[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%f", &proportions[i][j]);
        }
    }
}

// Function to generate the lp_solve file
void generateLpSolveFile(int n, int m, float prices[], float cost[], float limit[], float proportions[n][m]) {
    FILE *output = fopen("problema.lp", "w");
    if (output == NULL) {
        printf("Error creating output file.\n");
        exit(1);
    }

    // Write the objective function
    fprintf(output, "max: ");
    for (int i = 0; i < n; i++) {
        fprintf(output, "+%.2f*x%d ", prices[i], i);
    }
    for (int j = 0; j < m; j++) {
        fprintf(output, "-%.2f*c%d ", cost[j], j);
    }
    fprintf(output, ";\n");

    // Write the constraints for compound limits
    for (int j = 0; j < m; j++) {
        fprintf(output, "limit_constraint%d: ", j);
        for (int i = 0; i < n; i++) {
            fprintf(output, "+%.2f*x%d ", proportions[i][j], i);
        }
        fprintf(output, "- c%d <= 0;\n", j);
    }

    // Write the constraints for compound limits
    for (int j = 0; j < m; j++) {
        fprintf(output, "c%d <= %.2f;\n", j, limit[j]);
    }

    // Write non-negativity constraints for products
    for (int i = 0; i < n; i++) {
        fprintf(output, "x%d >= 0;\n", i);
    }

    fclose(output);
}
