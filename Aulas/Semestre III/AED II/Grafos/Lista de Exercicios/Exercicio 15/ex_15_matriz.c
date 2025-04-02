#include <stdio.h>
#include <stdlib.h>

#define V 7

typedef struct {
    int matriz[V + 1][V + 1];
    int flag[V + 1];
} GRAFO;

void inicializarGrafo(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
        for (int j = 1; j <= V; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

void inserirAresta(GRAFO *g, int i, int j) {
    g->matriz[i][j] = 1;
    g->matriz[j][i] = 1;
}

void exibirMatriz(GRAFO *g) {
    printf("Matriz de adjacência:\n    ");
    for (int j = 1; j <= V; j++) {
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 1; i <= V; i++) {
        printf("%2d: ", i);
        for (int j = 1; j <= V; j++) {
            printf("%2d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}


void zerarFlags(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
    }
}

void dfs(GRAFO *g, int i) {
    g->flag[i] = 1;
    for (int j = 1; j <= V; j++) {
        if (g->matriz[i][j] && g->flag[j] == 0) {
            dfs(g, j);
        }
    }
}

void numGruposDisjuntos(GRAFO *g) {
    zerarFlags(g);
    int grupos = 0;

    for (int i = 1; i <= V; i++) {
        if (g->flag[i] == 0) {
            dfs(g, i);
            grupos++;
        }
    }

    printf("Número de grupos disjuntos: %d\n", grupos);
}

int main() {
    GRAFO grafo;
    inicializarGrafo(&grafo);

    // Grupo 1: 1-2-3
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);

    // Grupo 2: 4-5
    inserirAresta(&grafo, 4, 5);

    // Grupo 3: 6-7
    inserirAresta(&grafo, 6, 7);

    exibirMatriz(&grafo);
    numGruposDisjuntos(&grafo);  // Esperado: 3

    return 0;
}

