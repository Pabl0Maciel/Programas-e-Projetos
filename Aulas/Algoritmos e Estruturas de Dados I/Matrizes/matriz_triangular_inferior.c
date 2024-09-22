#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *elementos;
    int ordem;
}MTI;

void inicializa_matriz(MTI *matriz, int n){
    matriz -> ordem = n;

    int num_elementos = (n + n*n) / 2;

    matriz -> elementos = (int*) malloc (num_elementos * sizeof(int));

    for (int i = 0; i < num_elementos; i++){
        matriz -> elementos[i] = 0;
    }
}

int posicao_matriz(int linha, int coluna){
    return ((((linha * linha) - linha) / 2)+ coluna -1);
}

int atribuir_matriz(MTI *matriz, int linha, int coluna, int val){
    if ((linha < 1) || (linha > (matriz -> ordem)) || (coluna < 1) || (coluna > (matriz -> ordem)) || (linha < coluna)) return -1;

    int pos = posicao_matriz(linha, coluna);

    matriz -> elementos[pos] = val;

    return 0;
}

int acessa_matriz(MTI *matriz, int linha, int coluna){
    if ((linha < 1) || (linha > (matriz -> ordem)) || (coluna < 1) || (coluna > (matriz -> ordem))) return -1;

    if (linha < coluna) return 0;

    return matriz -> elementos[posicao_matriz(linha, coluna)];
}

void exibir_matriz (MTI *matriz){
    for (int i = 1; i <= matriz -> ordem; i++){

        for (int j = 1; j <= matriz -> ordem; j++){
            printf("%4d ", acessa_matriz(matriz, i, j));
        }
        printf("\n");
    }
}

int main(){

    MTI matriz;
    int ordem = 3;

    inicializa_matriz(&matriz, ordem);

    for (int l = 1; l <= ordem; l++){
        
        for (int c = 1; c <= ordem; c++){
            atribuir_matriz(&matriz, l, c, random() % 100);
        }
    }
    exibir_matriz(&matriz);

    return 0;
}



