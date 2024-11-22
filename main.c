#include <stdio.h> 
#include <stdlib.h>

int main() {
    // Read the number of items
    int n, m;
    scanf("%d %d", &n, &m);

    // Read the n prices of the items
    int prices[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]);
    }

    // read cost and limit of the m compounds
    int cost[m], limit[m];
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &cost[i], &limit[i]);
    }

    // read the qnty of each compound for a liter of each product
    float proportions[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%f", &proportions[i][j]);
        }
    }

    #ifdef DEBUG
    // Imprimir os dados em formato de tabela
    printf("\t|");
    for (int j = 0; j < m; j++) {
        printf(" composto %d\t|", j + 1);
    }
    printf(" valor\t|\n");

    for (int i = 0; i < n; i++) {
        printf("prod %d\t|", i + 1);
        for (int j = 0; j < m; j++) {
            printf("    %.1f\t|", proportions[i][j]);
        }
        printf("    %d\t|\n", prices[i]);
    }

    printf("custo\t|");
    for (int j = 0; j < m; j++) {
        printf("    %d\t\t|", cost[j]);
    }
    printf("\n");

    printf("limite\t|");
    for (int j = 0; j < m; j++) {
        printf("    %d\t|", limit[j]);
    }
    printf("\n");
    #endif

     // Abrir um arquivo para saída no formato lp_solve
    FILE *output = fopen("problema.lp", "w");
    if (output == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        return 1;
    }

    // Escrever a função objetivo
    fprintf(output, "max: ");
    for (int i = 0; i < n; i++) {
        fprintf(output, "%d x%d", prices[i], i + 1);
        if (i < n - 1) {
            fprintf(output, " + ");
        }
    }
    fprintf(output, ";\n");

    // Escrever as restrições para os limites de compostos
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            fprintf(output, "%.1f x%d", proportions[i][j], i + 1);
            if (i < n - 1) {
                fprintf(output, " + ");
            }
        }
        fprintf(output, " <= %d;\n", limit[j]);
    }

    // Escrever as variáveis como não-negativas
    for (int i = 0; i < n; i++) {
        fprintf(output, "x%d >= 0;\n", i + 1);
    }

    // Fechar o arquivo
    fclose(output);

    printf("Arquivo 'problema.lp' gerado com sucesso!\n");



    return 0;
}