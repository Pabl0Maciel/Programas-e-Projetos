/************************************************************************************************/
/* Detecta ciclo em um grafo NÃO-DIRIGIDO representado por matriz de adjacência.               */
/* Usa busca em profundidade (DFS) com passagem do vértice pai para evitar falso ciclo.        */
/************************************************************************************************/

#include <stdio.h>
#include <stdbool.h>

#define V 7

/**************************************/
/*         ESTRUTURA DO GRAFO         */
/**************************************/

typedef struct {
    int matriz[V + 1][V + 1];  // matriz[i][j] = 1 se há aresta entre i e j
    int flag[V + 1];           // marcação de visitação
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

void inserirAresta(GRAFO *g, int i, int j) {
    g->matriz[i][j] = 1;
    g->matriz[j][i] = 1;  // grafo não-dirigido
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
/*    DETECÇÃO DE CICLO COM DFS       */
/**************************************/

bool dfsCicloMatriz(GRAFO *g, int atual, int pai) {
    g->flag[atual] = 1;

    for (int j = 1; j <= V; j++) {
        if (g->matriz[atual][j]) {
            if (g->flag[j] == 0) {
                if (dfsCicloMatriz(g, j, atual)) return true;
            } else if (j != pai) {
                return true;  // ciclo detectado
            }
        }
    }

    return false;
}

bool temCiclo(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        if (g->flag[i] == 0) {
            if (dfsCicloMatriz(g, i, -1)) return true;
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

    // Estrutura com ciclo
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 1, 3);
    inserirAresta(&grafo, 2, 4);
    inserirAresta(&grafo, 4, 6);
    inserirAresta(&grafo, 6, 7);
    inserirAresta(&grafo, 7, 5);
    inserirAresta(&grafo, 5, 3); // essa fecha o ciclo

    exibirMatriz(&grafo);

    if (temCiclo(&grafo)) {
        printf("\n⚠️  Ciclo detectado no grafo!\n");
    } else {
        printf("\n✅ O grafo NÃO possui ciclos.\n");
    }

    return 0;
}
