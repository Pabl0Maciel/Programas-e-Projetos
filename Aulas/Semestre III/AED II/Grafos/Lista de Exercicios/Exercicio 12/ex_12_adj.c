#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 7

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct no {
    int adj;
    struct no *prox;
} NO;

typedef struct {
    NO *inicio;
    int flag;
} VERTICE;

/**************************************/
/*         FUNÇÕES AUXILIARES         */
/**************************************/

void inicializarGrafo(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
    }
}

void inserirAresta(VERTICE *g, int i, int j) {
    NO *novo1 = malloc(sizeof(NO));
    novo1->adj = j;
    novo1->prox = g[i].inicio;
    g[i].inicio = novo1;

    NO *novo2 = malloc(sizeof(NO));
    novo2->adj = i;
    novo2->prox = g[j].inicio;
    g[j].inicio = novo2;
}

void exibirGrafo(VERTICE *g) {
    printf("Grafo:\n");
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
/*    DETECÇÃO DE CICLO COM DFS       */
/**************************************/

bool dfsCicloNaoDirigido(VERTICE *g, int atual, int pai) {
    g[atual].flag = 1;

    NO *p = g[atual].inicio;
    while (p) {
        if (g[p->adj].flag == 0) {
            if (dfsCicloNaoDirigido(g, p->adj, atual))
                return true;
        } else if (p->adj != pai) {
            return true; // ciclo detectado
        }
        p = p->prox;
    }

    return false;
}

bool temCiclo(VERTICE *g) {
    
    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) {
            if (dfsCicloNaoDirigido(g, i, -1)) {
                return true;
            }
        }
    }
    return false;
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);



    // Grafo com ciclo: estrutura mais complexa
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 4, 6);
    inserirAresta(grafo, 6, 7);
    inserirAresta(grafo, 7, 5);
    inserirAresta(grafo, 5, 3); // esta fecha o ciclo

    exibirGrafo(grafo);

    if (temCiclo(grafo)) {
        printf("\n⚠️  Ciclo detectado no grafo!\n\n");
    } else {
        printf("\n✅ O grafo NÃO possui ciclos.\n");
    }

    // Grafo SEM ciclo (removemos a aresta que fechava o ciclo)
    inicializarGrafo(grafo);

    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 4, 6);
    inserirAresta(grafo, 6, 7);
    inserirAresta(grafo, 7, 5);
    // Aresta 5–3 foi removida (sem ciclo)

    exibirGrafo(grafo);

    if (temCiclo(grafo)) {
        printf("\n⚠️  Ciclo detectado no grafo!\n");
    } else {
        printf("\n✅ O grafo NÃO possui ciclos.\n");
    }


    return 0;
}
