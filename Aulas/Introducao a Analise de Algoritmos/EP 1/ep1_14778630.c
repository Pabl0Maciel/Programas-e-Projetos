#include <stdio.h>
#include <stdlib.h>

// estrutura para armazenar o minimo e maximo
typedef struct{
    int Min;
    int Max;
}MinMax;

// funcao para imprimir a matriz
void imprimeMatriz(int **matriz, int N){
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

MinMax Acha_MinMax(int **matriz, int lin_inicio, int lin_fim, int col_inicio, int col_fim){
    MinMax Resultado, Resultado_Cima, Resultado_Baixo, Mat1, Mat2, Mat3, Mat4;

    // base: um elemento
    if ((lin_inicio == lin_fim) && (col_inicio == col_fim)){
        Resultado.Min = matriz[lin_inicio][col_inicio];
        Resultado.Max = matriz[lin_inicio][col_inicio];
        return Resultado;
    }

    // divide em 4 matrizes
    int lin_meio = (lin_inicio + lin_fim) / 2;
    int col_meio = (col_inicio + col_fim) / 2;

    // calcula os min e max das quatro matrizes
    Mat1 = Acha_MinMax(matriz,lin_inicio, lin_meio, col_inicio, col_meio);
    Mat2 = Acha_MinMax(matriz,lin_inicio, lin_meio, col_meio+1, col_fim);
    Mat3 = Acha_MinMax(matriz,lin_meio+1, lin_fim, col_meio+1, col_fim);
    Mat4 = Acha_MinMax(matriz,lin_meio+1, lin_fim, col_inicio, col_meio);

    // compara minimo e maximo entre mat1 e mat2
    if (Mat1.Min < Mat2.Min){
        Resultado_Cima.Min = Mat1.Min;
    }
    else{
        Resultado_Cima.Min = Mat2.Min;
    }

    if (Mat1.Max > Mat2.Max){
        Resultado_Cima.Max = Mat1.Max;
    }
    else{
        Resultado_Cima.Max = Mat2.Max;
    }

    // compara minimo e maximo entre mat3 e mat4

    if (Mat3.Min < Mat4.Min){
        Resultado_Baixo.Min = Mat3.Min;
    }
    else{
        Resultado_Baixo.Min = Mat4.Min;
    }

    if (Mat3.Max > Mat4.Max){
        Resultado_Baixo.Max = Mat3.Max;
    }
    else{
        Resultado_Baixo.Max = Mat4.Max;
    }

    // compara min e max dos resultados de cima e baixo e fornece o resultado final
    if (Resultado_Cima.Min < Resultado_Baixo.Min){
        Resultado.Min = Resultado_Cima.Min;
    }
    else{
        Resultado.Min = Resultado_Baixo.Min;
    }

    if (Resultado_Cima.Max > Resultado_Baixo.Max){
        Resultado.Max = Resultado_Cima.Max;
    }
    else{
        Resultado.Max = Resultado_Baixo.Max;
    }

    return Resultado;

}

int main(int argc, char *argv[]){
    
    // atribui o valor de N lido
    int N = atoi(argv[1]);
    printf("Valor de N: %d\n", N);

    // abre os arquivos de entrada e saida
    FILE *minha_entrada = fopen(argv[2], "r");

    FILE *minha_saida = fopen(argv[3], "w");

    // alocacao dinamica da matriz
    int **matriz = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matriz[i] = (int *)malloc(N * sizeof(int));
    }

    // copia os numeros da matriz de entrada
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(minha_entrada, "%d", &matriz[i][j]);
        }
    }
    
    // imprime a matriz
    imprimeMatriz(matriz, N);

    MinMax Resultado = Acha_MinMax(matriz, 0, N-1, 0, N-1);
    fprintf(minha_saida, "min = %d\n", Resultado.Min);
    fprintf(minha_saida, "max = %d\n", Resultado.Max);

    fclose(minha_entrada);
    fclose(minha_saida);
    

    return 0;
}