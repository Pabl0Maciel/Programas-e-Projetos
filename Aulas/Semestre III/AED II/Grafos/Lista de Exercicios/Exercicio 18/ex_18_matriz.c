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
/*     DFS CONTANDO TAMANHO DO CAMINHO */
/**************************************/

bool existeCaminho(GRAFO *g, int origem, int destino, int *tamCaminho) {
    g->flag[origem] = 1;

    if (origem == destino) {
        (*tamCaminho)++;
        return true;
    }

    for (int j = 1; j <= V; j++) {
        if (g->matriz[origem][j] && g->flag[j] == 0) {
            if (existeCaminho(g, j, destino, tamCaminho)) {
                (*tamCaminho)++;
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

    // Componente conectado: 1-2-3-4-5
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 4, 5);

    // Vértices 6 e 7 isolados

    printf("==== GRAFO ====\n");
    exibirMatriz(&grafo);

    // Teste 1: caminho entre 1 e 5
    int tam = 0;
    zerarFlags(&grafo);
    if (existeCaminho(&grafo, 1, 5, &tam)) {
        printf("\nCaminho entre 1 e 5 com %d vértices.\n", tam);
    } else {
        printf("\nNão existe caminho entre 1 e 5.\n");
    }

    // Teste 2: caminho entre 1 e 6 (não existe)
    tam = 0;
    zerarFlags(&grafo);
    if (existeCaminho(&grafo, 1, 6, &tam)) {
        printf("Caminho entre 1 e 6 com %d vértices.\n", tam);
    } else {
        printf("Não existe caminho entre 1 e 6.\n");
    }

    return 0;
}
