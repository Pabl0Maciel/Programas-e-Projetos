/************************************************************************************************/
/* Enunciado: Seja um grafo não-dirigido e ponderado (com um peso inteiro por aresta).         */
/* Escreva um algoritmo que, dado esse grafo e um custo mínimo `c`, retorne uma cópia contendo */
/* apenas as arestas com custo **maior** do que `c`.                                            */
/************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

/**************************************/
/*       ESTRUTURA DO GRAFO           */
/**************************************/

typedef struct no {
    int adj;
    int custo;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
} VERTICE;

/**************************************/
/*       PROTÓTIPOS DAS FUNÇÕES       */
/**************************************/
void inicializarGrafo(VERTICE *g);
bool inserirAresta(VERTICE *g, int i, int j, int custo);
void exibirGrafo(VERTICE *g);
NO *arestaExiste(VERTICE *g, int i, int j, NO **ant);
void grafoCustoMinimo(VERTICE *g, int *custoMinimo, VERTICE *grafoFiltrado);

/**************************************/
/*       FUNÇÃO PRINCIPAL DO PROBLEMA */
/**************************************/

void grafoCustoMinimo(VERTICE *g, int *custoMinimo, VERTICE *grafoFiltrado) {
    inicializarGrafo(grafoFiltrado);

    for (int i = 1; i <= V; i++) {
        NO *p = g[i].inicio;
        while (p) {
            if ((i < p->adj) && (p->custo > *custoMinimo)) {
                inserirAresta(grafoFiltrado, i, p->adj, p->custo);
                inserirAresta(grafoFiltrado, p->adj, i, p->custo);
            }
            p = p->prox;
        }
    }
}

/**************************************/
/*       FUNÇÕES AUXILIARES           */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
    }
}

NO *arestaExiste(VERTICE *g, int i, int j, NO **ant) {
    *ant = NULL;
    NO *p = g[i].inicio;

    while (p) {
        if (p->adj == j) return p;
        *ant = p;
        p = p->prox;
    }

    return NULL;
}

bool inserirAresta(VERTICE *g, int i, int j, int custo) {
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if (atual) return false; // já existe

    NO *novo = (NO *)malloc(sizeof(NO));
    novo->adj = j;
    novo->custo = custo;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;

    return true;
}

void exibirGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        printf("%d: ", i);
        NO *p = g[i].inicio;
        while (p) {
            printf("%d(%d) -> ", p->adj, p->custo);
            p = p->prox;
        }
        printf("NULL\n");
    }
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    VERTICE filtrado[V + 1];
    int custoMin = 7;

    inicializarGrafo(grafo);

    // Grafo original:
    inserirAresta(grafo, 1, 2, 10);
    inserirAresta(grafo, 2, 1, 10);  // não-dirigido

    inserirAresta(grafo, 1, 3, 5);
    inserirAresta(grafo, 3, 1, 5);

    inserirAresta(grafo, 2, 4, 8);
    inserirAresta(grafo, 4, 2, 8);

    inserirAresta(grafo, 3, 5, 6);
    inserirAresta(grafo, 5, 3, 6);

    printf("Grafo original:\n");
    exibirGrafo(grafo);

    grafoCustoMinimo(grafo, &custoMin, filtrado);

    printf("\nGrafo com arestas de custo > %d:\n", custoMin);
    exibirGrafo(filtrado);

    return 0;
}
