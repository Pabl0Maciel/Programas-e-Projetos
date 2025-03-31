/*********************************************************************/
/* Enunciado: Escreva um algoritmo para contar a quantidade de laços */
/*            em um grafo representado por matriz de adjacência.     */
/*********************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURA DO GRAFO           */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1]; // Índices de 1 até V
} GRAFO;

/*********************************************/
/*        FUNÇÃO PRINCIPAL DO PROBLEMA       */
/*********************************************/

/* Conta e imprime a quantidade de laços (i -> i) em um grafo */
void contarLacos(GRAFO *g) {
    int num_lacos = 0;
    for (int i = 1; i <= V; i++) {
        if (g->matriz[i][i] == 1) {
            num_lacos++;
        }
    }
    printf("Quantidade de laços: %d\n", num_lacos);
}

/*********************************************/
/*           FUNÇÕES AUXILIARES              */
/*********************************************/

/* Inicializa a matriz com zeros */
void inicializar(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

/* Insere uma aresta (i -> j), se ainda não existir */
bool inserirAresta(GRAFO *g, int i, int j) {
    if (g->matriz[i][j] == 1) return false; // já existe
    g->matriz[i][j] = 1;
    return true;
}

/* Exibe o grafo no formato de matriz */
void exibirGrafo(GRAFO *g) {
    printf("   ");
    for (int j = 1; j <= V; j++) {
        printf("%d ", j);
    }
    printf("\n");

    for (int i = 1; i <= V; i++) {
        printf("%d: ", i);
        for (int j = 1; j <= V; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

/*********************************************/
/*                  MAIN                     */
/*********************************************/

int main() {
    GRAFO grafo;

    /*************** TESTE 1: SEM LAÇOS ***************/
    inicializar(&grafo);
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 4, 5);
    printf("Teste 1 (sem laços):\n");
    exibirGrafo(&grafo);
    contarLacos(&grafo);

    /*************** TESTE 2: COM 2 LAÇOS ***************/
    inicializar(&grafo);
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 2); // laço
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 4, 4); // laço
    printf("\nTeste 2 (com 2 laços):\n");
    exibirGrafo(&grafo);
    contarLacos(&grafo);

    /*************** TESTE 3: TODOS COM LAÇO ***************/
    inicializar(&grafo);
    for (int i = 1; i <= V; i++) {
        inserirAresta(&grafo, i, i);
    }
    printf("\nTeste 3 (todos com laço):\n");
    exibirGrafo(&grafo);
    contarLacos(&grafo);

    return 0;
}
