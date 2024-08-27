#include <stdio.h>
#include <stdlib.h>

// estrutura para armazenar o minimo, maximo e suas coordenadas.
typedef struct{
    int Min;
    int Max;
    int LinMin;
    int ColMin;
    int LinMax;
    int ColMax;
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
    MinMax Resultado, Mat1, Mat2, Mat3, Mat4;

    // base: um elemento
    if ((lin_inicio == lin_fim) && (col_inicio == col_fim)){
        Resultado.Min = matriz[lin_inicio][col_inicio];
        Resultado.Max = matriz[lin_inicio][col_inicio];
        Resultado.LinMin = lin_inicio;
        Resultado.ColMin = col_inicio;
        Resultado.LinMax = lin_inicio;
        Resultado.ColMax = col_inicio;
        return Resultado;
    }

    // divide em 4 matrizes
    int lin_meio = (lin_inicio + lin_fim) / 2;
    int col_meio = (col_inicio + col_fim) / 2;

    // calcula os min e max das quatro matrizes
    Mat1 = Acha_MinMax(matriz,lin_inicio, lin_meio, col_inicio, col_meio);
    Mat2 = Acha_MinMax(matriz,lin_inicio, lin_meio, col_meio+1, col_fim);
    Mat3 = Acha_MinMax(matriz,lin_meio+1, lin_fim, col_inicio, col_meio);
    Mat4 = Acha_MinMax(matriz,lin_meio+1, lin_fim, col_meio+1, col_fim);

// compara minimo entre as quatro matrizes e acha o menor deles
    Resultado.Min = Mat1.Min;
    Resultado.LinMin = Mat1.LinMin;
    Resultado.ColMin = Mat1.ColMin;

    if (Mat2.Min < Resultado.Min){
        Resultado.Min = Mat2.Min;
        Resultado.LinMin = Mat2.LinMin;
        Resultado.ColMin = Mat2.ColMin;
    }

    // caso os minimos sejam iguais, verifica quem tem a menor linha e, em caso de empate, ve quem tem a menor coluna
    if (Mat2.Min == Resultado.Min){
        if (Mat2.LinMin < Resultado.LinMin){
            Resultado.LinMin = Mat2.LinMin;
            Resultado.ColMin = Mat2.ColMin;
        }
        if (Mat2.LinMin == Resultado.LinMin){
            if (Mat2.ColMin < Resultado.ColMin){
                Resultado.ColMin = Mat2.ColMin;
            }
        }
    }
    
    if (Mat3.Min < Resultado.Min){
        Resultado.Min = Mat3.Min;
        Resultado.LinMin = Mat3.LinMin;
        Resultado.ColMin = Mat3.ColMin;
    }

    // caso os minimos sejam iguais, verifica quem tem a menor linha e, em caso de empate, ve quem tem a menor coluna
    if (Mat3.Min == Resultado.Min){
        if (Mat3.LinMin < Resultado.LinMin){
            Resultado.LinMin = Mat3.LinMin;
            Resultado.ColMin = Mat3.ColMin;
        }
        if (Mat3.LinMin == Resultado.LinMin){
            if (Mat3.ColMin < Resultado.ColMin){
                Resultado.ColMin = Mat3.ColMin;
            }
        }
    }

    if (Mat4.Min < Resultado.Min){
        Resultado.Min = Mat4.Min;
        Resultado.LinMin = Mat4.LinMin;
        Resultado.ColMin = Mat4.ColMin;
    }
    
    // caso os minimos sejam iguais, verifica quem tem a menor linha e, em caso de empate, ve quem tem a menor coluna
    if (Mat4.Min == Resultado.Min){
        if (Mat4.LinMin < Resultado.LinMin){
            Resultado.LinMin = Mat4.LinMin;
            Resultado.ColMin = Mat4.ColMin;
        }
        if (Mat4.LinMin == Resultado.LinMin){
            if (Mat4.ColMin < Resultado.ColMin){
                Resultado.ColMin = Mat4.ColMin;
            }
        }
    }

// compara o maximo entre as quatro matrizes e acha o menor deles
    Resultado.Max = Mat1.Max;
    Resultado.LinMax = Mat1.LinMax;
    Resultado.ColMax = Mat1.ColMax;

    if (Mat2.Max > Resultado.Max){
        Resultado.Max = Mat2.Max;
        Resultado.LinMax = Mat2.LinMax;
        Resultado.ColMax = Mat2.ColMax;
    }

    // caso os maximos sejam iguais, verifica quem tem a menor linha e, em caso de empate, ve quem tem a menor coluna
    if (Mat2.Max == Resultado.Max){
        if (Mat2.LinMax < Resultado.LinMax){
            Resultado.LinMax = Mat2.LinMax;
            Resultado.ColMax = Mat2.ColMax;
        }
        if (Mat2.LinMax == Resultado.LinMax){
            if (Mat2.ColMax < Resultado.ColMax){
                Resultado.ColMax = Mat2.ColMax;
            }
        }
    }

    if (Mat3.Max > Resultado.Max){
        Resultado.Max = Mat3.Max;
        Resultado.LinMax = Mat3.LinMax;
        Resultado.ColMax = Mat3.ColMax;
    }


    // caso os maximos sejam iguais, verifica quem tem a menor linha e, em caso de empate, ve quem tem a menor coluna
    if (Mat3.Max == Resultado.Max){
        if (Mat3.LinMax < Resultado.LinMax){
            Resultado.LinMax = Mat3.LinMax;
            Resultado.ColMax = Mat3.ColMax;
        }
        if (Mat3.LinMax == Resultado.LinMax){
            if (Mat3.ColMax < Resultado.ColMax){
                Resultado.ColMax = Mat3.ColMax;
            }
        }
    }

    if (Mat4.Max > Resultado.Max){
        Resultado.Max = Mat4.Max;
        Resultado.LinMax = Mat4.LinMax;
        Resultado.ColMax = Mat4.ColMax;
    }
    
    // caso os maximos sejam iguais, verifica quem tem a menor linha e, em caso de empate, ve quem tem a menor coluna
    if (Mat4.Max == Resultado.Max){
        if (Mat4.LinMax < Resultado.LinMax){
            Resultado.LinMax = Mat4.LinMax;
            Resultado.ColMax = Mat4.ColMax;
        }
        if (Mat4.LinMax == Resultado.LinMax){
            if (Mat4.ColMax < Resultado.ColMax){
                Resultado.ColMax = Mat4.ColMax;
            }
        }
    }

    return Resultado;

}

int main(int argc, char *argv[]){
    
    // atribui o valor de N lido
    int N = atoi(argv[1]);
    //printf("Valor de N: %d\n", N);

    // abre os arquivos de entrada e saida
    FILE *minha_entrada = fopen(argv[2], "r");

    FILE *minha_saida = fopen(argv[3], "w");

    // alocacao dinamica da matriz
    int **matriz = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        matriz[i] = (int *)malloc(N * sizeof(int));
    }

    // copia os numeros do arquivo de entrada para a matriz
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(minha_entrada, "%d", &matriz[i][j]);
        }
    }
    
    // imprime a matriz
    //imprimeMatriz(matriz, N);

    // resultado
    MinMax Resultado = Acha_MinMax(matriz, 0, N-1, 0, N-1);
    fprintf(minha_saida, "min = %d; pos = (%d, %d)\n", Resultado.Min, Resultado.LinMin, Resultado.ColMin);
    fprintf(minha_saida, "max = %d; pos = (%d, %d)\n", Resultado.Max, Resultado.LinMax, Resultado.ColMax);

    fclose(minha_entrada);
    fclose(minha_saida);
    

    return 0;
}
