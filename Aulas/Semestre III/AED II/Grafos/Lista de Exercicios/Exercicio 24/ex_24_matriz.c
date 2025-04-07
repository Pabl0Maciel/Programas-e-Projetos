#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define TAM 100

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];  // 1 se há aresta, 0 se não
    int flag[V + 1];           // marcação para BFS
} GRAFO;

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

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

void zerarFlags(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
    }
}

void inserirAresta(GRAFO *g, int i, int j) {
    g->matriz[i][j] = 1;
    g->matriz[j][i] = 1;
}

void exibirMatriz(GRAFO *g) {
    printf("\nMatriz de adjacência:\n    ");
    for (int j = 1; j <= V; j++) printf("%2d ", j);
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
/*       CAMINHOS MAIS CURTOS (BFS)   */
/**************************************/

void caminhosMaisCurtos(GRAFO *g, int origem, int *dist) {
    FILA *f = malloc(sizeof(FILA));
    inicializaFila(f);
    zerarFlags(g);

    for (int i = 1; i <= V; i++)
        dist[i] = -1;

    entrarFila(f, origem);
    g->flag[origem] = 1;
    dist[origem] = 0;

    while (!filaVazia(f)) {
        int atual = sairFila(f);

        for (int j = 1; j <= V; j++) {
            if (g->matriz[atual][j] == 1 && g->flag[j] == 0) {
                g->flag[j] = 1;
                dist[j] = dist[atual] + 1;
                entrarFila(f, j);
            }
        }
    }

    free(f);
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO g;
    inicializarGrafo(&g);

    inserirAresta(&g, 1, 2);
    inserirAresta(&g, 1, 3);
    inserirAresta(&g, 2, 4);
    inserirAresta(&g, 3, 5);
    inserirAresta(&g, 5, 6);

    int dist[V + 1];
    int origem = 1;

    exibirMatriz(&g);

    caminhosMaisCurtos(&g, origem, dist);

    printf("📍 Caminhos mínimos a partir do vértice %d:\n", origem);
    for (int i = 1; i <= V; i++) {
        printf("- Até %d: %d arestas\n", i, dist[i]);
    }

    return 0;
}
