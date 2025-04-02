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
/*    DFS PARA CAMINHO ENTRE VÉRTICES */
/**************************************/

bool existeCaminho(GRAFO *g, int origem, int destino, int *pos, int *verticesCaminho) {
    g->flag[origem] = 1;

    if (origem == destino) {
        verticesCaminho[(*pos)++] = origem;
        return true;
    }

    for (int j = 1; j <= V; j++) {
        if (g->matriz[origem][j] && g->flag[j] == 0) {
            if (existeCaminho(g, j, destino, pos, verticesCaminho)) {
                verticesCaminho[(*pos)++] = origem;
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

    // Componente: 1-2-3-4-5
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 4, 5);

    // Vértices 6 e 7 isolados

    printf("==== GRAFO ====\n");
    exibirMatriz(&grafo);

    int caminho[V + 1], pos = 0;

    // Teste 1: caminho de 1 até 5
    zerarFlags(&grafo);
    pos = 0;
    if (existeCaminho(&grafo, 1, 5, &pos, caminho)) {
        printf("\nCaminho entre 1 e 5 encontrado: ");
        for (int i = pos - 1; i >= 0; i--) {
            printf("%d ", caminho[i]);
        }
        printf("\n");
    } else {
        printf("\nNão há caminho entre 1 e 5.\n");
    }

    // Teste 2: caminho de 1 até 6 (inexistente)
    zerarFlags(&grafo);
    pos = 0;
    if (existeCaminho(&grafo, 1, 6, &pos, caminho)) {
        printf("\nCaminho entre 1 e 6 encontrado: ");
        for (int i = pos - 1; i >= 0; i--) {
            printf("%d ", caminho[i]);
        }
        printf("\n");
    } else {
        printf("\nNão há caminho entre 1 e 6.\n");
    }

    return 0;
}
