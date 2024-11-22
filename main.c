#include <stdio.h>
#include <stdlib.h>

// Function declarations
void readInput(int n, int m, int prices[], int cost[], int limit[], float proportions[n][m]);
void printTable(int n, int m, int prices[], int cost[], int limit[], float proportions[n][m]);
void generateLpSolveFile(int n, int m, int prices[], int limit[], float proportions[n][m]);

int main() {
    // Read the number of products and compounds
    int n, m;
    scanf("%d %d", &n, &m);

    // Allocate data
    int prices[n];
    int cost[m], limit[m];
    float proportions[n][m];

    // Read input data
    readInput(n, m, prices, cost, limit, proportions);

#ifdef DEBUG
    // Print data in table format
    printTable(n, m, prices, cost, limit, proportions);
#endif

    // Generate the output file in lp_solve format
    generateLpSolveFile(n, m, prices, limit, proportions);

    printf("File 'problema.lp' successfully generated!\n");
    return 0;
}

// Function to read input data
void readInput(int n, int m, int prices[], int cost[], int limit[], float proportions[n][m]) {
    // Read product prices
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    // Read compound costs and limits
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &cost[i], &limit[i]);
    }

    // Read proportions of each compound in products
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%f", &proportions[i][j]);
        }
    }
}

// Function to print data in table format
void printTable(int n, int m, int prices[], int cost[], int limit[], float proportions[n][m]) {
    printf("\t|");
    for (int j = 0; j < m; j++) {
        printf(" compound %d\t|", j + 1);
    }
    printf(" value\t|\n");

    for (int i = 0; i < n; i++) {
        printf("prod %d\t|", i + 1);
        for (int j = 0; j < m; j++) {
            printf("    %.1f\t|", proportions[i][j]);
        }
        printf("    %d\t|\n", prices[i]);
    }

    printf("cost\t|");
    for (int j = 0; j < m; j++) {
        printf("    %d\t\t|", cost[j]);
    }
    printf("\n");

    printf("limit\t|");
    for (int j = 0; j < m; j++) {
        printf("    %d\t|", limit[j]);
    }
    printf("\n");
}

// Function to generate the lp_solve file
void generateLpSolveFile(int n, int m, int prices[], int limit[], float proportions[n][m]) {
    FILE *output = fopen("problema.lp", "w");
    if (output == NULL) {
        printf("Error creating output file.\n");
        exit(1);
    }

    // Write the objective function
    fprintf(output, "max: ");
    for (int i = 0; i < n; i++) {
        fprintf(output, "%d x%d", prices[i], i + 1);
        if (i < n - 1) {
            fprintf(output, " + ");
        }
    }
    fprintf(output, ";\n");

    // Write constraints for compound limits
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            fprintf(output, "%.1f x%d", proportions[i][j], i + 1);
            if (i < n - 1) {
                fprintf(output, " + ");
            }
        }
        fprintf(output, " <= %d;\n", limit[j]);
    }

    // Write non-negativity constraints
    for (int i = 0; i < n; i++) {
        fprintf(output, "x%d >= 0;\n", i + 1);
    }

    fclose(output);
}
