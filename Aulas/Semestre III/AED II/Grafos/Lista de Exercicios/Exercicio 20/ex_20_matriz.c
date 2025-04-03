#include <stdio.h>
#include <stdbool.h>

#define V 4

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
    g->matriz[j][i] = 1;  // grafo não-dirigido
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
/*          FUNCAO DO PROBLEMA        */
/**************************************/

bool ehCompleto(GRAFO *g) {
    for (int i = 1; i <= V; i++) {
        if (g->matriz[i][i] != 0) return false;
    }
    
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            if (i == j) continue;
            if (g->matriz[i][j] != 1) return false;
        }
    }
    return true;
}

/**************************************/
/*                MAIN                */
/**************************************/

int main() {
    GRAFO grafo;

    // Teste 1: grafo completo K4
    printf("==== Teste 1: Grafo completo ====\n");
    inicializarGrafo(&grafo);
    for (int i = 1; i <= V; i++) {
        for (int j = i + 1; j <= V; j++) {
            inserirAresta(&grafo, i, j);
        }
    }
    exibirMatriz(&grafo);
    printf("É completo? %s\n\n", ehCompleto(&grafo) ? "Sim ✅" : "Não ❌");

    // Teste 2: grafo incompleto
    printf("==== Teste 2: Grafo incompleto ====\n");
    inicializarGrafo(&grafo);
    inserirAresta(&grafo, 1, 2);
    inserirAresta(&grafo, 2, 3);  // falta várias conexões
    exibirMatriz(&grafo);
    printf("É completo? %s\n", ehCompleto(&grafo) ? "Sim ✅" : "Não ❌");

    return 0;
}
