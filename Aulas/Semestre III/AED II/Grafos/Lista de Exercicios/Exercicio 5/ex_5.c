/**********************************************************************/
/* Enunciado: Escreva um algoritmo que, dado um grafo m representado */
/*            por matriz de adjacência, retorne o mesmo grafo em     */
/*            listas de adjacência.                                   */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURAS DE DADOS          */
/**************************************/

typedef struct s {
    struct s *prox;
    int adj;
} NO;

typedef struct {
    NO *inicio;
    int flag;
    int via;
} VERTICE;

typedef struct {
    int matriz[V + 1][V + 1];
} GRAFO;

/*********************************************/
/*      PROTÓTIPOS DAS FUNÇÕES AUXILIARES    */
/*********************************************/
void inicializarGrafo(VERTICE *g);
bool inserirAresta(VERTICE *g, int i, int j);

/*********************************************/
/*        FUNÇÃO DO PROBLEMA (TOPO)          */
/*********************************************/

/* Converte um grafo em matriz para lista de adjacência */
void matrizParaLista(GRAFO *m, VERTICE *g) {
    inicializarGrafo(g);

    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            if (m->matriz[i][j] != 0) {
                inserirAresta(g, i, j);
            }
        }
    }
}

/*********************************************/
/*       DEFINIÇÃO DAS FUNÇÕES AUXILIARES    */
/*********************************************/


void inicializarMatriz(GRAFO *g) {
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            g->matriz[i][j] = 0;
}

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].via = -1;
    }
}

bool inserirAresta(VERTICE *g, int i, int j) {
    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
    return true;
}

void exibirMatriz(GRAFO *g) {
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

void exibirLista(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        printf("%d: ", i);
        NO *p = g[i].inicio;
        while (p) {
            printf("%d -> ", p->adj);
            p = p->prox;
        }
        printf("NULL\n");
    }
}

/*********************************************/
/*                  MAIN                     */
/*********************************************/

int main() {
    GRAFO matriz;
    VERTICE lista[V + 1];

    inicializarMatriz(&matriz);

    // Criação do grafo em matriz
    matriz.matriz[1][2] = 1;
    matriz.matriz[1][3] = 1;
    matriz.matriz[2][4] = 1;
    matriz.matriz[4][1] = 1;
    matriz.matriz[5][5] = 1; // laço

    printf("Grafo em matriz:\n");
    exibirMatriz(&matriz);

    matrizParaLista(&matriz, lista);

    printf("\nGrafo convertido para lista de adjacência:\n");
    exibirLista(lista);

    return 0;
}
