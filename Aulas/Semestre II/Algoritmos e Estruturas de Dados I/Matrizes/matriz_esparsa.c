#include <stdio.h>
#include <stdlib.h>

#define VALOR_PADRAO 0

typedef struct COL_{
    int valor;
    int n_col;
    struct COL_ *prox;
}COLUNA;

typedef struct{
    int n_linhas;
    int n_colunas;
    COLUNA **linhas;
}MATRIZ_ESPARSA;

void inicializar_matriz(MATRIZ_ESPARSA *matriz, int lin, int col){
    matriz -> n_linhas = lin;
    matriz -> n_colunas = col;
    matriz -> linhas = malloc(lin * sizeof(COLUNA*));

    for (int i = 0; i < lin; i++){
        matriz -> linhas[i] = NULL;
    }
}

int acessar_matriz (MATRIZ_ESPARSA *matriz, int lin, int col){
    if (lin < 1 || lin > matriz -> n_linhas) return -1;

    if (col < 1 || col > matriz -> n_colunas) return -1;

    COLUNA *coluna_atual = matriz -> linhas[lin-1];

    while (coluna_atual != NULL && coluna_atual -> n_col < col){

        coluna_atual = coluna_atual -> prox;
    }

    //coluna_atual = coluna_atual -> prox;

    if (coluna_atual != NULL && coluna_atual -> n_col == col) return coluna_atual -> valor;

    return VALOR_PADRAO;

}

int atribuir_matriz(MATRIZ_ESPARSA *matriz, int lin, int col, int valor){
    if (lin < 1 || lin > matriz -> n_linhas) return -1;

    if (col < 1 || col > matriz -> n_colunas) return -1;

    COLUNA *anterior = NULL;
    COLUNA *coluna_atual = matriz -> linhas[lin-1];

    while (coluna_atual != NULL && coluna_atual -> n_col < col){
        anterior = coluna_atual;
        coluna_atual = coluna_atual -> prox;
    }

    if (coluna_atual == NULL || coluna_atual -> n_col != col){
        if (valor != VALOR_PADRAO){
            COLUNA *nova_coluna = malloc(sizeof(COLUNA));
            if (nova_coluna == NULL) return -1;

            nova_coluna -> n_col = col;
            nova_coluna -> valor = valor;

            if (anterior == NULL){
                matriz -> linhas[lin-1] = nova_coluna;
            }
            else{
                anterior -> prox = nova_coluna;
            }

            nova_coluna -> prox = coluna_atual;
        }
    }

    else{
        if (valor != VALOR_PADRAO){
            coluna_atual -> valor = valor;
        }
        else{
            if (anterior == NULL){
                matriz -> linhas[lin-1] = matriz -> linhas[lin-1] -> prox;
            }
            anterior -> prox = coluna_atual -> prox;
            free(coluna_atual);
        }
    }

    return 1;
}

void exibir(MATRIZ_ESPARSA *matriz){

    for (int i = 1; i <= matriz -> n_linhas; i++){
        for (int j = 1; j <= matriz -> n_colunas; j++){
            printf("%2d ", acessar_matriz(matriz, i, j));
        }
        printf("\n");
    }
}

int main(){

    MATRIZ_ESPARSA *matriz = malloc(sizeof(MATRIZ_ESPARSA));

    inicializar_matriz(matriz, 4, 5);

    for (int i = 1; i <= matriz -> n_linhas; i++){
        for (int j = 1; j <= matriz -> n_colunas; j++){
            atribuir_matriz(matriz, i, j, i*10 + j);
        }
    }

    exibir(matriz);

    return 0;
}