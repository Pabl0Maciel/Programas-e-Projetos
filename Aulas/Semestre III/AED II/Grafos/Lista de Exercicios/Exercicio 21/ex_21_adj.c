#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6  // número de vértices (a-f → 1-6)

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct no {
    int adj;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
} VERTICE;

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
    }
}

bool arestaExiste(VERTICE *g, int i, int j) {
    NO *p = g[i].inicio;
    while (p) {
        if (p->adj == j) return true;
        p = p->prox;
    }
    return false;
}

void inserirAresta(VERTICE *g, int i, int j) {
    if (!arestaExiste(g, i, j)) {
        NO *novo1 = malloc(sizeof(NO));
        novo1->adj = j;
        novo1->prox = g[i].inicio;
        g[i].inicio = novo1;

        NO *novo2 = malloc(sizeof(NO));
        novo2->adj = i;
        novo2->prox = g[j].inicio;
        g[j].inicio = novo2;
    }
}

void exibirGrafo(VERTICE *g) {
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

/**************************************/
/*       GERA O GRAFO COMPLEMENTAR    */
/**************************************/

void grafoComplementar(VERTICE *g, VERTICE *gc) {
    inicializarGrafo(gc);

    for (int i = 1; i <= V; i++) {
        for (int j = i + 1; j <= V; j++) {
            if (!arestaExiste(g, i, j)) {
                inserirAresta(gc, i, j);
            }
        }
    }
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1], complemento[V + 1];
    inicializarGrafo(grafo);
    inicializarGrafo(complemento);

    // Arestas conforme o exemplo da imagem (a-f → 1-6)
    inserirAresta(grafo, 1, 2); // a-b
    inserirAresta(grafo, 1, 6); // a-f
    inserirAresta(grafo, 2, 3); // b-c
    inserirAresta(grafo, 2, 5); // b-e
    inserirAresta(grafo, 2, 6); // b-f
    inserirAresta(grafo, 3, 4); // c-d
    inserirAresta(grafo, 3, 5); // c-e
    inserirAresta(grafo, 4, 5); // d-e

    printf("🔷 Grafo original:\n");
    exibirGrafo(grafo);

    grafoComplementar(grafo, complemento);

    printf("\n🔁 Complemento do grafo:\n");
    exibirGrafo(complemento);

    return 0;
}
