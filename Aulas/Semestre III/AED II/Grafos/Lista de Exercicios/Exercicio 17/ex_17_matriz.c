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
/*         FUNÇÕES AUXILIARES         */
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

/**************************************/
/*     DFS PARA VERIFICAR CAMINHO     */
/**************************************/

bool existeCaminho(GRAFO *g, int origem, int destino) {
    g->flag[origem] = 1;

    if (origem == destino) {
        return true;
    }

    for (int j = 1; j <= V; j++) {
        if (g->matriz[origem][j] && g->flag[j] == 0) {
            if (existeCaminho(g, j, destino)) {
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
    GRAFO grafo;
    inicializarGrafo(&grafo);

    // Conectando 1-2-3 e 4-5. Vértices 6 e 7 isolados.
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);
    inserirAresta(&grafo, 4, 5);

    printf("==== Grafo ====\n");
    exibirMatriz(&grafo);

    // Teste 1: existe caminho de 1 a 3
    zerarFlags(&grafo);
    printf("\nExiste caminho entre 1 e 3? %s\n",
        existeCaminho(&grafo, 1, 3) ? "Sim" : "Não");

    // Teste 2: não há caminho entre 1 e 5
    zerarFlags(&grafo);
    printf("Existe caminho entre 1 e 5? %s\n",
        existeCaminho(&grafo, 1, 5) ? "Sim" : "Não");

    // Teste 3: não há caminho entre 1 e 6 (6 é isolado)
    zerarFlags(&grafo);
    printf("Existe caminho entre 1 e 6? %s\n",
        existeCaminho(&grafo, 1, 6) ? "Sim" : "Não");

    return 0;
}
