#include <stdio.h>
#include <stdlib.h>
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

void zerarFlags(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        g->flag[i] = 0;
    }
}

/**************************************/
/*     DFS PARA MEDIR MAIOR CICLO     */
/**************************************/

int dfsMaiorCiclo(GRAFO *g, int atual, int pai, int profundidade, int *prof) {
    g->flag[atual] = 1;
    prof[atual] = profundidade;

    int maior = 0;
    for (int j = 1; j <= V; j++) {
        if (g->matriz[atual][j]) {
            if (g->flag[j] == 0) {
                int tam = dfsMaiorCiclo(g, j, atual, profundidade + 1, prof);
                if (tam > maior) maior = tam;
            } else if (j != pai) {
                int tam = abs(prof[atual] - prof[j]) + 1;
                if (tam > maior) maior = tam;
            }
        }
    }

    g->flag[atual] = 2;
    return maior;
}

int comprimentoMaiorCiclo(GRAFO *g) {
    int prof[V + 1];
    zerarFlags(g);
    int maior = 0;

    for (int i = 1; i <= V; i++) {
        if (g->flag[i] == 0) {
            int tam = dfsMaiorCiclo(g, i, -1, 0, prof);
            if (tam > maior) maior = tam;
        }
    }

    return maior;
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO grafo;
    inicializarGrafo(&grafo);

    // Exemplo com ciclos
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);
    inserirAresta(&grafo, 3, 4);
    inserirAresta(&grafo, 4, 5);
    inserirAresta(&grafo, 5, 2); // ciclo 2-3-4-5-2
    inserirAresta(&grafo, 3, 6);
    inserirAresta(&grafo, 6, 7);
    inserirAresta(&grafo, 7, 3); // ciclo 3-6-7-3

    exibirMatriz(&grafo);

    int maior = comprimentoMaiorCiclo(&grafo);
    printf("\nComprimento do maior ciclo: %d\n", maior);  // Esperado: 4

    return 0;
}

