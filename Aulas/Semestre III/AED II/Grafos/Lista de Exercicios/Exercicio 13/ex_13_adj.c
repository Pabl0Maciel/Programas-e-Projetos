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

void zerarFlags(VERTICE *g) {
    for (int i = 1; i <= V; i++) {
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

bool excluirAresta(VERTICE *g, int i, int j) {
    NO *ant = NULL;
    NO *p = g[i].inicio;
    while (p) {
        if (p->adj == j) {
            if (ant)
                ant->prox = p->prox;
            else
                g[i].inicio = p->prox;
            free(p);
            return true;
        }
        ant = p;
        p = p->prox;
    }
    return false;
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
/*       DFS COM DETECÇÃO DE CICLO    */
/**************************************/

bool dfsCicloNaoDirigido(VERTICE *g, int atual, int pai, int *cicloU, int *cicloV) {
    g[atual].flag = 1;

    NO *p = g[atual].inicio;
    while (p) {
        if (g[p->adj].flag == 0) {
            if (dfsCicloNaoDirigido(g, p->adj, atual, cicloU, cicloV))
                return true;
        } else if (p->adj != pai) {
            *cicloU = atual;
            *cicloV = p->adj;
            return true;
        }
        p = p->prox;
    }

    return false;
}

bool removeCiclo(VERTICE *g) {
    int u = -1, v = -1;
    zerarFlags(g);

    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) {
            if (dfsCicloNaoDirigido(g, i, -1, &u, &v)) {
                excluirAresta(g, u, v);
                excluirAresta(g, v, u);
                printf("Aresta removida: %d - %d\n", u, v);
                return true;
            }
        }
    }
    return false;
}

/**************************************/
/*        REMOVE TODOS OS CICLOS      */
/**************************************/

void removeTodosOsCiclos(VERTICE *g) {
    int removidos = 0;
    while (removeCiclo(g)) {
        removidos++;
    }
    printf("\n✅ Remoção concluída. Total de arestas removidas: %d\n", removidos);
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // Exemplo com múltiplos ciclos
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 3);
    inserirAresta(grafo, 3, 4);
    inserirAresta(grafo, 4, 5);
    inserirAresta(grafo, 5, 2); // ciclo A
    inserirAresta(grafo, 3, 5); // ciclo B
    inserirAresta(grafo, 4, 6);
    inserirAresta(grafo, 6, 7);
    inserirAresta(grafo, 7, 3); // ciclo C

    printf("ANTES da remoção de ciclos:\n");
    exibirGrafo(grafo);

    removeTodosOsCiclos(grafo);

    printf("\nDEPOIS da remoção de ciclos:\n");
    exibirGrafo(grafo);

    return 0;
}
