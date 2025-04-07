/**********************************************************************/
/* Enunciado: Escreva um algoritmo para remover todos os laços        */
/*            (arestas que ligam um vértice a ele mesmo) de um grafo.*/
/*            Representação: matriz de adjacência.                    */
/**********************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURA DO GRAFO           */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1]; // índices de 1 até V
} GRAFO;

/*********************************************/
/*       FUNÇÃO PRINCIPAL DO PROBLEMA        */
/*********************************************/

/* Remove todas as arestas (i -> i), ou seja, os laços */
void removeLacos(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->matriz[i][i] = 0;
    }
}

/*********************************************/
/*             FUNÇÕES AUXILIARES            */
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

    /*************** TESTE 1: GRAFO COM 3 LAÇOS ***************/
    inicializar(&grafo);
    inserirAresta(&grafo, 1, 1); // laço
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 3, 3); // laço
    inserirAresta(&grafo, 4, 5);
    inserirAresta(&grafo, 5, 5); // laço

    printf("Teste 1 (com laços):\nAntes:\n");
    exibirGrafo(&grafo);
    removeLacos(&grafo);
    printf("Depois:\n");
    exibirGrafo(&grafo);

    /*************** TESTE 2: SEM NENHUM LAÇO ***************/
    inicializar(&grafo);
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 4, 5);

    printf("\nTeste 2 (sem laços):\nAntes:\n");
    exibirGrafo(&grafo);
    removeLacos(&grafo);
    printf("Depois:\n");
    exibirGrafo(&grafo);

    /*************** TESTE 3: TODOS OS VÉRTICES COM LAÇO ***************/
    inicializar(&grafo);
    for (int i = 1; i <= V; i++) {
        inserirAresta(&grafo, i, i); // todos com laço
    }

    printf("\nTeste 3 (todos com laço):\nAntes:\n");
    exibirGrafo(&grafo);
    removeLacos(&grafo);
    printf("Depois:\n");
    exibirGrafo(&grafo);

    return 0;
}
