#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define TAM 100

/**************************************/
/*         ESTRUTURAS DO GRAFO        */
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
/*         ESTRUTURA DA FILA          */
/**************************************/

typedef struct {
    int dados[TAM];
    int ini, fim;
} FILA;

void inicializaFila(FILA *f) {
    f->ini = f->fim = 0;
}

bool filaVazia(FILA *f) {
    return f->ini == f->fim;
}

bool entrarFila(FILA *f, int v) {
    if ((f->fim + 1) % TAM == f->ini) return false;
    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % TAM;
    return true;
}

int sairFila(FILA *f) {
    if (filaVazia(f)) return -1;
    int v = f->dados[f->ini];
    f->ini = (f->ini + 1) % TAM;
    return v;
}

/**************************************/
/*         FUNÇÕES DO GRAFO           */
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
/*       CAMINHOS MAIS CURTOS (BFS)   */
/**************************************/

void caminhosMaisCurtos(VERTICE *g, int origem, int *dist) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g);

    for (int i = 1; i <= V; i++)
        dist[i] = -1;

    entrarFila(f, origem);
    g[origem].flag = 1;
    dist[origem] = 0;

    while (!filaVazia(f)) {
        int atual = sairFila(f);
        NO *p = g[atual].inicio;

        while (p) {
            int v = p->adj;

            if (g[v].flag == 0) {
                g[v].flag = 1;
                dist[v] = dist[atual] + 1;
                entrarFila(f, v);
            }

            p = p->prox;
        }
    }

    free(f);
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    VERTICE grafo[V + 1];
    inicializarGrafo(grafo);

    inserirAresta(grafo, 1, 2);
    inserirAresta(grafo, 1, 3);
    inserirAresta(grafo, 2, 4);
    inserirAresta(grafo, 3, 5);
    inserirAresta(grafo, 5, 6);

    int dist[V + 1];
    int origem = 1;

    exibirGrafo(grafo);

    caminhosMaisCurtos(grafo, origem, dist);

    printf("📍 Caminhos mínimos a partir do vértice %d:\n", origem);
    for (int i = 1; i <= V; i++) {
        printf("- Até %d: %d arestas\n", i, dist[i]);
    }

    return 0;
}
