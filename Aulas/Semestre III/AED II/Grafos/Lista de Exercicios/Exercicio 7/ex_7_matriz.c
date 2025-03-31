/************************************************************************************************/
/* Enunciado: Seja um grafo não-dirigido e ponderado (com um peso inteiro por aresta).         */
/* Escreva um algoritmo que, dado esse grafo e um custo mínimo `c`, retorne uma cópia contendo */
/* apenas as arestas com custo **maior** do que `c`.                                            */
/************************************************************************************************/


#include <stdio.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURA DO GRAFO           */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];  // matriz[i][j] = custo ou 0 se não há aresta
} GRAFO;

/**************************************/
/*       PROTÓTIPOS DAS FUNÇÕES       */
/**************************************/
void inicializarGrafo(GRAFO *g);
void inserirAresta(GRAFO *g, int i, int j, int custo);
void exibirMatriz(GRAFO *g);
void grafoCustoMinimo(GRAFO *g, int custoMin, GRAFO *filtrado);

/**************************************/
/*    FUNÇÃO PRINCIPAL DO PROBLEMA    */
/**************************************/

void grafoCustoMinimo(GRAFO *g, int custoMin, GRAFO *filtrado) {
    inicializarGrafo(filtrado);

    for (int i = 1; i <= V; i++) {
        for (int j = i + 1; j <= V; j++) {
            if (g->matriz[i][j] > custoMin) {
                inserirAresta(filtrado, i, j, g->matriz[i][j]);
            }
        }
    }
}

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            g->matriz[i][j] = 0;
}

void inserirAresta(GRAFO *g, int i, int j, int custo) {
    g->matriz[i][j] = custo;
    g->matriz[j][i] = custo;  // grafo não-dirigido
}

void exibirMatriz(GRAFO *g) {
    printf("   ");
    for (int j = 1; j <= V; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 1; i <= V; i++) {
        printf("%2d: ", i);
        for (int j = 1; j <= V; j++) {
            printf("%2d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO grafo, filtrado;
    int custoMin = 7;

    inicializarGrafo(&grafo);

    // Arestas
    inserirAresta(&grafo, 1, 2, 10);
    inserirAresta(&grafo, 1, 3, 5);
    inserirAresta(&grafo, 2, 4, 8);
    inserirAresta(&grafo, 3, 5, 6);

    printf("Grafo original (matriz):\n");
    exibirMatriz(&grafo);

    grafoCustoMinimo(&grafo, custoMin, &filtrado);

    printf("\nGrafo com arestas de custo > %d:\n", custoMin);
    exibirMatriz(&filtrado);

    return 0;
}
