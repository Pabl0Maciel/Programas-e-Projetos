#include <stdio.h>
#include <stdlib.h>

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
/*       DFS PARA ORDEM E GRUPOS      */
/**************************************/

void dfsOrdemConclusao(VERTICE *g, int i, int *ordem, int *pos) {
    g[i].flag = 1;

    NO *p = g[i].inicio;
    while (p) {
        if (g[p->adj].flag == 0) {
            dfsOrdemConclusao(g, p->adj, ordem, pos);
        }
        p = p->prox;
    }

    ordem[(*pos)++] = i;
}

void dfsMarcaGrupo(VERTICE *g, int i) {
    g[i].flag = 1;
    NO *p = g[i].inicio;
    while (p) {
        if (g[p->adj].flag == 0) {
            dfsMarcaGrupo(g, p->adj);
        }
        p = p->prox;
    }
}

/**************************************/
/*     CONTA GRUPOS DISJUNTOS         */
/**************************************/

void numGruposDisjuntos(VERTICE *g) {
    int ordem[V + 1];
    int pos = 0;

    zerarFlags(g);

    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) {
            dfsOrdemConclusao(g, i, ordem, &pos);
        }
    }

    zerarFlags(g);
    int numGrupos = 0;

    for (int i = pos - 1; i >= 0; i--) {
        int v = ordem[i];
        if (g[v].flag == 0) {
            dfsMarcaGrupo(g, v);
            numGrupos++;
        }
    }

    printf("Número de grupos disjuntos: %d\n", numGrupos);
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    // Componente 1: 1-2-3
    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 2, 3);

    // Componente 2: 4-5
    inserirAresta(grafo, 4, 5);

    // Componente 3: 6-7
    inserirAresta(grafo, 6, 7);

    exibirGrafo(grafo);
    numGruposDisjuntos(grafo);  // Esperado: 3

    return 0;
}




