#include <stdio.h>
#include <stdbool.h>

#define V 7

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];
    int flag[V + 1];
} GRAFO;

/**************************************/
/*         INICIALIZAÇÃO              */
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

/**************************************/
/*         INSERÇÃO E REMOÇÃO         */
/**************************************/

void inserirAresta(GRAFO *g, int i, int j) {
    g->matriz[i][j] = 1;
    g->matriz[j][i] = 1;
}

void removerAresta(GRAFO *g, int i, int j) {
    g->matriz[i][j] = 0;
    g->matriz[j][i] = 0;
}

/**************************************/
/*         EXIBIÇÃO DO GRAFO          */
/**************************************/

void exibirMatriz(GRAFO *g) {
    printf("Matriz de adjacência:\n    ");
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
/*     DFS PARA DETECÇÃO DE CICLO     */
/**************************************/

bool dfsCiclo(GRAFO *g, int atual, int pai, int *u, int *v) {
    g->flag[atual] = 1;

    for (int j = 1; j <= V; j++) {
        if (g->matriz[atual][j]) {
            if (g->flag[j] == 0) {
                if (dfsCiclo(g, j, atual, u, v)) return true;
            } else if (j != pai) {
                *u = atual;
                *v = j;
                return true;
            }
        }
    }

    return false;
}

/**************************************/
/*       REMOVE UM ÚNICO CICLO        */
/**************************************/

bool removeCiclo(GRAFO *g) {
    int u = -1, v = -1;
    zerarFlags(g);

    for (int i = 1; i <= V; i++) {
        if (g->flag[i] == 0) {
            if (dfsCiclo(g, i, -1, &u, &v)) {
                removerAresta(g, u, v);
                printf("Aresta removida: %d - %d\n", u, v);
                return true;
            }
        }
    }
    return false;
}

/**************************************/
/*       REMOVE TODOS OS CICLOS       */
/**************************************/

void removeTodosOsCiclos(GRAFO *g) {
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
    GRAFO grafo;
    inicializarGrafo(&grafo);

    // Grafo com múltiplos ciclos
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 4, 5);
    inserirAresta(&grafo, 5, 2); // ciclo A
    inserirAresta(&grafo, 3, 5); // ciclo B
    inserirAresta(&grafo, 4, 6);
    inserirAresta(&grafo, 6, 7);
    inserirAresta(&grafo, 7, 3); // ciclo C

    printf("ANTES da remoção de ciclos:\n");
    exibirMatriz(&grafo);

    removeTodosOsCiclos(&grafo);

    printf("\nDEPOIS da remoção de ciclos:\n");
    exibirMatriz(&grafo);

    return 0;
}
