#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *elementos;
    int linha, coluna;
}MATRIZ;

int posicao_matriz(MATRIZ *matriz, int linha, int coluna){
    if ((linha <= 0 || linha > matriz -> linha) || (coluna <= 0 || coluna > matriz -> coluna)) return -1;
    
    int offset_linha = (matriz -> coluna) * (linha-1);
    int offset_coluna = coluna - 1;

    int pos = offset_linha + offset_coluna;

    return pos;
}

int acessa_matriz(MATRIZ *matriz, int linha, int coluna){
    if ((linha <= 0 || linha > matriz -> linha) || (coluna <= 0 || coluna > matriz -> coluna)) return -1;

    int pos = posicao_matriz(matriz, linha, coluna);

    return matriz -> elementos[pos];
}

void inicializar_matriz(MATRIZ *matriz, int linha, int coluna){
    matriz -> linha = linha;
    matriz -> coluna = coluna;
    matriz -> elementos = malloc(linha * coluna * sizeof(int));
}

int atribuir_matriz (MATRIZ *matriz, int linha, int coluna, int valor){
    if ((linha <= 0 || linha > matriz -> linha) || (coluna <= 0 || coluna > matriz -> coluna)) return -1;

    int pos = posicao_matriz(matriz, linha, coluna);

    matriz -> elementos[pos] = valor;
    
    return 0;
}

void exibir_matriz (MATRIZ *matriz){
    for (int i = 1; i <= matriz -> linha; i++){

        for (int j = 1; j <= matriz -> coluna; j++){
            printf("%4d ", acessa_matriz(matriz, i, j));
        }
        printf("\n");
    }
}

int main(){

    MATRIZ matriz;
    int linha = 3;
    int coluna = 4;

    inicializar_matriz(&matriz, linha, coluna);

    for (int l = 1; l <= linha; l++){
        
        for (int c = 1; c <= coluna; c++){
            atribuir_matriz(&matriz, l, c, random() % 100);
        }
    }
    exibir_matriz(&matriz);

    atribuir_matriz(&matriz, 1, 1, 1234);
	printf("\n");
	atribuir_matriz(&matriz, 3, 4, 4321);
	exibir_matriz(&matriz);

    return 0;
}