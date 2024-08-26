#include <stdio.h>
#include <stdlib.h>

#define N_MAXIMO 64

void imprimeMatriz(int matriz[N_MAXIMO][N_MAXIMO], int N){
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main(int argc, char *argv[]){
    int N = atoi(argv[1]);
    printf("Valor de N: %d\n", N);

    FILE *minha_entrada = fopen(argv[2], "r");

    FILE *minha_saida = fopen(argv[3], "w");

    int matriz[N_MAXIMO][N_MAXIMO];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(minha_entrada, "%d", &matriz[i][j]);
        }
    }
    imprimeMatriz(matriz, N);

    fprintf(minha_saida, "min = %d; pos = (%d, %d)\n", 8, 1, 1);
    fprintf(minha_saida, "max = %d; pos = (%d, %d)\n", 254, 3, 4);

    fclose(minha_entrada);
    return 0;
}